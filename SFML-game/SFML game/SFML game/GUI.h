#pragma once
#include "SFML/Graphics.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"
#include <iostream>
class GUI
{
private:
	float size;
	ImVec2 buttonSize;
	std::string username;
	std::string password;
	char ubuf[24];
	char pbuf[24];
	bool* p_open = NULL;
	sf::Window* window;

public:
	GUI(sf::Window* window);
	bool createButton(const char* text, float x, float y, float posx, float posy);
	void loginmenu();
};

