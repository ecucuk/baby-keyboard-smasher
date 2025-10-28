//
//  Color.h
//  BabySmasherGame
//
//  Created by Ergün CÜCÜK on 26.10.2025.
//

#ifndef COLOR_H
#define COLOR_H 1U

#include <SDL3/SDL_pixels.h>

#include <map>
#include <vector>
#include <utility>
#include <algorithm> // std::clamp

namespace game::gui::color {

enum class Colors {
  RED,
  GREEN,
  BLUE,
  YELLOW,
  MAGENTA,
  CYAN,
  ORANGE,
  PURPLE,
  PINK,
  LIME,
};

class Color {
 public:
  Color() {
    colorMap = {
        {Colors::RED, m_colors.at(static_cast<uint32_t>(Colors::RED))},
        {Colors::GREEN, m_colors.at(static_cast<uint32_t>(Colors::GREEN))},
        {Colors::BLUE, m_colors.at(static_cast<uint32_t>(Colors::BLUE))},
        {Colors::YELLOW, m_colors.at(static_cast<uint32_t>(Colors::YELLOW))},
        {Colors::MAGENTA, m_colors.at(static_cast<uint32_t>(Colors::MAGENTA))},
        {Colors::CYAN, m_colors.at(static_cast<uint32_t>(Colors::CYAN))},
        {Colors::ORANGE, m_colors.at(static_cast<uint32_t>(Colors::ORANGE))},
        {Colors::PURPLE, m_colors.at(static_cast<uint32_t>(Colors::PURPLE))},
        {Colors::PINK, m_colors.at(static_cast<uint32_t>(Colors::PINK))},
        {Colors::LIME, m_colors.at(static_cast<uint32_t>(Colors::LIME))}};
  }

  ~Color() {
    m_colors.clear();
    colorMap.clear();
  }

  SDL_Color get(Colors name) { return colorMap.at(name); }

  std::vector<SDL_Color> GetAllColors() { return m_colors; }

  SDL_Color GenerateRandomColor() {
    int randomIndex = rand() % 10;

    return get(static_cast<Colors>(randomIndex));
  }

  // Yeni: RGB'yi açan yardımcı fonksiyon (amount: 0.0 - 1.0 arası)
  static SDL_Color lightenColor(const SDL_Color& color, float amount) {
    SDL_Color result = color;
    result.r = static_cast<Uint8>(std::clamp(int(color.r + (255 - color.r) * amount), 0, 255));
    result.g = static_cast<Uint8>(std::clamp(int(color.g + (255 - color.g) * amount), 0, 255));
    result.b = static_cast<Uint8>(std::clamp(int(color.b + (255 - color.b) * amount), 0, 255));
    // Alpha olduğu gibi bırakılır
    return result;
  }

  // Yeni: RGB'yi koyultan yardımcı fonksiyon (amount: 0.0 - 1.0 arası)
  static SDL_Color darkenColor(const SDL_Color& color, float amount) {
    SDL_Color result = color;
    result.r = static_cast<Uint8>(std::clamp(int(color.r * (1.0f - amount)), 0, 255));
    result.g = static_cast<Uint8>(std::clamp(int(color.g * (1.0f - amount)), 0, 255));
    result.b = static_cast<Uint8>(std::clamp(int(color.b * (1.0f - amount)), 0, 255));
    // Alpha olduğu gibi bırakılır
    return result;
  }

  // Seçilen ana renkten soft gradient için açık veya koyu bir ton üretir.
  std::pair<SDL_Color, SDL_Color> GetGradientPair(Colors name) {
    SDL_Color base = get(name);

    // Rastgele açıktan koyuya mı, yoksa koyudan açığa mı karar verelim?
    bool lighten = rand() % 2 == 0;
    float amount = 0.25f + static_cast<float>(rand()) / RAND_MAX * 0.25f; // 0.25 ile 0.5 arası

    if (lighten) {
      SDL_Color light = lightenColor(base, amount);
      return {base, light};
    } else {
      SDL_Color dark = darkenColor(base, amount);
      return {base, dark};
    }
  }

  // Rastgele ana renk ve onun açığı/koyusu ile gradient çifti döner
  std::pair<SDL_Color, SDL_Color> GenerateRandomGradientColors() {
    int randomIndex = rand() % 10;
    Colors randomColor = static_cast<Colors>(randomIndex);
    return GetGradientPair(randomColor);
  }

 private:
  std::vector<SDL_Color> m_colors{
      {255, 0, 0, 255},      // RED
      {0, 255, 0, 255},      // GREEN
      {0, 0, 255, 255},      // BLUE
      {255, 255, 0, 255},    // YELLOW
      {255, 0, 255, 255},    // MAGENTA
      {0, 255, 255, 255},    // CYAN
      {255, 128, 0, 255},    // ORANGE
      {128, 0, 255, 255},    // PURPLE
      {255, 192, 203, 255},  // PINK
      {0, 255, 128, 255}     // LIME
  };

  std::map<Colors, SDL_Color> colorMap;
};

}  // namespace game::gui::color

#endif  // !COLOR_H
