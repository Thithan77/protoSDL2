#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "texture.h"
#include <vector>
class Map{
public:
	Map(const char* filepath,SDL_Renderer* renderer);
	~Map();
	inline Texture getTexture(int n){return textures[n];};
	Texture getTexture(int level,int x,int y);

private:
	std::vector<Texture> textures;
	std::vector<int> tabI;
	std::vector<int> tabI2;
	int mapWidth;
	int mapHeight;
};