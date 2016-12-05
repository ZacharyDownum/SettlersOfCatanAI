#include "Node.h"

Node::Node()
{
	port = GameBoard::Elements::None;
	occupiedBy = GameBoard::PlayerColors::None;
	typeOfBuilding = GameBoard::BuildingType::None;
}
