#ifndef SCREEN_HPP_INCLUDED
#define SCREEN_HPP_INCLUDED

#include <vector>
#include <initializer_list>
#include <memory>
#include <gui/GuiComponent.hpp>
#include <SDL.h>

namespace gui {

  /** Represents a screen and its components that the user can interact with.
   *
   * \author Luke Sell
   */

  class Screen {

   public:

    Screen(const Screen&) = delete;

    Screen& operator=(const Screen&) = delete;

    virtual ~Screen() {}

    /** Renders all components that are part of the screen onto the window.
     */

    void render() const;

    /** Handles events for all components that are part of the screen.
     *
     * \param event Is the event to be considered.
     */

    void handleEvent(const SDL_Event* const event) const;

    /** Updates all components that are part of the screen.
     */

    void update();

   protected:

    Screen() : components{} {}

    /** Adds components to the screen.
     *
     * \param cs Is the list of components to add.
     */

    void addComponents(const std::initializer_list<GuiComponent*>& cs);

   private:

    /** The list of all components that are part of the screen.
     */

    std::vector<std::unique_ptr<GuiComponent>> components;

  };
}

#endif // SCREEN_HPP_INCLUDED
