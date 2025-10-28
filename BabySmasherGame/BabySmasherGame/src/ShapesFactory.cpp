//
//  ShapesFactory.cpp
//  BabySmasherGame
//
//  Created by Ergün CÜCÜK on 26.10.2025.
//

#include "ShapesFactory.h"

namespace game::gui::shape {


/**
 * @brief Rastgele bir şekil oluşturur
 * @param screenWidth Ekran genişliği
 * @param screenHeight Ekran yüksekliği
 * @param key Basılan tuş
 * @return unique_ptr<IShape> Oluşturulan şekil
 */
std::unique_ptr<gui::shape::IShape> ShapeFactory::createRandom(int screenWidth, int screenHeight, char key) {
    float x = rand() % screenWidth;
    float y = rand() % screenHeight;
    float vx = (rand() % 200 - 100) * 2.0f;
    float vy = (rand() % 200 - 100) * 2.0f;
    int size = 50 + rand() % 100;
    color::Color shape_color{};
    
    SDL_Color color = shape_color.GenerateRandomColor();
    
    int shapeType = rand() % 4;
    
    switch (shapeType) {
        case 0: return std::make_unique <gui::shape::Circle>(x, y, vx, vy, size, color, key);
        case 1: return std::make_unique <gui::shape::Square>(x, y, vx, vy, size, color, key);
        case 2: return std::make_unique <gui::shape::Triangle>(x, y, vx, vy, size, color, key);
        case 3: return std::make_unique <gui::shape::Star>(x, y, vx, vy, size, color, key);
        default: return std::make_unique<gui::shape::Circle>(x, y, vx, vy, size, color, key);
    }
}

}
