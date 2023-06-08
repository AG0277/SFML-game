#include "GameState.h"


Map::Map()
{
	pyramid =
	{
"###########",
"#         #",
"#ohhhhhhho#",
"#ghhhhhhhg#",
"#ghooooohg#",
"#ghhhhhhhg#",
"#ooooooooo#",
"#         #",
"#         #",
"#         #",
"##########",
	};

	kite =
	{
"##########",
"#         #",
"#o   g   o#",
"#o   g   o#",
"#o   g   o#",
"#o   g   o#",
"#o   g   o#",
"#         #",
"#         #",
"#         #",
"##########",
	};
	labirynth =
	{
"###########",
"#         #",
"#ooooooooo#",
"#ghhhhhhhg#",
"#ghohohohg#",
"#ghhhhhhhg#",
"#ooooooooo#",
"#         #",
"#         #",
"#         #",
"##########",
	};

	random =
	{
"###########",
"#         #",
"#ggg     g#",
"#         #",
"#ggg      #",
"#         #",
"#         #",
"#         #",
"#         #",
"#         #",
"##########",
	};

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(0, 3);
	random_number =  distr(gen);

	map.push_back(&pyramid);
	map.push_back(&kite);
	map.push_back(&labirynth);
	map.push_back(&random);
}

int GameState::generateNumber()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(0, 2);
	return distr(gen);
}

void GameState::initBlocks()
{
	for (int j = 0; j < map.size(); j++)
	{
		for (int k = 0; k < map.at(j).size(); k++)
		{
			if (map.at(j).at(k) == 'g')
			{
				this->block.push_back(new BlockYellow(gameDifficulty + std::floor(8.0 * gameLevel) * 10));
				this->block.at(this->block.size() - 1)->getSprite()->setPosition(this->block.at(0)->getSprite()->getGlobalBounds().width * (k - 1) + 8, this->block.at(0)->getSprite()->getGlobalBounds().height * j);
			}
			else if (map.at(j).at(k) == 'h')
			{
				this->block.push_back(new BlockYellow(1));
				this->block.at(this->block.size() - 1)->getSprite()->setPosition(this->block.at(0)->getSprite()->getGlobalBounds().width * (k - 1) + 8, this->block.at(0)->getSprite()->getGlobalBounds().height * j);
			}
			else if (map.at(j).at(k) == 'o')
			{
				this->block.push_back(new BlockYellow(gameDifficulty + std::floor(3.0 * gameLevel) * 10));
				this->block.at(this->block.size() - 1)->getSprite()->setPosition(this->block.at(0)->getSprite()->getGlobalBounds().width * (k - 1) + 8, this->block.at(0)->getSprite()->getGlobalBounds().height * j);
			}
		}
	}
	blocksAmountPerRow = this->window->getSize().x / block.at(0)->getSprite()->getGlobalBounds().width;
}

void GameState::initBall()
{
	currentBallPos.x = videoMode.width / 2;
	currentBallPos.y = videoMode.height * 0.98 - 100;
	this->ball.push_back(new Ball(videoMode, currentBallPos));
}

void GameState::initBackground()
{
	if (!this->worldBackgroundTexture.loadFromFile("Textures/background.png"))
		std::cout << "ERROR::FAILED TO LOAD TEXTURE background\n";
	this->worldBackgroud.setTexture(worldBackgroundTexture);
	if (!this->framebackgroundtex.loadFromFile("Textures/background1.png"))
		std::cout << "ERROR::FAILED TO LOAD TEXTURE frame\n";
	this->framebackground.setTexture(framebackgroundtex);
}

void GameState::initFont()
{
	if (!font.loadFromFile("font/arial.ttf"))
		std::cout << "ERROR::FAILED TO LOAD FONT\n";
	text.setFont(font);
}

GameState::GameState(sf::RenderWindow* window, sf::VideoMode videoMode, std::stack<States*>* states)
	:States(window, videoMode, states)
{
	Map map;
	this->map = *map.map.at(map.random_number);
	initBlocks();
	collision = CollisionManager();
	initBackground();
	initBall();
	initFont();
	colisionON = true;
	canModify = true;
	numberOfBlocksSpawned = 4;
	DidYouWin = false;
	gameON = true;
	howManyBalls = 90;
	gameDifficulty = 10;
}

GameState::~GameState()
{
	for (auto* ball : ball)
		delete ball;
	for (auto* block : block)
		delete block;
}

void GameState::fireBalls()
{
	this->ball.push_back(new Ball(videoMode, currentBallPos));
	ballsCounter++;
	ballsPushed++;
	this->ball.at(ballsCounter - 1)->directions(mousePos.x, mousePos.y);

}

std::vector<int> GameState::randomNumbers()
{
	if (numberOfBlocksSpawned < 7)
		numberOfBlocksSpawned = numberOfBlocksSpawned +1;
	else
	{
		numberOfBlocksSpawned = 3;
		gameDifficulty += 10;
	}
	std::vector<int> nums(blocksAmountPerRow);
	std::iota(nums.begin(), nums.end(), 1);
	std::mt19937 gen(std::random_device{}());
	std::shuffle(nums.begin(), nums.end(), gen);
	nums.resize(std::floor(numberOfBlocksSpawned));
	return nums;
}

void GameState::addBlocks()
{
	float temp1 = 8;
	std::vector<int> temp = randomNumbers();
	for (int i = 0; i < temp.size(); i++)
	{
		this->block.push_back(new BlockYellow(gameDifficulty+std::floor(8.0*gameLevel)*10));
		this->block.at(this->block.size() - 1)->getSprite()->setPosition(this->block.at(0)->getSprite()->getGlobalBounds().width * (temp.at(i) - 1) + 8, this->block.at(0)->getSprite()->getGlobalBounds().height*2);
	}
}

