#include "gameHandler.h"
#include <iostream>
#include <math.h>
int mainHandler::handleEvents(){
	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_QUIT:
				return -1;
			case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_z:
							speed.y = -3;
							break;
						case SDLK_s:
							speed.y = 3;
							break;
						case SDLK_q:
							speed.x = -3;
							break;
						case SDLK_d:
							speed.x = 3;
							break;
					}
				break;
			case SDL_KEYUP:
					switch(event.key.keysym.sym){
						case SDLK_z:
							speed.y = 0;
							break;
						case SDLK_s:
							speed.y = 0;
							break;
						case SDLK_q:
							speed.x = 0;
							break;
						case SDLK_d:
							speed.x = 0;
							break;
					}
				break;
			case SDL_MOUSEBUTTONDOWN:
				int dx = event.button.x - 1080/2;
				int dy = event.button.y - 720/2;
				float h = sqrt(pow(dx,2)+pow(dy,2));
				bulletPositions.push_back({(float)position.x,(float)position.y});
				bulletVelocities.push_back({dx/h*10,dy/h*10});
		}
	}
	return 0;
}
void mainHandler::update(){
	position.x += speed.x;
	position.y += speed.y;
	for(int i = 0;i< bulletPositions.size();i++){
		bulletPositions[i].x += bulletVelocities[i].x;
		bulletPositions[i].y += bulletVelocities[i].y;
	}
}
void mainHandler::draw(){
	game->clearWindow(51,51,51);
	/*
	SDL_Rect re{position.x,position.y,32,32};
	Texture te = map->getTexture(470);
	game->drawTexture(&te,re);
	*/
	int width = 1080/2;
	int height = 720/2;
	for(int i = position.x-(width)-32;i < position.x+(width)+32;i+=32){
		for(int j = position.y-(height)-32;j < position.y+(height)+32;j+=32){
			Texture te = map->getTexture(0,i/32-1,j/32-1);
			SDL_Rect rect{(i/32)*32-position.x+width,(j/32)*32-position.y+height,32,32};
			game->drawTexture(&te,rect);
			Texture te2 = map->getTexture(1,i/32-1,j/32-1);
			game->drawTexture(&te2,rect);
	}
	}
	SDL_Rect rect{width-16,height-16,32,32};
	game->drawTexture(perso,rect);
	for(int i = 0;i< bulletPositions.size();i++){
		rect = {(int)bulletPositions[i].x-4-position.x+width,(int)bulletPositions[i].y-4-position.y+height,16,16};
		game->drawTexture(bullet,rect);
	}
}
mainHandler::mainHandler(Game* gameM){
	game = gameM;
	perso = game->createTexture("res/chapo.png",16,16);
	bullet = game->createTexture("res/bullet.png",8,8);
	position = {32,32};
	speed = {0,0};
	map = game->createMap("res/map.json");
	
}
mainHandler::~mainHandler(){
	delete perso;
}