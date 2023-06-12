#include "MainMenu.h"


void MainMenu::initfont()
{
	if (!font.loadFromFile("font/ARKANOID.ttf"))
		std::cout << "ERROR::FAILED TO LOAD ARKANOID FONT\n";
	if (!fontOptimus.loadFromFile("font/OptimusPrinceps.ttf"))
		std::cout << "ERROR::FAILED TO LOAD ARKANOID FONT\n";
}

void MainMenu::initTexturesAndSprites()
{

	if (!worldBackgroundTexture.loadFromFile("Textures/MainMenuBackground.png"))
		std::cout << "ERROR::FAILED TO LOAD TEXTURE BLOCK\n";
	else
	{
		worldBackgroud.setTexture(worldBackgroundTexture);
		this->worldBackgroud.scale(1.2f, 1.2f);
	}

	if (!textureBall.loadFromFile("Textures/ball2.png"))
		std::cout << "ERROR::FAILED TO LOAD TEXTURE BLOCK\n";
	else
	{
		spriteBall.setTexture(textureBall);
		this->spriteBall.scale(0.32f, 0.32f);
	}

	if (!textureBlock.loadFromFile("Textures/Grey200.png"))
		std::cout << "ERROR::FAILED TO LOAD TEXTURE BLOCK\n";
	else
	{
		spriteBlock.setTexture(textureBlock);
		spriteBlock.setColor(sf::Color::Red);
		this->spriteBlock.scale(0.3f, 0.3f);
	}

	if (!textureBall2.loadFromFile("Textures/ball.png"))
		std::cout << "ERROR::FAILED TO LOAD TEXTURE BLOCK\n";
	else
	{
		spriteBall2.setTexture(textureBall2);
		this->spriteBall2.scale(0.09f, 0.09f);
	}
}

MainMenu::MainMenu(sf::RenderWindow* window, sf::VideoMode videoMode, std::stack<States*>* states):States(window,videoMode,states)
{
	this->initTexturesAndSprites();
	this->initfont();
	this->gameTitle();
	displayNewGame = false;
	displayIntroduction = false;
}

void MainMenu::imgui()
{
	int x = this->window->getSize().x / 2;
	int y = this->window->getSize().y *0.45;
	int buttonx = 350;
	int buttony = 100;
	if (gui->createButton("New Game", buttonx, buttony, x - buttonx / 2, y))
		displayNewGame = true;
	if (gui->createButton("Introduction", buttonx, buttony, x - buttonx / 2, y + buttony))
		displayIntroduction = true;
	if(gui->createButton("Leaderboard", buttonx, buttony, x - buttonx / 2, y + buttony*2))
		this->states->push(new LeaderboardState(this->window, this->videoMode, this->states));
	if (gui->createButton("Exit", buttonx, buttony, x - buttonx / 2, y + buttony * 3))
		endState();
}

void MainMenu::gameTitle()
{
	std::string string = "Bricks Breaker";
	textTitle = gui->createText(string, font, 80, (float)this->window->getSize().x / 3.5);
	textTitle.setFillColor(sf::Color::White);
}

void MainMenu::selectDifficulty()
{
	int x = this->window->getSize().x / 2;
	int y = this->window->getSize().y * 0.45;
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
	if (gui->createButton("Go back", buttonx, buttony, x - buttonx / 2, y + buttony * 3))
		displayNewGame = false;
}

void MainMenu::gameIntroduction()
{
	int x = this->window->getSize().x *0.1;
	int y = this->window->getSize().y * 0.45;
	std::string string = "Goal of the game is to either destroy all blocks,\nor get as many pointsas possible.\n\n\n            Release LMB to fire balls\n\n            give you as much points\n            as they had initial HP\n\n            give you five additional balls ";
	//std::string string = "Goal of the game is to either destroy all blocks,\nor get as many pointsas possible.\n\nHere are some tips:\n1. Release LMB to fire balls in given direction\n2. Destroying block gives as much points \nas the block has had inital health points\n3. There are balls you can collect which,\ngive you five additional balls\n4. For playing on higer difficulty levels,\nyour are getting more points.";
	textGameIntroduction = gui->createText(string, fontOptimus, 30, y, x);
	spriteBall2.setPosition(65, 515);
	spriteBlock.setPosition(80, 610);
	spriteBall.setPosition(47, 685);

	int buttonx = 350;
	int buttony = 80;
	if (gui->createButton("Go back", buttonx, buttony, x*5 - buttonx / 2, 785))
		displayIntroduction = false;

}

void MainMenu::setEvent(sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed && displayIntroduction == true)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			displayIntroduction = false;

		}
	}

	if (event.type == sf::Event::KeyPressed && displayNewGame == true)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			displayNewGame = false;

		}
	}
}

void MainMenu::update(const float& deltaTime, sf::Time& dt)
{

	ImGui::SFML::Update(*window, dt);
	if (!displayIntroduction)
	{
		if (!displayNewGame)
			imgui();
		else
			selectDifficulty();
	}
	else
		gameIntroduction();
	
}

void MainMenu::render(sf::RenderTarget* target)
{
	window->draw(this->worldBackgroud);
	window->draw(this->textTitle);
	if (displayIntroduction)
	{
		window->draw(this->textGameIntroduction);
		window->draw(this->spriteBall);
		window->draw(this->spriteBlock);
		window->draw(this->spriteBall2);
	}
	ImGui::SFML::Render(*window);
}
