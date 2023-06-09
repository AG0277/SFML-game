#pragma once


struct Map
{
	std::vector<std::string> pyramid;
	std::vector<std::string> kite;
	std::vector<std::string> labirynth;
	std::vector<std::string> random;
	std::vector<std::vector<std::string>*> map;
	int random_number;
	Map();

};

class GameState :public States
{
private:
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
	sf::Vector2i NewBallPosition;
	std::vector<std::string> map;
	int blocksAmountPerRow;
	int maxAmountOfBalls;
	int howManyBalls;
	int gameDifficulty;
	std::pair<int, int> gridXandYsize;
	sf::Texture BallTexture;
	// private initlializers

	void initBlocks();
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
	int generateNumber(int first, int second);
	void addBlocks();
	void changeGameBoard();
	void collisionManager(const float& deltaTime);
	void displayTextOnBlocks(Block* block);
	void updateBallPosition(const float& deltaTime);
	void updateBlock();
	void updateFiredBalls(const float& deltaTime);
	void updateGUI();
	void update(const float& deltaTime, sf::Time& dt) ;

	// render function
	void render(sf::RenderTarget* target) ;
};
