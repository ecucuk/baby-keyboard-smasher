//
//  Game.cpp
//  BabySmasherGame
//
//  Created by Ergün CÜCÜK on 26.10.2025.
//

#include "Game.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <filesystem>  // C++17 ile mevcut

#include "Resources.h"
#include "ShapesFactory.h"

namespace game {

/**
 * @brief Initializes the game.
 * @return true on success, false on failure
 */
bool Game::initialize() {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    SDL_Log("SDL_Init error: %s", SDL_GetError());
    return false;
  }

  if (TTF_Init() == -1) {
    SDL_Log("TTF_Init error: %s", TTF_GetError());
    return false;
  }

  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
    SDL_Log("Mix_OpenAudio error: %s", Mix_GetError());
    return false;
  }

  SDL_DisplayMode displayMode;
  if (SDL_GetCurrentDisplayMode(0, &displayMode) < 0) {
    SDL_Log("SDL_GetCurrentDisplayMode error: %s", SDL_GetError());
    return false;
  }
  m_screenWidth = displayMode.w;
  m_screenHeight = displayMode.h;

  m_window =
      SDL_CreateWindow("Baby Smash - Klavyeye Bas ve Eğlen!",
                       SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       m_screenWidth, m_screenHeight, SDL_WINDOW_FULLSCREEN);

  if (!m_window) {
    SDL_Quit();
    return false;
  }

  m_renderer = SDL_CreateRenderer(
      m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (!m_renderer) {
    SDL_DestroyWindow(m_window);
    SDL_Quit();
    return false;
  }
  SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);

  std::string fontPath{};
  if (const char* basePath = SDL_GetBasePath()) {
    // .app bundle: Contents/MacOS/ -> up to Resources
    fontPath =
        std::string(basePath) + "../Resources/assets/font/OpenSans-Bold.ttf";
  } else {
    // Terminal run fallback within repo
    fontPath = "assets/font/OpenSans-Bold.ttf";
  }

  m_font = TTF_OpenFont(fontPath.c_str(), 64);
  if (!m_font) {
    SDL_Log("Font yüklenemedi: %s", SDL_GetError());
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
    return false;
  }

  if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) == 0) {
    SDL_Log("IMG_Init error: %s", IMG_GetError());
    return false;
  }

  // 🔹 Arka planı hex array'den yükle (SDL2)
  SDL_RWops* rw = SDL_RWFromConstMem(BackgroundImage, BackgroundImageLen);
  if (!rw) {
    SDL_Log("SDL_RWFromConstMem error: %s", SDL_GetError());
    return false;
  }

  SDL_Surface* surface = IMG_Load_RW(rw, 1);  // 1 = RWops'i otomatik kapat
  if (!surface) {
    SDL_Log("IMG_Load_RW error: %s", IMG_GetError());
    return false;
  }

  m_backgroundTexture = SDL_CreateTextureFromSurface(m_renderer, surface);
  SDL_FreeSurface(surface);

  if (!m_backgroundTexture) {
    SDL_Log("SDL_CreateTextureFromSurface error: %s", SDL_GetError());
    return false;
  }

  // --- Sesleri Yükle ---
  std::string soundBasePath;
  if (const char* basePath = SDL_GetBasePath()) {
    soundBasePath = std::string(basePath) + "../Resources/assets/voices/";
  } else {
    soundBasePath = "assets/voices/";
  }

  m_helloSound = Mix_LoadWAV((soundBasePath + "hello.wav").c_str());
  m_goodbyeSound = Mix_LoadWAV((soundBasePath + "goodbye.wav").c_str());
  m_popSound = Mix_LoadWAV((soundBasePath + "pop.wav").c_str());

  if (!m_helloSound || !m_goodbyeSound || !m_popSound) {
    SDL_Log("Ses dosyası yüklenemedi: %s", Mix_GetError());
  } else {
    // Oyunun başlangıcında merhaba sesi çal
    Mix_PlayChannel(-1, m_helloSound, 0);
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
    if (event.type == SDL_QUIT) {
      m_running = false;
    } else if (event.type == SDL_KEYDOWN) {
      if (event.key.keysym.sym == SDLK_ESCAPE) {
        m_running = false;
      } else {
        // Yeni şekil oluştur
        std::string letter = SDL_GetKeyName(event.key.keysym.sym);
        m_shapes.push_back(
            m_factory->createRandom(m_screenWidth, m_screenHeight, letter));
        // Pop sesi çal
        if (m_popSound) {
          Mix_PlayChannel(-1, m_popSound, 0);
        }

        m_bgDimAlpha = 120.0f;

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
  if (m_shapes.empty()) {
    m_bgDimAlpha -= 200.0f * deltaTime;
  } else {
    m_bgDimAlpha += 200.0f * deltaTime;
  }
  if (m_bgDimAlpha < 0.0f) m_bgDimAlpha = 0.0f;
  if (m_bgDimAlpha > 120.0f) m_bgDimAlpha = 120.0f;

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
    SDL_Rect dstRect = {0, 0, m_screenWidth, m_screenHeight};
    SDL_RenderCopy(m_renderer, m_backgroundTexture, nullptr, &dstRect);
  }

  if (m_bgDimAlpha > 0.0f) {
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, (Uint8)m_bgDimAlpha);
    SDL_Rect dimRect = {0, 0, m_screenWidth, m_screenHeight};
    SDL_RenderFillRect(m_renderer, &dimRect);
  }

  // Şekilleri çiz
  for (auto& shape : m_shapes) {
    shape->draw(m_renderer, m_font);
  }

  // Başlangıç mesajı
  if (m_shapes.empty() && m_font) {
    const char* message = "Selam Arden, Bir tuşa bas ve eğlenceye başla!";
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Color outlineColor = {0, 0, 0, 255};

    SDL_Surface* textSurface =
        TTF_RenderUTF8_Blended(m_font, message, textColor);

    SDL_Surface* outlineSurface =
        TTF_RenderUTF8_Blended(m_font, message, outlineColor);

    if (textSurface && outlineSurface) {
      SDL_Texture* textTexture =
          SDL_CreateTextureFromSurface(m_renderer, textSurface);
      SDL_Texture* outlineTexture =
          SDL_CreateTextureFromSurface(m_renderer, outlineSurface);

      SDL_FreeSurface(textSurface);
      SDL_FreeSurface(outlineSurface);

      if (textTexture && outlineTexture) {
        int iW = 0, iH = 0;
        SDL_QueryTexture(textTexture, nullptr, nullptr, &iW, &iH);
        float textW = static_cast<float>(iW);
        float textH = static_cast<float>(iH);

        // Glow size and rect for glow background
        SDL_Rect glowRect = {(int)(m_screenWidth / 2.0f - textW * 0.6f),
                             (int)(m_screenHeight / 2.0f - textH * 0.6f),
                             (int)(textW * 1.2f), (int)(textH * 1.2f)};

        // Soft glow
        SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 40);
        SDL_RenderFillRect(m_renderer, &glowRect);

        // Outline (draw multiple offset copies)
        for (int ox = -2; ox <= 2; ++ox) {
          for (int oy = -2; oy <= 2; ++oy) {
            if (ox == 0 && oy == 0) continue;
            SDL_Rect oRect = {(int)(m_screenWidth / 2.0f - textW / 2.0f + ox),
                              (int)(m_screenHeight / 2.0f - textH / 2.0f + oy),
                              (int)textW, (int)textH};
            SDL_RenderCopy(m_renderer, outlineTexture, nullptr, &oRect);
          }
        }

        // Draw main text
        SDL_Rect dstRect = {(int)(m_screenWidth / 2.0f - textW / 2.0f),
                            (int)(m_screenHeight / 2.0f - textH / 2.0f),
                            (int)textW, (int)textH};
        SDL_RenderCopy(m_renderer, textTexture, nullptr, &dstRect);

        SDL_DestroyTexture(textTexture);
        SDL_DestroyTexture(outlineTexture);
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

  if (m_goodbyeSound) {
    Mix_PlayChannel(-1, m_goodbyeSound, 0);
    SDL_Delay(1200);  // Sesin çalması için 1.2 saniye beklet
  }
}

/**
 * @brief Cleans up all resources.
 */
void Game::cleanup() {
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

  if (m_helloSound) {
    Mix_FreeChunk(m_helloSound);
    m_helloSound = nullptr;
  }

  if (m_goodbyeSound) {
    Mix_FreeChunk(m_goodbyeSound);
    m_goodbyeSound = nullptr;
  }

  if (m_popSound) {
    Mix_FreeChunk(m_popSound);
    m_popSound = nullptr;
  }

  Mix_CloseAudio();
  Mix_Quit();

  IMG_Quit();

  TTF_Quit();
  SDL_Quit();
}

}  // namespace game
