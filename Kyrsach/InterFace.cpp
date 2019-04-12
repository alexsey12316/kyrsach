#include "InterFace.h"


InterFace::InterFace(sf::RenderWindow & window, Player&player)
{
	gui.setTarget(window);
	this->player = &player;
	health_line.loadFromFile("Menu/health.png");
	mana_line.loadFromFile("Menu/mana.png");
	health_shell.loadFromFile("Menu/health_bar.png");
	mana_shell.loadFromFile("Menu/mana_bar.png");
	death_tex.loadFromFile("Menu/you_died1.png");
	win_tex.loadFromFile("Menu/you_win.png");


	health_pic = tgui::Picture::create();
	mana_pic = tgui::Picture::create();
	health_pic->getRenderer()->setTexture(health_shell);
	mana_pic->getRenderer()->setTexture(mana_shell);
	mana_pic->setPosition(0, 100);

	health_bar = tgui::ProgressBar::create();
	mana_bar = tgui::ProgressBar::create();
	health_bar->getRenderer()->setBackgroundColor(sf::Color::Black);
	mana_bar->getRenderer()->setBackgroundColor(sf::Color::Black);
	health_bar->getRenderer()->setTextureFill(health_line);
	mana_bar->getRenderer()->setTextureFill(mana_line);
	health_bar->setSize(310, 38);
	mana_bar->setSize(310, 38);
	health_bar->setPosition(93, 30);
	mana_bar->setPosition(93, 130);

	health_bar->setMinimum(0);
	health_bar->setMaximum(this->player->getMaxHealth());
	health_bar->setValue(this->player->getHealth());

	mana_bar->setMinimum(0);
	mana_bar->setMaximum(this->player->getMaxMana());
	mana_bar->setValue(this->player->getMana());

	death_pic = tgui::Picture::create();
	death_pic->getRenderer()->setTexture(death_tex);
	death_pic->hideWithEffect(tgui::ShowAnimationType::Fade, sf::seconds(0));

	start_tex.loadFromFile("start.png");
	start_pic = tgui::Picture::create();
	start_pic->getRenderer()->setTexture(start_tex);
	//start_pic->hideWithEffect(tgui::ShowAnimationType::SlideToRight, sf::seconds(5));
	win_pic = tgui::Picture::create();
	win_pic->getRenderer()->setTexture(win_tex);
	win_pic->hideWithEffect(tgui::ShowAnimationType::Fade, sf::seconds(0));

	gui.add(win_pic);
	gui.add(health_bar);
	gui.add(mana_bar);
	gui.add(health_pic);
	gui.add(mana_pic);
	gui.add(start_pic);
	gui.add(death_pic);
	stage = GameStage::start;
}

InterFace::~InterFace()
{
}

void InterFace::UpDate()
{
	health_bar->setValue(player->getHealth());
	mana_bar->setValue(player->getMana());
	if (stage == GameStage::start)
	{
		start_pic->hideWithEffect(tgui::ShowAnimationType::SlideFromBottom, sf::seconds(15));
		stage = GameStage::play;

	}
	if (player->isDead() && stage != GameStage::dead)
	{
		stage = GameStage::dead;
		death_pic->showWithEffect(tgui::ShowAnimationType::Fade, sf::seconds(5));

	
	}
}

void InterFace::draw()
{
	gui.draw();
}

void InterFace::setWin()
{
	win_pic->showWithEffect(tgui::ShowAnimationType::Fade, sf::seconds(5));
}
