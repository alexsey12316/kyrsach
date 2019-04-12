#pragma once
#ifndef PROTECT
#define PROTECT
#include<TGUI/TGUI.hpp>
#include "Enemy.h"
#include "Player.h"
#include "Magic.h"
#include "InterFace.h"
#include<list>
#include<Windows.h>
#include<ctime>
#include<thread>
#include<mutex>

class GameEngine {
public:
	GameEngine();
	~GameEngine();
	enum State{menu,play,New,end};
	void mainLoop();
	void Menu();
	void Game();
	void Loading();


private:
	sf::RenderWindow window;
	int width, height;
	State state;
	sf::Texture menuTex;
	sf::Sprite menuSprite;
	Animation loading;
	bool load;
};




#endif //PROTECT