#ifndef BSTREE_H
#define BSTREE_H

#include <iostream>

#include "BSNode.h"

template<typename Type>
class BSTree
{
private:
	BSNode<Type>* rootPtr = nullptr;		// Pointer to the rootPtr node of this tree
	int nodeCount = 0;			// Counter for how many nodes are currently in the tree 
	int spaceCount = 5;	// The number of spaces to add between each level of the tree when counting

	BSNode<Type>* InsertNode(BSNode<Type>* nodeToCheck, Type& newValue, int height = -1)		// Inserts a new node 
	{
		// If the node being checked is null, creates a new node to occupy that spot on the tree
		if (nodeToCheck == nullptr)
		{
			BSNode<Type>* newNode = new BSNode<Type>(newValue, height);
			// If this is the first node in the tree, sets this node as the root
			if (rootPtr == nullptr)
			{
				rootPtr = newNode;
			}
			return newNode;
		}

		// Otherwise, looks at the current node's value to determine which branch to traverse next
		if (newValue < nodeToCheck->GetValue())
		{
			// Move down the tree along the left branch (runs recursively until an available node is found)
			nodeToCheck->SetLeftChildPtr(InsertNode(nodeToCheck->GetLeftChildPtr(), newValue, nodeToCheck->GetHeight()));
			nodeToCheck->GetLeftChildPtr()->SetParentPtr(nodeToCheck);
		}
		else if (newValue > nodeToCheck->GetValue())
		{
			// Move down the tree along the right branch (runs recursively until an available node is found)
			nodeToCheck->SetRightChildPtr(InsertNode(nodeToCheck->GetRightChildPtr(), newValue, nodeToCheck->GetHeight()));
			nodeToCheck->GetRightChildPtr()->SetParentPtr(nodeToCheck);
		}		

		// Returns the next node to be checked (allows this function to run recursively until the node is created)
		return nodeToCheck;
	}

	void DeleteNode(BSNode<Type>* nodePtr)	// Deletes a node from the tree
	{
		// Target node is a leaf
		if (nodePtr->GetLeftChildPtr() == nullptr && nodePtr->GetRightChildPtr() == nullptr)
		{
			// Target node is the root node
			if (nodePtr == rootPtr)
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
		}
		// Target node has only one child
		else if ((nodePtr->GetLeftChildPtr() == nullptr && nodePtr->GetRightChildPtr() != nullptr) ||
			(nodePtr->GetLeftChildPtr() != nullptr && nodePtr->GetRightChildPtr() == nullptr))
		{
			BSNode<Type>* childNode = nullptr;
			// If this node only has a left child
			if (nodePtr->GetLeftChildPtr() != nullptr)
			{
				// If the target node is the root node
				if (nodePtr == rootPtr)
				{
					// Sets the left child as the root pointer
					rootPtr = nodePtr->GetLeftChildPtr();
					// Clears the left child's parent pointer
					nodePtr->GetLeftChildPtr()->SetParentPtr(nullptr);
				}
				else
				{
					// Swap the values of this node and its left child node
					SwapValues(nodePtr, nodePtr->GetLeftChildPtr());
					// Deletes the left child node
					childNode = nodePtr->GetLeftChildPtr();
					// Sets this node's left child pointer to null
					nodePtr->SetLeftChildPtr(nullptr);
				}
			}
			// If this node only has a right child
			else if (nodePtr->GetRightChildPtr() != nullptr)
			{
				// If the target node is the root node
				if (nodePtr == rootPtr)
				{
					// Sets the right child as the root pointer
					rootPtr = nodePtr->GetRightChildPtr();
					// Clears the right child's parent pointer
					nodePtr->GetRightChildPtr()->SetParentPtr(nullptr);
				}
				else
				{
					// Swap the values of this node and its right child node
					SwapValues(nodePtr, nodePtr->GetRightChildPtr());
					// Deletes the right child node
					childNode = nodePtr->GetRightChildPtr();
					// Sets this node's right child pointer to null
					nodePtr->SetRightChildPtr(nullptr);
				}
			}
			// Stores orphaned child node as the target node
			nodePtr = childNode;
		}
		// Target node has two children
		else if (nodePtr->GetLeftChildPtr() != nullptr && nodePtr->GetRightChildPtr() != nullptr)
		{
			// Attempts to find the successor node by checking for a left branch in the target node's right subtree
			if (nodePtr->GetRightChildPtr()->GetLeftChildPtr() != nullptr)
			{
				// Looks for the smallest value in the right subtree as a successor
				BSNode<Type>* successor = MinNode(nodePtr->GetRightChildPtr());
				// Sets the left child pointer of the successor's parent to null
				successor->GetParentPtr()->SetLeftChildPtr(nullptr);
				// Swaps the values of the target node and the successor
				SwapValues(nodePtr, successor);
				// Sets the successor node as the target node
				nodePtr = successor;
			}
			// Otherwise, simply uses the next highest value as the successor node
			else
			{
				// If the target pointer is its parent's left child, sets the successor as the parent's new left child
				if (nodePtr->GetParentPtr()->GetLeftChildPtr() == nodePtr)
				{
					nodePtr->GetParentPtr()->SetLeftChildPtr(nodePtr->GetRightChildPtr());
				}
				// If the target pointer is its parent's right child, sets the successor as the parent's new right child
				else if (nodePtr->GetParentPtr()->GetRightChildPtr() == nodePtr)
				{
					nodePtr->GetParentPtr()->SetRightChildPtr(nodePtr->GetRightChildPtr());
				}
				// Sets the target pointer's parent as the parent of the successor node
				nodePtr->GetRightChildPtr()->SetParentPtr(nodePtr->GetParentPtr());
				// Sets the target pointer's left child as the left child of the successor node
				nodePtr->GetRightChildPtr()->SetLeftChildPtr(nodePtr->GetLeftChildPtr());
				// Sets the successor as the target pointer's left child's parent node
				nodePtr->GetLeftChildPtr()->SetParentPtr(nodePtr->GetRightChildPtr());
			}
		}
		// Deletes the target node
		delete nodePtr;
		// Decreases the node count
		DecreaseNodeCount();
		// Updates the heights of all nodes in the tree
		UpdateNodeHeight(rootPtr);
	}

