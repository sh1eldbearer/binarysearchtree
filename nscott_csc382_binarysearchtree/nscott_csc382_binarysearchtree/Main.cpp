/*																								  */

#include <iostream>
#include <array>

#include "BSTree.h"

// See function definitions for descriptions
template<typename Type> bool GetUserInput(Type* userInput);
bool TestUserInput();

int main()
{
	BSTree<double> theBST;
	bool(runProgram) = true;
	int menuInput;
	double userInput;
	
	// Simple testing array
	// TODO: Function for dynamically sized arrays?

	
	std::array<double,19> testValues = { 8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15, 14.5, 16, 15.5, 17 };
	//std::array<double, 9> testValues = { 12, 8, 5, 11, 4, 7, 2, 18, 17 };
	//std::array<double, 10> testValues = { 2, 1, 3, 4, 5, 6, 7, 8, 9, 10 };
	for (int count = 0; count < (int)testValues.size(); count++)
	{
		theBST.InsertValue(testValues[count]);
	}

	while (runProgram)
	{
		std::cout << " 1. Add a new node" << std::endl;
		std::cout << " 2. Find a value stored in the tree" << std::endl;
		std::cout << " 3. Delete a node from the tree" << std::endl;
		std::cout << " 4. Show the minimum value stored in the tree" << std::endl;
		std::cout << " 5. Show the maximum value stored in the tree" << std::endl;
		std::cout << " 6. Rotate a node to the left" << std::endl;
		std::cout << " 7. Rotate a node to the right" << std::endl;
		//std::cout << "44. Balance the tree" << std::endl;
		std::cout << "55. Display info about a specific node" << std::endl;
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
					theBST.InsertValue(userInput);
				}
				break;
			case 2:		// Find a new node
				std::cout << "Enter the value you want to find: ";
				if (GetUserInput(&userInput))
				{
					theBST.FindValue(userInput);
				}
				break;
			case 3:		// Delete a node containing a value
				std::cout << "Enter the value you wish to delete: ";
				if (GetUserInput(&userInput))
				{
					theBST.DeleteValue(userInput);
				}
				break;
			case 4:
				std::cout << "The smallest value stored in the tree is " <<
					theBST.MinValue() << std::endl;
				break;
			case 5:
				std::cout << "The smallest value stored in the tree is " <<
					theBST.MaxValue() << std::endl;
				break;
			case 6:
				std::cout << "Enter the value you wish to rotate to the left: ";
				if (GetUserInput(&userInput))
				{
					theBST.LeftNodeRotation(theBST.FindValue(userInput, false));
				}
				break;
			case 7:
				std::cout << "Enter the value you wish to rotate to the right: ";
				if (GetUserInput(&userInput))
				{
					theBST.RightNodeRotation(theBST.FindValue(userInput, false));
				}
				break;
			case 44:
				//theBST.BalanceTree();
				break;
			case 55:
				std::cout << "Enter the value of the node you wish to know about: ";
				if (GetUserInput(&userInput))
				{
					theBST.GetNodeDetails(theBST.FindValue(userInput, false));
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
template<typename Type> bool GetUserInput(Type* userInput) 
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