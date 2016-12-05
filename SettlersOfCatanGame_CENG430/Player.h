#pragma once

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include "GameBoard.h"
#include "Node.h"

class Player
{
	protected:
		//choose move will call the rest of these functions to make its move
		virtual bool buildSettlement(GameBoard* gameboard, int nodeNumber);
		virtual bool upgradeSettlement(GameBoard* gameboard, int nodeNumber);
		virtual bool buildRoad(GameBoard* gameboard, int edgeNumber);
		virtual bool buyDevelopmentCard(GameBoard* gameboard);
		virtual bool playDevelopmentCard(GameBoard* gameboard, GameBoard::DevelopmentCardTypes cardType);
		virtual bool usePort(GameBoard* gameboard, GameBoard::Elements fromElement, GameBoard::Elements toElement);
		virtual bool exchangeCards(GameBoard* gameboard, GameBoard::Elements fromElement, GameBoard::Elements toElement);
		virtual bool checkWinConditions(GameBoard* gameboard);

		//returns the longest length of road out of all potential branches
		virtual int evaluateRoadLength(Edge* startingEdge, std::vector<Edge*> connectedEdges, int roadLength);

		virtual void makeRandomMove(GameBoard* gameboard);

		virtual void playKnightCard(GameBoard* gameboard) = 0;
		virtual void playMonopolyCard(GameBoard* gameboard) = 0;
		virtual void playRoadBuildingCard(GameBoard* gameboard) = 0;


	public:
		Player();
		Player(std::string name);

		std::map<GameBoard::Elements, int> resourceCards;
		std::vector<GameBoard::DevelopmentCardTypes> developmentCards;
		
		int numberOfVictoryPoints;
		int lengthOfLongestRoad;
		int numberOfKnightsPlayed;

		GameBoard::PlayerColors color;

		std::string name;
		
		virtual void evaluateVictoryPoints(GameBoard* gameboard);
		virtual void evaluateLongestRoad(GameBoard* gameboard);
		
		//allow the player to make their move and then end their turn
		virtual void chooseMove(GameBoard* gameboard) = 0;
		//needs to handle error checking
		virtual int chooseRobberLocation(GameBoard* gameboard) = 0;
		virtual GameBoard::PlayerColors choosePlayerToStealCardFrom(GameBoard* gameboard, int robberTileNumber) = 0;
};

std::ostream& operator<<(std::ostream &out, const Player& p) {
	return out << p.name << "(" << p.color << ")";
}