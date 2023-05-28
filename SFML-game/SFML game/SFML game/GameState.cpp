#include "GameState.h"


Map::Map()
{
	pyramid =
	{
"###############",
"#g           g#",
"#gg         gg#",
"#ggg       ggg#",
"#      g      #",
"#     ggg     #",
"#    ggggg    #",
"#   ggggggg   #",
"#  ggggggggg  #",
"# ggggggggggg #",
"#ggggggggggggg#",
"#             #",
"#             #",
"#             #",
"###############",
	};

	kite =
	{
"###############",
"#             #",
"#      g      #",
"#     g g     #",
"#    g g g    #",
"#   g g g g   #",
"#  g g g g g  #",
"#   g g g g   #",
"#    g g g    #",
"#     g g     #",
"#      g      #",
"#             #",
"#             #",
"#             #",
"###############",
	};
	labirynth =
	{
"###############",
"#ggggggggggggg#",
"#g           g#",
"#g ggggggggg g#",
"#g g       g g#",
"#g g ggggg g g#",
"#g g ggggg g g#",
"#g g       g g#",
"#g ggggggggg g#",
"#g           g#",
"#ggggggggggggg#",
"#             #",
"#             #",
"#             #",
"###############",
	};
	numberOfBlocksSpawned = 2;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(0, 3);
	random_number = 3;// distr(gen);
	if (random_number == 3)
	{
		std::string temp= "               ";
			for (int j = 0; j < 15; j++)
				random.push_back( temp);
				
			for (int k = 1; k < 4; k++)
				random.at(2).at(k)='g';
	}

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
					this->block.push_back(new BlockYellow);
					this->block.at(this->block.size() -1)->getSprite()->setPosition(this->block.at(0)->getSprite()->getGlobalBounds().width * (k-1) + 12, this->block.at(0)->getSprite()->getGlobalBounds().height * j);
				}
			}
		}
}

void GameState::initPlayer()
{
	this->player = new Player(videoMode);
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

GameState::GameState(sf::RenderWindow* window, sf::VideoMode videoMode,std::stack<States*>* states)
	:States(window,videoMode,states)
{
	Map map;
	this->map = *map.map.at(map.random_number);
	initBlocks();
	collision = CollisionManager();
	initBackground();
	initPlayer();
	initBall();
	initFont();
	colisionON = true;
	canModify = true;
	numberOfBlocksSpawned = 4;

}

GameState::~GameState()
{
	delete this->player;
	for (auto* ball : ball)
		delete ball;
	for (auto* block : block)
		delete block;
}


void GameState::fireBalls()
{
		this->ball.push_back(new Ball(videoMode,currentBallPos));
		ballsCounter++;
		ballsPushed++;
		this->ball.at(ballsCounter - 1)->directions(mousePos.x, mousePos.y);

}

std::vector<int> GameState::randomNumbers()
{
	if (numberOfBlocksSpawned < 10)
		numberOfBlocksSpawned=numberOfBlocksSpawned+0.4;
	std::vector<int> nums(13);
	std::iota(nums.begin(), nums.end(), 1);
	std::mt19937 gen(std::random_device{}());
	std::shuffle(nums.begin(), nums.end(), gen);
	nums.resize(std::floor(numberOfBlocksSpawned));
	return nums;
}

void GameState::addBlocks()
{
	std::vector<int> temp = randomNumbers();
	for (int i = 0; i < temp.size(); i++)
	{
			this->block.push_back(new BlockYellow);
			this->block.at(this->block.size() - 1)->getSprite()->setPosition(this->block.at(0)->getSprite()->getGlobalBounds().width * (temp.at(i)-1) + 12, this->block.at(0)->getSprite()->getGlobalBounds().height);
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
		sf::Mouse::getPosition(*this->window);
	

	}
	if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && canModify == true)
	{
		mousePos = sf::Mouse::getPosition(*this->window);
		ball.erase(ball.begin());
		canModify = false;
		fireBalls();
	}
}

void GameState::updatePlayerPosition()
{

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
	int counter = 0;
	for (auto* block : block)
	{
		if (!block->update())
			this->block.erase(this->block.begin() + counter);
		++counter;
	}

}

void GameState::updateFiredBalls(const float& deltaTime)
{

	float temp = videoMode.width/20;
	this->dt = (dt+temp) ;
	if (dt > 100)
	{
		if (ballsPushed > 0 && ballsPushed < 30&& canModify==false )
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

	for (auto ball:ball)
	{
		bool doublecolision = false;
		if (colisionON == true)
			for (int j = 0; j < block.size(); j++)
			{
				bool changeX = false;
				bool changeY = false;
				if (this->collision.handleCollisions(*ball, *block.at(j), changeX, changeY))
				{
					if (doublecolision == false)
						ball->updateDirection(changeX, changeY);
					block.at(j)->updateHit();
					doublecolision = true;
				}
			}
		bool changeX = false;
		bool changeY = false;
		bool delBall = false;
		if (this->collision.handleBackground_BallCollisions(*ball, worldBackgroud, changeX, changeY, delBall,newPos))
		{
			if (newPos == true)
			{
				this->NewBallPosition.x= (int)ball->getSprite().getPosition().x;
				this->NewBallPosition.y = (int)ball->getSprite().getPosition().y-10;

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
				}
			}
		}
		++counter;
	}

	if (block.size() <= 0)
		std::cout << "asd";

	for (auto block : block)
	{
		if (collision.handleBackground_BlockCollisions(*block, worldBackgroud))
		{
			this->endState();
		}
	}
}

void GameState::updateGUI()
{
	if (this->gui->createButton("PULL BALLS", 200, 100, 300, 797))\
	{
		colisionON = false;
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
	this->updatePlayerPosition();
	this->updateBallPosition(deltaTime);
	this->updateFiredBalls(deltaTime);
}

void GameState::render(sf::RenderTarget* target)
{
	window->draw(this->worldBackgroud);
	window->draw(this->framebackground);
	for (auto* ball : ball)
		ball->render(this->window);
	for (auto* block : block)
	{
		block->render(this->window);
		text.setString(std::to_string(block->getHealth()));
		text.setPosition(block->getSprite()->getGlobalBounds().left+ block->getSprite()->getGlobalBounds().width/4, block->getSprite()->getGlobalBounds().top+ block->getSprite()->getGlobalBounds().height/4);
		window->draw(text);
			
	}
	raytracing.render(this->window);

	ImGui::SFML::Render(*window);

}
