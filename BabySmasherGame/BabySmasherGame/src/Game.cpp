//
//  Game.cpp
//  BabySmasherGame
//
//  Created by Ergün CÜCÜK on 26.10.2025.
//

#include <filesystem>  // C++17 ile mevcut

#include "Game.h"
#include "Resources.h"
#include "ShapesFactory.h"

#include "SDL3_image/SDL_image.h"

namespace game {

/**
 * @brief Initializes the game.
 * @return true on success, false on failure
 */
bool Game::initialize() {
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
    return false;
  }

  if (!TTF_Init()) {
    SDL_Log("TTF_Init error: %s", SDL_GetError());
    return false;
  }

  const SDL_DisplayMode* displayMode =
      SDL_GetCurrentDisplayMode(SDL_GetPrimaryDisplay());
  if (!displayMode) {
    SDL_Quit();
    return false;
  }

  m_screenWidth = displayMode->w;
  m_screenHeight = displayMode->h;

  m_window =
      SDL_CreateWindow("Baby Smash - Klavyeye Bas ve Eğlen!", m_screenWidth,
                       m_screenHeight, SDL_WINDOW_FULLSCREEN);

  if (!m_window) {
    SDL_Quit();
    return false;
  }

  m_renderer = SDL_CreateRenderer(m_window, nullptr);

  if (!m_renderer) {
    SDL_DestroyWindow(m_window);
    SDL_Quit();
    return false;
  }

  std::string fontPath{"/Users/ergun.cucuk/Library/Fonts/OpenSans-Medium.ttf"};

  m_font = TTF_OpenFont(fontPath.c_str(), 64);
  if (!m_font) {
    SDL_Log("Font yüklenemedi: %s", SDL_GetError());
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
    return false;
  }

  // 🔹 Arka planı hex array'den yükle
  SDL_IOStream* io = SDL_IOFromConstMem(BackgroundImage, BackgroundImageLen);
  if (!io) {
    SDL_Log("SDL_IOFromConstMem error: %s", SDL_GetError());
    return false;
  }

  SDL_Surface* surface = IMG_Load_IO(io, true);
  if (!surface) {
    SDL_Log("IMG_Load_IO error: %s", SDL_GetError());
    return false;
  }

  m_backgroundTexture = SDL_CreateTextureFromSurface(m_renderer, surface);
  SDL_DestroySurface(surface);

  if (!m_backgroundTexture) {
    SDL_Log("SDL_CreateTextureFromSurface error: %s", SDL_GetError());
    return false;
  }

  srand(static_cast<unsigned int>(SDL_GetTicks()));

  return true;
}

/**
 * @brief Processes game events.
 */
void Game::handleEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_EVENT_QUIT) {
      m_running = false;
    } else if (event.type == SDL_EVENT_KEY_DOWN) {
      if (event.key.key == SDLK_ESCAPE) {
        m_running = false;
      } else {
        // Yeni şekil oluştur
        std::string letter = SDL_GetKeyName(event.key.key);
        m_shapes.push_back(
            m_factory->createRandom(m_screenWidth, m_screenHeight, letter));

        // Maksimum 29 şekil
        if (m_shapes.size() > 29) {
          m_shapes.erase(m_shapes.begin());
        }
      }
    }
  }
}

/**
 * @brief Updates the game state.
 * @param deltaTime Frame time in seconds
 */
void Game::update(float deltaTime) {
  m_shapes.erase(
      std::remove_if(
          m_shapes.begin(), m_shapes.end(),
          [deltaTime, this](std::unique_ptr<gui::shape::IShape>& shape) {
            shape->update(deltaTime, m_screenWidth, m_screenHeight);
            return shape->isDead();
          }),
      m_shapes.end());
}

/**
 * @brief Renders the game scene.
 */
void Game::render() {
  // Ekranı temizle
  SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
  SDL_RenderClear(m_renderer);

  // 🔹 Arka plan
  if (m_backgroundTexture) {
    SDL_FRect dstRect = {0, 0, (float)m_screenWidth, (float)m_screenHeight};
    SDL_RenderTexture(m_renderer, m_backgroundTexture, nullptr, &dstRect);
  }

  // Şekilleri çiz
  for (auto& shape : m_shapes) {
    shape->draw(m_renderer, m_font);
  }

  // Başlangıç mesajı
  if (m_shapes.empty() && m_font) {
    const char* message = "Selam Arden, Bir tuşa bas ve eğlenceye başla!";
    SDL_Color textColor = {255, 255, 255, 255};

    // SDL3_ttf: length parametresi gerekli
    SDL_Surface* textSurface =
        TTF_RenderText_Blended(m_font, message, strlen(message), textColor);
    if (textSurface) {
      SDL_Texture* textTexture =
          SDL_CreateTextureFromSurface(m_renderer, textSurface);
      SDL_DestroySurface(textSurface);

      if (textTexture) {
        // Metin boyutunu öğren
        float textW, textH;
        SDL_GetTextureSize(textTexture, &textW, &textH);

        SDL_FRect dstRect = {m_screenWidth / 2.0f - textW / 2.0f,
                             m_screenHeight / 2.0f - textH / 2.0f,
                             static_cast<float>(textW),
                             static_cast<float>(textH)};

        // Arka plan dikdörtgeni (yarı saydam)
        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 160);
        SDL_RenderFillRect(m_renderer, &dstRect);

        // Metni çiz
        SDL_RenderTexture(m_renderer, textTexture, nullptr, &dstRect);

        SDL_DestroyTexture(textTexture);
      }
    }
  }

  SDL_RenderPresent(m_renderer);
}

/**
 * @brief The main game loop.
 */
void Game::run() {
  Uint64 lastTime = SDL_GetTicks();

  while (m_running) {
    Uint64 currentTime = SDL_GetTicks();
    float deltaTime = (currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;

    handleEvents();
    update(deltaTime);
    render();

    SDL_Delay(16);  // ~60 FPS
  }
}

/**
 * @brief Cleans up all resources.
 */
void Game::cleanup() {
    m_shapes.clear();
    m_shapes.clear();
    
    if (m_backgroundTexture) {
        SDL_DestroyTexture(m_backgroundTexture);
        m_backgroundTexture = nullptr;
    }
    
    if (m_font) {
        TTF_CloseFont(m_font);
        m_font = nullptr;
    }
    
    if (m_renderer) {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }
    
    if (m_window) {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }
    
    TTF_Quit();
    SDL_Quit();
}

}  // namespace game
