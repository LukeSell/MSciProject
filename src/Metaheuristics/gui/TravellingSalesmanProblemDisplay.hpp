#ifndef TRAVELLINGSALESMANPROBLEMDISPLAY_HPP_INCLUDED
#define TRAVELLINGSALESMANPROBLEMDISPLAY_HPP_INCLUDED

#include <SDL.h>
#include <gui/GuiComponent.hpp>
#include <gui/Application.hpp>
#include <opp/TravellingSalesmanProblem.hpp>

namespace gui {

  /** Handles displaying of problem and interaction with the user.
   *
   * \author Luke Sell
   */

  class TravellingSalesmanProblemDisplay : public GuiComponent {

    using Tsp = opp::TravellingSalesmanProblem;

   public:

    TravellingSalesmanProblemDisplay() = default;

    TravellingSalesmanProblemDisplay(const TravellingSalesmanProblemDisplay&) = delete;

    TravellingSalesmanProblemDisplay& operator=(const TravellingSalesmanProblemDisplay&) = delete;

    bool isSelected() const override {
      return false;
    }

    std::function<void()> handleEvent(const SDL_Event* const) const override {
      return []{};
    }

    /** Handles the updating of the display with the most recently found solution.
     */

    void update() override {
      for (const auto& s : Application::getInstance().getResults()) {
        tsp.setOptimal(s);
      }
    }

    /** Renders the problem to the window.
     */

    void render() const override;

    Tsp getTsp() const {
      return tsp;
    }

    /** Assigns a newly generated problem to the display.
     */

    void newTsp() {
      tsp = Tsp{};
    }

   private:

    /** The bounds of the display.
     */

    const SDL_Rect boundingBox = {80, 40, 1000, 1000};

    /** The size to render the cities on the display.
     */

    const int cSz = 10;

    /** The currently assigned problem.
     */

    Tsp tsp;

  };
}

#endif // TRAVELLINGSALESMANPROBLEMDISPLAY_HPP_INCLUDED
