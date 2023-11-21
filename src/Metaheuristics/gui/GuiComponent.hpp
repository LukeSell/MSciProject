#ifndef GUICOMPONENT_HPP_INCLUDED
#define GUICOMPONENT_HPP_INCLUDED

#include <SDL.h>
#include <functional>

namespace gui {

  /** Represents a component of the GUI.
   *
   * \author Luke Sell
   */

  class GuiComponent {

   public:

    virtual ~GuiComponent() {}

    /** Determines if the component is selected by the user.
     *
     * \return The selection status.
     */

    virtual bool isSelected() const = 0;

    /** Determines the action to be taken.
     *
     * \param event Is the event to be considered.
     *
     * \return The action to be taken.
     */

    virtual std::function<void()> handleEvent(const SDL_Event* const event) const = 0;

    /** Updates the component.
     */

    virtual void update() = 0;

    /** Renders the component onto the window.
     */

    virtual void render() const = 0;

  };
}

#endif // GUICOMPONENT_HPP_INCLUDED
