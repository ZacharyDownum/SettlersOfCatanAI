#include <map>
#include <iostream>
#include "GameBoardTestCases.h"
#include "ResourceTile.h"
#include "Node.h"
#include "Edge.h"
#include "Player.h"

using std::map;
using std::cout;
using std::endl;

//main function that returns zero if all test cases passed
//will return the number of the test that failed (based on the order of the functions below) if one actually failed
//the int returned will be based off base 2 return codes (first one is 1, second is 2, third is 4, etc...)
//ex.: if runTestCases() returns 15, that means that the first 4 functions failed
int GameBoardTestCases::runTestCases()
{
	return gameBoard_checkResourceTileInitialConditions() + gameBoard_checkNodeInitialConditions() + gameBoard_checkEdgeInitialConditions() + gameBoard_checkDevelopmentCardInitialConditions() + gameBoard_checkPlayerInitialConditions() + gameBoard_checkRobberLocationInitialConditions()
			+ resourceTile_checkNodeAssociations()
			+ node_checkEdgeAssociations()
			+ edge_checkNodeAssociations();
}


//this will ensure that the proper number of each element is contained within the resource tile list in the game board
int GameBoardTestCases::gameBoard_checkResourceTileInitialConditions()
{
	//should either return 1 or 0
	int returnValue = 0;

	//there should be 4 Grain, 4 Lumber, 4 Wool, 3 Ore, 3 Brick, and 1 Desert
	//this map will count the Elements that are contained within the resource tiles
	//if these do not match up at the end, the test should fail
	map<GameBoard::Elements, int> elementsCounter;
	elementsCounter.insert(std::make_pair(GameBoard::Elements::Grain, 4));
	elementsCounter.insert(std::make_pair(GameBoard::Elements::Lumber, 4));
	elementsCounter.insert(std::make_pair(GameBoard::Elements::Wool, 4));
	elementsCounter.insert(std::make_pair(GameBoard::Elements::Ore, 3));
	elementsCounter.insert(std::make_pair(GameBoard::Elements::Brick, 3));
	elementsCounter.insert(std::make_pair(GameBoard::Elements::Desert, 1));

	//this map holds the numbers for the rollValues and how many times they should occur
	map<int, int> rollValueCounter;
	for (int i = 2; i < 13; ++i)
	{
		//2, 7, and 12 are only represented once, all others are represented 2 times
		if (i == 2 || i == 7 || i == 12)
		{
			rollValueCounter.insert(std::make_pair(i, 1));
		}
		else
		{
			rollValueCounter.insert(std::make_pair(i, 2));
		}
	}

	for (ResourceTile tile : board.tiles)
	{
		--elementsCounter[tile.element];
		--rollValueCounter[tile.rollValue];
		if (tile.borderingNodes.empty())
		{
			returnValue = 1;
		}
	}

	if (returnValue <= 0)
	{
		for (auto p : elementsCounter)
		{
			if (p.second != 0)
			{
				if (p.first == GameBoard::Elements::Grain)
				{
					cout << "Grain is off by " << p.second << endl;
				}
				else if (p.first == GameBoard::Elements::Brick)
				{
					cout << "Brick is off by " << p.second << endl;
				}
				else if (p.first == GameBoard::Elements::Desert)
				{
					cout << "Desert is off by " << p.second << endl;
				}
				else if (p.first == GameBoard::Elements::Lumber)
				{
					cout << "Lumber is off by " << p.second << endl;
				}
				else if (p.first == GameBoard::Elements::Ore)
				{
					cout << "Ore is off by " << p.second << endl;
				}
				else if (p.first == GameBoard::Elements::Wool)
				{
					cout << "Wool is off by " << p.second << endl;
				}
				returnValue = 1;
			}
		}
	}

	if (returnValue <= 0)
	{
		for (auto p : rollValueCounter)
		{
			if (p.second != 0)
			{
				cout << "Roll Number " << p.first << " is off by " << p.second << endl;
				returnValue = 1;
			}
		}
	}

	return returnValue;
}


//this will ensure that the initial node conditions are what they are expected to be
//for each node in the game board
int GameBoardTestCases::gameBoard_checkNodeInitialConditions()
{
	//should either return 2 or 0
	int returnValue = 0;

	for (Node node : board.nodes)
	{
		if (node.occupiedBy != GameBoard::PlayerColors::None
			|| node.typeOfBuilding != GameBoard::BuildingType::None
			|| node.borderingEdges.empty())
		{
			returnValue = 2;
		}
	}

	//those nodes should have a trade "any" port
	if (board.nodes[0].port != GameBoard::Elements::Any
		|| board.nodes[3].port != GameBoard::Elements::Any
		|| board.nodes[10].port != GameBoard::Elements::Any
		|| board.nodes[15].port != GameBoard::Elements::Any
		|| board.nodes[26].port != GameBoard::Elements::Any
		|| board.nodes[32].port != GameBoard::Elements::Any
		|| board.nodes[47].port != GameBoard::Elements::Any
		|| board.nodes[51].port != GameBoard::Elements::Any
		|| board.nodes[0].port != GameBoard::Elements::Any)
	{
		returnValue = 2;
	}
	else if (board.nodes[1].port != GameBoard::Elements::Wool
		|| board.nodes[5].port != GameBoard::Elements::Wool)
	{
		returnValue = 2;
	}
	else if (board.nodes[42].port != GameBoard::Elements::Brick
		|| board.nodes[46].port != GameBoard::Elements::Brick)
	{
		returnValue = 2;
	}
	else if (board.nodes[49].port != GameBoard::Elements::Lumber
		|| board.nodes[52].port != GameBoard::Elements::Lumber)
	{
		returnValue = 2;
	}
	else if (board.nodes[33].port != GameBoard::Elements::Grain
		|| board.nodes[38].port != GameBoard::Elements::Grain)
	{
		returnValue = 2;
	}
	else if (board.nodes[11].port != GameBoard::Elements::Ore
		|| board.nodes[16].port != GameBoard::Elements::Ore)
	{
		returnValue = 2;
	}

	return returnValue;
}


