/*																								  */

#include <iostream>

#include "BSTree.h"

template<typename T> bool GetUserInput(T* userInput);
bool TestUserInput();

int main()
{
	BSTree<double> theBST;
	bool(runProgram) = true;
	int menuInput;
	double userInput, userInput2;

	while (runProgram)
	{
		std::cout << " 1. Add a new node" << std::endl;
		std::cout << " 2. Find a value stored in the tree" << std::endl;
		std::cout << " 3. Delete a node from the tree" << std::endl;
		std::cout << " 4. Swap two node values" << std::endl;
		std::cout << "66. Display tree" << std::endl;
		std::cout << "99. Exit program" << std::endl;
		std::cout << std::endl;

		std::cout << "Your choice: ";
		if (GetUserInput(&menuInput))
		{
			switch (menuInput)
			{
			case 1:		// Add a new node
				std::cout << "Enter the node value: ";
				if (GetUserInput(&userInput))
				{
					theBST.CreateNode(userInput);
				}
				break;
			case 2:		// Find a new node
				std::cout << "Enter the value you want to find: ";
				if (GetUserInput(&userInput))
				{
					theBST.FindNode(userInput, true);
				}
				break;
			case 4:
				std::cout << "Enter the first value to swap: ";
				if (GetUserInput(&userInput))
				{
					std::cout << "Enter the second value to swap: ";
					if (GetUserInput(&userInput2))
					{
						theBST.SwapValues(userInput, userInput2);
					}
				}
				break;
			case 66:
				theBST.PrintTree();
				break;
			case 99:	// Exit program
				runProgram = false;
				break;
			default:
				std::cout << "Function not implemented." << std::endl;
			}
			std::cout << std::endl;
		}
	}

	return 0; // Exit program
}

// Gets user input
template<typename T> bool GetUserInput(T* userInput) 
{
	std::cin >> *userInput;

	return TestUserInput();
}

// Tests cin for failure and clears cin's flags and input buffer afterward
bool TestUserInput()
{
	bool failure;

	// Checks to see if there were any problems getting the user's input
	failure = std::cin.fail();
	// Clears cin's failure flag for next input
	std::cin.clear();
	// Clears the input buffer
	std::cin.ignore(256, '\n');

	if (failure) // User did not input a valid value
	{
		std::cout << "Invalid entry. Please try again." << std::endl;
	}

	// Returns whether the input was valid (true) or not (false)
	return !failure;
}