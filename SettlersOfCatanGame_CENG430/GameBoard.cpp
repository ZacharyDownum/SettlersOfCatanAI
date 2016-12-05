#include <algorithm>
#include <ctime>
#include "GameBoard.h"
#include "Edge.h"
#include "Node.h"
#include "ResourceTile.h"
#include "Player.h"

class Node;
class Edge;
class ResourceTile;

using std::random_shuffle;
using std::vector;

//the locationOfRobber is set to a default value here to avoid compiler errors
//it is actually set in the initializeResourceTiles method
GameBoard::GameBoard()
{
	robberTileNumber = -1;
	std::srand(std::time(0));

	initializeResourceTiles();
	initializeNodes();
	initializeEdges();
	initializePorts();
	initializeDevelopmentCards();
}

GameBoard::GameBoard(const GameBoard& g)
{
	tiles = g.tiles;
	nodes = g.nodes;
	edges = g.edges;
	developmentCards = g.developmentCards;
	players = g.players;
	robberTileNumber = g.robberTileNumber;
}

void GameBoard::initializeResourceTiles()
{
	vector<int> rollValues = { 5, 2, 6, 3, 8, 10, 9, 12, 11, 4, 8, 10, 9, 4, 5, 6, 3, 11 };
	vector<Elements> initialTiles = { GameBoard::Elements::Lumber, GameBoard::Elements::Lumber, GameBoard::Elements::Lumber, GameBoard::Elements::Lumber,
										GameBoard::Elements::Wool, GameBoard::Elements::Wool, GameBoard::Elements::Wool, GameBoard::Elements::Wool,
										GameBoard::Elements::Grain, GameBoard::Elements::Grain, GameBoard::Elements::Grain, GameBoard::Elements::Grain,
										GameBoard::Elements::Brick, GameBoard::Elements::Brick, GameBoard::Elements::Brick,
										GameBoard::Elements::Ore, GameBoard::Elements::Ore, GameBoard::Elements::Ore,
										GameBoard::Elements::Desert };
	random_shuffle(initialTiles.begin(), initialTiles.end());

	for (int i = 0; i < initialTiles.size(); ++i)
	{
		if (initialTiles[i] != GameBoard::Elements::Desert)
		{
			int value = rollValues.front();
			rollValues.erase(rollValues.begin());

			ResourceTile r(initialTiles[i], value);
			tiles.push_back(std::move(r));
		}
		else
		{
			ResourceTile r(initialTiles[i], 7);
			robberTileNumber = i;
			tiles.push_back(std::move(r));
		}
	}
}

void GameBoard::initializeNodes()
{
	nodes.resize(NUMBER_OF_NODES);
	for (int i = 0; i < NUMBER_OF_NODES; ++i)
	{
		Node temp;
		nodes[i] = std::move(temp);
	}
	
	//every 6 elements in this vector represent the node numbers
	//that are associated with each resource tile,
	//in the order the resource tiles appear in their list
	const vector<int> nodeToTileAssociationList = {39, 44, 48, 51, 47, 43,
											40, 45, 49, 52, 48, 44,
											41, 46, 50, 53, 49, 45,
											31, 37, 42, 46, 41, 36,
											20, 26, 32, 37, 31, 25,
											10, 15, 20, 25, 19, 14,
											2, 6, 10, 14, 9, 5,
											1, 5, 9, 13, 8, 4,
											0, 4, 8, 12, 7, 3,
											7, 12, 17, 22, 16, 11,
											16, 22, 28, 33, 27, 21,
											28, 34, 39, 43, 38, 33,
											29, 35, 40, 44, 39, 34,
											30, 36, 41, 45, 40, 35,
											19, 25, 31, 36, 30, 24,
											9, 14, 19, 24, 18, 13,
											8, 13, 18, 23, 17, 12,
											17, 23, 29, 34, 28, 22,
											18, 24, 30, 35, 29, 23};

	for (int tileNumber = 0; tileNumber < 19; ++tileNumber)
	{
		for (int nodeNumber = tileNumber * 6; nodeNumber < (tileNumber + 1) * 6; ++nodeNumber)
		{
			tiles[tileNumber].borderingNodes.push_back(&nodes[nodeToTileAssociationList[nodeNumber]]);
		}
	}
}

void GameBoard::initializeEdges()
{
	edges.resize(NUMBER_OF_EDGES);
	for (int edgeNumber = 0; edgeNumber < NUMBER_OF_EDGES; ++edgeNumber)
	{
		Edge temp;
		edges[edgeNumber] = std::move(temp);
	}

	//every 2 elements in this vector represent the node numbers
	//that are associated with each edge,
	//in the order the edges appear in their list
	const vector<int> nodeToEdgeAssociationList = {3, 0,
													0, 4,
													4, 1,
													1, 5,
													5, 2,
													2, 6,
													3, 7,
													4, 8,
													5, 9,
													6, 10,
													11, 7,
													7, 12,
													12, 8,
													8, 13,
													13, 9,
													9, 14,
													14, 10,
													10, 15,
													11, 16,
													12, 17,
													13, 18,
													14, 19,
													15, 20,
													21, 16,
													16, 22,
													22, 17,
													17, 23,
													23, 18,
													18, 24,
													24, 19,
													19, 25,
													25, 20,
													20, 26,
													21, 27,
													22, 28,
													23, 29,
													24, 30,
													25, 31,
													26, 32,
													27, 33,
													33, 28,
													28, 34,
													34, 29,
													29, 35,
													35, 30,
													30, 36,
													36, 31,
													31, 37,
													37, 32,
													33, 38,
													34, 39,
													35, 40,
													36, 41,
													37, 42,
													38, 43,
													43, 39,
													39, 44,
													44, 40,
													40, 45,
													45, 41,
													41, 46,
													46, 42,
													43, 47,
													44, 48,
													45, 49,
													46, 50,
													47, 51,
													51, 48,
													48, 52,
													52, 49,
													49, 53,
													53, 50};

	for (int edgeNumber = 0; edgeNumber < NUMBER_OF_EDGES; ++edgeNumber)
	{
		for (int nodeNumber = edgeNumber * 2; nodeNumber < (edgeNumber + 1) * 2; ++nodeNumber)
		{
			edges[edgeNumber].borderingNodes.push_back(&nodes[nodeToEdgeAssociationList[nodeNumber]]);
			nodes[nodeToEdgeAssociationList[nodeNumber]].borderingEdges.push_back(&edges[edgeNumber]);
		}
	}
}

