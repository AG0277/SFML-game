#pragma once
#include"States.h"
#include "MainMenu.h"
#include <unordered_map>
#include <algorithm>
#include <random>
#include <numeric>
#include "PauseGameState.h"
#include "RayTracing.h"

struct Map
{
	std::vector<std::string> pyramid;
	std::vector<std::string> kite;
	std::vector<std::string> labirynth;
	std::vector<std::string> random;
	std::vector<std::vector<std::string>*> map;
	int random_number;
	float numberOfBlocksSpawned;
	Map();

};

class GameState :public States
{
private:
	// Game member classes
	Player* player;
	std::vector<Block*> block;
	std::vector<Ball*> ball;
	int ballsCounter;
	int ballsPushed;
	sf::Vector2i currentBallPos;
	sf::Vector2i mousePos;
	float dt;
	bool colisionON;
	bool canModify;
	sf::Text text;
	sf::Font font;
	sf::Texture framebackgroundtex;
	sf::Sprite framebackground;
	float numberOfBlocksSpawned;
	RayTracing raytracing;
	sf::Vector2i NewBallPosition;
	std::vector<std::string> map;
	// private initlializers

	void initBlocks();
	void initPlayer();
	void initBall();
	void initBackground();
	void initFont();

public:
	GameState(sf::RenderWindow* window, sf::VideoMode videoMode, std::stack<States*>* states) ;
	virtual ~GameState() ;

	void fireBalls();
	// update functions
	void setEvent(sf::Event& event);
	std::vector<int>  randomNumbers();
	int generateNumber();
	void addBlocks();
	void changeGameBoard();
	void collisionManager(const float& deltaTime);
	void updatePlayerPosition();
	void updateBallPosition(const float& deltaTime);
	void updateBlock();
	void updateFiredBalls(const float& deltaTime);
	void updateGUI();
	void update(const float& deltaTime, sf::Time& dt) ;

	// render function
	void render(sf::RenderTarget* target) ;
};
