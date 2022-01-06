#include "Algo.h"
#include<iostream>
Algo::Algo(Grid& grid)
	:
	mGrid(grid)
{
	
	operations.push_back([this]() {UpdateClosedList(); });
	operations.push_back([this]() {UpdateOpenList(); });
	
	
}

void Algo::SetStart(Tile &start)
{
	if (mStartNode)
		mStartNode->color = sf::Color::White; //default color
	mStartNode = &start;
	mStartNode->IsValid = true;
	mStartNode->color = sf::Color::Yellow;// start color
		
}

void Algo::SetEnd(Tile &end)
{
	if (mEndNode)
		mEndNode->color = sf::Color::White;
	mEndNode = &end;
	mEndNode->IsValid = true;
	mEndNode->color = sf::Color::Green; //end color
}

void Algo::SetUnwalkable(Tile& node)
{
	if (mStartNode == &node)
		mStartNode = nullptr;
	else if (mEndNode == &node)
		mEndNode = nullptr;

	node.IsValid = !node.IsValid;
	node.color = node.IsValid ? sf::Color::White : sf::Color(165, 42, 42, 255);  //white/brown
}

void Algo::Update()
{
	if (mCurrentNode != mEndNode)
	{
		operations[oIndex]();
		oIndex = (oIndex + 1) % operations.size();
	}
	else 
	{
		Finish();
	}
}

void Algo::UpdateClosedList()
{
	auto cc = [](Tile* lhs, Tile* rhs)
	{
		if (lhs->f() < rhs->f())
		{
			return true;
		}
		else if (lhs->f() == rhs->f())
		{
			return lhs->g < rhs->g;
		}
		return false;
	};

	if (openList.size() != 0) 
	{

		std::sort(openList.begin(), openList.end(), cc);
		auto itr = openList.begin();

		mCurrentNode = *itr;
		mCurrentNode->color = sf::Color::Blue;
		
		closedList.push_back(*itr);
		openList.erase(itr);
	}
	else 
	{
		Stop();//unsuccessful
	}
	
}

void Algo::UpdateOpenList()
{

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i != 0 || j != 0)
			{
				int index_i = mCurrentNode->index.i + i;
				int index_j = mCurrentNode->index.j + j;

				if (index_i < mGrid.GetGridSize().y && index_j < mGrid.GetGridSize().x) //y for rows & x for cols
				{
					Tile& tile = mGrid.GetTile(index_i, index_j);

					if (tile.IsValid) 
					{
						auto found = std::find(closedList.begin(), closedList.end(), &tile);
						if (found == closedList.end())    //not found
						{
							found = std::find(openList.begin(), openList.end(), &tile);
							int G = (mCurrentNode->g + Grid::getDistance(*mCurrentNode, tile));//g cost with current path

							if (found != openList.end()) //already in openlist
							{
								if (tile.g > G) {
									tile.g = G;
									tile.ParentNode = mCurrentNode;
								}
							}
							else
							{
								tile.color = sf::Color::Red;
								tile.h = Grid::getDistance(tile, *mEndNode);
								tile.g = G;
								tile.ParentNode = mCurrentNode;
								openList.push_back(&tile);
							}
						}

					}
				}
			}
		}
	}
}

bool Algo::Run()
{
	if (mStartNode != nullptr && mEndNode != nullptr && mEndNode != mStartNode)
	{
		openList.push_back(mStartNode);
		mActive = true;
		return true;
	}
	return false;

}

void Algo::Stop()
{
	mActive = false;
}

bool Algo::IsActive() const
{
	return mActive;
}

void Algo::Reset()
{
	openList.clear();
	closedList.clear();
	oIndex = 0;
	mStartNode = nullptr;
	mEndNode = nullptr;
	mGrid.Reset();
	
}

void Algo::Finish()
{
	mEndNode->color = sf::Color::Green;
	mStartNode->color = sf::Color::Yellow;

	mCurrentNode = mCurrentNode->ParentNode;
	while (mCurrentNode != mStartNode)
	{
		mCurrentNode->color = sf::Color::Cyan;
		mCurrentNode = mCurrentNode->ParentNode;
	}

	Stop();
}
