#include "Menu.h"


GameEngine::GameEngine()
	:width(1280), height(720)
{
	window.create(sf::VideoMode(width, height), "Game", sf::Style::Fullscreen);
	window.setFramerateLimit(70);
	state = State::menu;
	menuTex.loadFromFile("Menu/menu.png");
	menuSprite.setTexture(menuTex);
	load = 0;
	loading.setImage("Menu/loading.png");
	loading.setFrameSize(150, 150);
	loading.setPosition(1100, 560);
	loading.setSize(1, 24);
}

GameEngine::~GameEngine()
{
}

void GameEngine::mainLoop()
{
	while (window.isOpen())
	{
		switch (state)
		{
		case GameEngine::menu:
			Menu();
			break;
		case GameEngine::New:
			state = State::play;
		case GameEngine::play:
		{
			window.setActive(0);
			std::thread t([&]() {Loading(); });
			t.detach();
			Game();

			break;
		}
		case GameEngine::end:
			window.close();
		}
	}
}

void GameEngine::Menu()
{
	sf::View camera;
	camera.setSize(width, height);
	camera.setCenter(width / 2, height / 2);

	sf::Font font;
	font.loadFromFile("Menu/font.ttf");
	sf::String str;
	tgui::Gui gui(window);
	sf::Texture arrTexture[4];
	for (int i = 0; i < 4; i++)
	{
		arrTexture[i].loadFromFile("Menu/button" + std::to_string(i + 1) + ".png");
	}
	std::shared_ptr<tgui::Button> end = tgui::Button::create();
	end->setSize(272, 36);
	end->setPosition("39.5%", "55%");
	tgui::Borders b;
	b.updateParentSize(tgui::Vector2f(0, 0));
	gui.add(end);
	end->getRenderer()->setBorders(b);
	end->getRenderer()->setTexture(arrTexture[0]);
	end->getRenderer()->setTextureHover(arrTexture[1]);
	end->getRenderer()->setTextureDown(arrTexture[3]);
	end->getRenderer()->setFont(font);
	end->getRenderer()->setTextColor(sf::Color::Yellow);
	std::shared_ptr<tgui::Button> start = tgui::Button::create();
	start = start->copy(end);
	start->setPosition("39.5%", "45%");
	gui.add(start);

	start->showWithEffect(tgui::ShowAnimationType::SlideFromTop, sf::seconds(1));
	end->showWithEffect(tgui::ShowAnimationType::SlideFromBottom, sf::seconds(1));
	str = "Play";
	start->setTextSize(30);
	start->setText(str);
	str = "Exit";
	end->setTextSize(30);
	end->setText(str);

	end->connect("pressed", [&]() {state = State::end; });
	start->connect("pressed", [&]() {state = State::play;});

	while (state == State::menu)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			gui.handleEvent(event);
		}
		load = 0;
		window.setView(camera);
		window.clear();
		window.draw(menuSprite);
		gui.draw();
		window.display();

	}

}

