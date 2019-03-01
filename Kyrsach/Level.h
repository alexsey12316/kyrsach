#ifndef LEVEL_H
#define LEVEL_H

#pragma comment(lib,"sfml-graphics.lib")
#pragma comment(lib,"sfml-window.lib")
#pragma comment(lib,"sfml-system.lib")

#include <string>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include"Box2D/Box2D.h"

using namespace std;
using namespace sf;

const float SCALE = 30.0f;
const float DEG = 57.29577f;

struct Layer
{
	int opacity;
	vector<Sprite> tiles;
};

class Level
{
public:
	bool LoadFromFile(string filename);
	void DrawTiles(RenderWindow &window);
	void Draw(RenderWindow &window);
	void DrawTiles(RenderWindow &window,View &camera);
	FloatRect GetViewRegion(View &camera);
	Vector2i GetTileSize();
	b2World * GetWorld();
	Level();
	~Level();
	

	
	


private:
	
	int width, height, tileWidth, tileHeight;
	Rect<float> drawingBounds;
	vector<Layer> layers;
	b2World *world;
	RenderTexture MapTexture;
	Sprite MapSprite;
	vector<Texture> tilesetImage;

	vector<int> firstTileID;
};

#endif
