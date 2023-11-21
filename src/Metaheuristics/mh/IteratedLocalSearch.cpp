#include <mh/IteratedLocalSearch.hpp>
#include <gui/Application.hpp>

using mh::IteratedLocalSearch;
using gui::killFlag;
using opp::Solution;

Solution IteratedLocalSearch::perturb(const Solution& s) const {
  auto currentS = s;

  // Apply perturbation
  for (int i = 0; i < prtMax; ++i) {
    currentS = neighbour(currentS);
  }

  return currentS;
}

Solution IteratedLocalSearch::findOptimal() const {
  auto currentS = randomSolution();
  auto homeS = currentS;
  auto optimalS = currentS;

  // Restart loop
  for (int i = 0; i < rstMax && !killFlag; ++i) {

    // Local Search
    for (int j = 0; j < lclMax; ++j) {
      auto testNeighbour = neighbour(currentS);
      if (testNeighbour.cost < currentS.cost) {
        currentS = testNeighbour;
      }
    }

    // Update optimal solution
    if (currentS.cost < optimalS.cost) {
      optimalS = currentS;
    }

    // Update home solution
    if (currentS.cost < homeS.cost) {
      homeS = currentS;
    }

    currentS = perturb(homeS);
  }
  return optimalS;
}
