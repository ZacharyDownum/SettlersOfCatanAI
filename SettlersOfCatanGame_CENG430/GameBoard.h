#pragma once

#include <vector>
#include <iostream>

class Edge;
class Node;
class Player;
class ResourceTile;

class GameBoard
{
	private:
		void initializeResourceTiles();
		void initializeNodes();
		void initializeEdges();
		void initializePorts();
		void initializeDevelopmentCards();
		void initializePlayers();

		void executeTurn();

		const int NUMBER_OF_NODES = 54;
		const int NUMBER_OF_EDGES = 72;
		const int NUMBER_OF_KNIGHT_CARDS = 14;
		const int NUMBER_OF_VICTORYPOINT_CARDS = 5;
		const int NUMBER_OF_YEAROFPLENTY_CARDS = 2;
		const int NUMBER_OF_MONOPOLY_CARDS = 2;
		const int NUMBER_OF_ROADBUILDING_CARDS = 2;


	public:
		enum class PlayerColors
		{
			None,
			Red,
			Blue,
			White,
			Orange
		};

		enum class Elements
		{
			None,
			Any,
			Lumber,
			Brick,
			Grain,
			Wool,
			Ore,
			Desert
		};

		enum class BuildingType
		{
			None,
			Settlement,
			City
		};

		enum class DevelopmentCardTypes
		{
			Knight,
			VictoryPoint,
			YearOfPlenty,
			Monopoly,
			RoadBuilding
		};
		
		std::vector<ResourceTile> tiles;
		std::vector<Node> nodes;
		std::vector<Edge> edges;
		std::vector<DevelopmentCardTypes> developmentCards;
		std::vector<Player*> players;
		
		int robberTileNumber;

		GameBoard();
		GameBoard(const GameBoard& g);

		void rollDice(Player& p);
		//only reason to return false is if the resourceTileNumber was the same one the robber is currently on
		//this functionality is moved to the player class
		void moveRobber(Player& p);
		void stealCard(Player& fromPlayer, Player& toPlayer);
		void distributeCards(int diceNumber);

		void startGame();
};

std::ostream& operator<<(std::ostream& out, const GameBoard::PlayerColors& color) {
	if (color == GameBoard::PlayerColors::Blue)
	{
		return out << "Blue";
	}
	else if (color == GameBoard::PlayerColors::Orange)
	{
		return out << "Orange";
	}
	else if (color == GameBoard::PlayerColors::Red)
	{
		return out << "Red";
	}
	else if (color == GameBoard::PlayerColors::White)
	{
		return out << "White";
	}
	else if (color == GameBoard::PlayerColors::None)
	{
		return out << "None";
	}

	return out;
}