void GameState::changeGameBoard()
{
	for (auto* block : block)
	{
		block->getSprite()->setPosition(block->getSprite()->getGlobalBounds().left, block->getSprite()->getGlobalBounds().top + block->getSprite()->getGlobalBounds().height);
	}
	addBlocks();
}

void GameState::setEvent(sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
		if (event.key.code == sf::Keyboard::Escape)
		{
			this->states->push(new PauseGameState(window, videoMode, states));
		}
	if (event.type == event.MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && canModify == true)
	{
		//raytracing.direction(sf::Mouse::getPosition(*this->window),currentBallPos);

	}
	if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && canModify == true)
	{
		mousePos = sf::Mouse::getPosition(*this->window);
		ball.erase(ball.begin());
		canModify = false;
		fireBalls();
	}
}

void GameState::updateBallPosition(const float& deltaTime)
{
	int counter = 0;
	for (auto* ball : ball)
	{
		ball->update(deltaTime);
	}
}

void GameState::updateBlock()
{
	std::vector<int> eraseBallAt;
	int counter=0;
	for (auto* block : block)
	{
		if (!block->update())
		{
			points+=block->getPoints();
			eraseBallAt.push_back(counter);
		}
		++counter;
	}

	for (int i=0;i<eraseBallAt.size();i++)
	{
		this->block.erase(this->block.begin() + eraseBallAt.at(i));
	}

}

void GameState::updateFiredBalls(const float& deltaTime)
{

	float temp = videoMode.width / 20;
	this->dt = (dt + temp);
	if (dt > 100)
	{
		if (ballsPushed > 0 && ballsPushed < howManyBalls && canModify == false)
		{

			fireBalls();
		}
		dt = 0;
	}
}

void GameState::collisionManager(const float& deltaTime)
{
	int counter = 0;
	bool newPos = false;

	for (auto ball : ball)
	{
		bool doublecollision = false;
		if (colisionON == true)
			for (int j = 0; j < block.size(); j++)
			{
				bool changeX = false;
				bool changeY = false;
				if (this->collision.handleCollisions(*ball, *block.at(j), changeX, changeY) && !ball->gethasBeenHit())
				{
					if (doublecollision == false)
					{
						ball->updateDirection(changeX, changeY);
						ball->sethasBeenHit(true);
					}
					block.at(j)->updateHit();
					doublecollision = true;
				}
			}
		bool changeX = false;
		bool changeY = false;
		bool delBall = false;
		if (this->collision.handleBackground_BallCollisions(*ball, worldBackgroud, changeX, changeY, delBall, newPos))
		{
			if (newPos == true)
			{
				this->NewBallPosition.x = (int)ball->getSprite().getPosition().x;
				this->NewBallPosition.y = (int)ball->getSprite().getPosition().y - 10;

				newPos = false;
			}
			ball->updateDirection(changeX, changeY);
			if (delBall == true)
			{
				this->ball.erase(this->ball.begin() + counter);
				counter--;
				ballsCounter--;
				if (this->ball.size() == 0 && canModify == false)
				{
					changeGameBoard();
					this->currentBallPos = NewBallPosition;
					this->ball.push_back(new Ball(videoMode, NewBallPosition));
					canModify = true;
					ballsPushed = 0;
					colisionON = true;
					collision.setnewPos();
					howManyBalls = 90;
				}
			}
		}
		++counter;
	}

	if (block.size() <= 0)
	{
		gameON = false;
		DidYouWin = true;
		this->endState();
		this->states->push(new PauseGameState(window, videoMode, states));
	}

	for (const auto &block : block)
	{
		if (collision.handleBackground_BlockCollisions(*block, worldBackgroud))
		{
			DidYouWin = false;
			gameON = false;
			this->endState();
			this->states->push(new PauseGameState(window, videoMode, states));
		}
	}
}

void GameState::displayTextOnBlocks(Block* block)
{
	text.setString(std::to_string(block->getHealth()));
	if (block->getHealth() < 100)
		text.setPosition(block->getSprite()->getGlobalBounds().left + block->getSprite()->getGlobalBounds().width / 4, block->getSprite()->getGlobalBounds().top + block->getSprite()->getGlobalBounds().height / 4);
	else
		text.setPosition(block->getSprite()->getGlobalBounds().left + block->getSprite()->getGlobalBounds().width *0.15, block->getSprite()->getGlobalBounds().top + block->getSprite()->getGlobalBounds().height /4);
}

void GameState::updateGUI()
{
	if (this->gui->createButton("PULL BALLS", 200, 100, this->window->getSize().x/2-100, this->window->getSize().y -102))
	{
		
		colisionON = false;
		howManyBalls = 0;
		for (int i = 0; i < ball.size(); i++)
		{
			ball.at(i)->directions(400, 800);
		}
	}
}

void GameState::update(const float& deltaTime, sf::Time& dt)
{
	ImGui::SFML::Update(*window, dt);
	this->updateGUI();
	this->collisionManager(deltaTime);
	this->updateBlock();
	this->updateBallPosition(deltaTime);
	this->updateFiredBalls(deltaTime);
}

void GameState::render(sf::RenderTarget* target)
{
	window->draw(this->worldBackgroud);
	window->draw(this->framebackground);
	for (const auto& ball : ball)
		ball->render(this->window);
	for (const auto& block : block)
	{
		block->render(this->window);
		displayTextOnBlocks(block);
		window->draw(text);
	}

	ImGui::SFML::Render(*window);

}
