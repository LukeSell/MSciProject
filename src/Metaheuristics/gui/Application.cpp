#include <gui/Application.hpp>
#include <InitError.hpp>
#include <ratio>
#include <iostream>

using gui::Application;
using Tsp = opp::TravellingSalesmanProblem;
using opp::Solution;

Application::Application() try
:
  logger{"results/"}, window{nullptr, SDL_DestroyWindow},
  renderer{nullptr, SDL_DestroyRenderer}, font{nullptr, TTF_CloseFont},
  running{true} {

  // Create the window
  window.reset(SDL_CreateWindow(
                 "Metaheuristics",
                 SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                 width, height, SDL_WINDOW_FULLSCREEN));
  if (!window) {
    throw InitError{};
  }

  // Create the renderer
  renderer.reset(SDL_CreateRenderer(window.get(), -1, 0));
  if (!renderer) {
    throw InitError{};
  }
  SDL_SetRenderDrawBlendMode(renderer.get(), SDL_BLENDMODE_BLEND); // Enables transparent overlays

  // Open the font
  font.reset(TTF_OpenFont("courbd.ttf", fontSize));

} catch (const InitError& e) {
  std::cerr << "Error while initialising SDL: "
            << e.e
            << std::endl;
  throw;
}

void Application::render() const {

  // Clear the screen
  SDL_SetRenderDrawColor(renderer.get(), 255, 255, 255, 255);
  SDL_RenderClear(renderer.get());
  SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);

  currentScreen->render();

  // Render active sub threads marker
  if (!threads.empty() || !benchmarks.empty()) {
    SDL_SetRenderDrawColor(renderer.get(), 255, 0, 0, 255);
    SDL_Rect boundingBox{1475, 70, 50, 50};
    SDL_RenderFillRect(renderer.get(), &boundingBox);
    SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);
  }

  // Display the screen
  SDL_RenderPresent(renderer.get());

}

void Application::handleEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) { // Handle all events
    switch (event.type) {
      case SDL_QUIT:
        running = false;
        break;
      default:
        currentScreen->handleEvent(&event);
        break;
    }
  }
}

void Application::update() {

  // Handle active sub threads for metaheuristics
  for (auto i = threads.begin(); i != threads.end();) {
    if (i->wait_for(std::chrono::seconds{0}) == std::future_status::ready) {
      results.push_back(i->get());
      i = threads.erase(i);
    } else {
      ++i;
    }
  }

  currentScreen->update();

  // Log results
  for (const auto& s : results) {
    logger.log(s);
  }
  results.clear();

  // Handle active sub threads for benchmarks
  for (auto i = benchmarks.begin(); i != benchmarks.end();) {
    if (i->wait_for(std::chrono::seconds{0}) == std::future_status::ready) {
      i->get();
      i = benchmarks.erase(i);
    } else {
      ++i;
    }
  }
}

void Application::addThread(const std::function<Solution(Tsp tsp)>& f, const Tsp& tsp) {
  threads.push_back(std::async(std::launch::async, f, tsp));
}

void Application::addBenchmark(const std::function<void()>& f) {
  benchmarks.push_back(std::async(std::launch::async, f));
}

void Application::killThreads() {
  killFlag = true;
  for (auto& t : threads) {
    t.get();
  }
  for (auto& t : benchmarks) {
    t.get();
  }
  threads.clear();
  benchmarks.clear();
  killFlag = false;
}

std::atomic<bool> gui::killFlag{false};
