#pragma once
#include "SFML/Graphics.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"
#include <iostream>
class GUI
{
private:
	ImVec2 buttonSize;
	sf::Window* window;

	//float size;
	//std::string username;
	//std::string password;
	//char ubuf[24];
	//char pbuf[24];
	//bool* p_open = NULL;

public:
	GUI(sf::Window* window) { this->window = window; };
	bool createButton(const char* text, int x, int y, int posx, int posy,std::vector<float> color = { 0,0,0,255 });
	sf::Text createText(const std::string& text, const sf::Font& font, unsigned int charsize, float poxY, float posX=0);
	void loginmenu();
};

