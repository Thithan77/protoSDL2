#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
class Texture{
public:
	Texture(SDL_Renderer* renderer,const char* path,int w,int h);
	Texture(SDL_Texture* Mtexture);
	~Texture();
	inline SDL_Texture* getTexture(){return texture;};
private:
	SDL_Texture* texture;
};