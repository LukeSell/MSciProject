#ifndef MOVE_HPP_INCLUDED
#define MOVE_HPP_INCLUDED

#include <cstdint>

namespace opp {

  /** Represents a move, that is a transposition of two cities in a path.
   *
   * \author Luke Sell
   */

  struct Move {

    /** The left city in the move.
     */

    uint32_t cityA;

    /** The position of the left city in the path.
     */

    int indexA;

    /** The right city in the move.
     */

    uint32_t cityB;

    /** The position of the right city in the path.
     */

    int indexB;

    bool operator==(const Move& a) const {
      return (cityA == a.cityA
              && indexA == a.indexA
              && cityB == a.cityB
              && indexB == a.indexB);
    }

  };
}

#endif // MOVE_HPP_INCLUDED
