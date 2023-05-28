#include "PauseGameState.h"

void PauseGameState::initBackground()
{

	if (!worldBackgroundTexture.loadFromFile("Textures/test.png"))
		std::cout << "ERROR::FAILED TO LOAD TEXTURE BLOCK\n";
	worldBackgroud.setTexture(worldBackgroundTexture);
	this->worldBackgroud.scale(1.2f, 1.2f);

}

PauseGameState::PauseGameState(sf::RenderWindow* window, sf::VideoMode videoMode, std::stack<States*>* states) :States(window, videoMode, states)
{
	this->initBackground();
}

void PauseGameState::setEvent(sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	if (event.key.code == sf::Keyboard::Escape)
	{
		endState();
	}
}


void PauseGameState::imgui()
{
	float x = this->window->getSize().x / 2;
	float y = this->window->getSize().y * 3 / 5;
	int buttonx = 250;
	int buttony = 50;
	if (gui->createButton("Back to Main Menu", buttonx, buttony, x - buttonx / 2, y))
	{
		int s = 0;
		while (!states->empty())
		{
			states->pop();
		}
		this->states->push(new MainMenu(this->window, this->videoMode, this->states));
	}
	gui->createButton("Leaderboard", buttonx, buttony, x - buttonx / 2, y + buttony);
	if (gui->createButton("Back to the game", buttonx, buttony, x - buttonx / 2, y + buttony * 2))
		endState();
}
void PauseGameState::update(const float& deltaTime, sf::Time& dt)
{

	ImGui::SFML::Update(*window, dt);
	imgui();
}

void PauseGameState::render(sf::RenderTarget* target)
{
	window->draw(this->worldBackgroud);
	ImGui::SFML::Render(*window);
}

