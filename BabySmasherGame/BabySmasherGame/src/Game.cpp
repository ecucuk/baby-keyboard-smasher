//
//  Game.cpp
//  BabySmasherGame
//
//  Created by Ergün CÜCÜK on 26.10.2025.
//

#include "Game.h"

#include "ShapesFactory.h"

#include <filesystem> // C++17 ile mevcut

namespace game {

/**
 * @brief Oyunu başlatır
 * @return true Başarılı
 */
bool Game::initialize() {
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        return false;
    }
    
    if (!TTF_Init()) {
        SDL_Log("TTF_Init error: %s", SDL_GetError());
        return false;
    }
    
    const SDL_DisplayMode* displayMode = SDL_GetCurrentDisplayMode(SDL_GetPrimaryDisplay());
    if (!displayMode) {
        SDL_Quit();
        return false;
    }
    
    m_screenWidth = displayMode->w;
    m_screenHeight = displayMode->h;
    
    m_window = SDL_CreateWindow(
        "Baby Smash - Klavyeye Bas ve Eğlen!",
        m_screenWidth,
        m_screenHeight,
        SDL_WINDOW_FULLSCREEN
    );
    
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
    
    std::string fontPath {"../../font/OpenSans-Bold.ttf"};

    if (!std::filesystem::exists(fontPath)) {
        SDL_Log("Font bulunamadı: %s", fontPath.c_str());
    }

    m_font = TTF_OpenFont(fontPath.c_str(), 128);
    if (!m_font) {
        SDL_Log("Font yüklenemedi: %s", SDL_GetError());
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return false;
    }

    gui::color::Color{};
    srand(static_cast<unsigned int>(SDL_GetTicks()));
    
    return true;
}

/**
 * @brief Oyun olaylarını işler
 */
void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            m_running = false;
        }
        else if (event.type == SDL_EVENT_KEY_DOWN) {
            if (event.key.key == SDLK_ESCAPE) {
                m_running = false;
            }
            else {
                // Yeni şekil oluştur
                m_shapes.push_back(
                    m_factory->createRandom(m_screenWidth, m_screenHeight, event.key.key)
                );
                
                // Maksimum 50 şekil
                if (m_shapes.size() > 50) {
                    m_shapes.erase(m_shapes.begin());
                }
            }
        }
    }
}

/**
 * @brief Oyunu günceller
 * @param deltaTime Frame süresi
 */
void Game::update(float deltaTime) {
    // Şekilleri güncelle ve ölenleri sil
    m_shapes.erase(
                   std::remove_if(m_shapes.begin(), m_shapes.end(),
            [deltaTime, this](std::unique_ptr<gui::shape::IShape>& shape) {
                shape->update(deltaTime, m_screenWidth, m_screenHeight);
                return shape->isDead();
            }),
                   m_shapes.end()
    );
}

/**
 * @brief Ekranı çizer
 */
void Game::render() {
    // Ekranı temizle
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
    
    // Şekilleri çiz
    for (auto& shape : m_shapes) {
        shape->draw(m_renderer, m_font);
    }
    
    // Başlangıç mesajı
    if (m_shapes.empty()) {
        SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 128);
        SDL_FRect messageRect = {
            m_screenWidth/2.0f - 200,
            m_screenHeight/2.0f - 50,
            400, 100
        };
        SDL_RenderFillRect(m_renderer, &messageRect);
    }
    
    SDL_RenderPresent(m_renderer);
}

/**
 * @brief Ana oyun döngüsü
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
        
        SDL_Delay(16); // ~60 FPS
    }
}

/**
 * @brief Kaynakları temizler
 */
void Game::cleanup() {
    m_shapes.clear();
    if (m_renderer) SDL_DestroyRenderer(m_renderer);
    if (m_window) SDL_DestroyWindow(m_window);
    if (m_font) {
        TTF_CloseFont(m_font);
        m_font = nullptr;
    }
    SDL_Quit();
}

}
