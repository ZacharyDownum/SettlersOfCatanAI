#include "Player.h"
#include "Edge.h"
#include "Node.h"
#include <algorithm>

using std::vector;
using std::string;

Player::Player()
{
	resourceCards.insert(std::make_pair(GameBoard::Elements::Brick, 0));
	resourceCards.insert(std::make_pair(GameBoard::Elements::Grain, 0));
	resourceCards.insert(std::make_pair(GameBoard::Elements::Lumber, 0));
	resourceCards.insert(std::make_pair(GameBoard::Elements::Ore, 0));
	resourceCards.insert(std::make_pair(GameBoard::Elements::Wool, 0));

	numberOfVictoryPoints = 0;
	lengthOfLongestRoad = 0;
	numberOfKnightsPlayed = 0;

	color = GameBoard::PlayerColors::None;
}

Player::Player(string name)
{
	resourceCards.insert(std::make_pair(GameBoard::Elements::Brick, 0));
	resourceCards.insert(std::make_pair(GameBoard::Elements::Grain, 0));
	resourceCards.insert(std::make_pair(GameBoard::Elements::Lumber, 0));
	resourceCards.insert(std::make_pair(GameBoard::Elements::Ore, 0));
	resourceCards.insert(std::make_pair(GameBoard::Elements::Wool, 0));

	numberOfVictoryPoints = 0;
	lengthOfLongestRoad = 0;
	numberOfKnightsPlayed = 0;

	color = GameBoard::PlayerColors::None;

	this->name = name;
}

bool Player::buildSettlement(GameBoard* gameboard, int nodeNumber)
{
	bool result = true;

	if (this->resourceCards[GameBoard::Elements::Brick] < 1
		|| this->resourceCards[GameBoard::Elements::Lumber] < 1
		|| this->resourceCards[GameBoard::Elements::Grain] < 1
		|| this->resourceCards[GameBoard::Elements::Wool] < 1)
	{
		result = false;
	}
	
	if (result)
	{
		for (Edge* edgePointer : gameboard->nodes[nodeNumber].borderingEdges)
		{
			for (Node* nodePointer : edgePointer->borderingNodes)
			{
				if (nodePointer->occupiedBy != GameBoard::PlayerColors::None)
				{
					result = false;
				}
			}
		}
	}

	if (result)
	{
		gameboard->nodes[nodeNumber].occupiedBy = this->color;
		gameboard->nodes[nodeNumber].typeOfBuilding = GameBoard::BuildingType::Settlement;
		--this->resourceCards[GameBoard::Elements::Brick];
		--this->resourceCards[GameBoard::Elements::Lumber];
		--this->resourceCards[GameBoard::Elements::Grain];
		--this->resourceCards[GameBoard::Elements::Wool];
	}

	return result;
}

bool Player::upgradeSettlement(GameBoard * gameboard, int nodeNumber)
{
	bool result = false;

	if (gameboard->nodes[nodeNumber].occupiedBy == this->color
		&& gameboard->nodes[nodeNumber].typeOfBuilding == GameBoard::BuildingType::Settlement
		&& this->resourceCards[GameBoard::Elements::Grain] >= 2
		&& this->resourceCards[GameBoard::Elements::Ore] >= 3)
	{
		gameboard->nodes[nodeNumber].typeOfBuilding = GameBoard::BuildingType::City;
		this->resourceCards[GameBoard::Elements::Grain] -= 2;
		this->resourceCards[GameBoard::Elements::Ore] -= 3;

		result = true;
	}

	return result;
}

bool Player::buildRoad(GameBoard * gameboard, int edgeNumber)
{
	//if any nearby edges are your road
	//if any bordering nodes are your city or settlement

	bool result = false;

	if (this->resourceCards[GameBoard::Elements::Brick] >= 1
		&& this->resourceCards[GameBoard::Elements::Lumber] >= 1
		&& gameboard->edges[edgeNumber].occupiedBy == GameBoard::PlayerColors::None)
	{
		bool isValidLocation = false;
		for (Node* nodePointer : gameboard->edges[edgeNumber].borderingNodes)
		{
			if (nodePointer->occupiedBy == this->color)
			{
				isValidLocation = true;
			}
			else
			{
				for (Edge* edgePointer : nodePointer->borderingEdges)
				{
					if (edgePointer->occupiedBy == this->color)
					{
						if (nodePointer->occupiedBy == GameBoard::PlayerColors::None)
						{
							isValidLocation = true;
						}
					}
				}
			}
		}

		if (isValidLocation)
		{
			gameboard->edges[edgeNumber].occupiedBy = this->color;
			--this->resourceCards[GameBoard::Elements::Brick];
			--this->resourceCards[GameBoard::Elements::Lumber];
		}
	}

	return result;
}

bool Player::buyDevelopmentCard(GameBoard* gameboard)
{
	bool result = false;

	if (this->resourceCards[GameBoard::Elements::Wool] >= 1
		&& this->resourceCards[GameBoard::Elements::Grain] >= 1
		&& this->resourceCards[GameBoard::Elements::Ore] >= 1)
	{
		if (!gameboard->developmentCards.empty())
		{
			this->developmentCards.push_back(gameboard->developmentCards.back());
			gameboard->developmentCards.pop_back();
			--this->resourceCards[GameBoard::Elements::Wool];
			--this->resourceCards[GameBoard::Elements::Grain];
			--this->resourceCards[GameBoard::Elements::Ore];


			result = true;
		}
	}

	return result;
}

