#pragma once


class MainMenu:public States
{
private:
	sf::Font font;
	sf::Font fontOptimus;
	sf::Text textTitle;
	sf::Text textGameIntroduction;
	sf::Texture textureBlock;
	sf::Texture textureBall;
	sf::Sprite spriteBall;
	sf::Sprite spriteBlock;
	sf::Texture textureBall2;
	sf::Sprite spriteBall2;
	
	bool displayNewGame;
	bool displayIntroduction;
	void initfont();
	void initTexturesAndSprites();
	void gameTitle();
public:
	MainMenu(sf::RenderWindow* window, sf::VideoMode videoMode, std::stack<States*>* states);
	virtual ~MainMenu() {};

	void selectDifficulty();
	void gameIntroduction();
	void setEvent(sf::Event& event);
	void update(const float& deltaTime, sf::Time& dt);
	void render(sf::RenderTarget* target);
	void imgui();
};