void GameBoard::initializePorts()
{
	nodes[0].port = GameBoard::Elements::Any;
	nodes[1].port = GameBoard::Elements::Wool;
	nodes[3].port = GameBoard::Elements::Any;
	nodes[5].port = GameBoard::Elements::Wool;
	nodes[10].port = GameBoard::Elements::Any;
	nodes[11].port = GameBoard::Elements::Ore;
	nodes[15].port = GameBoard::Elements::Any;
	nodes[16].port = GameBoard::Elements::Ore;
	nodes[26].port = GameBoard::Elements::Any;
	nodes[32].port = GameBoard::Elements::Any;
	nodes[33].port = GameBoard::Elements::Grain;
	nodes[38].port = GameBoard::Elements::Grain;
	nodes[42].port = GameBoard::Elements::Brick;
	nodes[46].port = GameBoard::Elements::Brick;
	nodes[47].port = GameBoard::Elements::Any;
	nodes[49].port = GameBoard::Elements::Lumber;
	nodes[51].port = GameBoard::Elements::Any;
	nodes[52].port = GameBoard::Elements::Lumber;
}

void GameBoard::initializeDevelopmentCards()
{
	for (int cardCount = 0; cardCount < NUMBER_OF_KNIGHT_CARDS; ++cardCount)
	{
		developmentCards.push_back(GameBoard::DevelopmentCardTypes::Knight);
	}

	for (int cardCount = 0; cardCount < NUMBER_OF_VICTORYPOINT_CARDS; ++cardCount)
	{
		developmentCards.push_back(GameBoard::DevelopmentCardTypes::VictoryPoint);
	}

	for (int cardCount = 0; cardCount < NUMBER_OF_YEAROFPLENTY_CARDS; ++cardCount)
	{
		developmentCards.push_back(GameBoard::DevelopmentCardTypes::YearOfPlenty);
	}

	for (int cardCount = 0; cardCount < NUMBER_OF_MONOPOLY_CARDS; ++cardCount)
	{
		developmentCards.push_back(GameBoard::DevelopmentCardTypes::Monopoly);
	}

	for (int cardCount = 0; cardCount < NUMBER_OF_ROADBUILDING_CARDS; ++cardCount)
	{
		developmentCards.push_back(GameBoard::DevelopmentCardTypes::RoadBuilding);
	}

	random_shuffle(developmentCards.begin(), developmentCards.end());
}

void GameBoard::initializePlayers()
{
}


void GameBoard::rollDice(Player& p)
{
	vector<int> die1 = { 1, 2, 3, 4, 5, 6 };
	vector<int> die2 = { 1, 2, 3, 4, 5, 6 };

	random_shuffle(die1.begin(), die1.end());
	random_shuffle(die2.begin(), die2.end());

	int rollResult = die1.front() + die2.front();

	if (rollResult == 7)
	{
		moveRobber(p);
	}
	else
	{
		distributeCards(rollResult);
	}
}

void GameBoard::moveRobber(Player& player)
{
	robberTileNumber = player.chooseRobberLocation(this);

	GameBoard::PlayerColors chosenPlayer = player.choosePlayerToStealCardFrom(this, robberTileNumber);

	for (Player* p : players)
	{
		if (p->color == chosenPlayer)
		{
			stealCard(*p, player);
		}
	}
}

void GameBoard::stealCard(Player& fromPlayer, Player& toPlayer)
{
	vector<GameBoard::Elements> listOfPotentialCardsToSteal;

	for (auto pair : fromPlayer.resourceCards)
	{
		for (int i = 0; i < pair.second; ++i)
		{
			listOfPotentialCardsToSteal.push_back(pair.first);
		}
	}

	random_shuffle(listOfPotentialCardsToSteal.begin(), listOfPotentialCardsToSteal.end());

	++toPlayer.resourceCards[listOfPotentialCardsToSteal.front()];
	--fromPlayer.resourceCards[listOfPotentialCardsToSteal.front()];
}

void GameBoard::distributeCards(int diceNumber)
{
	for (ResourceTile& tile : tiles)
	{
		if (tile.rollValue == diceNumber)
		{
			for (Node* n : tile.borderingNodes)
			{
				if (n->occupiedBy != GameBoard::PlayerColors::None)
				{
					for (Player* p : players)
					{
						if (p->color == n->occupiedBy)
						{
							if (n->typeOfBuilding == GameBoard::BuildingType::Settlement)
							{
								++p->resourceCards[tile.element];
							}
							else
							{
								p->resourceCards[tile.element] += 2;
							}
						}
					}
				}
			}
		}
	}
}