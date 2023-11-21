#ifndef INITERROR_HPP_INCLUDED
#define INITERROR_HPP_INCLUDED

#include <SDL.h>

/** Represents the error thrown if SDL libraries cannot be initialised or the window and renderer cannot be created.
 *
 * \author Luke Sell
 */

struct InitError {

  /** Constructs the error with the error message obtained.
   */

  InitError() : e{SDL_GetError()} {}

  /** The error message obtained.
   */

  const char* e;

};

#endif // INITERROR_HPP_INCLUDED
