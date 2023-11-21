#include <mh/TabuSearch.hpp>
#include <algorithm>
#include <gui/Application.hpp>

using mh::TabuSearch;
using opp::Move;
using opp::Solution;
using gui::killFlag;

Move TabuSearch::generateMove(const Solution& s, const std::list<Move>& tabuList) const {
  Move m;

  // Generate Allowed move
  do {
    m = Metaheuristic::generateMove(s);
  } while (std::find(tabuList.begin(), tabuList.end(), m) != tabuList.end());

  return m;
}

Solution TabuSearch::findOptimal() const {
  auto currentS = randomSolution();
  auto optimalS = currentS;
  std::list<Move> tabuList = {};

  // Main loop
  for (int i = 0; i < lclMax && !killFlag; ++i) {
    auto bestNeighbour = neighbour(currentS, generateMove(currentS, tabuList));

    // Sampling gradient to find nearly best neighbour
    for (int j = 0; j < nbrMax; ++j) {
      auto testNeighbour = neighbour(currentS, generateMove(currentS, tabuList));
      if (testNeighbour.cost < bestNeighbour.cost) {
        bestNeighbour = testNeighbour;
      }
    }
    currentS = bestNeighbour;

    // Update Tabu moves
    tabuList.push_back(currentS.moveMade);
    if (tabuList.size() > tabuMax) {
      tabuList.pop_front();
    }

    // Update optimal solution
    if (currentS.cost < optimalS.cost) {
      optimalS = currentS;
    }
  }
  return optimalS;
}
