#ifndef APPLICATION_HPP_INCLUDED
#define APPLICATION_HPP_INCLUDED

#include <SDL.h>
#include <SDL_ttf.h>
#include <Logger.hpp>
#include <gui/Screen.hpp>
#include <opp/TravellingSalesmanProblem.hpp>
#include <opp/Solution.hpp>
#include <vector>
#include <atomic>
#include <future>
#include <functional>
#include <memory>

namespace gui {

  /** Used to notify active sub threads that they should end.
   */

  extern std::atomic<bool> killFlag;

  /** Handles all parts of running the program.
   *
   * For the current screen, performs actions of rendering, handling events and updating.
   * Also handles sub threads and files.
   *
   * \author Luke Sell
   */

  class Application {

    using Tsp = opp::TravellingSalesmanProblem;
    using Solution = opp::Solution;

   public:

    Application(const Application&) = delete;

    Application& operator=(const Application&) = delete;

    ~Application() {
      killThreads(); // Make sure sub threads are in a destructible state
    }

    static Application& getInstance() {
      static Application app;
      return app;
    }

    /** Renders the current screen.
     */

    void render() const;

    /** Handles all events for the current screen.
     */

    void handleEvents();

    /** Updates the current screen.
     *
     * Also checks if sub threads have returned and logs any results.
     */

    void update();

    /** Launches a new sub thread.
     *
     * \param f Is the function to run.
     * \param tsp Is the problem to be solved.
     */

    void addThread(const std::function<Solution(Tsp tsp)>& f, const Tsp& tsp);

    /** Launches a new sub thread.
     *
     * \param f Is the function to run.
     */

    void addBenchmark(const std::function<void()>& f);

    /** Notifies active sub threads that they should end,
     * waits for them to end and then removes them from the active sub threads.
     */

    void killThreads();

    std::vector<Solution> getResults() const {
      return results;
    }

    SDL_Renderer* getRenderer() const {
      return renderer.get();
    }

    TTF_Font* getFont() const {
      return font.get();
    }

    bool isRunning() const {
      return running;
    }

    void setRunning(const bool r) {
      running = r;
    }

    void setScreen(Screen* const cS) {
      currentScreen = cS;
    }

   private:

    /** Creates the window and renderer and opens necessary files.
     */

    Application();

    /** The width of the window.
     */

    const Uint32 width = 1920;

    /** The height of the window.
     */

    const Uint32 height = 1080;

    /** The size of the font used.
     */

    const Uint32 fontSize = 30;

    /** The active sub threads.
     */

    std::vector<std::future<Solution>> threads;

    /** The active sub threads.
     */

    std::vector<std::future<void>> benchmarks;

    /** The results obtained from running the metaheuristics.
     */

    std::vector<Solution> results;

    /** The logger used to log results.
     */

    Logger logger;

    /** The window that represents what the user sees.
     */

    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window;

    /** The renderer used to render onto the window.
     */

    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer;

    /** The font used for rendering text.
     */

    std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> font;

    /** The status of the application.
     */

    bool running;

    /** The currently active screen.
     */

    Screen* currentScreen;

  };
}

#endif // APPLICATION_HPP_INCLUDED
