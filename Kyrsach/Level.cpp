#include "level.h"
#include <iostream>
#include "TinyXML/tinyxml.h"
#pragma warning(disable : 4996)
using namespace std;
using namespace sf;



bool Level::LoadFromFile(string filename)
{
	string path;
	path = filename.substr(0, filename.find_last_of('/') + 1);
	TiXmlDocument levelFile(filename.c_str());

	if (!levelFile.LoadFile())
	{
		cout << "Loading level "" << filename << "" failed." << endl;
		return false;
	}
	else
		cout << "Map loaded" << endl;

	TiXmlElement *map;
	map = levelFile.FirstChildElement("map");

	width = atoi(map->Attribute("width"));
	height = atoi(map->Attribute("height"));
	tileWidth = atoi(map->Attribute("tilewidth"));
	tileHeight = atoi(map->Attribute("tileheight"));

	TiXmlElement *tilesetElement;

	vector<vector<Rect<int>>> subRects;



	tilesetElement = map->FirstChildElement("tileset");

	while (tilesetElement != NULL)
	{
		firstTileID.push_back(atoi(tilesetElement->Attribute("firstgid")));

		TiXmlElement *image = tilesetElement->FirstChildElement("image");
		string imagepath = image->Attribute("source");


		Image img;
		if (!img.loadFromFile(path + imagepath))                       //добавить путь
		{
			cout << "Failed to load tile sheet." << endl;
			return false;
		}

		img.createMaskFromColor(Color(109, 159, 185));
		Texture tiles;
		tiles.loadFromImage(img);
		//tiles.setSmooth(false);
		tilesetImage.push_back(tiles);

		int columns = tiles.getSize().x / tileWidth;
		int rows = tiles.getSize().y / tileHeight;

		vector<Rect<int>> SubSubRects;

		for (int y = 0; y < rows; y++)
			for (int x = 0; x < columns; x++)
			{
				Rect<int> rect;

				rect.top = y * tileHeight;
				rect.height = tileHeight;
				rect.left = x * tileWidth;
				rect.width = tileWidth;

				SubSubRects.push_back(rect);
			}
		tilesetElement = tilesetElement->NextSiblingElement("tileset");
		subRects.push_back(SubSubRects);
	}

	TiXmlElement *layerElement;
	layerElement = map->FirstChildElement("layer");
	while (layerElement)
	{
		Layer layer;

		if (layerElement->Attribute("opacity") != NULL)
		{
			float opacity = (float)strtod(layerElement->Attribute("opacity"), NULL);
			layer.opacity = 255 * (int)opacity;
		}
		else
		{
			layer.opacity = 255;
		}

		TiXmlElement *layerDataElement;
		layerDataElement = layerElement->FirstChildElement("data");

		if (layerDataElement == NULL)
		{
			cout << "Bad map. No layer information found." << endl;
		}

		TiXmlElement *tileElement;
		tileElement = layerDataElement->FirstChildElement("tile");

		if (tileElement == NULL)
		{
			cout << "Bad map. No tile information found." << endl;
			return false;
		}

		int x = 0;
		int y = 0;

		while (tileElement)
		{
			if (tileElement->Attribute("gid") != NULL)
			{
				int tileGID = atoi(tileElement->Attribute("gid"));
				if (firstTileID.size() == 1)
				{
					int subRectToUse = tileGID - firstTileID[0];

					if (subRectToUse >= 0)
					{
						Sprite sprite;
						sprite.setTexture(tilesetImage[0]);
						sprite.setTextureRect(subRects[0][subRectToUse]);
						sprite.setPosition(x * (float)tileWidth, y * (float)tileHeight);
						sprite.setColor(Color(255, 255, 255, layer.opacity));

						layer.tiles.push_back(sprite);
					}
				}
				else
				{
					for (size_t i = 0; i < firstTileID.size(); i++)
					{
						if ((i == firstTileID.size() - 1))
						{
							int subRectToUse = tileGID - firstTileID[i];

							if (subRectToUse >= 0)
							{
								Sprite sprite;
								sprite.setTexture(tilesetImage[i]);
								sprite.setTextureRect(subRects[i][subRectToUse]);
								sprite.setPosition(x * (float)tileWidth, y * (float)tileHeight);
								sprite.setColor(Color(255, 255, 255, layer.opacity));

								layer.tiles.push_back(sprite);
							}
						}
						else if ((tileGID >= firstTileID[i] && tileGID < firstTileID[i + 1]))
						{
							int subRectToUse = tileGID - firstTileID[i];

							if (subRectToUse >= 0)
							{
								Sprite sprite;
								sprite.setTexture(tilesetImage[i]);
								sprite.setTextureRect(subRects[i][subRectToUse]);
								sprite.setPosition(x * (float)tileWidth, y * (float)tileHeight);
								sprite.setColor(Color(255, 255, 255, layer.opacity));

								layer.tiles.push_back(sprite);
							}
							break;
						}
					}
				}
			}



			tileElement = tileElement->NextSiblingElement("tile");

			x++;
			if (x >= width)
			{
				x = 0;
				y++;
				if (y >= height)
					y = 0;
			}
		}

		layers.push_back(layer);

		layerElement = layerElement->NextSiblingElement("layer");
	}


	MapTexture.create(width*tileWidth, height*tileHeight);

	for (unsigned int layer = 0; layer < layers.size(); layer++)
		for (unsigned int tile = 0; tile < layers[layer].tiles.size(); tile++)
			MapTexture.draw(layers[layer].tiles[tile]);
	MapTexture.display();
	MapSprite.setTexture(MapTexture.getTexture());

	TiXmlElement *objectGroupElement;

	if (map->FirstChildElement("objectgroup") != NULL)
	{
		objectGroupElement = map->FirstChildElement("objectgroup");
		while (objectGroupElement)
		{
			TiXmlElement *objectElement;
			objectElement = objectGroupElement->FirstChildElement("object");

			while (objectElement)
			{

				float x = atof(objectElement->Attribute("x"));
				float y = atof(objectElement->Attribute("y"));

				float width, height;
				b2BodyDef definition;


				if (objectElement->Attribute("width") != NULL)
				{
					width = atof(objectElement->Attribute("width"));
					height = atof(objectElement->Attribute("height"));
					b2PolygonShape shape;
					definition.position.Set((x + width / 2) / SCALE, (y + height / 2) / SCALE);
					shape.SetAsBox(width / 2 / SCALE, height / 2 / SCALE);
					b2Body *body = world->CreateBody(&definition);
					body->CreateFixture(&shape, 1);

				}
				else if (objectElement->FirstChildElement("polygon") != NULL)
				{
					TiXmlElement *Polygon = objectElement->FirstChildElement("polygon");
					const char *str = Polygon->Attribute("points");
					char *str2 = new char[255];
					strcpy(str2, str);
					int counter = 0;
					str2 = strtok(str2, " ");

					while (str2 != NULL)
					{
						str2 = strtok(NULL, " ");
						counter++;
					}
					delete[] str2;
					str2 = new char[255];

					strcpy(str2, str);
					b2Vec2 *points = new b2Vec2[counter];
					for (int i = 0; i < counter; i++)
					{
						points[i].x = x;
						points[i].y = y;
					}
					int i = 0;
					str2 = strtok(str2, " ,");
					while (str2 != NULL)
					{
						points[i].x += atoi(str2);
						str2 = strtok(NULL, " ,");
						points[i].y += atoi(str2);
						str2 = strtok(NULL, " ,");
						i++;
					}
					delete[] str2;
					for (int i = 0; i < counter; i++)
					{
						points[i].x /= SCALE;
						points[i].y /= SCALE;
					}
					b2PolygonShape shape;
					shape.Set(points, counter);
					b2Body *body = world->CreateBody(&definition);
					body->CreateFixture(&shape, 1);

					delete[] points;
				}
				else if (objectElement->FirstChildElement("point") != NULL)
				{
					EnemyCoordinats.push_back(sf::Vector2f(x, y));
				}
				objectElement = objectElement->NextSiblingElement("object");
			}
			objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
		}
	}
	else
	{
		cout << "No object layers found..." << endl;
	}



	return true;
}


