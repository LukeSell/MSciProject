#ifndef MEMETICALGORITHM_HPP_INCLUDED
#define MEMETICALGORITHM_HPP_INCLUDED

#include <mh/Metaheuristic.hpp>
#include <opp/TravellingSalesmanProblem.hpp>
#include <opp/Solution.hpp>

namespace mh {

  /** Represents the use of the Memetic Algorithm to solve a problem.
   *
   * \author Luke Sell
   */

  class MemeticAlgorithm : public Metaheuristic {

    using Tsp = opp::TravellingSalesmanProblem;
    using Solution = opp::Solution;

   public:

    MemeticAlgorithm(const MemeticAlgorithm&) = delete;

    MemeticAlgorithm& operator=(const MemeticAlgorithm&) = delete;

    /** Constructs the Memetic Algorithm with the problem to be solved and search parameters.
     *
     * \param t Is the problem to be solved.
     */

    MemeticAlgorithm(const Tsp& t) : Metaheuristic{t}, lclMax{60}, genMax{600}, szp{300} {}

    /** Applies a local search to the solution.
     *
     * \param s Is the solution to apply the local search to.
     *
     * \return The solution found by the local search.
     */

    Solution localSearch(const Solution& s) const;

    /** Finds a near optimal solution to the problem using the Memetic Algorithm.
     *
     * \return The optimal solution.
     */

    Solution findOptimal() const override;

   private:

    /** The number of times to use local search for.
     */

    const int lclMax;

    /** The number of generations to run the Memetic Algorithm for.
     */

    const int genMax;

    /** The size of the population used by the Memetic Algorithm.
     */

    const int szp;

  };
}

#endif // MEMETICALGORITHM_HPP_INCLUDED
