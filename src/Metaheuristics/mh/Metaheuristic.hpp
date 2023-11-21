#ifndef METAHEURISTIC_HPP_INCLUDED
#define METAHEURISTIC_HPP_INCLUDED

#include <vector>
#include <utility>
#include <opp/Move.hpp>
#include <opp/Solution.hpp>
#include <opp/TravellingSalesmanProblem.hpp>

namespace mh {

  /** Represents a metaheuristic used to solve a problem.
   *
   * \author Luke Sell
   */

  class Metaheuristic {

    using Tsp = opp::TravellingSalesmanProblem;
    using Solution = opp::Solution;
    using Move = opp::Move;

   public:

    Metaheuristic(const Metaheuristic&) = delete;

    Metaheuristic& operator=(const Metaheuristic&) = delete;

    virtual ~Metaheuristic() {}

    /** Finds a near optimal solution to the problem using a metaheuristic.
     *
     * \return The optimal solution.
     */

    virtual Solution findOptimal() const = 0;

   protected:

    /** Constructs a metaheuristic with the problem to be solved.
     *
     * \param t Is the problem to be solved.
     */

    Metaheuristic(const Tsp& t) : tsp{t} {}

    /** Generates a move from the neighbourhood of a solution.
     *
     * \param s Is the solution to generate a move for.
     *
     * \return The move generated.
     */

    Move generateMove(const Solution& s) const {
      return tsp.generateMove(s);
    }

    /** Applies a move to a solution.
     *
     * \param s Is the solution to apply the move to.
     *
     * \return The neighbouring solution.
     */

    Solution neighbour(const Solution& s) const {
      return tsp.neighbour(s, tsp.generateMove(s));
    }

    /** Applies a move to a solution.
     *
     * \param s Is the solution to apply the move to.
     * \param m Is the move to apply.
     *
     * \return The neighbouring solution.
     */

    Solution neighbour(const Solution& s, const Move& m) const {
      return tsp.neighbour(s, m);
    }

    /** Generates a random solution to the problem.
     *
     * \return The random solution.
     */

    Solution randomSolution() const {
      return tsp.randomSolution();
    }

    /** Applies Uniform Order Based Crossover on parent solutions.
     *
     * \param p Is the population used.
     *
     * \return The pair of children generated.
     */

    std::pair<Solution, Solution> crossover(const std::vector<Solution>& p) const {
      return tsp.crossover(tsp.select(p), tsp.select(p));
    }

   private:

    /** The problem to be solved by a metaheuristic.
     */

    Tsp tsp;

  };
}

#endif // METAHEURISTIC_HPP_INCLUDED
