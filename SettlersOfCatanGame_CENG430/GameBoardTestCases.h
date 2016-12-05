#pragma once

#include "GameBoard.h"

/*
	Test cases delayed because of incomplete implementation:
		gameBoard_checkPlayerInitialConditions
*/

//naming format:	<object tested>_<part of object tested>
//note:  initial condition tests refer to everything except the various object associations (e.g. that each resource tile contains the correct node pointers)
//		association tests refer to the process of ensuring that stated vector pointer within the object has the correct associations
class GameBoardTestCases
{
	private:
		GameBoard board;

	public:
		int runTestCases();

		//1
		int gameBoard_checkResourceTileInitialConditions();
		//2
		int gameBoard_checkNodeInitialConditions();
		//4
		int gameBoard_checkEdgeInitialConditions();
		//8
		int gameBoard_checkDevelopmentCardInitialConditions();
		//16
		int gameBoard_checkPlayerInitialConditions();
		//32
		int gameBoard_checkRobberLocationInitialConditions();
		
		//64
		int resourceTile_checkNodeAssociations();

		//128
		int node_checkEdgeAssociations();

		//256
		int edge_checkNodeAssociations();
};