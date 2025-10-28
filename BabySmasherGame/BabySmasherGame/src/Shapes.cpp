//
//  Shapes.cpp
//  BabySmasherGame
//
//  Created by Ergün CÜCÜK on 26.10.2025.
//

#include "Shapes.h"
#include <SDL3_ttf/SDL_ttf.h>

namespace game::gui::shape {

/**
 * @brief Draws the shape with a letter at its center using the given renderer and font.
 * @param renderer Pointer to the SDL_Renderer used for drawing.
 * @param font Pointer to the TTF_Font for rendering the letter.
 */
void Circle::draw(SDL_Renderer* renderer, TTF_Font* font) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, getAlpha());
    
    int radius = size / 2;
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx*dx + dy*dy) <= (radius * radius)) {
                SDL_RenderPoint(renderer, x_y.first + dx, x_y.second + dy);
            }
        }
    }

    drawLetter(renderer, font, letter, x_y.first, x_y.second, size, getAlpha());
}

void Square::draw(SDL_Renderer* renderer, TTF_Font* font) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, getAlpha());
    
    SDL_FRect rect = {x_y.first - size/2.0f, x_y.second - size/2.0f, (float)size, (float)size};
    SDL_RenderFillRect(renderer, &rect);
    
    drawLetter(renderer, font, letter, x_y.first, x_y.second, size, getAlpha());
}

void Triangle::draw(SDL_Renderer* renderer, TTF_Font* font) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, getAlpha());
    
    for (int i = 0; i < size; i++) {
        SDL_RenderLine(renderer,
            x_y.first - i/2, x_y.second + size/2 - i,
            x_y.first + i/2, x_y.second + size/2 - i);
    }

    drawLetter(renderer, font, letter, x_y.first, x_y.second, size, getAlpha());
}

void Star::draw(SDL_Renderer* renderer, TTF_Font* font) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, getAlpha());
    
    const int points = 5;
    const float angleStep = 3.14159f * 2 / points;
    const float innerRadius = size * 0.4f;
    const float outerRadius = size * 0.8f;
    
    for (int i = 0; i < points * 2; i++) {
        float angle1 = i * angleStep / 2;
        float angle2 = (i + 1) * angleStep / 2;
        float r1 = (i % 2 == 0) ? outerRadius : innerRadius;
        float r2 = ((i + 1) % 2 == 0) ? outerRadius : innerRadius;
        
        int x1 = x_y.first + r1 * cos(angle1);
        int y1 = x_y.second + r1 * sin(angle1);
        int x2 = x_y.first + r2 * cos(angle2);
        int y2 = x_y.second + r2 * sin(angle2);
        
        SDL_RenderLine(renderer, x1, y1, x2, y2);
    }

    drawLetter(renderer, font, letter, x_y.first, x_y.second, size, getAlpha());
}

}
