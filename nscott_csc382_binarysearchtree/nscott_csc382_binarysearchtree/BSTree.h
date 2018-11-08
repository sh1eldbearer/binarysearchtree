#ifndef BSTree_h
#define BSTree_h

/*																								  */

#include <iostream>

#include "BSNode.h"

template<typename Type>
class BSTree
{
private:
	BSNode<Type>* rootPtr = nullptr;		// Pointer to the rootPtr node of this tree
	int nodeCount = 0;			// Counter for how many nodes are currently in the tree 
	int spaceCount = 5;	// The number of spaces to add between each level of the tree when counting

	BSNode<Type>* InsertNode(BSNode<Type>* nodeToCheck, Type newValue)		// Inserts a new node 
	{
		// If the node being checked is null, creates a new node to occupy that spot on the tree
		if (nodeToCheck == nullptr)
		{
			BSNode<Type>* newNode = new BSNode<Type>(newValue);
			return newNode;
		}

		// Otherwise, looks at the current node's value to determine which branch to traverse next
		if (newValue < nodeToCheck->GetValue())
		{
			// Move down the tree along the left branch (runs recursively until an avaiable node is found)
			nodeToCheck->SetLeftChildPtr(InsertNode(nodeToCheck->GetLeftChildPtr(), newValue));
			nodeToCheck->GetLeftChildPtr()->SetParentPtr(nodeToCheck);
		}
		else if (newValue > nodeToCheck->GetValue())
		{
			// Move down the tree along the right branch (runs recursively until an avaiable node is found)
			nodeToCheck->SetRightChildPtr(InsertNode(nodeToCheck->GetRightChildPtr(), newValue));
			nodeToCheck->GetRightChildPtr()->SetParentPtr(nodeToCheck);
		}

		return nodeToCheck;
	}

	template<typename Type>
	void DeleteNode(BSNode<Type>* nodePtr)	// Deletes a node from the tree
	{
		// TOOD: To be added after refactoring FindNode
		// Target node is a leaf
		if (nodePtr->GetLeftChildPtr() == nullptr && nodePtr->GetRightChildPtr() == nullptr)
		{
			// Target node is the root node
			if (nodePtr == this->rootPtr)
			{
				rootPtr = nullptr;
			}
			else 
			{
				// This node is the left child of the previous node
				if (nodePtr->GetParentPtr()->GetLeftChildPtr() == nodePtr)
				{
					// Makes the previous node's left child null (since it will be deleted)
					nodePtr->GetParentPtr()->SetLeftChildPtr(nullptr);
				}
				// This node is the right child of the previous node
				else if (nodePtr->GetParentPtr()->GetRightChildPtr() == nodePtr)
				{
					// Makes the previous node's right child null (since it will be deleted)
					nodePtr->GetParentPtr()->SetRightChildPtr(nullptr);
				}
			}
			// Deletes the node
			delete nodePtr;
			// Decreases the node count
			DecreaseNodeCount();
		}
		// Target node has only one child
		else if ((nodePtr->GetLeftChildPtr() == nullptr && nodePtr->GetRightChildPtr() != nullptr) ||
				 (nodePtr->GetLeftChildPtr() != nullptr && nodePtr->GetRightChildPtr() == nullptr))
		{
			// If this node only has a left child
			if (nodePtr->GetLeftChildPtr() != nullptr)
			{
				// Swap the values of this node and its left child node
				SwapValues(nodePtr, nodePtr->GetLeftChildPtr());
				// Deletes the left child node
				delete nodePtr->GetLeftChildPtr();
				// Sets this node's left child pointer to null
				nodePtr->SetLeftChildPtr(nullptr);
			}
			// If this node only has a right child
			else if (nodePtr->GetRightChildPtr() != nullptr)
			{
				// Swap the values of this node and its right child node
				SwapValues(nodePtr, nodePtr->GetRightChildPtr());
				// Deletes the right child node
				delete nodePtr->GetRightChildPtr();
				// Sets this node's right child pointer to null
				nodePtr->SetRightChildPtr(nullptr);
			}
			// Decreases the node count
			DecreaseNodeCount();
		}
		// Target node has two children
		else if (nodePtr->GetLeftChildPtr() != nullptr && nodePtr->GetRightChildPtr() != nullptr)
		{
			// Finds the successor node (the leftmost node in the right subtree)
			BSNode<Type>* succeessor = MinNode(nodePtr->GetRightChildPtr());
			// Swaps the values of the target node and the sucesssor
			SwapValues(nodePtr, succeessor);
			// Sets the left child pointer of the successor's parent to null
			succeessor->GetParentPtr()->SetLeftChildPtr(nullptr);
			// Deletes the successsor node, which now contains the value being deleted
			delete succeessor;
		}
	}

	void PrintNode(BSNode<Type> *node, int space)	// Prints the contents of a node to the console
	{
		// If the current node is null, don't print anything
		if (node == NULL)
		{
			return;
		}

		// Increase distance between levels for visual formatting
		space += spaceCount;

		// Attempts to print the right child first 
		PrintNode(node->GetRightChildPtr(), space);

		// Prints the current node 
		std::cout << std::endl;
		for (int i = spaceCount; i < space; i++)
		{
			std::cout << " ";
		}
		std::cout << node->GetValue() << std::endl;

		// Attempts to print the left child last 
		PrintNode(node->GetLeftChildPtr(), space);
	}