bool Player::playDevelopmentCard(GameBoard* gameboard, GameBoard::DevelopmentCardTypes cardType)
{
	bool result = false;

	vector<GameBoard::DevelopmentCardTypes>::iterator iter;
	iter = std::find(developmentCards.begin(), developmentCards.end(), cardType);

	if (iter != developmentCards.end())
	{
		if (cardType == GameBoard::DevelopmentCardTypes::Knight)
		{
			playKnightCard(gameboard);
		}
		else if (cardType == GameBoard::DevelopmentCardTypes::Monopoly)
		{
			playMonopolyCard(gameboard);
		}
		else if (cardType == GameBoard::DevelopmentCardTypes::RoadBuilding)
		{
			playRoadBuildingCard(gameboard);
		}
	}

	for (GameBoard::DevelopmentCardTypes card : this->developmentCards)
	{
		if (cardType == card)
		{

		}
	}

	result = true;
}

bool Player::usePort(GameBoard* gameboard, GameBoard::Elements fromElement, GameBoard::Elements toElement)
{
	bool result = false;

	for (Node node : gameboard->nodes)
	{
		if (node.occupiedBy == this->color && node.port == fromElement)
		{
			if (this->resourceCards[fromElement] >= 2)
			{
				this->resourceCards[fromElement] -= 2;
				++this->resourceCards[toElement];

				result = true;
			}
		}
	}

	for (Node node : gameboard->nodes)
	{
		if (node.occupiedBy == this->color && node.port == GameBoard::Elements::Any)
		{
			if (this->resourceCards[fromElement] >= 3)
			{
				this->resourceCards[fromElement] -= 3;
				++this->resourceCards[toElement];

				result = true;
			}
		}
	}

	return result;
}

bool Player::exchangeCards(GameBoard * gameboard, GameBoard::Elements fromElement, GameBoard::Elements toElement)
{
	bool result = false;

	if (this->resourceCards[fromElement] >= 4)
	{
		this->resourceCards[fromElement] -= 4;
		++this->resourceCards[toElement];

		result = true;
	}

	return result;
}

bool Player::checkWinConditions(GameBoard* gameboard)
{
	bool result = false;

	this->evaluateVictoryPoints(gameboard);

	if (this->numberOfVictoryPoints >= 10)
	{
		result = true;
	}

	return result;
}

int Player::evaluateRoadLength(Edge* startingEdge, vector<Edge*> connectedEdges, int roadLength)
{
	vector<Edge*>::iterator position = std::find(connectedEdges.begin(), connectedEdges.end(), startingEdge);
	connectedEdges.erase(position);
	++roadLength;

	if (!connectedEdges.empty())
	{
		for (Node* nodePointer : startingEdge->borderingNodes)
		{
			for (Edge* edgePointer : nodePointer->borderingEdges)
			{
				if (std::find(connectedEdges.begin(), connectedEdges.end(), edgePointer) != connectedEdges.end())
				{
					roadLength = std::max(roadLength, evaluateRoadLength(edgePointer, connectedEdges, roadLength));
				}
			}
		}
	}

	return roadLength;
}

void Player::makeRandomMove(GameBoard* gameboard)
{
	//need to finish this method
}

void Player::evaluateVictoryPoints(GameBoard* gameboard)
{
	int result = 0;

	this->numberOfVictoryPoints = result;
}

void Player::evaluateLongestRoad(GameBoard* gameboard)
{
	vector<Edge*> occupiedEdges;
	vector<Edge*> markedEdges;
	vector<Edge*>::iterator position;
	vector<vector<Edge*>> connectedEdgeSets;

	for (int edgeNumber = 0; edgeNumber < gameboard->edges.size(); ++edgeNumber)
	{
		if (gameboard->edges[edgeNumber].occupiedBy == this->color)
		{
			occupiedEdges.push_back(&gameboard->edges[edgeNumber]);
		}
	}

	while (!occupiedEdges.empty())
	{
		markedEdges.clear();
		markedEdges[0] = occupiedEdges[0];
		occupiedEdges.erase(occupiedEdges.begin());

		for (Edge* edgePointer : markedEdges)
		{
			for (Node* nodePointer : edgePointer->borderingNodes)
			{
				if (nodePointer->occupiedBy == GameBoard::PlayerColors::None || nodePointer->occupiedBy == this->color)
				{
					for (int edgeNumber = 0; edgeNumber < nodePointer->borderingEdges.size(); ++edgeNumber)
					{
						if (nodePointer->borderingEdges[edgeNumber] != edgePointer && nodePointer->borderingEdges[edgeNumber]->occupiedBy == this->color)
						{
							markedEdges.push_back(nodePointer->borderingEdges[edgeNumber]);
							position = std::find(occupiedEdges.begin(), occupiedEdges.end(), nodePointer->borderingEdges[edgeNumber]);
							occupiedEdges.erase(position);
						}
					}
				}
			}
		}

		connectedEdgeSets.push_back(markedEdges);
	}

	//Ok, for each set, do the following:
	int longestRoadLength = 0;
	for (vector<Edge*> vectorPointer : connectedEdgeSets)
	{
		Edge* startingEdge = NULL;

		// Set startingEdge
		for (Edge* edgePointer : vectorPointer)
		{
			int numberConnectedEdges = 0;
			for (Node* nodePointer : edgePointer->borderingNodes)
			{
				for (Edge* edgePointer2 : nodePointer->borderingEdges)
				{
					if (edgePointer2->occupiedBy == this->color && edgePointer != edgePointer2)
					{
						++numberConnectedEdges;
					}
				}
			}

			if (numberConnectedEdges == 1)
			{
				startingEdge = edgePointer;
			}
		}
		if (startingEdge == NULL)
		{
			int k = rand() % vectorPointer.size();
			startingEdge = vectorPointer[k];
		}

		longestRoadLength = evaluateRoadLength(startingEdge, vectorPointer, longestRoadLength);

	}

	this->lengthOfLongestRoad = longestRoadLength;
}