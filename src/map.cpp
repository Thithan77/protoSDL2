#include <fstream>
#include <iostream>
#include "map.h"
#include <string>
#include "texture.h"
#define LOG(x) std::cout << "[LOG]" << x << std::endl;
using namespace std;
Map::Map(const char* filepath,SDL_Renderer* renderer){
	string file;
	string line;
	LOG("Loading file " + (string)filepath)
	ifstream myfile (filepath);
	if (myfile.is_open()){
		while(getline(myfile,line)){
			file += line;
		}
			myfile.close();
			rapidjson::Document d;
			d.Parse(file.c_str());
			int width = d["width"].GetInt();
			int height = d["height"].GetInt();
			const string tilesetpath = (string)"res/" + d["tilesets"].GetArray()[0]["source"].GetString();
			cout << tilesetpath << endl;
			string filetile;
			string linetile;
			ifstream myfile (tilesetpath.c_str());
			if (myfile.is_open()){
			while(getline(myfile,linetile)){
				filetile += linetile;
			}
				myfile.close();
				rapidjson::Document e;
				e.Parse(filetile.c_str());
				int columns = e["columns"].GetInt();
				int tilecount = e["tilecount"].GetInt();
				int imagewidth = e["imagewidth"].GetInt();
				int imageheight = e["imageheight"].GetInt();
				string imagepath = (string)"res/" + e["image"].GetString();
				
				SDL_Texture* texture;
				texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, imagewidth, imageheight);
				SDL_Surface* surface{};
				SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_BLEND);
				cout << imagepath.c_str() << endl;
				surface = IMG_Load(imagepath.c_str());
				uint32_t keyColor;
			    // gets the proper color for white (255,255,255)
			    keyColor = SDL_MapRGB(surface->format, 255, 255, 255);
			    // enables transparency for all white pixels
			    SDL_SetColorKey(surface, SDL_TRUE, keyColor);
				texture = SDL_CreateTextureFromSurface(renderer,surface);
				SDL_FreeSurface(surface);
				
				SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
				for(int i = 0;i < tilecount;i++){
					SDL_Texture* texturemini = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 32, 32);
					SDL_SetTextureBlendMode(texturemini, SDL_BLENDMODE_BLEND);
					SDL_SetRenderTarget(renderer, texturemini);
					SDL_Rect rect{i%columns*32,i/columns*32,32,32};
					SDL_RenderCopy(renderer, texture, &rect, NULL);
					Texture text{texturemini};
					textures.push_back(text);
					//cout << i%columns << "-" ;
					//cout << i/columns << "-" ;
				}
				SDL_SetRenderTarget(renderer, NULL);
				cout << textures.size() << " textures loaded ! "<< endl;
			}
			else cout << "Unable to open file";
			mapWidth = d["layers"].GetArray()[0]["width"].GetInt();
			mapHeight = d["layers"].GetArray()[0]["height"].GetInt();
			const rapidjson::Value& tab = d["layers"].GetArray()[0]["data"];
			for (rapidjson::SizeType i = 0; i < tab.Size(); i++) // Uses SizeType instead of size_t
       			tabI.push_back(tab[i].GetInt());
       		const rapidjson::Value& tab2 = d["layers"].GetArray()[1]["data"];
       		for (rapidjson::SizeType i = 0; i < tab2.Size(); i++) // Uses SizeType instead of size_t
       			tabI2.push_back(tab2[i].GetInt());
		}
	else cout << "Unable to open file"; 
}
Map::~Map(){
	
}
Texture Map::getTexture(int level,int x,int y){
	if(x >= 0 && y >= 0){
		if(level == 0){
		int a = tabI[y*(mapWidth)+x];
		return textures[a-1];
	}else if(level == 1){
		int a = tabI2[y*(mapWidth)+x];
		if(a == 0){return textures[156];}
		return textures[a-1];
	}else{
		return textures[0];
	}
	}else{
		return textures[0];
	}
}