	void DeleteAllNodes(BSNode<Type>* startNode)	// Deletes a node, and all of its child nodes
	{
		// Prevents errors if there is no node at this address
		if (startNode == nullptr)
		{
			return;
		}

		// Deletes nodes in the left subtree
		DeleteAllNodes(startNode->GetLeftChildPtr());
		// Deletes nodes in the right subtree
		DeleteAllNodes(startNode->GetRightChildPtr());
		// Deletes the starting node 
		DeleteNode(startNode);
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

	BSNode<Type>* MinNode()	// Finds the node containing the smallest value stored in the tree, starting at the root node
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

	BSNode<Type>* MinNode(BSNode<Type>* node) // Finds the node containing the smallest value stored in the tree, starting at a specific node
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

	BSNode<Type>* MaxNode()	// Finds the node containing the largest value stored in the tree, starting at the root node
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

	BSNode<Type>* MaxNode(BSNode<Type>* node) // Finds the node containing the largest value stored in the tree, starting at a specific node
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

	BSNode<Type>* FindHighestNode(BSNode<Type>* startingNode) // Finds the highest node in the tree by recursively checking down from an initial node
	{
		// Initializes the starting node as the highest node in the tree
		BSNode<Type>* highestNode = startingNode;

		// If a nullptr was passed into the function, or if the starting node has no children, exits the function immediately to prevent exceptions
		if (startingNode == nullptr || (startingNode->GetLeftChildPtr() == nullptr && startingNode->GetRightChildPtr() == nullptr))
		{
			return highestNode;
		}

		// Checks the left child's height
		if (startingNode->GetLeftChildPtr() != nullptr)
		{
			// Checks the left child's height against the highest node's height
			if (startingNode->GetLeftChildPtr()->GetHeight() > highestNode->GetHeight())
			{
				// If the left child's height is greater than the highest node's, the child becomes the new highest node
				highestNode = startingNode->GetLeftChildPtr();
			}
			// Checks the left child to see if any of its children are the highest node
			FindHighestNode(startingNode->GetLeftChildPtr(), highestNode);
		}

		// Checks the right child's height
		if (startingNode->GetRightChildPtr() != nullptr)
		{
			// Checks the right child's height against the highest node's height
			if (startingNode->GetRightChildPtr()->GetHeight() > highestNode->GetHeight())
			{
				// If the right child's height is greater than the highest node's, the child becomes the new highest node
				highestNode = startingNode->GetRightChildPtr();
			}
			// Checks the right child to see if any of its children are the highest node
			FindHighestNode(startingNode->GetRightChildPtr(), highestNode);
		}

		return highestNode;
	}

	BSNode<Type>* FindHighestNode(BSNode<Type>* startingNode, BSNode<Type>*& highestNode) // Finds the highest node in the tree by recursively checking down from an initial node
	{
		// The highest node is passed as a reference to a pointer, so the original function keeps track of the highest node in the tree

		// If a nullptr was passed into the function, or if the starting node has no children, exits the function immediately to prevent exceptions
		if (startingNode == nullptr || (startingNode->GetLeftChildPtr() == nullptr && startingNode->GetRightChildPtr() == nullptr))
		{
			return highestNode;
		}

		// Checks the left child's height
		if (startingNode->GetLeftChildPtr() != nullptr)
		{
			// Checks the left child's height against the highest node's height
			if (startingNode->GetLeftChildPtr()->GetHeight() > highestNode->GetHeight())
			{
				// If the left child's height is greater than the highest node's, the child becomes the new highest node
				highestNode = startingNode->GetLeftChildPtr();
			}
			// Checks the left child to see if any of its children are the highest node
			FindHighestNode(startingNode->GetLeftChildPtr(), highestNode);
		}

		// Checks the right child's height
		if (startingNode->GetRightChildPtr() != nullptr)
		{
			// Checks the right child's height against the highest node's height
			if (startingNode->GetRightChildPtr()->GetHeight() > highestNode->GetHeight())
			{
				// If the right child's height is greater than the highest node's, the child becomes the new highest node
				highestNode = startingNode->GetRightChildPtr();
			}
			// Checks the right child to see if any of its children are the highest node
			FindHighestNode(startingNode->GetRightChildPtr(), highestNode);
		}

		return highestNode;
	}

	void UpdateNodeHeight(BSNode<Type>* node, int height = 0)	// Updates the height value of each node in the tree
	{
		// If there are no nodes in the tree, exits the function
		if (IsTreeEmpty(false))
		{
			return;
		}

		node->SetHeight(height);
		if (node->GetLeftChildPtr() != nullptr)
		{
			UpdateNodeHeight(node->GetLeftChildPtr(), height + 1);
		}
		if (node->GetRightChildPtr() != nullptr)
		{
			UpdateNodeHeight(node->GetRightChildPtr(), height + 1);
		}
	}

	void UpdateParentNodePtrs(BSNode<Type>* node)	// Updates a node's parent's child pointers
	{
		// Checks to see if the pivotNode has a parent (i.e. is not the root node)
		if (node->GetParentPtr() != nullptr)
		{
			// Updates the appropriate child pointer of the pivotNode's parent
			if (node->GetParentPtr()->GetLeftChildPtr() == node)	// If the pivotNode is its parent's left child node
			{
				// Changes the parent's left child to the pivot node's left child node
				node->GetParentPtr()->SetLeftChildPtr(node->GetLeftChildPtr());
			}
			else if (node->GetParentPtr()->GetRightChildPtr() == node)	//If the pivotNode is its parent's right child node
			{
				// Changes the parent's right child to the pivot node's left child node
				node->GetParentPtr()->SetRightChildPtr(node->GetLeftChildPtr());
			}
		}
	}
public:
	BSTree() {}		// Constructor
	~BSTree() {}	// Destructor

	BSNode<Type>* GetRootPtr()		// Returns the memory address of the root node
	{
		return rootPtr;
	}

	void SetRootPtr(Type* newPtr)		// Changes which node is the tree's root node
	{
		rootPtr = newPtr;
	}

	int GetNodeCount()		// Returns the current count of nodes in the tree
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

	void InsertValue(Type nodeValue)	// Creates a new node in the tree
	{
		// Attempts to see if there is already a node containing this value in the tree
		if (FindValue(nodeValue, false) != nullptr)
		{
			std::cout << "This value already exists in the tree." << std::endl;
			return;
		}

		// Creates a new node
		InsertNode(rootPtr, nodeValue);

		// Increases the node count
		IncreaseNodeCount();
		// Attempt to balance the tree
		BalanceTree(nodeValue);
	}

	void SwapValues(BSNode<Type>* node1, BSNode<Type>* node2)		// Swaps the position of two values
	{
		node1->SetValue(node1->GetValue() + node2->GetValue());
		node2->SetValue(node1->GetValue() - node2->GetValue());
		node1->SetValue(node1->GetValue() - node2->GetValue());
	}

	BSNode<Type>* FindValue(Type findValue, bool verbose = true)	// Attempts to find a node containing the given value
	{
		// If there are no nodes in the tree, returns nullptr and displays an error message
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

	void DeleteValue(Type delValue, bool verbose = true)	// Deletes a value from the tree
	{
		// If there are no nodes in the tree, displays an error message
		if (IsTreeEmpty(verbose))
		{
			return;
		}

		// TOOD: To be added after refactoring FindNode
		BSNode<Type>* delNode = FindValue(delValue, false);

		// If the value was not found in the tree, returns a nullptr
		if (delNode == nullptr)
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

	void DeleteAllValues(bool verbose = true)	// Deletes all the nodes in the tree 
	{
		// If there are no nodes in the tree, displays an error message
		if (IsTreeEmpty(verbose))
		{
			return;
		}

		DeleteAllNodes(rootPtr);
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

	void LeftNodeRotation(BSNode<Type>* pivotNode)	// Rotates a node left for balancing
	{
		// Updates the appropriate child pointers of the pivotNode's parent node (if it exists)
		UpdateParentNodePtrs(pivotNode);

		// Sets the pivotNode's right child as the pivotNode's new parent
		pivotNode->SetParentPtr(pivotNode->GetRightChildPtr());
		if (pivotNode == rootPtr)
		{
			rootPtr = pivotNode->GetRightChildPtr();
			rootPtr->SetParentPtr(nullptr);
		}
		
		// Checks to see if the pivotNode's new parent had a left child node
		if (pivotNode->GetRightChildPtr()->GetLeftChildPtr() != nullptr)
		{
			// Changes the pivotNode's right child to point to the old right child's left child node
			pivotNode->SetRightChildPtr(pivotNode->GetRightChildPtr()->GetLeftChildPtr());
			// Sets the pivotNode as the parent of its new right child node
			pivotNode->GetRightChildPtr()->SetParentPtr(pivotNode);
		}
		// If not, sets the pivotNode's right child pointer to null
		else
		{
			pivotNode->SetRightChildPtr(nullptr);
		}

		// Sets the pivotNode as the left child of its parent node
		pivotNode->GetParentPtr()->SetLeftChildPtr(pivotNode);

		UpdateNodeHeight(rootPtr);
	}

	void RightNodeRotation(BSNode<Type>* pivotNode)	// Rotates a node right for balancing
	{
		// Updates the appropriate child pointers of the pivotNode's parent node (if it exists)
		UpdateParentNodePtrs(pivotNode);

		// Sets the pivotNode's left child as the pivotNode's new parent
		pivotNode->SetParentPtr(pivotNode->GetLeftChildPtr());
		if (pivotNode == rootPtr)
		{
			rootPtr = pivotNode->GetLeftChildPtr();
			rootPtr->SetParentPtr(nullptr);
		}

		// Checks to see if the pivotNode's new parent had a right child node
		if (pivotNode->GetLeftChildPtr()->GetRightChildPtr() != nullptr)
		{
			// Changes the pivotNode's left child to point to the old left child's right child node
			pivotNode->SetLeftChildPtr(pivotNode->GetLeftChildPtr()->GetRightChildPtr());
			// Sets the pivotNode as the parent of its new left child node
			pivotNode->GetLeftChildPtr()->SetParentPtr(pivotNode);
		}
		// If not, sets the pivotNode's left child pointer to null
		else
		{
			pivotNode->SetLeftChildPtr(nullptr);
		}

		// Sets the pivotNode as the right child of its parent node
		pivotNode->GetParentPtr()->SetRightChildPtr(pivotNode);

		UpdateNodeHeight(rootPtr);
	}

	void GetNodeDetails(BSNode<Type>* node)		// Shows the value stored in a node and its adjacent node addresses and stored values
	{
		// If the pointer is null, exits the function (prevents exceptions)
		if (node == nullptr)
		{
			return;
		}

		// Displays the node's information
		std::cout << "Node value: " << node->GetValue() << std::endl;
		std::cout << "Node height: " << node->GetHeight() << std::endl;
		if (node->GetParentPtr() != nullptr)
		{
			std::cout << "Parent: " << node->GetParentPtr() << " (Value: " << node->GetParentPtr()->GetValue() << ")" << std::endl;
		}
		else
		{
			std::cout << "This is the root node." << std::endl;
		}
		if (node->GetLeftChildPtr() != nullptr)
		{
			std::cout << "Left child: " << node->GetLeftChildPtr() << " (Value: " << node->GetLeftChildPtr()->GetValue() << ")" << std::endl;
		}
		else
		{
			std::cout << "No left child node." << std::endl;
		}
		if (node->GetRightChildPtr() != nullptr)
		{
			std::cout << "Right child: " << node->GetRightChildPtr() << " (Value: " << node->GetRightChildPtr()->GetValue() << ")" << std::endl;
		}
		else
		{
			std::cout << "No right child node." << std::endl;
		}
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
		else
		{
			return false;
		}
	}

	void PrintTree() // Prints the tree to the console (right branches are on top)
	{ 
		if (IsTreeEmpty(true))
		{
			return;
		}
		PrintNode(rootPtr, 0);
	}

	void BalanceTree(Type newValue)
	{
		int leftHeight = 0, rightHeight = 0;

		// Checks to see if there is a left subtree
		if (rootPtr->GetLeftChildPtr() != nullptr)
		{
			// Finds the highest node in the subtree, and returns its height
			leftHeight = FindHighestNode(rootPtr->GetLeftChildPtr())->GetHeight();
		}

		// Checks to see if there is a right subtree
		if (rootPtr->GetRightChildPtr() != nullptr)
		{
			// Finds the highest node in the subtree, and returns its height
			rightHeight = FindHighestNode(rootPtr->GetRightChildPtr())->GetHeight();
		}

		// Calculates the difference levels between the left and right subtrees
		int balanceValue = leftHeight - rightHeight;

		// If there is 1 or less levels of difference between the subtrees, exits the function
		if (balanceValue > -1 || balanceValue < 1)
		{
			return;
		}	

		// Checks for a left subtree
		if (rootPtr->GetLeftChildPtr() != nullptr)
		{
			// Left-left case
			if (balanceValue > 1 && newValue < rootPtr->GetLeftChildPtr()->GetValue())
			{
				RightNodeRotation(rootPtr);
			}
			// Left-right case
			else if (balanceValue > 1 && newValue > rootPtr->GetLeftChildPtr()->GetValue())
			{
				LeftNodeRotation(rootPtr->GetLeftChildPtr());
				RightNodeRotation(rootPtr);
			}
		}
		// Checks for a right subtree
		if (rootPtr->GetRightChildPtr() != nullptr)
		{
			// Right-right case
			if (balanceValue < -1 && newValue > rootPtr->GetRightChildPtr()->GetValue())
			{
				LeftNodeRotation(rootPtr);
			}
			// Right-left case
			else if (balanceValue < -1 && newValue < rootPtr->GetRightChildPtr()->GetValue())
			{
				RightNodeRotation((rootPtr->GetRightChildPtr()));
				LeftNodeRotation((rootPtr));
			}
		}
	}
};

#endif