#include "Menu.h"

#include "Enemy.h"
#include "Player.h"
#include "Magic.h"

#include<list>
#include<Windows.h>
#include<ctime>

#define WIDTH   900
#define HEIGHT  540
//#define FRAMERATE  

void Game(sf::RenderWindow & window)
{
	srand(time(0));
	window.setFramerateLimit(70);
	sf::View camera;
	Level lvl;
	lvl.LoadFromFile("maps/map2.tmx");
	b2World *world = lvl.GetWorld();
	std::vector<sf::Vector2f> *enemyCoords = lvl.GetEnemyVector();

	std::list<Magic*> magic;

	Player p(world, enemyCoords->at(0).x, enemyCoords->at(0).y, camera);

	std::list<Enemy*> enemies;
	for (size_t i = 1; i < enemyCoords->size(); i++)
	{
		EnemyKnight_2* a = new EnemyKnight_2(world, enemyCoords->at(i).x, enemyCoords->at(i).y);

		enemies.push_back(a);
	}

	p.SetMagic(magic);


	camera.setSize(WIDTH, HEIGHT);



	double time;
	sf::Clock clock;
	while (window.isOpen())
	{
		//CameraMovement(camera);
#ifdef FRAMERATE
		system("cls");
#endif // FRAMERATE

		time = clock.restart().asSeconds();

#ifdef FRAMERATE
		std::cout << 1 / time << "\n";
#endif // FRAMERATE

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}



		world->Step(1 / 60.0f, 8, 3);
		p.Control();
		p.Ability();
		p.Update(time);
		p.SetCamera(camera);
		for (auto Iter = enemies.begin(), end = enemies.end(); Iter != end; )
		{
			if ((*Iter)->isDelete())
			{
				delete *Iter;
				Iter = enemies.erase(Iter);
			}
			else
			{
				(*Iter)->behavior(time);
				(*Iter)->Update(time);
				++Iter;
			}
		}


		for (auto MagicIter = magic.begin(), end = magic.end(); MagicIter != end; )
		{
			if ((*MagicIter)->isDestroy())
			{
				delete *MagicIter;
				MagicIter = magic.erase(MagicIter);
			}
			else
			{
				(*MagicIter)->UpDate(time);
				++MagicIter;
			}
		}


		window.setView(camera);
		window.clear();
		lvl.Draw(window);
		p.Draw(window);

		for (auto it : enemies)
		{
			it->Draw(window);
		}

		for (auto it : magic)
		{
			it->Draw(window);
		}
		window.display();
	}



}










void CameraMovement(sf::View & camera)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		camera.move(0, -5);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		camera.move(0, 5);

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		camera.move(-5, 0);

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		camera.move(5, 0);

	}


}
