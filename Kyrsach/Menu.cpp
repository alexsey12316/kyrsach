#include "Menu.h"
#include "Level.h"
#include "Player.h"


#define WIDTH   900
#define HEIGHT  540

void Game(sf::RenderWindow & window)
{
	window.setFramerateLimit(70);
	Level lvl;
	lvl.LoadFromFile("maps/map2.tmx");
	b2World *world = lvl.GetWorld();
	Player p(world,150, 500);



	sf::View camera;
	camera.setSize(WIDTH, HEIGHT);



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
		world->Step(1 / 60.0f, 8, 3);
		p.Control();
		p.Update(time);
		p.SetCamera(camera);

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
