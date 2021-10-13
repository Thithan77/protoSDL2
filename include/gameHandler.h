#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "game.h"
#include <vector>
struct vec2float{
	float x;
	float y;
};
class mainHandler: public gameHandler{
public:
	mainHandler(Game* gameM);
	~mainHandler();
	int handleEvents();
	void update();
	void draw();
private:
	SDL_Event event;
	Game* game;
	Texture* perso;
	Texture* bullet;
	SDL_Point position;
	SDL_Point speed;
	std::vector<vec2float> bulletPositions;
	std::vector<vec2float> bulletVelocities;
	Map* map;
};