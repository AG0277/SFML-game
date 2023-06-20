#include "pch.h"
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

int GameState::generateNumber(int first, int second)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(first, second);
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
	gridXandYsize = std::make_pair((int)this->block.at(0)->getSprite()->getGlobalBounds().width, (int)this->block.at(0)->getSprite()->getGlobalBounds().height);
}

void GameState::initBall()
{
	currentBallPos.x = videoMode.width / 2;
	currentBallPos.y = videoMode.height * 0.98 - 100;
	this->ball.push_back(new Ball(videoMode, currentBallPos, BallTexture));
}

void GameState::initBackground()
{
	if (!this->worldBackgroundTexture.loadFromFile("Textures/background.png"))
		std::cout << "ERROR::FAILED TO LOAD TEXTURE background\n";
	this->worldBackgroud.setTexture(worldBackgroundTexture);
	if (!this->framebackgroundtex.loadFromFile("Textures/background1.png"))
		std::cout << "ERROR::FAILED TO LOAD TEXTURE frame\n";
	this->framebackground.setTexture(framebackgroundtex);

	if (!BallTexture.loadFromFile("Textures/ball.png"))
		std::cout << "ERROR::FAILED TO LOAD ball frame\n";
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
	maxAmountOfBalls = 90;
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
	this->ball.push_back(new Ball(videoMode, currentBallPos,BallTexture));
	ballsCounter++;
	ballsPushed++;
	this->ball.at(ballsCounter - 1)->directions(mousePos.x, mousePos.y);

}

std::vector<int> GameState::randomNumbers()
{
	if (numberOfBlocksSpawned < 7)
		numberOfBlocksSpawned = numberOfBlocksSpawned +0.8;
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
	int chanceForSpwaningBall =  generateNumber(1, 5);
	std::vector<int> temp = randomNumbers();
	int randomPositionToSwapBall=generateNumber(1, temp.size());
	for (int i = 0; i < temp.size(); i++)
	{
		if (chanceForSpwaningBall != 1)
		{
			this->block.push_back(new BlockYellow(gameDifficulty + std::floor(8.0 * gameLevel) * 10));
			this->block.at(this->block.size() - 1)->getSprite()->setPosition(gridXandYsize.first * (temp.at(i) - 1) + 8, gridXandYsize.second * 2);
		}
		else
		{
			if(i== randomPositionToSwapBall-1)
			{
				this->block.push_back(new BlockBall);
				this->block.at(this->block.size() - 1)->getSprite()->setPosition(gridXandYsize.first * (temp.at(i) - 1) + 8-35, gridXandYsize.second * 2-15);
			}
			else
			{
				this->block.push_back(new BlockYellow(gameDifficulty + std::floor(8.0 * gameLevel) * 10));
				this->block.at(this->block.size() - 1)->getSprite()->setPosition(gridXandYsize.first * (temp.at(i) - 1) + 8, gridXandYsize.second * 2);
			}
		}
	}
}

void GameState::changeGameBoard()
{
	for (auto* block : block)
	{
		block->getSprite()->setPosition(block->getSprite()->getGlobalBounds().left, block->getSprite()->getGlobalBounds().top + gridXandYsize.second);
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
	if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && canModify == true)
	{
		this->mousePos = sf::Mouse::getPosition(*this->window);
		delete this->ball.at(0);
		this->ball.erase(ball.begin());
		this->canModify = false;
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
			if (block->getPoints() > 10 || block->getPoints() == 1)
				points += block->getPoints();
			else if (block->getPoints() == 2)
				this->maxAmountOfBalls += 5;
			eraseBallAt.push_back(counter);
		}
		++counter;
	}

	for (int i=0;i<eraseBallAt.size();i++)
	{
		delete this->block.at(eraseBallAt.at(i));
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
				delete this->ball.at(counter);
				this->ball.erase(this->ball.begin() + counter);
				counter--;
				ballsCounter--;
				if (this->ball.size() == 0 && canModify == false)
				{
					changeGameBoard();
					this->currentBallPos = NewBallPosition;
					this->ball.push_back(new Ball(videoMode, NewBallPosition, BallTexture));
					canModify = true;
					ballsPushed = 0;
					colisionON = true;
					collision.setnewPos();
					howManyBalls = maxAmountOfBalls;
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
	if (BlockYellow* ptr = dynamic_cast<BlockYellow*>(block))
	{
		text.setString(std::to_string(ptr->getHealth()));
		if (ptr->getHealth() < 100)
			text.setPosition(block->getSprite()->getGlobalBounds().left + block->getSprite()->getGlobalBounds().width / 4, block->getSprite()->getGlobalBounds().top + block->getSprite()->getGlobalBounds().height / 4);
		else
			text.setPosition(block->getSprite()->getGlobalBounds().left + block->getSprite()->getGlobalBounds().width * 0.15, block->getSprite()->getGlobalBounds().top + block->getSprite()->getGlobalBounds().height / 4);
	}
}

void GameState::updateGUI()
{
	if (this->gui->createButton("PULL BALLS", 200, 100, this->window->getSize().x/2-100, this->window->getSize().y -102)&&canModify==false)
	{
		
		colisionON = false;
		howManyBalls = 0;
		for (int i = 0; i < ball.size(); i++)
		{
			ball.at(i)->directions(this->window->getSize().x/2, this->window->getSize().y);
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