Vector2i Level::GetTileSize()
{
	return Vector2i(tileWidth, tileHeight);
}

b2World * Level::GetWorld()
{
	return this->world;
}

Level::Level()
{

	world = new b2World(b2Vec2(0, 9.8));
}

Level::~Level()
{
	delete world;
}

void Level::DrawTiles(RenderWindow &window)
{
	for (unsigned int layer = 0; layer < layers.size(); layer++)
		for (unsigned int tile = 0; tile < layers[layer].tiles.size(); tile++)
			window.draw(layers[layer].tiles[tile]);
}

void Level::Draw(RenderWindow & window)
{
	window.draw(MapSprite);
}


#define DRAW

void Level::DrawTiles(RenderWindow & window, View & camera)
{

#ifdef DRAW

	/*Vector2f Center = camera.getCenter();
	Vector2f Size = camera.getSize();
	Size.x = 1600;
	Size.y = 1200;


	int x = (Center.x - Size.x / 2) / tileWidth;
	if (x < 0)
		x = 0;
	int y = (Center.y - Size.y / 2) / tileHeight;
	if (y < 0)
		y = 0;
	int rows = y + height;
	for (unsigned int layer = 0; layer < layers.size(); layer++)
		for (y; y < rows; y++)
		{
			int last = layers[layer].tiles.size();
			for (unsigned int tile = x + y * width; tile < width + x + y * width; tile++)
				if(tile<last)
				window.draw(layers[layer].tiles[tile]);
		}*/

	window.draw(MapSprite);


#else

	Vector2f Center = camera.getCenter();
	Vector2f Size = camera.getSize();

	Rect<int> cameraArea = Rect<int>(Center.x - Size.x / 2, Center.y - Size.y / 2, Size.x, Size.y);

	for (unsigned int layer = 0; layer < layers.size(); layer++)
		for (unsigned int tile = 0; tile < layers[layer].tiles.size(); tile++)
			if (layers[layer].tiles[tile].getTextureRect().intersects(cameraArea))
				window.draw(layers[layer].tiles[tile]);


#endif // DRAW

}

vector<Vector2f>* Level::GetEnemyVector()
{
	return &EnemyCoordinats;
}

FloatRect Level::GetViewRegion(View & camera)
{
	return sf::FloatRect(camera.getCenter().x - (camera.getSize().x / 2), camera.getCenter().y - (camera.getSize().y / 2), camera.getSize().x, camera.getSize().y);

}

