#pragma once

#include <SDL.h>

struct context {
	bool running;
	bool paused;
	Uint64  ticks;
};