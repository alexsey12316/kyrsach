#pragma once
#include<TGUI/TGUI.hpp>
#include"Player.h"
class InterFace
{
public:
	InterFace(sf::RenderWindow &window,Player& player);
	~InterFace();
	void UpDate();
	void draw();
	void setWin();

private:
	enum GameStage{start,win,dead,play};
	//int MaxHealth, MaxMana;
	Player *player;
	std::shared_ptr<tgui::ProgressBar> health_bar;
	std::shared_ptr<tgui::ProgressBar> mana_bar;
	std::shared_ptr<tgui::Picture> mana_pic;
	std::shared_ptr<tgui::Picture> health_pic;
	std::shared_ptr<tgui::Picture> death_pic;
	std::shared_ptr<tgui::Picture> start_pic;
	std::shared_ptr<tgui::Picture> win_pic;
	tgui::Gui gui;
	sf::Texture health_shell, mana_shell, health_line, mana_line,death_tex,start_tex,win_tex;
	GameStage stage;
};

