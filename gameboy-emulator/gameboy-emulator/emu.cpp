#pragma once

#include "common.cpp"	
#include "bus.cpp"
#include "cart.cpp"
#include "cpu.cpp"
#include "ctx.cpp"
#include "ppu.cpp"
#include "timer.cpp"

static context ctx;

context* get_context() {
	return &ctx;
}

void delay(Uint32 ms) {
	SDL_Delay(ms);
}

int emulator(int argc, char** argv) {
	if (argc < 2) {
		printf("No cartridge file given.");
		return -1;
	}
	if (!cart_load(argv[1])) {
		printf("Failed to load cartridge.");
	}
	printf("Cartridge loaded.");

	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	cpu_init();

	ctx.running = true;
	ctx.paused = false;
	ctx.ticks = 0;

	while(ctx.running) {
		if (ctx.paused) {
			delay(10);
			continue;
		}

		if (!cpu_step()) {
			printf("CPU stoped");
			return -3;
		}

		ctx.ticks++;
	}
	printf("Game not running anymore");
	return 0;
}