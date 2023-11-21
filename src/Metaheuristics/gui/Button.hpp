#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include <SDL.h>
#include <functional>
#include <memory>
#include <gui/GuiComponent.hpp>

namespace gui {

  /** Represents part of the GUI that can be displayed and clicked on.
   *
   * Allows the user to use the application and its functionality.
   *
   * \author Luke Sell
   */

  class Button : public GuiComponent {

   public:

    Button(const Button&) = delete;

    Button& operator=(const Button&) = delete;

    /** Constructs a button, with all necessary textures generated.
     *
     * \param x Is the x position to render the button on the window.
     * \param y Is the y position to render the button on the window.
     * \param a Is the action the button performs when clicked on.
     * \param t Is the text the button displays.
     */

    Button(const int x, const int y, const std::function<void()>& a, const char* t);

    /** Determines if the mouse position is within the bounds of the button.
     *
     * \return The selection status.
     */

    bool isSelected() const override;

    /** Determines the action to be performed.
     *
     * \param event Is the user event to be considered.
     *
     * \return The action to be performed by the application.
     */

    std::function<void()> handleEvent(const SDL_Event* const event) const override;

    void update() override {}

    /** Renders the button onto the window.
     */

    void render() const override;

   private:

    /** The width of the button.
     */

    const int w = 400;

    /** The height of the button.
     */

    const int h = 100;

    /** The bounds of the button.
     */

    SDL_Rect boundingBox;

    /** The bounds of the buttons text.
     */

    SDL_Rect centreBoundingBox;

    /** The action this button performs.
     */

    std::function<void()> action;

    /** The graphical representation of the text.
     */

    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> text;

    /** The graphical representation of the button.
     */

    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> box;

  };
}

#endif // BUTTON_HPP_INCLUDED
