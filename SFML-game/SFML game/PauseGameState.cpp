#include "pch.h"
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
	std::string string = "Score: ";
	std::string score = string + std::to_string(points);
	std::string winorlose;

	if (!gameON)
		if (DidYouWin)
			winorlose = "You Won";
		else
			winorlose = "You lost";

	winorlosetext=gui->createText(winorlose, font, 90, (float)this->window->getSize().y / 10);
	text = gui->createText(score, font, 60, (float)this->window->getSize().y / 10 + 100);
}

PauseGameState::PauseGameState(sf::RenderWindow* window, sf::VideoMode videoMode, std::stack<States*>* states) :States(window, videoMode, states)
{
	this->initBackground();
	this->initfont();
	this->DisplayScore();
	this->playerInputSize = 50;
	if (!gameON)
		playerDecision = gui->createText("Would you like to\n save your score", font, 50, text.getPosition().y + 200);
	YesNoInput = true;
}

void PauseGameState::setEvent(sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed && gameON == true)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			endState();
		}
	}
	else if (event.type == sf::Event::KeyPressed && gameON == false)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			YesNoInput = true;
		}
	}

	if (event.type == sf::Event::TextEntered && event.text.unicode == '\b')
	{
		if(playerInput.size()>0)
		{
			playerInput.pop_back();
			playerText.setString(playerInput);
			playerText.setPosition(this->window->getSize().x / 2 - playerText.getGlobalBounds().width / 2, playerText.getPosition().y);
		}
	}
	else if (event.type == sf::Event::TextEntered && event.text.unicode == 13 && playerInput.size()>0)
	{
		std::string temp = playerInput.substr(10, playerInput.size());
		writeScore(points,temp );
		while (!states->empty())
		{
			states->pop();
		}
		this->states->push(new MainMenu(this->window, this->videoMode, this->states));
	}
	else if (event.type == sf::Event::TextEntered && ((event.text.unicode>=48 && event.text.unicode<=57 )|| event.text.unicode ==32|| (event.text.unicode >= 65 && event.text.unicode <= 90) || (event.text.unicode >= 97 && event.text.unicode <= 122)))
	{
		if (playerInput.size() < 26)
		{
			playerInput += static_cast<char>(event.text.unicode);
			playerText.setString(playerInput);
			playerText.setPosition((float)this->window->getSize().x / 2 - playerText.getGlobalBounds().width / 2, playerText.getPosition().y);
		}
	}
}

void PauseGameState::imguiGameON()
{
	int x = (int) this->window->getSize().x / 2;
	int y = (int) this->window->getSize().y *0.4;
	int buttonx = 400;
	int buttony = 100;
	if (gui->createButton("Back to Main Menu", buttonx, buttony, x - buttonx / 2, y))
	{
		while (!states->empty())
		{
			states->pop();
		}
		points = 0;
		this->states->push(new MainMenu(this->window, this->videoMode, this->states));
	}
	if (gui->createButton("Leaderboard", buttonx, buttony, x - buttonx / 2, y + buttony))
		this->states->push(new LeaderboardState(this->window, this->videoMode, this->states));

	if (gui->createButton("Back to the game", buttonx, buttony, x - buttonx / 2, y + buttony * 2))
		endState();
}

void PauseGameState::imguiGameOFF()
{
	int x = (int)this->window->getSize().x * 0.5;
	int y = (int)this->window->getSize().y * 0.6;
	int buttonx = 400;
	int buttony = 100;
	if (YesNoInput)
	{
		if (gui->createButton("Yes", buttonx / 2, buttony, x - buttonx / 2, y))
		{
			playerInput = "Nickname: ";
			playerText = gui->createText(playerInput, font, playerInputSize, y * 0.8);
			YesNoInput = false;
		}
		if (gui->createButton("No", buttonx / 2, buttony, x, y))
		{
			while (!states->empty())
			{
				states->pop();
			}
			points = 0;
			this->states->push(new MainMenu(this->window, this->videoMode, this->states));
		}

		if (gui->createButton("Leaderboard", buttonx, buttony, x - buttonx / 2, y + buttony))
		{
			this->states->push(new LeaderboardState(this->window, this->videoMode, this->states));
		}
	}
	else
	{
		playerText.setPosition(x - playerText.getGlobalBounds().width / 2,y*0.5);
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
	if (!YesNoInput)
		window->draw(this->playerText);
	if (YesNoInput)
		window->draw(this->playerDecision);
	ImGui::SFML::Render(*window);
}

