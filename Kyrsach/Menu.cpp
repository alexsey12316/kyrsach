#include "Menu.h"
#include "Level.h"
#include "Player.h"

void Game(sf::RenderWindow & window)
{
	window.setFramerateLimit(60);
	Level lvl;
	lvl.LoadFromFile("maps/test.tmx");
	std::vector<Object> objects;
	objects = lvl.GetAllObjects();

	Player p(150, 500);
	p.setObjects(objects);



	sf::View camera;
	camera.setSize(900, 540);
	double time;
	sf::Clock clock;
	while (window.isOpen())
	{
		time = clock.getElapsedTime().asSeconds();
		clock.restart();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		p.Control();
		p.Update(time);
		camera.setCenter(p.getPosition());


		window.setView(camera);
		window.clear();
		lvl.Draw(window);
		p.Draw(window);
		window.display();
	}

	

}










void CameraMovement(sf::View & camera)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) )
	{
		camera.move(0, -1);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) )
	{
		camera.move(0, 1);

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		camera.move( -1,0);

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		camera.move(1, 0);

	}


}
