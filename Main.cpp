#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "Application.h"
int main()
{
	
	sf::RenderWindow mWindow(sf::VideoMode(1280, 720), "A* PathFinding");

	Application app(mWindow);

	sf::Clock clock;
	sf::Time elapsedTime = sf::Time::Zero;
	sf::Time frameTime = sf::seconds(1 / 60.f);

	sf::Event e;
	while (mWindow.isOpen())
	{
		while (mWindow.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				mWindow.close();
			}
			app.HandleInput(e);
		}
		
		elapsedTime += clock.restart();
		if (elapsedTime >= frameTime)
		{
			app.Update();
		   elapsedTime -= frameTime;

		}

		mWindow.clear();
		app.Render();
		mWindow.display();
	
	}
	return 0;
}