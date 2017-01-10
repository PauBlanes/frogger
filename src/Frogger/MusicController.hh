#pragma once

#include <SDL/SDL_mixer.h>

#define MC MusicController::Instance()


class MusicController {
public:
	inline static MusicController &Instance(void) {
		static MusicController musicController;
		return musicController;
	}
private:
	Mix_Music *music = NULL;

	Mix_Chunk *move = NULL;
};
