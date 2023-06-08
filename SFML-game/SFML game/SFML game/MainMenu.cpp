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
	displayNewGame = false;
}

void MainMenu::imgui()
{
	int x = this->window->getSize().x / 2;
	int y = this->window->getSize().y *3/5;
	int buttonx = 350;
	int buttony = 100;
	if (gui->createButton("New Game", buttonx, buttony, x - buttonx / 2, y))
		displayNewGame = true;

	if(gui->createButton("Leaderboard", buttonx, buttony, x - buttonx / 2, y + buttony))
		this->states->push(new LeaderboardState(this->window, this->videoMode, this->states));

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
	text.setPosition((float)this->window->getSize().x/20, (float)this->window->getSize().x / 3.5);
}

void MainMenu::selectDifficulty()
{
	int x = this->window->getSize().x / 2;
	int y = this->window->getSize().y * 3 / 5;
	int buttonx = 350;
	int buttony = 100;
	std::vector<float> green = { 0,0.9,0,255 };
	std::vector<float> orange = { 0.9,0.55,0,255 };
	std::vector<float> red = { 0.9,0,0,255 };
	if (gui->createButton("Easy", buttonx, buttony, x - buttonx / 2, y,green))
	{
		gameLevel = 0.8;
		this->states->push(new GameState(this->window, this->videoMode, this->states));
	}
	if (gui->createButton("Medium", buttonx, buttony, x - buttonx / 2, y + buttony,orange))
	{
		gameLevel = 1;
		this->states->push(new GameState(this->window, this->videoMode, this->states));
	}
	if (gui->createButton("Hard", buttonx, buttony, x - buttonx / 2, y + buttony * 2,red))
	{
		gameLevel = 1.2;
		this->states->push(new GameState(this->window, this->videoMode, this->states));
	}
}

void MainMenu::update(const float& deltaTime, sf::Time& dt)
{

	ImGui::SFML::Update(*window, dt);
	if (!displayNewGame)
		imgui();
	else
		selectDifficulty();
}

void MainMenu::render(sf::RenderTarget* target)
{
	window->draw(this->worldBackgroud);
	window->draw(this->text);
	ImGui::SFML::Render(*window);
}
