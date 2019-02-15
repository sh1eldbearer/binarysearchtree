#include <iostream>
#include <array>
#include <ctime>

#include "BSTree_OLD.h"

// See function definitions for descriptions
template<typename Type> bool TestUserInput(Type* userInput, bool clearScreen = false);
template <typename Type> void AddNodes(BSTree_OLD<Type>* theBST, int nodeCount);
/*
int main()
{
	BSTree_OLD<double> theBST;
	bool(runProgram) = true;
	int menuInput;
	double userInput;

	// Simple testing arrays
	std::array<double, 19> testArray = { 8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15, 14.5, 16, 15.5, 17 };
	std::array<double, 9> testArray2 = { 12, 8, 5, 11, 4, 7, 2, 18, 17 };
	std::array<double, 10> testArray3 = { 2, 1, 3, 4, 5, 6, 7, 8, 9, 10 };

	while (runProgram)
	{
		std::cout << "--- BINARY SEARCH TREE ---" << std::endl;
		std::cout << " 1. Add a new node" << std::endl;
		std::cout << " 2. Find a value stored in the tree" << std::endl;
		std::cout << " 3. Show the minimum value stored in the tree" << std::endl;
		std::cout << " 4. Show the maximum value stored in the tree" << std::endl;
		std::cout << " 5. Display info about a specific node" << std::endl;
		std::cout << " 6. Display tree (WARNING: Very tall trees will be difficult to read!)" << std::endl;
		std::cout << " 8. Delete a node from the tree" << std::endl;
		std::cout << " 9. Delete ALL the nodes from the tree" << std::endl;
		std::cout << "11. Add test array 1 to the BST (erases all other data)" << std::endl;
		std::cout << "12. Add test array 2 to the BST (erases all other data)" << std::endl;
		std::cout << "13. Add test array 3 to the BST (erases all other data)" << std::endl;
		std::cout << "16. Add 100 nodes to the BST (erases all other data)" << std::endl;
		std::cout << "17. Add 1000 nodes to the BST (erases all other data)" << std::endl;
		std::cout << "18. Add 10000 nodes to the BST (erases all other data)" << std::endl;
		std::cout << "19. Add 100000 nodes to the BST (erases all other data)" << std::endl;
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
			case 2:		// Find a value stored in the tree
				std::cout << "Enter the value you want to find: ";
				if (GetUserInput(&userInput))
				{
					theBST.FindValue(userInput);
				}
				break;
			case 3:		// Show the minimum value stored in the tree
				std::cout << "The smallest value stored in the tree is " <<
					theBST.MinValue(theBST.GetRoot()) << std::endl;
				break;
			case 4:		// Show the maximum value stored in the tree
				std::cout << "The smallest value stored in the tree is " <<
					theBST.MaxValue(theBST.GetRoot()) << std::endl;
				break;
			case 5:		// Display info about a specific node
				std::cout << "Enter the value of the node you wish to know more about: ";
				if (GetUserInput(&userInput))
				{
					theBST.GetNodeDetails(theBST.FindValue(userInput, false));
				}
				break;
			case 6:		// Display tree
				theBST.PrintTree();
				break;
			case 8:		// Delete a node from the tree
				std::cout << "Enter the value you wish to delete: ";
				if (GetUserInput(&userInput))
				{
					theBST.DeleteValue(userInput);
				}
				break;
			case 9:		// Delete ALL the nodes from the tree
				theBST.DeleteAllValues();
				break;
			case 11:	// Add test array 1 to the BST
				theBST.DeleteAllValues(false);
				for (int count = 0; count < (int)testArray.size(); count++)
				{
					theBST.InsertValue(testArray[count]);
				}
				break;
			case 12:	// Add test array 2 to the BST
				theBST.DeleteAllValues(false);
				for (int count = 0; count < (int)testArray2.size(); count++)
				{
					theBST.InsertValue(testArray2[count]);
				}
				break;
			case 13:	// Add test array 3 to the BST
				theBST.DeleteAllValues(false);
				for (int count = 0; count < (int)testArray3.size(); count++)
				{
					theBST.InsertValue(testArray3[count]);
				}
				break;
			case 16:	// Add 100 nodes to the BST
				AddNodes(&theBST, 100);
				break;
			case 17:	// Add 1000 nodes to the BST
				AddNodes(&theBST, 1000);
				break;
			case 18:	// Add 10000 nodes to the BST
				AddNodes(&theBST, 10000);
				break;
			case 19:	// Add 100000 nodes to the BST
				AddNodes(&theBST, 100000);
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
*/

// Gets user input
template<typename Type> bool TestUserInput(Type* userInput, bool clearScreen)
{
	bool failure;

	std::cin >> *userInput;

	if (clearScreen)
	{
		system("cls");
	}
	else
	{
		std::cout << std::endl;
	}

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

// Adds a number of nodes to the BST
template <typename Type> void AddNodes(BSTree_OLD<Type>* theBST, int nodeCount)
{
	//theBST->DeleteAllValues(false);
	std::cout << "Working...\n";
	clock_t runTimer;
	runTimer = clock();
	for (int count = 0; count < nodeCount; count++)
	{
		theBST->Insert((Type)count, false);
	}
	runTimer = clock() - runTimer;
	std::cout << "Adding " << nodeCount << " nodes took " << runTimer << " clicks (" << ((float)runTimer / CLOCKS_PER_SEC) << " seconds).\n\n";
}