#include "Game.h"

// private functions


void Game::initWindow()
{
	this->videoMode = sf::VideoMode(735, 900);
	this->window = new sf::RenderWindow(videoMode, "Bricks Breaker", sf::Style::Titlebar | sf::Style::Close);
	this->window->setVerticalSyncEnabled(false);
	ImGui::SFML::Init(*window);
	window->setKeyRepeatEnabled(false);


	this->window->setFramerateLimit(120);
}

void Game::initStates()
{
	this->states.push(new MainMenu(this->window, this->videoMode, &this->states));
}


// constructor, destructor

Game::Game()
{
	initWindow();
	initStates();
}

Game::~Game()
{
	delete this->window;

	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}


void Game::updateDeltaTime()
{
	this->deltaTime = 1;
	this->dt = dtClock.restart();
	//this->deltaTime = this->dtClock.getElapsedTime().asSeconds();
	//std::cout << dtClock.restart().asSeconds() << std::endl;
}

const bool Game::running() const
{
	return this->window->isOpen();
}

bool Game::pollEvents()
{

	while (this->window->pollEvent(sfmlEvent))
	{
		ImGui::SFML::ProcessEvent(*window, sfmlEvent);
		if (sfmlEvent.type == sf::Event::Closed)
		{
			this->window->close();
			ImGui::SFML::Shutdown();
			exit(EXIT_SUCCESS);
		}
		
		this->states.top()->setEvent(sfmlEvent);
		//if (sfmlEvent.type == sf::Event::KeyPressed)
		//{
		//	this->states.top()->setEvent(sfmlEvent);
		//	//states.push(new PauseGameState(window, videoMode, &states));
		//	//int x = 5;
		//	//this->window->close();
		//	//ImGui::SFML::Shutdown();
		//	//exit(EXIT_SUCCESS);
		//}
		//if (sfmlEvent.type == sf::Event::mou)
		//{
		//	this->states.top()->setEvent(sfmlEvent);
		//}
	}
	return true;
}

bool Game::update()
{
	int j = 0;
	if (this->pollEvents())
	{
		if (this->window->hasFocus())
		{
			if (!this->states.empty())
			{
				this->states.top()->update(this->deltaTime, this->dt);
				if (j <= 0)
				{
					ImVec2 buttonPos(this->window->getSize().x + 200, this->window->getSize().y + 200);
					ImVec2 buttonPos1(0, 0);
					ImGui::SetWindowPos(buttonPos1);
					ImGui::SetNextWindowSize(buttonPos);
				}
				j=1;

				if (this->states.top()->getQuit())
				{
					this->states.top()->endState();
					delete this->states.top();
					this->states.pop();
				}
				std::cout << states.size();
			}
			else
				this->window->close();
		}
		return true;
	}
}

void Game::render()
{

	this->window->clear();
	if (!this->states.empty())
		this->states.top()->render(this->window);
	this->window->display();
}
