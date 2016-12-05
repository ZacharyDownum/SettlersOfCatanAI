#pragma once

#include "Player.h"

class HumanPlayer : Player
{
	protected:
		virtual void getVictoryPoints(GameBoard* gameboard);
		virtual void getArmySizes(GameBoard* gameboard);
		virtual void getLongestRoadLengths(GameBoard* gameboard);

		virtual void getColors(GameBoard* gameboard);
		virtual void listResourceCards(GameBoard* gameboard);
		virtual void listDevelopmentCards(GameBoard* gameboard);

		virtual void getName(GameBoard* gameboard);

		virtual void playKnightCard(GameBoard* gameboard);
		virtual void playMonopolyCard(GameBoard* gameboard);
		virtual void playRoadBuildingCard(GameBoard* gameboard);


	public:
		HumanPlayer(std::string name);

		virtual void chooseMove(GameBoard* gameboard);
		//needs to handle error checking
		virtual int chooseRobberLocation(GameBoard* gameboard);
		virtual GameBoard::PlayerColors choosePlayerToStealCardFrom(GameBoard* gameboard, int robberTileNumber);
		virtual GameBoard::Elements chooseResourceCardToSteal(GameBoard* gameboard);
		virtual int chooseEdgeToBuildRoadOn(GameBoard* gameboard);
};