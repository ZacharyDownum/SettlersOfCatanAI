#include "GameBoard.h"
#include "Node.h"
#include "Edge.h"
#include "ResourceTile.h"
#include "Player.h"
#include "GameBoardTestCases.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main()
{
	//need to finish GameBoardTestCases
	//Find out from Dr. Foust about the issue with gameBoard_checkRobberLocationInitialConditions pointers
	GameBoardTestCases tester;
	cout << tester.runTestCases() << endl;
	cout << "Test";
}