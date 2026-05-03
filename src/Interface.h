#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <vector>
#include <string>
#include <functional>

struct MenuItem {
    std::string text;
    std::function<void()> onClick;
};

class Interface {
private:
    bool menuOpen = false;
    float menuX = 0;
    float menuY = 0;
    float menuWidth = 120;
    float itemHeight = 30;
    int hoveredIndex = -1;

    TTF_Font* font = nullptr;
    std::vector<MenuItem> items;

public:
    Interface();
    ~Interface();

    bool init(const char* fontPath, int fontSize);
    void addMenuItem(const std::string& text, std::function<void()> onClick);

    bool handleEvent(const SDL_Event& event);
    void render(SDL_Renderer* renderer);
};