//
//  ShapesFactory.h
//  BabySmasherGame
//
//  Created by Ergün CÜCÜK on 26.10.2025.
//

#ifndef SHAPESFACTORY_H
#define SHAPESFACTORY_H

#include <stdio.h>

#include "Shapes.h"

namespace game::gui::shape {
/**
 * @brief Şekil fabrika sınıfı
 *
 * Rastgele şekiller oluşturur
 */
class ShapeFactory {
 public:
  /**
   * @brief Rastgele bir şekil oluşturur
   * @param screenWidth Ekran genişliği
   * @param screenHeight Ekran yüksekliği
   * @param key Basılan tuş
   * @return unique_ptr<IShape> Oluşturulan şekil
   */
  std::unique_ptr<gui::shape::IShape> createRandom(int screenWidth,
                                                   int screenHeight, char key);
  /**
   * @brief Belirli bir türde şekil döndürür
   * @param type Şekil türü
   * @param key Basılan tuş
   * @return unique_ptr<IShape> Oluşturulan şekil
   */
  std::unique_ptr<gui::shape::IShape> getShape(ShapeType type, char key);

  /**
   * @brief Belirli bir türdeki şekli kaldırır
   * @param type Şekil türü
   * @param key Basılan tuş
   * @return bool Şekil başarıyla kaldırıldıysa true
   */
  bool removeShape(ShapeType type, char key);
};
}  // namespace game::gui::shape

#endif  // !SHAPESFACTORY_H
