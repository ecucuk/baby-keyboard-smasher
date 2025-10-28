//
//  Shapes.h
//  BabySmasherGame
//
//  Created by Ergün CÜCÜK on 26.10.2025.
//

#ifndef SHAPES_H
#define SHAPES_H 1U

#include "IShape.h"

namespace game::gui::shape {

/**
 * @brief A class representing a circle shape.
 * 
 * Inherits from IShape and provides implementation for drawing a circle with a letter inside.
 */
class Circle : public IShape {
 public:
  /**
   * @brief Constructor for Circle
   * @param x Initial X coordinate
   * @param y Initial Y coordinate
   * @param vx X velocity
   * @param vy Y velocity
   * @param size Diameter of the circle
   * @param startColor Gradient start color
   * @param endColor Gradient end color
   * @param key Letter to display inside the circle
   */
  Circle(float x, float y, float vx, float vy, int size, SDL_Color startColor,
         SDL_Color endColor, std::string key)
      : IShape(x, y, vx, vy, size, startColor, endColor, std::move(key)) {}

  /**
   * @brief Draws the circle on the screen.
   * @param renderer The SDL renderer
   * @param font The font for rendering the letter
   */
  void draw(SDL_Renderer* renderer, TTF_Font* font) override;
};

/**
 * @brief A class representing a square shape.
 * 
 * Inherits from IShape and provides implementation for drawing a square with a letter inside.
 */
class Square : public IShape {
 public:
  /**
   * @brief Constructor for Square
   * @param x Initial X coordinate
   * @param y Initial Y coordinate
   * @param vx X velocity
   * @param vy Y velocity
   * @param size Width and height of the square
   * @param startColor Gradient start color
   * @param endColor Gradient end color
   * @param key Letter to display inside the square
   */
  Square(float x, float y, float vx, float vy, int size, SDL_Color startColor,
         SDL_Color endColor, std::string key)
      : IShape(x, y, vx, vy, size, startColor, endColor, std::move(key)) {}

  /**
   * @brief Draws the square on the screen.
   * @param renderer The SDL renderer
   * @param font The font for rendering the letter
   */
  void draw(SDL_Renderer* renderer, TTF_Font* font) override;
};

/**
 * @brief A class representing a triangle shape.
 * 
 * Inherits from IShape and provides implementation for drawing a triangle with a letter inside.
 */
class Triangle : public IShape {
 public:
  /**
   * @brief Constructor for Triangle
   * @param x Initial X coordinate
   * @param y Initial Y coordinate
   * @param vx X velocity
   * @param vy Y velocity
   * @param size Size parameter for the triangle
   * @param startColor Gradient start color
   * @param endColor Gradient end color
   * @param key Letter to display inside the triangle
   */
  Triangle(float x, float y, float vx, float vy, int size, SDL_Color startColor,
           SDL_Color endColor, std::string key)
      : IShape(x, y, vx, vy, size, startColor, endColor, std::move(key)) {}

  /**
   * @brief Draws the triangle on the screen.
   * @param renderer The SDL renderer
   * @param font The font for rendering the letter
   */
  void draw(SDL_Renderer* renderer, TTF_Font* font) override;
};

/**
 * @brief A class representing a star shape.
 * 
 * Inherits from IShape and provides implementation for drawing a star with a letter inside.
 */
class Star : public IShape {
 public:
  /**
   * @brief Constructor for Star
   * @param x Initial X coordinate
   * @param y Initial Y coordinate
   * @param vx X velocity
   * @param vy Y velocity
   * @param size Size parameter for the star
   * @param startColor Gradient start color
   * @param endColor Gradient end color
   * @param key Letter to display inside the star
   */
  Star(float x, float y, float vx, float vy, int size, SDL_Color startColor,
       SDL_Color endColor, std::string key)
      : IShape(x, y, vx, vy, size, startColor, endColor, std::move(key)) {}

  /**
   * @brief Draws the star on the screen.
   * @param renderer The SDL renderer
   * @param font The font for rendering the letter
   */
  void draw(SDL_Renderer* renderer, TTF_Font* font) override;
};

}  // namespace game::gui::shape

#endif  // !SHAPES_H
