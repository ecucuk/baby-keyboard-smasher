//
//  Color.h
//  BabySmasherGame
//
//  Created by Ergün CÜCÜK on 26.10.2025.
//

#ifndef COLOR_H
#define COLOR_H 1U

#include <SDL3/SDL_pixels.h>

#include <vector>
#include <map>

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
    
    Color()
    {
        colorMap = {
            {Colors::RED,     m_colors.at(static_cast<uint32_t>(Colors::RED))},
            {Colors::GREEN,   m_colors.at(static_cast<uint32_t>(Colors::GREEN))},
            {Colors::BLUE,    m_colors.at(static_cast<uint32_t>(Colors::BLUE))},
            {Colors::YELLOW,  m_colors.at(static_cast<uint32_t>(Colors::YELLOW))},
            {Colors::MAGENTA, m_colors.at(static_cast<uint32_t>(Colors::MAGENTA))},
            {Colors::CYAN,    m_colors.at(static_cast<uint32_t>(Colors::CYAN))},
            {Colors::ORANGE,  m_colors.at(static_cast<uint32_t>(Colors::ORANGE))},
            {Colors::PURPLE,  m_colors.at(static_cast<uint32_t>(Colors::PURPLE))},
            {Colors::PINK,    m_colors.at(static_cast<uint32_t>(Colors::PINK))},
            {Colors::LIME,    m_colors.at(static_cast<uint32_t>(Colors::LIME))}
        };
    }
    
    ~Color()
    {
        m_colors.clear();
        colorMap.clear();
    }
    
        
    SDL_Color get(Colors name)
    {
        return colorMap.at(name);
    }
    
    std::vector<SDL_Color> GetAllColors()
    {
        return m_colors;
    }
    
    SDL_Color GenerateRandomColor()
    {
            int randomIndex = rand() % 10;
        
            return get(static_cast<Colors>(randomIndex));
    }
    
private:
    std::vector<SDL_Color> m_colors {
        {255, 0, 0, 255},     // RED
        {0, 255, 0, 255},     // GREEN
        {0, 0, 255, 255},     // BLUE
        {255, 255, 0, 255},   // YELLOW
        {255, 0, 255, 255},   // MEGANTA
        {0, 255, 255, 255},   // CYAN
        {255, 128, 0, 255},   // ORANGE
        {128, 0, 255, 255},   // PURPLE
        {255, 192, 203, 255}, // PINK
        {0, 255, 128, 255}    // LIGHT_GREEN
    };
    
    std::map<Colors, SDL_Color> colorMap;
};

} // namespace game::gui::color

#endif // !COLOR_H
