/*																								  */

#include <iostream>

#include "BSTree.h"

int main()
{
	BSTree<double> theBST;
	bool(runProgram) = true;
	int menuInput;
	double userInput;

	while (runProgram)
	{
		std::cout << " 1. Add a new node" << std::endl;
		std::cout << "99. Exit program" << std::endl;
		std::cout << std::endl;

		std::cout << "Your choice: ";
		std::cin >> menuInput;

		switch (menuInput)
		{
		case 1:		// Add a new node
			std::cout << "Enter the node value: ";
			std::cin >> userInput;
			theBST.CreateNode(userInput);
			break;
		case 99:	// Exit program
			runProgram = false;
			break;
		default:
			std::cout << "Function not implemented." << std::endl;
		}
		std::cout << std::endl;
	}
	return 0; // Exit program
}