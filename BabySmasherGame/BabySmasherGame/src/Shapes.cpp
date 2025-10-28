//
//  Shapes.cpp
//  BabySmasherGame
//
//  Created by Ergün CÜCÜK on 26.10.2025.
//

#include <SDL3_ttf/SDL_ttf.h>

#include <cmath>

#include "Shapes.h"

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
  float cx = x_y.first;
  float cy = x_y.second;
  Uint8 alpha = getAlpha();

  for (int y = -radius; y <= radius; ++y) {
    for (int x = -radius; x <= radius; ++x) {
      float dist = std::sqrt(x * x + y * y);
      if (dist <= radius) {
        // t: merkezde 0, kenarda 1
        float t = dist / radius;
        SDL_Color c = interpolateColor(startColor, endColor, t, alpha);
        SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
        SDL_RenderPoint(renderer, cx + x, cy + y);
      }
    }
  }

  drawLetter(renderer, font, letter, cx, cy, size, alpha);
}

/**
 * @brief Kareyi üstten alta linear gradient ile çizer.
 */
void Square::draw(SDL_Renderer* renderer, TTF_Font* font) {
  int half = size / 2;
  Uint8 alpha = getAlpha();

  for (int y = 0; y < size; ++y) {
    float t = static_cast<float>(y) / (size - 1);
    SDL_Color c = interpolateColor(startColor, endColor, t, alpha);
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    SDL_RenderLine(renderer, x_y.first - half, x_y.second - half + y,
                   x_y.first + half, x_y.second - half + y);
  }

  drawLetter(renderer, font, letter, x_y.first, x_y.second, size, alpha);
}

/**
 * @brief Üçgeni tabandan tepeye linear gradient ile çizer.
 */
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
    SDL_RenderLine(renderer, startX, drawY, endX, drawY);
  }

  drawLetter(renderer, font, letter, x_y.first, x_y.second, size, alpha);
}

/**
 * @brief Star için: çizgiler üzerinde gradient efekti.
 */
void Star::draw(SDL_Renderer* renderer, TTF_Font* font) {
  const int points = 5;
  const float angleStep = 3.14159f * 2 / points;
  const float innerRadius = size * 0.4f;
  const float outerRadius = size * 0.8f;
  float cx = x_y.first;
  float cy = x_y.second;
  Uint8 alpha = getAlpha();

  // Star'ın kenarlarını gradient ile çiz
  for (int i = 0; i < points * 2; i++) {
    float angle1 = i * angleStep / 2;
    float angle2 = (i + 1) * angleStep / 2;
    float r1 = (i % 2 == 0) ? outerRadius : innerRadius;
    float r2 = ((i + 1) % 2 == 0) ? outerRadius : innerRadius;

    float x1 = cx + r1 * std::cos(angle1);
    float y1 = cy + r1 * std::sin(angle1);
    float x2 = cx + r2 * std::cos(angle2);
    float y2 = cy + r2 * std::sin(angle2);

    // Çizgi boyunca renk interpolasyonu
    int steps = static_cast<int>(std::hypot(x2 - x1, y2 - y1));
    for (int s = 0; s <= steps; ++s) {
      float t = steps > 0 ? static_cast<float>(s) / steps : 0.0f;
      SDL_Color c = interpolateColor(startColor, endColor, t, alpha);
      int px = static_cast<int>(x1 + (x2 - x1) * t);
      int py = static_cast<int>(y1 + (y2 - y1) * t);
      SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
      SDL_RenderPoint(renderer, px, py);
    }
  }

  drawLetter(renderer, font, letter, cx, cy, size, alpha);
}

}  // namespace game::gui::shape
