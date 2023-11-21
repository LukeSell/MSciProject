#include <gui/Button.hpp>
#include <SDL_ttf.h>
#include <gui/Application.hpp>

using gui::Button;

Button::Button(const int x, const int y, const std::function<void()>& a, const char* t)
  : boundingBox{x, y, w, h}, action{a},
    text{nullptr, SDL_DestroyTexture}, box{nullptr, SDL_DestroyTexture} {
  auto renderer = Application::getInstance().getRenderer();

  // Generate graphical representation of text
  auto surface = TTF_RenderText_Blended(Application::getInstance().getFont(), t, {0, 0, 0, 255});
  text.reset(SDL_CreateTextureFromSurface(renderer, surface));
  centreBoundingBox.x = boundingBox.x + ((boundingBox.w - surface->w) / 2);
  centreBoundingBox.y = boundingBox.y + ((boundingBox.h - surface->h) / 2);
  centreBoundingBox.w = surface->w;
  centreBoundingBox.h = surface->h;
  SDL_FreeSurface(surface);

  // Generate graphical representation of button
  box.reset(SDL_CreateTexture(renderer,
                              SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
                              w, h));
  SDL_SetRenderTarget(renderer, box.get());
  SDL_SetRenderDrawColor(renderer, 175, 175, 175, 255);
  SDL_Rect tempBoundingBox{0, 0, w, h};
  SDL_RenderFillRect(renderer, &tempBoundingBox);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderDrawRect(renderer, &tempBoundingBox);
  SDL_SetRenderTarget(renderer, nullptr);
}

bool Button::isSelected() const {
  SDL_Point m;
  SDL_GetMouseState(&m.x, &m.y);
  return SDL_PointInRect(&m, &boundingBox);
}

std::function<void()> Button::handleEvent(const SDL_Event* const event) const {
  if (event->type == SDL_MOUSEBUTTONUP) {
    return action;
  }
  return []{};
}

void Button::render() const {
  auto renderer = Application::getInstance().getRenderer();

  // Render button
  SDL_RenderCopy(renderer, box.get(), nullptr, &boundingBox);

  // Render selection overlay
  if (isSelected()) {
    SDL_SetRenderDrawColor(renderer, 50, 150, 50, 170);
    SDL_RenderFillRect(renderer, &boundingBox);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  }

  // Render text
  SDL_RenderCopy(renderer, text.get(), nullptr, &centreBoundingBox);
}
