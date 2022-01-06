#include "Application.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

Application::Application(sf::RenderWindow& window)
	:
	mWindow(window),
	mGrid(),
	mAlgo(mGrid)
{
	{
		mGrid.CenterTheGrid(window);
		mGrid.GridSetup();
	}
}
void Application::HandleInput(sf::Event& event)
{
	if (mActiveInput)
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			Tile& tile = mGrid.GetTile(sf::Mouse::getPosition(mWindow));
			switch (event.mouseButton.button)
			{
			case sf::Mouse::Left:
				mAlgo.SetStart(tile);
				break;
			case sf::Mouse::Right:
				mAlgo.SetEnd(tile);
				break;
			case sf::Mouse::Middle:
				mAlgo.SetUnwalkable(tile);
				break;
			default:
				break;
			}
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Enter)
			{
				mActiveInput = !mAlgo.Run();// if alog starts to run disable input otherwise not;
			}
		}

	}

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
	{
		if (!mAlgo.IsActive())
		{
			mAlgo.Reset();
			mActiveInput = true;
		}
	}
}

void Application::Update()
{
	if (mAlgo.IsActive())
		mAlgo.Update();
}

void Application::Render() const
{
	mWindow.draw(mGrid);
}
