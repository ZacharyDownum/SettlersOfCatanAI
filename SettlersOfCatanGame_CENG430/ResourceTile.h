#pragma once

#include <vector>
#include "GameBoard.h"

class ResourceTile
{
	private:

	public:
		std::vector<Node*> borderingNodes;
		
		GameBoard::Elements element;
		int rollValue;
		
		ResourceTile(GameBoard::Elements e, int value);
};