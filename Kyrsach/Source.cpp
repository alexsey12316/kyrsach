#include<SFML/Graphics.hpp>

#include"Menu.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "kyrsach",sf::Style::Fullscreen);
	Game(window);
}