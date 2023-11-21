#include <iostream>
#include <cstdlib>
#include <SDL.h>
#include <SDL_ttf.h>
#include <InitError.hpp>
#include <gui/Application.hpp>
#include <gui/Menu.hpp>

int main(int, char**) try {
  constexpr Uint32 FPS = 30;
  constexpr Uint32 DELAY = 1000 / FPS;
  std::ios_base::sync_with_stdio(false);

  // Initialise libraries
  if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO)) {
    throw InitError{};
  } else if (TTF_Init()) {
    throw InitError{};
  }
  atexit(&SDL_Quit);
  atexit(&TTF_Quit);

  auto& app = gui::Application::getInstance();
  app.setScreen(&gui::Menu::getInstance());

  // Application loop
  while (app.isRunning()) {
    auto frameTime = SDL_GetTicks();
    app.handleEvents();
    app.update();
    app.render();
    frameTime = SDL_GetTicks() - frameTime;
    if (frameTime < DELAY) {
      SDL_Delay(DELAY - frameTime);
    }
  }

  return 0;
} catch (const InitError& e) {
  std::cerr << "Error while initialising SDL: "
            << e.e
            << std::endl;
  throw;
} catch (...) {
  std::cerr << "An unknown error forced the application to close."
            << std::endl;
  return 1;
}
