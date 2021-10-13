#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "game.h"
#define LOG(x) std::cout << "[LOG]" << x << std::endl;
using namespace std;

int main(int argc,char* argv[]){
	LOG("Lancement du prototype");
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	Game game("Prototype de jeu");
	game.gameLoop();
	SDL_Quit();
	return 0;
}