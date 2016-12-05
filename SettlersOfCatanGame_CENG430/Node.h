#pragma once

#include <vector>
#include "GameBoard.h"

class Node
{
	private:

	public:
		std::vector<Edge*> borderingEdges;

		GameBoard::PlayerColors occupiedBy;
		GameBoard::BuildingType typeOfBuilding;
		GameBoard::Elements port;

		Node();
};