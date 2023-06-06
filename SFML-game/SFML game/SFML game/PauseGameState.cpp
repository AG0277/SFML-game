#include "PauseGameState.h"

void PauseGameState::initfont()
{
	if (!font.loadFromFile("font/OptimusPrinceps.ttf"))
		std::cout << "ERROR::FAILED TO LOAD ARKANOID FONT\n";
}

void PauseGameState::initBackground()
{

	if (!worldBackgroundTexture.loadFromFile("Textures/PauseMenuBackground.png"))
		std::cout << "ERROR::FAILED TO LOAD TEXTURE BLOCK\n";
	worldBackgroud.setTexture(worldBackgroundTexture);
	this->worldBackgroud.scale(0.8f,0.8f);

}

void PauseGameState::DisplayScore()
{
	int wincharSize = 90;
	text.setFont(font);
	text.setCharacterSize(60);
	std::string string = "Score: ";
	std::string score = string + std::to_string(points);
	text.setString(score);
	text.setFillColor(sf::Color::White);
	winorlosetext.setFont(font);
	winorlosetext.setCharacterSize(wincharSize);
	std::string winorlose;
	if (!gameON)
		if (DidYouWin)
			winorlose = "You Won";
		else
			winorlose = "You lost";
	winorlosetext.setString(winorlose);
	winorlosetext.setPosition(this->window->getSize().x * 0.26, this->window->getSize().y / 10);
	text.setPosition(this->window->getSize().x * 0.3, this->window->getSize().y / 10 + wincharSize + 20);
}

PauseGameState::PauseGameState(sf::RenderWindow* window, sf::VideoMode videoMode, std::stack<States*>* states) :States(window, videoMode, states)
{
	this->initBackground();
	this->initfont();
	this->DisplayScore();
}

void PauseGameState::setEvent(sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			endState();
		}
	}
}


void PauseGameState::imguiGameON()
{
	float x = this->window->getSize().x / 2;
	float y = this->window->getSize().y *0.4;
	int buttonx = 400;
	int buttony = 100;
	if (gui->createButton("Back to Main Menu", buttonx, buttony, x - buttonx / 2, y))
	{
		while (!states->empty())
		{
			states->pop();
		}
		this->states->push(new MainMenu(this->window, this->videoMode, this->states));
	}
	if (gui->createButton("Leaderboard", buttonx, buttony, x - buttonx / 2, y + buttony))
		this->states->push(new LeaderboardState(this->window, this->videoMode, this->states));

	if (gui->createButton("Back to the game", buttonx, buttony, x - buttonx / 2, y + buttony * 2))
		endState();
}
void PauseGameState::imguiGameOFF()
{
	float x = this->window->getSize().x *0.5;
	float y = this->window->getSize().y * 0.5;
	int buttonx = 400;
	int buttony = 100;
	if (gui->createButton("Yes", buttonx/2, buttony, x - buttonx / 2, y))
		int z = 0;
	if (gui->createButton("No", buttonx/2, buttony, x, y ))
	{
		while (!states->empty())
		{
			states->pop();
		}
		this->states->push(new MainMenu(this->window, this->videoMode, this->states));
	}

	if (gui->createButton("Leaderboard", buttonx, buttony, x - buttonx / 2, y + buttony ))
	{
		this->states->push(new LeaderboardState(this->window, this->videoMode, this->states));
	}
}


void PauseGameState::update(const float& deltaTime, sf::Time& dt)
{

	ImGui::SFML::Update(*window, dt);
	if (gameON)
		imguiGameON();
	else
		imguiGameOFF();
}

void PauseGameState::render(sf::RenderTarget* target)
{
	window->draw(this->worldBackgroud);
	window->draw(this->text);
	window->draw(this->winorlosetext);
	ImGui::SFML::Render(*window);
}

