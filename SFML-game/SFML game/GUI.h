#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

class GUI
{
private:
	ImVec2 buttonSize;
	sf::Window* window;

public:
	GUI(sf::Window* window) { this->window = window; };
	bool createButton(const char* text, int x, int y, int posx, int posy,std::vector<float> color = { 0,0,0,255 }, std::vector<float> textColor = { 1,1,1,255 });
	sf::Text createText(const std::string& text, const sf::Font& font, unsigned int charsize, float poxY, float posX=0);
	void loginmenu();
};

