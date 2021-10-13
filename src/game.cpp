#include "game.h"
#include "gameHandler.h"
#define LOG(x) std::cout << "[LOG]" << x << std::endl;
Game::Game(const char* windowname){
	window = SDL_CreateWindow(windowname,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1080,720,SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	gameRunning = true;
	handler = new mainHandler(this);
}
Game::~Game(){
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	delete handler;
}
int Game::gameLoop(){
	while(gameRunning){
		int res = handler->handleEvents();
		if(res == -1){
			gameRunning = false;
		}
		handler->update();
		handler->draw();
		SDL_RenderPresent(renderer);
	}
	return 0;
}
void Game::drawRect(int x,int y,int w, int h){
	SDL_Rect rect{x,y,w,h};
	SDL_RenderFillRect(renderer,&rect);
}
void Game::fillRect(int x,int y,int w, int h){
	SDL_Rect rect{x,y,w,h};
	SDL_RenderFillRect(renderer,&rect);
}
void Game::clearWindow(int r,int g,int b){
	SDL_SetRenderDrawColor(renderer,r,g,b,255);
	SDL_RenderClear(renderer);
}
void Game::setDrawColor(int r,int g,int b){
	SDL_SetRenderDrawColor(renderer,r,g,b,255);
}
Texture* Game::createTexture(const char* path,int w,int h){
	Texture* texture = new Texture(renderer,path,w,h);
	return texture;
}
void Game::drawTexture(Texture* texture,SDL_Rect rect,const double angle){
	SDL_RenderCopyEx(renderer, texture->getTexture(), nullptr, &rect,angle,NULL,SDL_FLIP_NONE);
}
Map* Game::createMap(const char* path){
	Map* map = new Map(path,renderer);
	return map;
}