void GameEngine::Game()
{
	srand(time(0));
	sf::View camera;
	Level lvl;
	lvl.LoadFromFile("maps/dungeon/dungeon.tmx");
	b2World *world = lvl.GetWorld();
	std::vector<sf::Vector2f> *enemyCoords = lvl.GetEnemyVector();

	std::list<Magic*> magic;

	Player p(world, enemyCoords->at(0).x, enemyCoords->at(0).y, camera);
	InterFace interFace(window, p);
	std::list<Enemy*> enemies;
	for (size_t i = 1; i < enemyCoords->size(); i++)
	{
		EnemyKnight_2* a = new EnemyKnight_2(world, enemyCoords->at(i).x, enemyCoords->at(i).y);

		enemies.push_back(a);
	}

	p.SetMagic(magic);
	camera.setSize(width, height);

	double time;
	sf::Clock clock;
	bool isPause = 0;
	tgui::Gui gui(window);

	while (state == State::play)
	{

		time = clock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event))
		{
			//if (event.type == sf::Event::KeyReleased)
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				isPause = 1;
				sf::Texture texture;
				sf::Vector2u windowSize = window.getSize();
				texture.create(windowSize.x, windowSize.y);
				sf::Vector2f tempCam;
				tempCam.x = camera.getCenter().x;
				tempCam.y = camera.getCenter().y;
				camera.setCenter(width / 2, height / 2);
				window.setView(camera);
				camera.setCenter(tempCam);
				texture.update(window);
				sf::Sprite sprite(texture);

				sf::Font font;
				font.loadFromFile("Menu/font.ttf");
				sf::String str;
				tgui::Gui gui2(window);
				sf::Texture arrTexture[4];
				for (int i = 0; i < 4; i++)
				{
					arrTexture[i].loadFromFile("Menu/button" + std::to_string(i + 1) + ".png");
				}
				std::shared_ptr<tgui::Button> end = tgui::Button::create();
				end->setSize(272, 36);
				end->setPosition("39.5%", "60%");
				tgui::Borders b;
				b.updateParentSize(tgui::Vector2f(0, 0));
				gui2.add(end);
				end->getRenderer()->setBorders(b);
				end->getRenderer()->setTexture(arrTexture[0]);
				end->getRenderer()->setTextureHover(arrTexture[1]);
				end->getRenderer()->setTextureDown(arrTexture[3]);
				end->getRenderer()->setFont(font);
				end->getRenderer()->setTextColor(sf::Color::Yellow);
				std::shared_ptr<tgui::Button> contin = tgui::Button::create();
				contin = contin->copy(end);
				contin->setPosition("39.5%", "40%");
				gui2.add(contin);
				str = "Continue";
				contin->setTextSize(30);
				contin->setText(str);
				str = "Exit";
				end->setTextSize(30);
				end->setText(str);
				std::shared_ptr<tgui::Button> restart = tgui::Button::create();
				restart = restart->copy(end);
				str = "Restart";
				restart->setTextSize(30);
				restart->setText(str);
				restart->setPosition("39.5%", "50%");
				gui2.add(restart);

				restart->connect("pressed", [&]() {state = State::New; isPause = 0; });
				end->connect("pressed", [&]() {state = State::menu; isPause = 0; });
				contin->connect("pressed", [&]() {isPause = 0; });

				contin->showWithEffect(tgui::ShowAnimationType::Fade, sf::seconds(1));
				end->showWithEffect(tgui::ShowAnimationType::Fade, sf::seconds(1));
				restart->showWithEffect(tgui::ShowAnimationType::Fade, sf::seconds(1));
				sf::Clock timer;
				while (isPause)
				{
					sf::Event event2;
					while (window.pollEvent(event2))
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)&&timer.getElapsedTime().asSeconds()>0.7)
							isPause = 0;
						gui2.handleEvent(event2);

					}
					load = 0;
					window.clear();
					window.draw(sprite);
					gui2.draw();
					window.display();
				}
			}
		}

		world->Step(1 / 60.0f, 8, 3);
		if (enemies.size() > 0)
		{
			p.Control();
			p.Ability();
		}
		p.Update(time);
		if (p.isDead() || enemies.size() == 0)
		{
			if (!isPause)
			{

				sf::Font font;
				font.loadFromFile("Menu/font.ttf");
				sf::String str;
				sf::Texture arrTexture[4];
				for (int i = 0; i < 4; i++)
				{
					arrTexture[i].loadFromFile("Menu/button" + std::to_string(i + 1) + ".png");
				}
				std::shared_ptr<tgui::Button> end = tgui::Button::create();
				end->setSize(272, 36);
				end->setPosition("39.5%", "65%");
				tgui::Borders b;
				b.updateParentSize(tgui::Vector2f(0, 0));
				gui.add(end);
				end->getRenderer()->setBorders(b);
				end->getRenderer()->setTexture(arrTexture[0]);
				end->getRenderer()->setTextureHover(arrTexture[1]);
				end->getRenderer()->setTextureDown(arrTexture[3]);
				end->getRenderer()->setFont(font);
				end->getRenderer()->setTextColor(sf::Color::Yellow);
				str = "Exit";
				end->setText(str);
				end->setTextSize(30);

				std::shared_ptr<tgui::Button> restart = tgui::Button::create();
				restart = restart->copy(end);
				str = "Restart";
				restart->setText(str);
				restart->setPosition("39.5%", "30%");
				gui.add(restart);
				if (enemies.size() == 0)
				{
					interFace.setWin();
				}
				restart->showWithEffect(tgui::ShowAnimationType::Fade, sf::seconds(5));
				end->showWithEffect(tgui::ShowAnimationType::Fade, sf::seconds(5));
				restart->connect("pressed", [&]() {state = State::New; isPause = 0; });
				end->connect("pressed", [&]() {state = State::menu; isPause = 0; });

			}


			isPause = 1;
			gui.handleEvent(event);
		}

		if (load)
		{
			load = 0;
		}
		p.SetCamera(camera);
		lvl.SetCavera(camera);
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
		interFace.UpDate();

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
		interFace.draw();
		gui.draw();
		window.display();
	}

}



void GameEngine::Loading()
{
	std::mutex protect;
	double time;
	sf::Clock clock;
	loading.setAnimation(0, Animation::AnimationType::loop);
	protect.lock();
	load = 1;
	sf::View camera;
	camera.setCenter(width / 2, height / 2);
	camera.setSize(width , height );
	window.setView(camera);
	while (load)
	{
		time = clock.restart().asSeconds();
		loading.Animate(15*time);

		window.clear();
		window.draw(menuSprite);
		loading.draw(window);
		window.display();
	}
	window.setActive(0);
	protect.unlock();
}
