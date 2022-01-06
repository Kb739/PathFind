#include "Grid.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <cassert>

Grid::Grid(unsigned int col, unsigned int row)
	:
	mTileSize(30),
	mCol(col),mRow(row)
{
	assert(col > 0 && row > 0);
	
}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
	for (int i = 0; i < mRow; i++)
	{
		for (int j = 0; j < mCol; j++)
		{
			const Tile& tile = mGridArray[i][j];

			sf::RectangleShape drawRect = mTileRect;
			drawRect.setPosition(tile.position);
			drawRect.setFillColor(tile.color);
			drawRect.setOutlineThickness(1);
			drawRect.setOutlineColor(sf::Color::Black);

			target.draw(drawRect);
		}
	}
}

Tile& Grid::GetTile(sf::Vector2i worldPosition)
{
	assert(GetGridBounds().contains(worldPosition.x, worldPosition.y));

	
	worldPosition.x -= getPosition().x;
	worldPosition.y -= getPosition().y;
	int i = worldPosition.y / mTileSize;
	int j = worldPosition.x / mTileSize;

	return mGridArray[i][j];
}

Tile& Grid::GetTile(int index_x, int index_y)
{
	return mGridArray[index_x][index_y];
}

sf::IntRect Grid::GetGridBounds() const
{
	sf::Vector2i pos(int(getPosition().x), int(getPosition().y));
	sf::Vector2i GridSize(mTileSize * mCol, mTileSize * mRow);
	return sf::IntRect(pos, GridSize);
}

void Grid::GridSetup()
{
	mTileRect.setSize(sf::Vector2f(mTileSize, mTileSize));
	
	for (int i = 0; i < mRow; i++)
	{
		std::vector<Tile> v;
		for (int j = 0; j < mCol; j++)
		{
			
			sf::Vector2f tilePos = getPosition() + sf::Vector2f(j * mTileSize, i * mTileSize);
			Tile tile(tilePos);

			tile.index.i = i;
			tile.index.j = j;
			v.push_back(tile);
		}
		mGridArray.push_back(v);
	}
}

void Grid::CenterTheGrid(const sf::RenderWindow& window)
{
	sf::Vector2f screenCenter(window.getSize().x * .5f, window.getSize().y * .5f);
	sf::Vector2f gridHalfSize(mCol * mTileSize * .5f, mRow * mTileSize * .5f);

	setPosition(screenCenter - gridHalfSize);

}

int Grid::getDistance(Tile& t1, Tile& t2)
{
	sf::Vector2f dv(t2.position - t1.position);
	
	return dv.x * dv.x + dv.y * dv.y;
}

sf::Vector2u Grid::GetGridSize()const
{
	return sf::Vector2u(mCol, mRow);
}

void Grid::Reset()
{
	for (auto& Row : mGridArray)
	{
		for (Tile& tile : Row)
		{
			tile.color = sf::Color::White;
			tile.IsValid = true;
			tile.ParentNode = nullptr;
			tile.g = 0;
			tile.h = 0;
		}
	}
}
