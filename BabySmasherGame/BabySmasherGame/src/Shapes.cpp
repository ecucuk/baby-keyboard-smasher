//
//  Shapes.cpp
//  BabySmasherGame
//
//  Created by Ergün CÜCÜK on 26.10.2025.
//

#include "Shapes.h"

#include <SDL.h>
#include <SDL_ttf.h>

#include <cmath>

namespace game::gui::shape {

// Yardımcı: renkler arası interpolasyon
static SDL_Color interpolateColor(const SDL_Color& a, const SDL_Color& b,
                                  float t, Uint8 alpha) {
  SDL_Color result;
  result.r = static_cast<Uint8>(a.r + (b.r - a.r) * t);
  result.g = static_cast<Uint8>(a.g + (b.g - a.g) * t);
  result.b = static_cast<Uint8>(a.b + (b.b - a.b) * t);
  result.a = alpha;
  return result;
}

/**
 * @brief Daireyi merkezden kenara doğru radial gradient ile çizer.
 */
void Circle::draw(SDL_Renderer* renderer, TTF_Font* font) {
  int radius = size / 2;
  int cx = static_cast<int>(x_y.first);
  int cy = static_cast<int>(x_y.second);
  Uint8 alpha = getAlpha();

  for (int y = -radius; y <= radius; ++y) {
    for (int x = -radius; x <= radius; ++x) {
      float dist = std::sqrt(x * x + y * y);
      if (dist <= radius) {
        // t: merkezde 0, kenarda 1
        float t = dist / radius;
        SDL_Color c = interpolateColor(startColor, endColor, t, alpha);
        SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
        SDL_RenderDrawPoint(renderer, cx + x, cy + y);
      }
    }
  }

  drawLetter(renderer, font, letter, cx, cy, size, alpha);
}

void Square::draw(SDL_Renderer* renderer, TTF_Font* font) {
  int half = size / 2;
  Uint8 alpha = getAlpha();
  for (int y = 0; y < size; ++y) {
    float t = static_cast<float>(y) / (size - 1);
    SDL_Color c = interpolateColor(startColor, endColor, t, alpha);
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    SDL_RenderDrawLine(renderer,
                       x_y.first - half, x_y.second - half + y,
                       x_y.first + half, x_y.second - half + y);
  }
  drawLetter(renderer, font, letter, x_y.first, x_y.second, size, alpha);
}

void Triangle::draw(SDL_Renderer* renderer, TTF_Font* font) {
  int h = size;
  int baseY = x_y.second + h / 2;
  int centerX = x_y.first;
  Uint8 alpha = getAlpha();

  for (int y = 0; y < h; ++y) {
    float t = static_cast<float>(y) / (h - 1);
    SDL_Color c = interpolateColor(startColor, endColor, t, alpha);

    float pct = static_cast<float>(y) / h;
    int halfWidth = static_cast<int>((h / 2) * (1 - pct));
    int startX = centerX - halfWidth;
    int endX = centerX + halfWidth;
    int drawY = baseY - y;

    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    SDL_RenderDrawLine(renderer, startX, drawY, endX, drawY);
  }

  drawLetter(renderer, font, letter, x_y.first, x_y.second, size, alpha);
}

void Star::draw(SDL_Renderer* renderer, TTF_Font* font) {
  const int points = 5;
  const float angleStep = 3.14159f * 2 / points;
  const float innerRadius = size * 0.4f;
  const float outerRadius = size * 0.8f;
  float cx = x_y.first;
  float cy = x_y.second;
  Uint8 alpha = getAlpha();

  std::vector<SDL_FPoint> vertices;

  // Yıldızın noktalarını hesapla
  for (int i = 0; i < points * 2; i++) {
    float angle = i * 3.14159f / points;
    float r = (i % 2 == 0) ? outerRadius : innerRadius;
    vertices.push_back({cx + r * std::cos(angle), cy + r * std::sin(angle)});
  }

  // --- Yıldızı doldur: bounding box + inside test ---
  float minX = cx - outerRadius, maxX = cx + outerRadius;
  float minY = cy - outerRadius, maxY = cy + outerRadius;

  for (int y = minY; y <= maxY; y++) {
    for (int x = minX; x <= maxX; x++) {
      // Nokta yıldız içinde mi? (Winding rule)
      bool inside = false;
      for (int i = 0, j = vertices.size() - 1; i < vertices.size(); j = i++) {
        float xi = vertices[i].x, yi = vertices[i].y;
        float xj = vertices[j].x, yj = vertices[j].y;

        bool intersect = ((yi > y) != (yj > y)) &&
                         (x < (xj - xi) * (y - yi) / (yj - yi + 0.0001f) + xi);

        if (intersect) inside = !inside;
      }

      if (inside) {
        // merkez → kenar gradient
        float dist = sqrtf((x - cx)*(x - cx) + (y - cy)*(y - cy));
        float t = dist / outerRadius;
        SDL_Color c = interpolateColor(startColor, endColor, t, alpha);
        SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
        SDL_RenderDrawPoint(renderer, x, y);
      }
    }
  }

  // --- Dış hatları çiz (net, keskin) ---
  SDL_Color outline = {255, 255, 255, alpha};
  SDL_SetRenderDrawColor(renderer, outline.r, outline.g, outline.b, outline.a);
  for (int i = 0; i < vertices.size(); ++i) {
    int next = (i + 1) % vertices.size();
    SDL_RenderDrawLine(renderer, vertices[i].x, vertices[i].y,
                       vertices[next].x, vertices[next].y);
  }

  // --- Harfi çiz (tam ortada) ---
  drawLetter(renderer, font, letter, cx, cy, size, alpha);
}

}  // namespace game::gui::shape
