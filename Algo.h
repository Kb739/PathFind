#pragma once
#include <SFML/System/Time.hpp>
#include <functional>
#include "Grid.h"
class Algo
{
	
public:
	Algo(Grid& grid);
	void SetStart(Tile &start);
	void SetEnd(Tile &end);
	void SetUnwalkable(Tile& node);
	void Update();
	void UpdateClosedList();
	void UpdateOpenList();

	bool Run();
	void Stop();
	bool IsActive()const;
	void Reset();
private:
	void Finish();
private:
	std::vector<std::function<void()>> operations;
	int oIndex = 0;
	
	Tile* mStartNode = nullptr;
	Tile* mEndNode = nullptr;
	Tile* mCurrentNode = nullptr;
	std::vector<Tile*> openList;
	std::vector<Tile*>closedList;
	Grid& mGrid;
	bool mActive = false;
};

