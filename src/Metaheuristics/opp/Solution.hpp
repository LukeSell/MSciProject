#ifndef SOLUTION_HPP_INCLUDED
#define SOLUTION_HPP_INCLUDED

#include <vector>
#include <SDL.h>
#include <opp/Move.hpp>

namespace opp {

  /** Represents a city in the Travelling Salesman Problem.
   *
   * \author Luke Sell
   */

  struct City {

    /** The name of the city in the problem.
     */

    Uint32 name;

    /** The location of the city in the problem.
     */

    SDL_Point location;

    bool operator==(const City& a) const {
      return (name == a.name);
    }

  };

  /** Represents a solution to the Travelling Salesman Problem.
   *
   * \author Luke Sell
   */

  struct Solution {

    Solution() = default;

    Solution(const std::vector<City>& o) : order{o} {}

    /** The tour of cities that solves the problem.
     */

    std::vector<City> order;

    /** The move made to obtain this solution.
     */

    Move moveMade;

    /** The cost of the tour that solves the problem.
     */

    int cost;

  };
}

#endif // SOLUTION_HPP_INCLUDED
