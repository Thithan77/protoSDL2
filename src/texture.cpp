#include "texture.h"
Texture::Texture(SDL_Renderer* renderer, const char* path,int w,int h){
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
	SDL_Surface* surface{};
	SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_BLEND);
	surface = IMG_Load(path);
	uint32_t keyColor;
    // gets the proper color for white (255,255,255)
    keyColor = SDL_MapRGB(surface->format, 255, 255, 255);
    // enables transparency for all white pixels
    SDL_SetColorKey(surface, SDL_TRUE, keyColor);
	texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
}
Texture::~Texture(){
	
}
Texture::Texture(SDL_Texture* Mtexture){
	texture = Mtexture;
}