//this will ensure that the intial edge conditions are what they are expected to be
//for each edge in the game board
int GameBoardTestCases::gameBoard_checkEdgeInitialConditions()
{
	//should either return 4 or 0
	int returnValue = 0;

	for (Edge edge : board.edges)
	{
		if (edge.occupiedBy != GameBoard::PlayerColors::None
			|| edge.borderingNodes.empty())
		{
			returnValue = 4;
		}
	}

	return returnValue;
}


//this will ensure that the initial development card conditions are what they are expected to be
//for each development card in the game board
int GameBoardTestCases::gameBoard_checkDevelopmentCardInitialConditions()
{
	//should either return 8 or 0
	int returnValue = 0;

	map<GameBoard::DevelopmentCardTypes, int> developmentCardCounter;
	developmentCardCounter.insert(std::make_pair(GameBoard::DevelopmentCardTypes::Knight, 14));
	developmentCardCounter.insert(std::make_pair(GameBoard::DevelopmentCardTypes::Monopoly, 2));
	developmentCardCounter.insert(std::make_pair(GameBoard::DevelopmentCardTypes::RoadBuilding, 2));
	developmentCardCounter.insert(std::make_pair(GameBoard::DevelopmentCardTypes::VictoryPoint, 5));
	developmentCardCounter.insert(std::make_pair(GameBoard::DevelopmentCardTypes::YearOfPlenty, 2));

	for (GameBoard::DevelopmentCardTypes card : board.developmentCards)
	{
		--developmentCardCounter[card];
	}

	for (auto iter : developmentCardCounter)
	{
		if (iter.second != 0)
		{
			if (iter.first == GameBoard::DevelopmentCardTypes::Knight)
			{
				cout << "Knight cards are off by " << iter.second << endl;
			}
			else if (iter.first == GameBoard::DevelopmentCardTypes::Monopoly)
			{
				cout << "Monopoly cards are off by " << iter.second << endl;
			}
			else if (iter.first == GameBoard::DevelopmentCardTypes::RoadBuilding)
			{
				cout << "Road Building cards are off by " << iter.second << endl;
			}
			else if (iter.first == GameBoard::DevelopmentCardTypes::VictoryPoint)
			{
				cout << "Victory Point cards are off by " << iter.second << endl;
			}
			else if (iter.first == GameBoard::DevelopmentCardTypes::YearOfPlenty)
			{
				cout << "Year Of Plenty cards are off by " << iter.second << endl;
			}

			returnValue = 8;
		}
	}

	return returnValue;
}


//Cannot fill this out until we finish the player class
//this will ensure that the initial player conditions are what they are expected to be
//for each development card in the game board
int GameBoardTestCases::gameBoard_checkPlayerInitialConditions()
{
	//should either return 16 or 0
	int returnValue = 0;
	return returnValue;
}


//this will ensure that the initial robber location conditions are what they are expected to be
//for each development card in the game board
int GameBoardTestCases::gameBoard_checkRobberLocationInitialConditions()
{
	//should either return 32 or 0
	int returnValue = 0;

	for (auto tilePointer = board.tiles.begin(); tilePointer != board.tiles.end(); ++tilePointer)
	{
		if (tilePointer->element == GameBoard::Elements::Desert)
		{
			if (&board.tiles[board.robberTileNumber] != tilePointer._Ptr)
			{
				returnValue = 32;
			}
		}
	}

	return returnValue;
}


//this will ensure that each resource tile has the correct node associations
//based on the numbering scheme for the nodes and resource tiles established previously
int GameBoardTestCases::resourceTile_checkNodeAssociations()
{
	//should either return 64 or 0
	int returnValue = 0;
	return returnValue;
}


//this will ensure that each node has the correct edge associations based on the numbering scheme
//of nodes and edges established previous
int GameBoardTestCases::node_checkEdgeAssociations()
{
	//should either return 128 or 0
	int returnValue = 0;
	return returnValue;
}


//this will ensure that each edge has the correct node associations based on the numbering scheme
//of edges and nodes established previous
int GameBoardTestCases::edge_checkNodeAssociations()
{
	//should either return 256 or 0
	int returnValue = 0;
	return returnValue;
}
