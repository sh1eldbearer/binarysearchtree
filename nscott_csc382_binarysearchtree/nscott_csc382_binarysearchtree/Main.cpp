#include <iostream>
#include <array>
#include <ctime>

#include "BSTree.h"

// See function definitions for descriptions
template<typename Type> bool TestUserInput(Type* userInput, bool clearScreen = false);
template <typename Type> void AddNodes(BSTree<Type>* theBST, int nodeCount);

int main()
{
	BSTree<float> theBST;
	bool runProgram = true;
	int menuInput;
	float userInput;

	// Simple testing arrays	
	std::array<float, 19> testArray1 = { 8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15, 14.5, 16, 15.5, 17 };
	std::array<float, 9> testArray2 = { 12, 8, 5, 11, 4, 7, 2, 18, 17 };
	std::array<float, 10> testArray3 = { 2, 1, 3, 4, 5, 6, 7, 8, 9, 10 };

	while (runProgram)
	{
		std::cout << "BINARY SEARCH TREE PROGRAM\n\n"
			<< " 1. Insert new value into tree"
			<< "\n 6. Delete value from the tree\n"

			<< "\n11. Find a value in the tree"
			<< "\n12. Find the minimum value stored in the tree"
			<< "\n13. Find the maximum value stored in the tree\n"

			<< "\n66. Print the tree\n"

			<< "\n71. Insert test array 1 into the tree"
			<< "\n72. Insert test array 2 into the tree"
			<< "\n73. Insert test array 3 into the tree\n"

			<< "\n99. Exit program"
			
			<< "\n\nYour choice, please: ";

		if (TestUserInput(&menuInput, true))
		{
			switch (menuInput)
			{
			case 1:
				std::cout << "Enter the value you wish to insert: ";
				if (TestUserInput(&userInput))
				{
					theBST.Insert(userInput);
				}
				break;
			case 6:
				std::cout << "Enter the value you wish to delete: ";
				if (TestUserInput(&userInput))
				{
					theBST.Delete(userInput);
				}
				break;
			case 11:
				std::cout << "Enter the value you wish to find: ";
				if (TestUserInput(&userInput))
				{
					theBST.Find(userInput);
				}
				break;
			case 12:
				theBST.Minimum();
				break;
			case 13:
				theBST.Maximum();
				break;
			case 66:
				theBST.Print();
				break;
			case 71:
				for (int count = 0; count < testArray1.size(); count++)
				{
					theBST.Insert(testArray1[count]);
				}
				break;
			case 72:
				for (int count = 0; count < (int)testArray2.size(); count++)
				{
					theBST.Insert(testArray2[count]);
				}
				break;
			case 73:
				for (int count = 0; count < (int)testArray3.size(); count++)
				{
					theBST.Insert(testArray3[count]);
				}
				break;
			case 81:	// Add 100 nodes to the BST
				AddNodes(&theBST, 100);
				break;
			case 82:	// Add 1000 nodes to the BST
				AddNodes(&theBST, 1000);
				break;
			case 83:	// Add 10000 nodes to the BST
				AddNodes(&theBST, 10000);
				break;
			case 84:	// Add 100000 nodes to the BST
				AddNodes(&theBST, 100000);
				break;
			case 99:
				runProgram = false;
				break;
			default:
				std::cout << "Sorry, can't do that.\n";
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