#include <mh/GeneticAlgorithm.hpp>
#include <vector>
#include <gui/Application.hpp>

using mh::GeneticAlgorithm;
using opp::Solution;
using gui::killFlag;

Solution GeneticAlgorithm::findOptimal() const {

  // Generate population
  std::vector<Solution> currentP(szp);
  for (auto& s : currentP) {
    s = randomSolution();
  }
  auto optimalS = currentP[0];

  // Generation loop
  for (int i = 0; i < genMax && !killFlag; ++i) {

    // Update optimal solution
    for (const auto& s : currentP) {
      if (s.cost < optimalS.cost) {
        optimalS = s;
      }
    }

    // Generate next generation
    std::vector<Solution> nextP = {};
    for (Uint32 j = 0; j < currentP.size() / 2; ++j) {
      auto cAB = crossover(currentP);
      nextP.push_back(neighbour(cAB.first));
      nextP.push_back(neighbour(cAB.second));
    }
    currentP = nextP;
  }
  return optimalS;
}
