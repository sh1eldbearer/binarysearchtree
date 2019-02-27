#include <iostream>
#include <array>
#include <ctime>

#include "BSTree.h"

// See function definitions for descriptions
template<typename Type> bool TestUserInput(Type* userInput, bool clearScreen = false);
template <typename Type> void AddNodes(BSTree<Type>* theBST, int nodeCount);

int main()
{
	BSTree<int> theBST;
	bool runProgram = true;
	int menuInput;
	int userInput;

	while (runProgram)
	{
		std::cout << "BINARY SEARCH TREE PROGRAM\n\n"
			<< " 1. Insert new value into tree"
			<< "\n 6. Delete value from the tree"
			<< "\n 7. Delete all values from the tree\n"

			<< "\n11. Find a value in the tree"
			<< "\n12. Find the minimum value stored in the tree"
			<< "\n13. Find the maximum value stored in the tree\n"

			<< "\n66. Print the tree\n"

			<< "\nOPTIONS 81-85 WILL DELETE ALL VALUES IN THE TREE BEFORE ADDING NEW VALUES"
			<< "\nENTER NEGATIVE MENU NUMBERS TO ADD VALUES FROM LARGEST TO SMALLEST"
			<< "\n81. Insert 10 values into the tree"
			<< "\n82. Insert 100 values into the tree"
			<< "\n83. Insert 1000 values into the tree"
			<< "\n84. Insert 10000 values into the tree"
			<< "\n85. Insert 100000 values into the tree\n"

			<< "\n99. Exit program"
			
			<< "\n\nYour choice, please: ";

		if (TestUserInput(&menuInput, true))
		{
			switch (menuInput)
			{
			case 1:		// Insert a value
				std::cout << "Enter the value you wish to insert: ";
				if (TestUserInput(&userInput))
				{
					theBST.Insert(userInput);
				}
				break;
			case 6:		// Delete a value
				std::cout << "Enter the value you wish to delete: ";
				if (TestUserInput(&userInput))
				{
					theBST.Delete(userInput);
				}
				break;
			case 7:		// Delete all values
				theBST.DeleteAll();
				break;
			case 11:	// Find a value
				std::cout << "Enter the value you wish to find: ";
				if (TestUserInput(&userInput))
				{
					theBST.Find(userInput);
				}
				break;
			case 12:	// Find the minimum value
				theBST.Minimum();
				break;
			case 13:	// Find the maximum value
				theBST.Maximum();
				break;
			case 66:	// Print the tree to the console
				theBST.Print();
				break;
			case -81:	// Add 10 nodes to the BST (reverse)
				AddNodes(&theBST, -10);
				break;
			case 81:	// Add 10 nodes to the BST
				AddNodes(&theBST, 10);
				break;
			case -82:	// Add 100 nodes to the BST (reverse)
				AddNodes(&theBST, -100);
				break;
			case 82:	// Add 100 nodes to the BST
				AddNodes(&theBST, 100);
				break;
			case -83:	// Add 1000 nodes to the BST (reverse)
				AddNodes(&theBST, -1000);
				break;
			case 83:	// Add 1000 nodes to the BST
				AddNodes(&theBST, 1000);
				break;
			case -84:	// Add 10000 nodes to the BST (reverse)
				AddNodes(&theBST, -10000);
				break;
			case 84:	// Add 10000 nodes to the BST
				AddNodes(&theBST, 10000);
				break;
			case -85:	// Add 100000 nodes to the BST (reverse)
				AddNodes(&theBST, -100000);
				break;
			case 85:	// Add 100000 nodes to the BST
				AddNodes(&theBST, 100000);
				break;
			case 99:	// Exit the program
				runProgram = false;
				break;
			default:	// Invalid entry
				std::cout << "Sorry, can't do that.\n\n";
				break;
			}
		}
	}
}

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
template <typename Type> void AddNodes(BSTree<Type>* theBST, int nodeCount)
{
	theBST->DeleteAll(false);
	std::cout << "Working...\n";
	clock_t runTimer;
	runTimer = clock();
	if (nodeCount > 0)
	{
		for (int count = 1; count <= nodeCount; count++)
		{
			theBST->Insert((Type)count, false);
		}
	}
	else
	{
		for (int count = -nodeCount; count > 0; count--)
		{
			theBST->Insert((Type)count, false);
		}
	}
	runTimer = clock() - runTimer;
	system("cls");
	std::cout << "Adding " << nodeCount << " nodes took " << runTimer << " clicks (" << ((float)runTimer / CLOCKS_PER_SEC) << " seconds).\n\n\a";
}