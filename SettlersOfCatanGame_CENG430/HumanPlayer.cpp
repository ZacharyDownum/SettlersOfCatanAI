#include "HumanPlayer.h"
#include "GameBoard.h"
#include <iostream>

using std::string;
using std::cout;
using std::cin;
using std::endl;

HumanPlayer::HumanPlayer(string name) : Player(name)
{
}

void HumanPlayer::getVictoryPoints(GameBoard* gameboard)
{
	for (Player* p : gameboard->players)
	{
		cout << *p << ": " << p->numberOfVictoryPoints << " Victory Points" << endl;
	}
}

void HumanPlayer::getArmySizes(GameBoard* gameboard)
{
	for (Player* p : gameboard->players)
	{
		cout << *p << ": " << p->numberOfKnightsPlayed << " Knights" << endl;
	}
}

void HumanPlayer::getLongestRoadLengths(GameBoard* gameboard)
{
	for (Player* p : gameboard->players)
	{
		p->evaluateLongestRoad(gameboard);
		cout << *p << ": " << p->lengthOfLongestRoad << " sections long" << endl;
	}
}

void HumanPlayer::getColors(GameBoard* gameboard)
{
	for (Player* p : gameboard->players)
	{
		cout << p->name << " is the color " << p->color << endl;
	}
}

void HumanPlayer::listResourceCards(GameBoard* gameboard)
{

}

void HumanPlayer::listDevelopmentCards(GameBoard* gameboard)
{
}

void HumanPlayer::playKnightCard(GameBoard * gameboard)
{
	gameboard->moveRobber(*this);
	++numberOfKnightsPlayed;
}

void HumanPlayer::playMonopolyCard(GameBoard * gameboard)
{
	GameBoard::Elements chosenResource = GameBoard::Elements::None;

	string input = "None";
	cout << "Which resource card type do you want to steal?" << endl;

	std::getline(cin, input);
	while (input != "Lumber" && input != "Grain" && input != "Wool" && input != "Brick" && input != "Ore")
	{
		cout << "Please input either: Lumber, Grain, Wool, Brick, or Ore." << endl;
		std::getline(cin, input);
	}

	if (input == "Lumber")
	{
		chosenResource = GameBoard::Elements::Lumber;
	}
	else if (input == "Grain")
	{
		chosenResource = GameBoard::Elements::Grain;
	}
	else if (input == "Wool")
	{
		chosenResource = GameBoard::Elements::Wool;
	}
	else if (input == "Brick")
	{
		chosenResource = GameBoard::Elements::Brick;
	}
	else if (input == "Ore")
	{
		chosenResource = GameBoard::Elements::Ore;
	}

	for (Player* p : gameboard->players)
	{
		if (p != this)
		{
			for (auto pair : p->resourceCards)
			{
				if (pair.first == chosenResource)
				{
					this->resourceCards[chosenResource] += pair.second;
					pair.second = 0;
				}
			}
		}
	}
}

void HumanPlayer::playRoadBuildingCard(GameBoard * gameboard)
{
	int chosenEdgeNumber = -1;
	cout << "Please choose an edge number to build a road on." << endl;

	cin >> chosenEdgeNumber;

	this->resourceCards[GameBoard::Elements::]
	if ()


	while (input != "Lumber" && input != "Grain" && input != "Wool" && input != "Brick" && input != "Ore")
	{
		cout << "Please input either: Lumber, Grain, Wool, Brick, or Ore." << endl;
		std::getline(cin, input);
	}
}

void HumanPlayer::chooseMove(GameBoard* gameboard)
{
}

int HumanPlayer::chooseRobberLocation(GameBoard* gameboard)
{
}

GameBoard::PlayerColors HumanPlayer::choosePlayerToStealCardFrom(GameBoard* gameboard, int robberTileNumber)
{
}

GameBoard::Elements HumanPlayer::chooseResourceCardToSteal(GameBoard* gameboard)
{
}

int HumanPlayer::chooseEdgeToBuildRoadOn(GameBoard * gameboard)
{
}
