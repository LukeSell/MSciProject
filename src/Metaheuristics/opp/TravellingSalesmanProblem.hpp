#ifndef TRAVELLINGSALESMANPROBLEM_HPP_INCLUDED
#define TRAVELLINGSALESMANPROBLEM_HPP_INCLUDED

#include <utility>
#include <random>
#include <vector>
#include <deque>
#include <SDL.h>
#include <opp/Move.hpp>
#include <opp/Solution.hpp>

namespace opp {

  /** Representation of the Euclidean Travelling Salesman Problem.
   *
   * \author Luke Sell
   */

  class TravellingSalesmanProblem {

   public:

    /** Constructs a randomly generated Euclidean Travelling Salesman Problem.
     */

    TravellingSalesmanProblem();

    /** Generates a move from the neighbourhood of a solution.
     *
     * \param s Is the solution to generate a move for.
     *
     * \return The move generated.
     */

    Move generateMove(const Solution& s) const;

    /** Applies a move to a solution.
     *
     * \param s Is the solution to apply the move to.
     * \param m Is the move to apply.
     *
     * \return The neighbouring solution.
     */

    Solution neighbour(const Solution& s, const Move& m) const;

    /** Generates a random solution to the problem.
     *
     * \return The random solution.
     */

    Solution randomSolution() const;

    /** Selects a solution from the population using Tournament Selection.
     *
     * \param p Is the population to select from.
     *
     * \return The selected solution.
     */

    Solution select(const std::vector<Solution>& p) const;

    /** Applies Uniform Order Based Crossover on parent solutions.
     *
     * \param pA Is the first parent.
     * \param pB Is the second parent.
     *
     * \return The pair of children generated.
     */

    std::pair<Solution, Solution> crossover(const Solution& pA, const Solution& pB) const;

    /** Calculates the cost of a solution.
     *
     * \param s Is the solution to calculate the cost for.
     *
     * \return The cost of the solution.
     */

    int cost(const Solution& s) const;

    Solution getOptimal() const {
      return optimal;
    }

    void setOptimal(const Solution& s) {
      optimal = s;
    }

   private:

    /** Used in Crossover to copy the preserved elements of parents to children and determine the elements to be changed.
     *
     * \param b Is the bit string used to crossover.
     * \param pA Is the first parent.
     * \param pB Is the second parent.
     * \param cA Is the first child.
     * \param cB Is the second child.
     * \param vA Is the first list of elements to be changed.
     * \param vB Is the second list of elements to be changed.
     */

    void copyPreserved(const std::deque<bool>& b,
                       const Solution& pA, const Solution& pB,
                       Solution& cA, Solution& cB,
                       std::deque<City>& vA, std::deque<City>& vB) const;

    /** Used in Crossover to reorder the elements to be changed in respect to their order in the other parent.
     *
     * \param p Is the other parent to be used.
     * \param v Is the list of elements to be changed.
     * \param w Is the reordered list of elements to be changed.
     */

    void reorder(const Solution& p, std::deque<City>& v, std::deque<City>& w) const;

    /** Used in Crossover to copy the changed elements of parents to children after reordering.
     *
     * \param b Is the bit string used to crossover.
     * \param cA Is the first child.
     * \param cB Is the second child.
     * \param wA Is the first reordered list of elements to be changed.
     * \param wB Is the second reordered list of elements to be changed.
     */

    void copyChanged(const std::deque<bool>& b,
                     Solution& cA, Solution& cB,
                     std::deque<City>& wA, std::deque<City>& wB) const;

    /** The bounds of the problem.
     */

    static constexpr SDL_Rect boundingBox = {100, 60, 960, 960};

    /** The size of the problem, that is the number of cities.
     */

    int sz;

    /** The number of participants in a tournament for selection.
     */

    int trmMax;

    /** The random device used to generate a seed for the random number generator.
     */

    static thread_local std::random_device rd;

    /** The random number generator used to generate problems and implement stochastic functionality.
     */

    static thread_local std::mt19937 rng;

    /** The matrix representing distances between cities.
     */

    std::vector<std::vector<int>> distanceMatrix;

    /** The initially generated solution to the problem and its cities.
     */

    Solution optimal;

  };
}

#endif // TRAVELLINGSALESMANPROBLEM_HPP_INCLUDED
