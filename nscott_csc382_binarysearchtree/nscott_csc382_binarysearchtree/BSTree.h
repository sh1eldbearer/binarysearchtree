#ifndef BSTree_h
#define BSTree_h

/*																								  */

#include <iostream>

#include "BSNode.h"

// TODO: Delete before submitting
int COUNT = 10;

template<typename Type>
class BSTree
{
private:
	BSNode<Type>* rootPtr = nullptr;		// Pointer to the rootPtr node of this tree
	int nodeCount = 0;			// Counter for how many nodes are currently in the tree 
public:
	BSTree() {}		// Constructor
	~BSTree() {}	// Destructor

	BSNode<Type>* GetRootPtr()		// Returns the memory address of the root node
	{
		return rootPtr;
	}

	template<typename Type>
	void SetRootPtr(Type* newPtr)		// Changes which node is the tree's root node
	{
		rootPtr = newPtr;
	}

	int GetNodecount()		// Returns the current count of nodes in the tree
	{
		return nodeCount;
	}

	void IncreaseNodeCount()	// Increases the count of nodes in the tree
	{
		nodeCount++;
	}

	void DecreaseNodeCount()	// Decreases the count of nodes in the tree
	{
		nodeCount--;
	}

	template<typename Type>
	void CreateNode(Type nodeValue)	// Creates a new node in the tree
	{
		// Attempts to see if there is already a node containing this value in the tree
		if (!IsTreeEmpty())		// Must check for an empty tree first to supress FindNode's error message
		{
			if (FindNode(nodeValue, false) != nullptr)
			{
				std::cout << "This value already exists in the tree." << std::endl;
			}
		}

		// Creates a new node
		if (rootPtr == nullptr)
		{
			rootPtr = rootPtr->InsertNode(rootPtr, nodeValue);
		}
		else
		{
			rootPtr->InsertNode(rootPtr, nodeValue);
		}
		IncreaseNodeCount();
	}

	template<typename Type>
	void SwapValues(Type value1, Type value2)		// Swaps the position of two values
	{
		BSNode<Type>* tempNode1 = FindNode(value1, false);
		BSNode<Type>* tempNode2 = FindNode(value2, false);
		
		// TODO: Test for valid switch before switching
		if (tempNode1 != nullptr && tempNode2 != nullptr)
		{
			tempNode1->SetValue(tempNode1->GetValue() + tempNode2->GetValue());
			tempNode2->SetValue(tempNode1->GetValue() - tempNode2->GetValue());
			tempNode1->SetValue(tempNode1->GetValue() - tempNode2->GetValue());
		}
		else
		{
			std::cout << "One or more values were not found in the tree. Please try again." << std::endl;
		}
	}

	template<typename Type>
	BSNode<Type>* FindNode(Type findValue, bool verbose)	// Attempts to find a node containing the given value
	{
		// If there are no nodes in the tree, returns nullptr and displays and error message
		if (IsTreeEmpty())
		{
			std::cout << "There are no nodes in the tree." << std::endl;
			return nullptr;
		}

		BSNode<Type>* currentNode = rootPtr;

		// Traverse the tree to find the value
		while (currentNode != nullptr)
		{
			// Checks the current node for a value match
			if (currentNode->GetValue() == findValue)
			{
				// Breaks out of the loop immediately
				break;
			}
			// Checks to see if the node is a leaf (no children)
			else if (currentNode->GetLeftChildPtr() == nullptr && currentNode->GetRightChildPtr() == nullptr)
			{
				//  Returns a null pointer if the node is a leaf (loop will exit)
				currentNode = nullptr;
			}
			// Compares the value being looked for with the current node's value
			// Checks for a smaller value
			else if (currentNode->GetValue() > findValue)
			{
				// Travels down the left branch to look for the next match
				currentNode = currentNode->GetLeftChildPtr();
			}
			// Checks for a larger value
			else if (currentNode->GetValue() < findValue)
			{
				// Travels down the right branch to look fro the next match
				currentNode = currentNode->GetRightChildPtr();
			}
		}

		// Verbose mode will output success/failure messages to the console
		if (verbose)
		{
			std::cout << "Value \"" << findValue << "\" ";
			// No match was found
			if (currentNode == nullptr)
			{
				std::cout << "not found in the tree." << std::endl;
			}
			// A match was found
			else
			{
				std::cout << "found at address " << currentNode << "." << std::endl;
			}
		}
		return currentNode;
	}

	template<typename Type>
	void DeleteNode(BSNode<Type>* nodePtr)	// Deletes a node from the tree
	{

	}

	Type MaxValue()		// Finds the largest value stored in the tree
	{

	}

	bool IsTreeEmpty()		// Tests to see if the tree is empty
	{
		// Tree is really and truly empty
		if (rootPtr == nullptr && nodeCount == 0)
		{
			return true;
		}
		// TODO: Delete this when you're sure everything works right!
		// Tree thinks it might be empty, but I didn't adjust the count properly somewhere
		else if ((rootPtr == nullptr && nodeCount != 0) ||
			(rootPtr != nullptr && nodeCount == 0))
		{
			std::cout << "The root pointer and node count variables don't match up." << 
				" Not sure what happened, so here's a TRUE." << std::endl;
			std::cout << "Root address: " << rootPtr << "; Node count: " << nodeCount << std::endl;
			return true;
		}
		else
		{
			return false;
		}
	}

	// TODO: Delete before submission
	// Function to print binary tree in 2D 
	// It does reverse inorder traversal 
	void print2DUtil(BSNode<Type> *node, int space)
	{
		// Base case 
		if (node == NULL)
		{
			return;
		}

		// Increase distance between levels 
		space += COUNT;

		// Process right child first 
		print2DUtil(node->GetRightChildPtr(), space);

		// Print current node after space 
		// count 
		std::cout << "\n";
		for (int i = COUNT; i < space; i++)
		{
			std::cout << " ";
		}
		std::cout << node->GetValue() << std::endl;

		// Process left child 
		print2DUtil(node->GetLeftChildPtr(), space);
	}

	// TODO: Delete before submission
	// Wrapper over print2DUtil() 
	void print2D()
	{
		// Pass initial space count as 0 
		print2DUtil(rootPtr, 0);
	}
};

#endif