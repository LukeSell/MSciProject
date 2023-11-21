#ifndef GENETICALGORITHM_HPP_INCLUDED
#define GENETICALGORITHM_HPP_INCLUDED

#include <mh/Metaheuristic.hpp>
#include <opp/TravellingSalesmanProblem.hpp>
#include <opp/Solution.hpp>

namespace mh {

  /** Represents the use of the Genetic Algorithm to solve a problem.
   *
   * \author Luke Sell
   */

  class GeneticAlgorithm : public Metaheuristic {

    using Tsp = opp::TravellingSalesmanProblem;
    using Solution = opp::Solution;

   public:

    GeneticAlgorithm(const GeneticAlgorithm&) = delete;

    GeneticAlgorithm& operator=(const GeneticAlgorithm&) = delete;

    /** Constructs the Genetic Algorithm with the problem to be solved and search parameters.
     *
     * \param t Is the problem to be solved.
     */

    GeneticAlgorithm(const Tsp& t) : Metaheuristic{t}, genMax{600}, szp{300} {}

    /** Finds a near optimal solution to the problem using the Genetic Algorithm.
     *
     * \return The optimal solution.
     */

    Solution findOptimal() const override;

   private:

    /** The number of generations to run the Genetic Algorithm for.
     */

    const int genMax;

    /** The size of the population used by the Genetic Algorithm.
     */

    const int szp;

  };
}

#endif // GENETICALGORITHM_HPP_INCLUDED
