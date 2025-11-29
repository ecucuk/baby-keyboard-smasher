//
//  Game.hpp
//  BabySmasherGame
//
//  Created by Ergün CÜCÜK on 26.10.2025.
//

#ifndef GAME_HPP
#define GAME_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdio.h>

#include "IShape.h"
#include "ShapesFactory.h"

namespace game {

/**
 * @brief Ana oyun sınıfı
 */
class Game {
 private:
  SDL_Window* m_window{nullptr};
  SDL_Renderer* m_renderer{nullptr};
  TTF_Font* m_font{nullptr};
  SDL_Texture* m_backgroundTexture{nullptr};
  Mix_Chunk* m_helloSound{nullptr};
  Mix_Chunk* m_goodbyeSound{nullptr};
  Mix_Chunk* m_popSound{nullptr};

  std::vector<std::unique_ptr<gui::shape::IShape>> m_shapes{};
  bool m_running{};
  int m_screenWidth{};
  int m_screenHeight{};
  float m_bgDimAlpha{0.0f};
  std::unique_ptr<gui::shape::ShapeFactory> m_factory{};

 public:
  /**
   * @brief Constructor
   */
  Game()
      : m_window(nullptr),
        m_renderer(nullptr),
        m_running(true),
        m_screenWidth(0),
        m_screenHeight(0),
        m_factory(std::make_unique<gui::shape::ShapeFactory>()) {}

  /**
   * @brief Destructor
   */
  ~Game() { cleanup(); }

  /**
   * @brief Oyunu başlatır
   * @return true Başarılı
   */
  bool initialize();

  /**
   * @brief Oyun olaylarını işler
   */
  void handleEvents();

  /**
   * @brief Oyunu günceller
   * @param deltaTime Frame süresi
   */
  void update(float deltaTime);

  /**
   * @brief Ekranı çizer
   */
  void render();

  /**
   * @brief Ana oyun döngüsü
   */
  void run();

  /**
   * @brief Kaynakları temizler
   */
  void cleanup();
};

}  // namespace game

#endif  // !GAME_HPP
