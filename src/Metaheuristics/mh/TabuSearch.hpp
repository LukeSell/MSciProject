#ifndef TABUSEARCH_HPP_INCLUDED
#define TABUSEARCH_HPP_INCLUDED

#include <mh/Metaheuristic.hpp>
#include <list>
#include <opp/Move.hpp>
#include <opp/Solution.hpp>
#include <opp/TravellingSalesmanProblem.hpp>

namespace mh {

  /** Represents the use of Tabu Search to solve a problem.
   *
   * \author Luke Sell
   */

  class TabuSearch : public Metaheuristic {

    using Tsp = opp::TravellingSalesmanProblem;
    using Move = opp::Move;
    using Solution = opp::Solution;

   public:

    TabuSearch(const TabuSearch&) = delete;

    TabuSearch& operator=(const TabuSearch&) = delete;

    /** Constructs the Tabu Search with the problem to be solved and search parameters.
     *
     * \param t Is the problem to be solved.
     */

    TabuSearch(const Tsp& t) : Metaheuristic{t}, lclMax{100000}, nbrMax{40}, tabuMax{10} {}

    /** Generates a move from the neighbourhood of a solution, that is not tabu.
     *
     * \param s Is the solution to generate a move for.
     * \param tabuList Is the list of forbidden moves.
     *
     * \return The generated move.
     */

    Move generateMove(const Solution& s, const std::list<Move>& tabuList) const;

    /** Finds a near optimal solution to the problem using Tabu Search.
     *
     * \return The optimal solution.
     */

    Solution findOptimal() const override;

   private:

    /** The number of times to use local search for.
     */

    const int lclMax;

    /** The number of neighbours to consider when gradient sampling.
     */

    const int nbrMax;

    /** The maximum number of moves that are considered tabu at any one time.
     */

    const Uint32 tabuMax;

  };
}

#endif // TABUSEARCH_HPP_INCLUDED
