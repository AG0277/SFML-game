#include "LeaderboardState.h"

void LeaderboardState::sort(std::vector<std::pair<std::string, int>>& scores, int howmanynumbers)
{
	std::vector<std::pair<std::string, int>> topnumbers;
	auto comparator = [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
		return a.second > b.second;
	};

	std::priority_queue<std::pair<std::string, int>, std::vector<std::pair<std::string, int>>, decltype(comparator)> maxHeap(comparator);

	for (const auto& pair : scores) {
		maxHeap.push(pair);
		if (maxHeap.size() > howmanynumbers) {
			maxHeap.pop();
		}
	}

	while (!maxHeap.empty()) {
		topnumbers.push_back(maxHeap.top());
		maxHeap.pop();
	}

	std::reverse(topnumbers.begin(), topnumbers.end());

	this->displayOveralScore = topnumbers;
}

void LeaderboardState::readScore()
{
	std::vector<std::pair<std::string, int>> scores;
	std::string line;
	//std::regex pattern(R"((\w+)->(\d+))");
	std::regex pattern(R"(([\w\s]+)->(\d+))");
	std::ifstream scoreFile("Score.txt");
	if (scoreFile.is_open())
	{
		while (std::getline(scoreFile, line))
		{
			std::smatch match;
			if (std::regex_search(line, match, pattern))
			{
				std::string name = match[1].str();
				int number = (int)std::stof(match[2].str());
				scores.push_back(std::make_pair(name, number));
			}
		}
		sort(scores, 5);
		scoreFile.close();
	}
}


void LeaderboardState::initfont()
{
	if (!font.loadFromFile("font/OptimusPrinceps.ttf"))
		std::cout << "ERROR::FAILED TO LOAD OptimusPrinceps FONT\n";
}

void LeaderboardState::initBackground()
{

	if (!worldBackgroundTexture.loadFromFile("Textures/MainMenuBackground.png"))
		std::cout << "ERROR::FAILED TO LOAD TEXTURE BLOCK\n";
	worldBackgroud.setTexture(worldBackgroundTexture);
}

void LeaderboardState::leaderboardDisplay()
{
	int charsize = 80;
	std::string string = "Leaderboard";
	std::string leaderboard;
	std::string iToStr;
	readScore();
	for (int i = 1; i < displayOveralScore.size()+1; i++)
	{
		iToStr = std::to_string(i);
		leaderboard += (iToStr+". "+displayOveralScore.at(i-1).first + " " + std::to_string(displayOveralScore.at(i-1).second) + "\n");
	}

	text = gui->createText(string, font, charsize, this->window->getSize().y * 0.1);
	leaderboardtext = gui->createText(leaderboard, font, charsize-30, this->window->getSize().y * 0.1 + charsize);
}

LeaderboardState::LeaderboardState(sf::RenderWindow* window, sf::VideoMode videoMode, std::stack<States*>* states) :States(window, videoMode, states)
{
	this->initBackground();
	this->initfont();
	this->leaderboardDisplay();
}

void LeaderboardState::setEvent(sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
		if (event.key.code == sf::Keyboard::Escape)
		{
			endState();
		}
}

void LeaderboardState::imgui()
{
	float x = this->window->getSize().x / 2;
	float y = this->window->getSize().y * 3 / 5;
	int buttonx = 350;
	int buttony = 100;

	if (gui->createButton("Go back", buttonx, buttony, x - buttonx / 2, y +100))
		endState();
}


void LeaderboardState::update(const float& deltaTime, sf::Time& dt)
{

	ImGui::SFML::Update(*window, dt);
	imgui();
}

void LeaderboardState::render(sf::RenderTarget* target)
{
	window->draw(this->worldBackgroud);
	window->draw(this->text);
	window->draw(this->leaderboardtext);
	ImGui::SFML::Render(*window);
}