	BSNode<Type>* MinNode()		// Finds the node containing the smallest value stored in the tree
	{
		// Starts at the node passed into the function (or rootPtr, if one was not passed)
		BSNode<Type>* nodeToCheck = rootPtr;

		// Checks if the current node has a left child
		while (nodeToCheck->GetLeftChildPtr() != nullptr)
		{
			// Sets the current node's left child as the current node
			nodeToCheck = nodeToCheck->GetLeftChildPtr();
		}

		// Once the rightmost node in the tree has been found, returns a pointer to that node
		return nodeToCheck;
	}

	BSNode<Type>* MinNode(BSNode<Type>* node)		// Finds the node containing the smallest value stored in the tree
	{
		// Starts at the node passed into the function (or rootPtr, if one was not passed)
		BSNode<Type>* nodeToCheck = node;

		// Checks if the current node has a left child
		while (nodeToCheck->GetLeftChildPtr() != nullptr)
		{
			// Sets the current node's left child as the current node
			nodeToCheck = nodeToCheck->GetLeftChildPtr();
		}

		// Once the rightmost node in the tree has been found, returns a pointer to that node
		return nodeToCheck;
	}

	BSNode<Type>* MaxNode()		// Finds the node containing the largest value stored in the tree
	{
		// Starts at the node passed into the function (or rootPtr, if one was not passed)
		BSNode<Type>* nodeToCheck = rootPtr;

		// Checks if the current node has a right child
		while (nodeToCheck->GetRightChildPtr() != nullptr)
		{
			// Sets the current node's right child as the current node
			nodeToCheck = nodeToCheck->GetRightChildPtr();
		}

		// Once the rightmost node in the tree has been found, returns a pointer to that node
		return nodeToCheck;
	}

	BSNode<Type>* MaxNode(BSNode<Type>* node)		// Finds the node containing the largest value stored in the tree
	{
		// Starts at the node passed into the function (or rootPtr, if one was not passed)
		BSNode<Type>* nodeToCheck = node;

		// Checks if the current node has a right child
		while (nodeToCheck->GetRightChildPtr() != nullptr)
		{
			// Sets the current node's right child as the current node
			nodeToCheck = nodeToCheck->GetRightChildPtr();
		}

		// Once the rightmost node in the tree has been found, returns a pointer to that node
		return nodeToCheck;
	}
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
	void InsertValue(Type nodeValue)	// Creates a new node in the tree
	{
		// Attempts to see if there is already a node containing this value in the tree
		if (FindValue(nodeValue, false) != nullptr)
		{
			std::cout << "This value already exists in the tree." << std::endl;
			return;
		}

		// Creates a new node
		if (rootPtr == nullptr)
		{
			rootPtr = InsertNode(rootPtr, nodeValue);
		}
		else
		{
			InsertNode(rootPtr, nodeValue);
		}
		IncreaseNodeCount();
	}

	template<typename Type>
	void SwapValues(BSNode<Type>* node1, BSNode<Type>* node2)		// Swaps the position of two values
	{
		node1->SetValue(node1->GetValue() + node2->GetValue());
		node2->SetValue(node1->GetValue() - node2->GetValue());
		node1->SetValue(node1->GetValue() - node2->GetValue());
	}

	template<typename Type>
	BSNode<Type>* FindValue(Type findValue, bool verbose = true)	// Attempts to find a node containing the given value
	{
		// If there are no nodes in the tree, returns nullptr and displays and error message
		if (IsTreeEmpty(verbose))
		{
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
				// Travels down the right branch to look for the next match
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
	void DeleteValue(Type delValue, bool verbose = true)	// Deletes a value from the tree
	{
		if (IsTreeEmpty())
		{
			return;
		}

		// TOOD: To be added after refactoring FindNode
		BSNode<Type>* delNode = FindValue(delValue, false);

		// If the value was not found in the tree, returns a nullptr
		if (delNode == NULL)
		{
			// Verbose mode will output success/failure messages to the console
			if (verbose)
			{
				std::cout << "Value \"" << delValue << "\" not found in the tree." << std::endl;
			}
		}
		// If the value was found in the tree, deletes that value from the tree
		else
		{
			DeleteNode(delNode);
		}
	}

	Type MinValue()		// Finds the smallest value stored in the tree
	{
		// Returns the value contained by the node passed into the function
		return MinNode()->GetValue();
	}

	Type MaxValue()		// Finds the largest value stored in the tree
	{
		// Returns the value contained by the node passed into the function
		return MaxNode()->GetValue();
	}

	bool IsTreeEmpty(bool verbose = true)		// Tests to see if the tree is empty
	{
		// Tree is really and truly empty
		if (rootPtr == nullptr && nodeCount == 0)
		{
			// Verbose mode will output success/failure messages to the console
			if (verbose)
			{
				std::cout << "There are no nodes in the tree." << std::endl;
			}
			return true;
		}
		// TODO: Delete this when I'm absolutely sure everything works right!
		// Tree thinks it might be empty, but I didn't adjust the count properly somewhere
		else if ((rootPtr == nullptr && nodeCount != 0) ||
			(rootPtr != nullptr && nodeCount == 0))
		{
			std::cout << "The root pointer and node count variables don't match up." <<
				" Not sure what happened, so here's a false TRUE value." << std::endl <<
				"Go fix your code, goofball!" << std::endl << 
				"Root address: " << rootPtr << "; Node count: " << nodeCount << std::endl;
			return true;
		}
		else
		{
			return false;
		}
	}
	void PrintTree() // Prints the tree to the console (right branches are on top)
	{ 
		PrintNode(rootPtr, 0);
	}
};

#endif