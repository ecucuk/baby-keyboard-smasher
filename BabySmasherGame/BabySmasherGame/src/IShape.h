//
//  IShape.h
//  BabySmasherGame
//
//  Created by Ergün CÜCÜK on 25.10.2025.
//

#ifndef ISHAPE_H
#define ISHAPE_H 1U

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_textengine.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "Color.h"

namespace game::gui::shape {

enum class ShapeType { CIRCLE, SQUARE, TRIANGLE, STAR };

class IShape {
 public:
  /**
   * @brief Constructor
   * @param posX X koordinatı
   * @param posY Y koordinatı
   * @param velX X hızı
   * @param velY Y hızı
   * @param sz Boyut
   * @param col Renk
   * @param key Basılan tuş
   */
  IShape(float posX, float posY, float velX, float velY, int sz, SDL_Color col,
         char key)
      : x_y(std::make_pair(posX, posY)),
        vx_vy(std::make_pair(velX, velY)),
        size(sz),
        color(col),
        letter(key),
        lifetime(3.0f),
        rotation(0),
        rotationSpeed((rand() % 200 - 100) / 50.0f) {}

  virtual ~IShape() = default;

  /**
   * @brief Şekli çizer (saf sanal fonksiyon)
   * @param renderer SDL renderer
   */
  virtual void draw(SDL_Renderer* renderer, TTF_Font* font) = 0;

  /**
   * @brief Şekli günceller
   * @param deltaTime Frame süresi (saniye)
   * @param screenWidth Ekran genişliği
   * @param screenHeight Ekran yüksekliği
   */
  virtual void update(float deltaTime, int screenWidth, int screenHeight) {
    x_y.first += vx_vy.first * deltaTime;
    x_y.second += vx_vy.second * deltaTime;
    rotation += rotationSpeed * deltaTime;
    lifetime -= deltaTime;

    // Ekran sınırlarında zıplama
    if (x_y.first < 0 || x_y.first > screenWidth) vx_vy.first *= -1;
    if (x_y.second < 0 || x_y.second > screenHeight) vx_vy.second *= -1;
  }

  /**
   * @brief Şeklin yaşam süresinin bitip bitmediğini kontrol eder
   * @return true Yaşam süresi bitti
   */
  bool isDead() const { return lifetime <= 0; }

  /**
   * @brief Mevcut transparanlığı hesaplar
   * @return Uint8 Alpha değeri (0-255)
   */
  Uint8 getAlpha() const { return static_cast<Uint8>(255 * (lifetime / 3.0f)); }

 protected:
  /**
   * @brief Harfi çizer
   * @param renderer SDL renderer
   */
  void drawLetter(SDL_Renderer* renderer, TTF_Font* font, char letter, float x,
                  float y, float size, Uint8 alpha) {
    if (!renderer || !font) return;

    char text[2] = {letter, '\0'};

    SDL_Color textColor = {255, 255, 255, alpha};

    // SDL3_ttf: length parametresi eklendi
    SDL_Surface* textSurface =
        TTF_RenderText_Blended(font, text, strlen(text), textColor);
    if (!textSurface) return;

    SDL_Texture* textTexture =
        SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_DestroySurface(textSurface);  // SDL3: SDL_FreeSurface yerine

    if (!textTexture) return;

    SDL_FRect dstRect = {x - size / 4.0f, y - size / 4.0f, size / 2.0f,
                         size / 2.0f};

    SDL_RenderTexture(renderer, textTexture, nullptr, &dstRect);
    SDL_DestroyTexture(textTexture);
  }

  std::pair<float, float> x_y;
  std::pair<float, float> vx_vy;
  int size;
  SDL_Color color;
  ShapeType type;
  char letter;
  float lifetime;
  float rotation;
  float rotationSpeed;
};

}  // namespace game::gui::shape
#endif  // !ISHAPE_H
