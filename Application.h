#pragma once
#include "Algo.h"
namespace sf {
	class Event;
}
class Application
{
public:
	Application(sf::RenderWindow& window);
	void HandleInput(sf::Event& event);
	void Update();
	void Render()const;
private:
	Grid mGrid;
	Algo mAlgo;
	sf::RenderWindow& mWindow;
	bool mActiveInput = true;
};

