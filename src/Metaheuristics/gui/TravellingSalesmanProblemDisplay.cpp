#include <gui/TravellingSalesmanProblemDisplay.hpp>

using gui::TravellingSalesmanProblemDisplay;

void TravellingSalesmanProblemDisplay::render() const {
  auto o = tsp.getOptimal().order;
  auto renderer = Application::getInstance().getRenderer();

  // Render display bounds
  SDL_RenderDrawRect(renderer, &boundingBox);

  // Render cities
  for (const auto& city : o) {
    SDL_Rect c{city.location.x - cSz / 2, city.location.y - cSz / 2, cSz, cSz};
    SDL_RenderFillRect(renderer, &c);
  }

  // Render edges
  for (Uint32 i = 0; i < o.size() - 1; ++i) {
    SDL_RenderDrawLine(renderer,
                       o[i].location.x, o[i].location.y,
                       o[i + 1].location.x, o[i + 1].location.y);
  }
  SDL_RenderDrawLine(renderer,
                       o[o.size() - 1].location.x, o[o.size() - 1].location.y,
                       o[0].location.x, o[0].location.y);
}
