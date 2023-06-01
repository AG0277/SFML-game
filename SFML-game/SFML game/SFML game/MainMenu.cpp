#include "MainMenu.h"


void MainMenu::initfont()
{
	if (!font.loadFromFile("font/ARKANOID.ttf"))
		std::cout << "ERROR::FAILED TO LOAD ARKANOID FONT\n";
}

void MainMenu::initBackground()
{

	if (!worldBackgroundTexture.loadFromFile("Textures/MainMenuBackground.png"))
		std::cout << "ERROR::FAILED TO LOAD TEXTURE BLOCK\n";
	worldBackgroud.setTexture(worldBackgroundTexture);
	this->worldBackgroud.scale(1.2f, 1.2f);
}

MainMenu::MainMenu(sf::RenderWindow* window, sf::VideoMode videoMode, std::stack<States*>* states):States(window,videoMode,states)
{
	this->initBackground();
	this->initfont();
	this->gameTitle();
}

void MainMenu::imgui()
{
	float x = this->window->getSize().x / 2;
	float y = this->window->getSize().y *3/5;
	int buttonx = 350;
	int buttony = 100;
	if (gui->createButton("New Game", buttonx, buttony, x - buttonx / 2, y))
	{
		
		this->states->push(new GameState(this->window, this->videoMode, this->states));
	}
	gui->createButton("Leaderboard", buttonx, buttony, x - buttonx / 2, y + buttony);
	if (gui->createButton("Exit", buttonx, buttony, x - buttonx / 2, y + buttony * 2))
		endState();
}
void MainMenu::gameTitle()
{
	text.setFont(font);
	text.setCharacterSize(80);
	std::string string = "Bricks Breaker";
	text.setString(string);
	text.setFillColor(sf::Color::White);
	text.setPosition(this->window->getSize().x/20, this->window->getSize().x / 3.5);
}

void MainMenu::update(const float& deltaTime, sf::Time& dt)
{

	ImGui::SFML::Update(*window, dt);
	imgui();
}

void MainMenu::render(sf::RenderTarget* target)
{
	window->draw(this->worldBackgroud);
	window->draw(this->text);
	ImGui::SFML::Render(*window);
}
