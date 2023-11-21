#include <gui/Screen.hpp>

using gui::Screen;

void Screen::addComponents(const std::initializer_list<GuiComponent*>& cs) {
  for (const auto c : cs) {
    components.push_back(std::unique_ptr<GuiComponent>{c});
  }
}

void Screen::render() const {
  for (const auto& c : components) {
    c->render();
  }
}

void Screen::handleEvent(const SDL_Event* const event) const {
  for (const auto& c : components) {
    if (c->isSelected()) {
      c->handleEvent(event)();
    }
  }
}

void Screen::update() {
  for (auto& c : components) {
    c->update();
  }
}
