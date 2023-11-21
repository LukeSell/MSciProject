#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED

#include <gui/Screen.hpp>

namespace gui {

  /** Represents the main menu screen and all of its components.
   *
   * \author Luke Sell
   */

  class Menu : public Screen {

   public:

    Menu(const Menu&) = delete;

    Menu& operator=(const Menu&) = delete;

    static Menu& getInstance() {
      static Menu menu;
      return menu;
    }

   private:

    /** Constructs the main menu screen and all of its components.
     */

    Menu();

  };
}

#endif // MENU_HPP_INCLUDED
