#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "texture.h"
#include "map.h"
class gameHandler{
public:
	virtual int handleEvents() = 0; // while events loop
	virtual void update() = 0; // update the game / Variables 
	virtual void draw() = 0; // draw everything on the screen
};
class Game{
public:
	Game(const char* windowname); // Constructor 
	~Game(); // Destructor
	int gameLoop(); // The main game loop
	void drawRect(int x,int y,int w, int h); // draw a non-filled rectangle
	void fillRect(int x,int y,int w, int h); // draw a filled rectangle
	void clearWindow(int r,int g,int b); // clear the window (paint this color on the whole screen)
	void setDrawColor(int r,int g,int b); // change renderer draw color
	Texture* createTexture(const char* path,int w,int h);
	void drawTexture(Texture* texture,SDL_Rect rect,const double angle = 0.0d);
	Map* createMap(const char* path);
private:
	SDL_Window *window;
	SDL_Renderer *renderer;
	bool gameRunning;
	gameHandler* handler;

};