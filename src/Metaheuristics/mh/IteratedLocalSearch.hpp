#ifndef ITERATEDLOCALSEARCH_HPP_INCLUDED
#define ITERATEDLOCALSEARCH_HPP_INCLUDED

#include <mh/Metaheuristic.hpp>
#include <opp/TravellingSalesmanProblem.hpp>
#include <opp/Solution.hpp>

namespace mh {

  /** Represents the use of Iterated Local Search to solve a problem.
   *
   * \author Luke Sell
   */

  class IteratedLocalSearch : public Metaheuristic {

    using Tsp = opp::TravellingSalesmanProblem;
    using Solution = opp::Solution;

   public:

    IteratedLocalSearch(const IteratedLocalSearch&) = delete;

    IteratedLocalSearch& operator=(const IteratedLocalSearch&) = delete;

    /** Constructs the Iterated Local Search with the problem to be solved and search parameters.
     *
     * \param t Is the problem to be solved.
     */

    IteratedLocalSearch(const Tsp& t) : Metaheuristic{t}, prtMax{2}, rstMax{300}, lclMax{20000} {}

    /** Perturbs the solution to escape a local optima.
     *
     * \param s Is the solution to perturb.
     *
     * \return The perturbed solution.
     */

    Solution perturb(const Solution& s) const;

    /** Finds a near optimal solution to the problem using Iterated Local Search.
     *
     * \return The optimal solution.
     */

    Solution findOptimal() const override;

   private:

    /** The size of the perturbation to be used.
     */

    const int prtMax;

    /** The number of times the search will be restarted from the home solution.
     */

    const int rstMax;

    /** The number of times to use local search for before restarting.
     */

    const int lclMax;

  };
}

#endif // ITERATEDLOCALSEARCH_HPP_INCLUDED
