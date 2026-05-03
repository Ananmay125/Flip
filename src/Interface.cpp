#include "interface.h"
#include <iostream>

Interface::Interface() {
    TTF_Init();
}

Interface::~Interface() {
    if (font) TTF_CloseFont(font);
    TTF_Quit();
}

bool Interface::init(const char* fontPath, int fontSize) {
    font = TTF_OpenFont(fontPath, fontSize);
    if (!font) {
        std::cout << "Failed to load font: " << SDL_GetError() << "\n";
        return false;
    }
    return true;
}

void Interface::addMenuItem(const std::string& text, std::function<void()> onClick) {
    items.push_back({ text, onClick });
}

bool Interface::handleEvent(const SDL_Event& event) {
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        if (event.button.button == SDL_BUTTON_RIGHT) {
            menuOpen = true;
            menuX = event.button.x;
            menuY = event.button.y;
            hoveredIndex = -1;
            return true;
        }
        else if (event.button.button == SDL_BUTTON_LEFT) {
            if (menuOpen) {
                if (hoveredIndex >= 0 && hoveredIndex < items.size()) {
                    items[hoveredIndex].onClick();
                }

                menuOpen = false;
                return true;
            }
        }
    }
    else if (event.type == SDL_EVENT_MOUSE_MOTION) {
        if (menuOpen) {
            float mx = event.motion.x;
            float my = event.motion.y;

            if (mx >= menuX && mx <= menuX + menuWidth &&
                my >= menuY && my <= menuY + (items.size() * itemHeight)) {
                hoveredIndex = (int)((my - menuY) / itemHeight);
            }
            else {
                hoveredIndex = -1;
            }
            return true;
        }
    }
    return false;
}

void Interface::render(SDL_Renderer* renderer) {
    if (!menuOpen || items.empty() || !font) return;

    float totalHeight = items.size() * itemHeight;

    // Draw Dark Background
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 240);
    SDL_FRect bgRect = { menuX, menuY, menuWidth, totalHeight };
    SDL_RenderFillRect(renderer, &bgRect);

    // Draw Light Border
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderRect(renderer, &bgRect);

    // Draw Menu Items
    for (size_t i = 0; i < items.size(); ++i) {
        SDL_FRect itemRect = { menuX, menuY + (i * itemHeight), menuWidth, itemHeight };

        // Draw Hover Box
        if (i == hoveredIndex) {
            SDL_SetRenderDrawColor(renderer, 70, 130, 200, 255);
            SDL_RenderFillRect(renderer, &itemRect);
        }

        // Draw Text
        SDL_Color textColor = { 255, 255, 255, 255 };
        SDL_Surface* textSurf = TTF_RenderText_Blended(font, items[i].text.c_str(), 0, textColor);

        if (textSurf) {
            SDL_Texture* textTex = SDL_CreateTextureFromSurface(renderer, textSurf);

            float textW = (float)textSurf->w;
            float textH = (float)textSurf->h;

            SDL_FRect destRect = { menuX + 10, itemRect.y + (itemHeight - textH) / 2.0f, textW, textH };

            SDL_RenderTexture(renderer, textTex, NULL, &destRect);

            SDL_DestroyTexture(textTex);
            SDL_DestroySurface(textSurf);
        }
    }
}