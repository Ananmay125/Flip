#include "input.h"
#include <iostream>
void InputHandler::secret(SDL_Keycode key, void(*changeAnim)(const char*)) {
	if (check1 && key == SDLK_7) {
		SDL_Log("1: Seven pressed");
		check1 = false; check2 = true;
	}
	else if (check2) {
		if (key == SDLK_1) {
			SDL_Log("2: One pressed");
			check2 = false; check3 = true;
		}
		else {
			SDL_Log("Reseted boi");
			check1 = true; check2 = false;
		}
	}

	else if (check3) {
		if (key == SDLK_3)
		{
			check3 = false;
			check4 = true;
		}
		else
		{
			check1 = true;
			check3 = false;
		}
	}

	else if (check4) {
		if (key == SDLK_0)
		{
			SDL_Log("4 checks done");
			check4 = false;
			check5 = true;
		}
		else
		{
			check1 = true;
			check4 = false;
		}
	}

	else if (check5) {
		if (key == SDLK_6)
		{
			SDL_Log("5 checks done");
			currentGif = "resources/Secret/p3.gif";
			isSecret();
			changeAnim(currentGif);
			check5 = false;
			check1 = true;
		}
		else
		{
			check1 = true;
			check5 = false;
		}
	}
}