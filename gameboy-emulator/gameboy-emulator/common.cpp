#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

using namespace std;

#define BIT_GET(a, n) ((a & (1 << n)) ? 1 : 0)
#define BIT_SET(a, n, on) (on ? a |= (1 << n) : a &= ~(1 << n))
#define BETWEEN(a, b, c) ((a >= b) && (a <= c))

void delay(Uint32 ms) {
	return;
}