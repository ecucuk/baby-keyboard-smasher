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
 * @brief Daire şekli
 */
class Circle : public IShape {
public:
    Circle(float x, float y, float vx, float vy, int size, SDL_Color color, char key)
        : IShape(x, y, vx, vy, size, color, key) {}
    
    void draw(SDL_Renderer* renderer, TTF_Font* font) override;
};

/**
 * @brief Kare şekli
 */
class Square : public IShape {
public:
    Square(float x, float y, float vx, float vy, int size, SDL_Color color, char key)
        : IShape(x, y, vx, vy, size, color, key) {}
    
    void draw(SDL_Renderer* renderer, TTF_Font* font) override;
};

/**
 * @brief Üçgen şekli
 */
class Triangle : public IShape {
public:
    Triangle(float x, float y, float vx, float vy, int size, SDL_Color color, char key)
        : IShape(x, y, vx, vy, size, color, key) {}
    
    void draw(SDL_Renderer* renderer, TTF_Font* font) override;
};

/**
 * @brief Yıldız şekli
 */
class Star : public IShape {
public:
    Star(float x, float y, float vx, float vy, int size, SDL_Color color, char key)
        : IShape(x, y, vx, vy, size, color, key) {}
    
    void draw(SDL_Renderer* renderer, TTF_Font* font) override;
};

} // namespace game::gui::shape

#endif // !SHAPES_H
