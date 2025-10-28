//
//  ShapesFactory.cpp
//  BabySmasherGame
//
//  Created by Ergün CÜCÜK on 26.10.2025.
//

#include "ShapesFactory.h"
#include "Shapes.h"

namespace game::gui::shape {

/**
 * @brief Creates a shape with random properties and gradient color.
 */
std::unique_ptr<gui::shape::IShape> ShapeFactory::createRandom(
    int screenWidth, int screenHeight, const std::string& key) {
  float x = rand() % screenWidth;
  float y = rand() % screenHeight;
  float vx = (rand() % 200 - 100) * 2.0f;
  float vy = (rand() % 200 - 100) * 2.0f;
  int size = 50 + rand() % 100;
  color::Color shape_color{};

  // Gradient için iki renk al
  auto gradientColors = shape_color.GenerateRandomGradientColors();
  SDL_Color startColor = gradientColors.first;
  SDL_Color endColor = gradientColors.second;

  int shapeType = rand() % 4;

  switch (shapeType) {
    case 0:
      return std::make_unique<Circle>(x, y, vx, vy, size, startColor, endColor, key);
    case 1:
      return std::make_unique<Square>(x, y, vx, vy, size, startColor, endColor, key);
    case 2:
      return std::make_unique<Triangle>(x, y, vx, vy, size, startColor, endColor, key);
    case 3:
      return std::make_unique<Star>(x, y, vx, vy, size, startColor, endColor, key);
    default:
      return std::make_unique<Circle>(x, y, vx, vy, size, startColor, endColor, key);
  }
}



}  // namespace game::gui::shape
