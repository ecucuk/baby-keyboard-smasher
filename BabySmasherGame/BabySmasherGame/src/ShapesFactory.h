//
//  ShapesFactory.h
//  BabySmasherGame
//
//  Created by Ergün CÜCÜK on 26.10.2025.
//

#ifndef SHAPESFACTORY_H
#define SHAPESFACTORY_H 1U

#include <memory>
#include <string>
#include "IShape.h"
#include "Color.h"

namespace game::gui::shape {

/**
 * @brief The shape factory class.
 *
 * Provides methods for creating and managing shape objects.
 */
class ShapeFactory {
 public:
    ShapeFactory() = default;
    ~ShapeFactory() = default;
    
  /**
   * @brief Creates a shape with random properties.
   * @param screenWidth Width of the screen
   * @param screenHeight Height of the screen
   * @param key The key pressed (used as a letter in the shape)
   * @return unique_ptr<IShape> The newly created shape
   */
  std::unique_ptr<gui::shape::IShape> createRandom(
      int screenWidth, int screenHeight, const std::string& key);
};

}  // namespace game::gui::shape

#endif  // !SHAPESFACTORY_H
