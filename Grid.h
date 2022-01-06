#pragma once
#include <SFML/Graphics/RectangleShape.hpp>

namespace sf {
	class RenderWindow;
}
struct Index {
	int i = 0;
	int j = 0;
};
struct Tile {
	Tile()
		:
		Tile(sf::Vector2f(0, 0))
	{

	}
	Tile(sf::Vector2f pos)
		:
		position(pos),
		color(sf::Color::White)
	{

	}
	Tile* ParentNode = nullptr;
	Index index;
	sf::Vector2f position;
	sf::Color color;
	bool IsValid = true;

	unsigned int g = 0, h = 0;
	float f()
	{
		return g + h;
	}
};
class Grid :public sf::Drawable, public sf::Transformable
{
	typedef std::vector<std::vector<Tile>> VVT;
public:
	Grid(unsigned int col = 20, unsigned int row = 20);
	void draw(sf::RenderTarget& target, sf::RenderStates states)const;
	Tile& GetTile(sf::Vector2i position);
	Tile& GetTile(int index_x, int index_y);
	sf::IntRect GetGridBounds()const;
	void GridSetup();
	void CenterTheGrid(const sf::RenderWindow& window);
	static int getDistance(Tile& t1, Tile& t2);
	sf::Vector2u GetGridSize() const;
	void Reset();

private:
	sf::RectangleShape mTileRect;
	const unsigned int mTileSize;
	const unsigned int mCol, mRow;
	VVT mGridArray;
	
};

