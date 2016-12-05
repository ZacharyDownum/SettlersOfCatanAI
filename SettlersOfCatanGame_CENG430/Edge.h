#pragma once

#include <vector>
#include "GameBoard.h"

class Edge
{
	private:

	public:
		std::vector<Node*> borderingNodes;

		GameBoard::PlayerColors occupiedBy;

		Edge();
};