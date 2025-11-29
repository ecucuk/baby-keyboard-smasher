//
//  IShape.h
//  BabySmasherGame
//
//  Created by Ergün CÜCÜK on 25.10.2025.
//

#ifndef ISHAPE_H
#define ISHAPE_H 1U

#include <SDL.h>
#include <SDL_ttf.h>
#include "Color.h"

namespace game::gui::shape {

/**
 * @brief The enumeration for the types of shapes.
 */
enum class ShapeType { CIRCLE, SQUARE, TRIANGLE, STAR };

/**
 * @brief Abstract base class for all shapes.
 *
 * Provides the interface and base functionality for shape classes.
 */
class IShape {
 public:
  /**
   * @brief Constructor
   * @param posX X coordinate
   * @param posY Y coordinate
   * @param velX X velocity
   * @param velY Y velocity
   * @param sz Size of the shape
   * @param color1 Gradient start color
   * @param color2 Gradient end color
   * @param key Letter displayed inside the shape
   */
  IShape(float posX, float posY, float velX, float velY, int sz, SDL_Color color1,
         SDL_Color color2, std::string key)
      : x_y(std::make_pair(posX, posY)),
        vx_vy(std::make_pair(velX, velY)),
        size(sz),
        startColor(color1),
        endColor(color2),
        letter(std::move(key)),
        lifetime(3.0f),
        rotation(0),
        rotationSpeed((rand() % 200 - 100) / 50.0f) {}

  virtual ~IShape() = default;

  /**
   * @brief Draws the shape on the screen. (pure virtual)
   * @param renderer SDL renderer
   * @param font Font used for rendering the letter
   */
  virtual void draw(SDL_Renderer* renderer, TTF_Font* font) = 0;

  /**
   * @brief Updates the shape's state (position, rotation, lifetime).
   * @param deltaTime Frame time in seconds
   * @param screenWidth Width of the screen
   * @param screenHeight Height of the screen
   */
  virtual void update(float deltaTime, int screenWidth, int screenHeight) {
    x_y.first += vx_vy.first * deltaTime;
    x_y.second += vx_vy.second * deltaTime;
    rotation += rotationSpeed * deltaTime;
    lifetime -= deltaTime;

    // Bounce back at the screen edges
    if (x_y.first < 0 || x_y.first > screenWidth) vx_vy.first *= -1;
    if (x_y.second < 0 || x_y.second > screenHeight) vx_vy.second *= -1;
  }

  /**
   * @brief Checks if the shape's lifetime has expired.
   * @return true if its lifetime is over
   */
  bool isDead() const { return lifetime <= 0; }

  /**
   * @brief Calculates the current alpha (transparency) value.
   * @return Uint8 Alpha value (0-255)
   */
  Uint8 getAlpha() const { return static_cast<Uint8>(255 * (lifetime / 3.0f)); }

 protected:
  /**
   * @brief Draws the given letter in the center of the shape.
   * @param renderer SDL renderer
   * @param font Font to use for rendering
   * @param letter The letter to render
   * @param x X coordinate of the letter
   * @param y Y coordinate of the letter
   * @param size Size of the bounding shape
   * @param alpha Alpha (transparency) value
   */
  void drawLetter(SDL_Renderer* renderer, TTF_Font* font,
                  const std::string& letter, float x, float y, float size,
                  Uint8 alpha) {
    if (!renderer || !font) return;

    std::string text{letter};

    SDL_Color textColor = {255, 255, 255, alpha};

      SDL_Surface* textSurface =
          TTF_RenderUTF8_Blended(font, text.c_str(), textColor);
      
    if (!textSurface) return;

    SDL_Texture* textTexture =
        SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    if (!textTexture) return;

    SDL_FRect dstRect = {x - size / 4.0f, y - size / 4.0f, size / 2.0f,
                         size / 2.0f};

    SDL_RenderCopyF(renderer, textTexture, nullptr, &dstRect);
    SDL_DestroyTexture(textTexture);
  }

  std::pair<float, float> x_y;   ///< Position (X, Y)
  std::pair<float, float> vx_vy; ///< Velocity (X, Y)
  int size;                      ///< Size of the shape
  SDL_Color startColor;          ///< Gradient start color
  SDL_Color endColor;            ///< Gradient end color
  ShapeType type;                ///< The type of the shape
  std::string letter;            ///< Letter displayed in the shape
  float lifetime;                ///< Remaining lifetime in seconds
  float rotation;                ///< Current rotation (unused)
  float rotationSpeed;           ///< Speed of rotation (unused)
};

}  // namespace game::gui::shape
#endif  // !ISHAPE_H
