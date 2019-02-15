#ifndef BSTREE_H
#define BSTREE_H 

#include <iostream>

#include "BSNode.h"
const int SPACE_COUNT = 5;	// The number of spaces to add between each level of the tree when counting in printing function

	/// <summary>
	/// 
	/// </summary>
	/// <param name="newValue"></param>
	/// <returns></returns>

template<typename Type> class BSTree
{
private:
	BSNode<Type>* root;

	/// <summary>
	/// Finds the node in the tree (or subtree) containing the minimum (smallest) value.
	/// </summary>
	/// <param name="startNode">The node from which to start the search.</param>
	/// <returns>A pointer to the node containing the minimum value stored in the tree (or subtree).</returns>
	BSNode<Type>* MinNode(BSNode<Type>* startNode)
	{
		BSNode<Type>* currentNode = startNode;

		// Check as far down the left branch as possible to find the smallest value
		while (currentNode->GetLeftChild() != nullptr)
		{
			currentNode = currentNode->GetLeftChild();
		}

		return currentNode;
	}

	/// <summary>
	/// Finds the node in the tree (or subtree) containing the maximum (largest) value.
	/// </summary>
	/// <param name="startNode">The node from which to start the search.</param>
	/// <returns>A pointer to the node containing the maximum value stored in the tree (or subtree).</returns>
	BSNode<Type>* MaxNode(BSNode<Type>* startNode)
	{
		BSNode<Type>* currentNode = startNode;

		// Check as far down the right branch as possible to find the largest value
		while (currentNode->GetRightChild() != nullptr)
		{
			currentNode = currentNode->GetRightChild();
		}
		
		return currentNode;
	}

	/// <summary>
	/// Prints the contents of a node to the console when called by Print().
	/// </summary>
	void PrintNode(BSNode<Type> *node, int space)
	{
		// If the current node is null, don't print anything
		if (node == NULL)
		{
			return;
		}

		// Increase distance between levels for visual formatting
		space += SPACE_COUNT;

		// Attempts to print the right child first 
		PrintNode(node->GetRightChild(), space);

		// Prints the current node 
		std::cout << std::endl;
		for (int i = SPACE_COUNT; i < space; i++)
		{
			std::cout << " ";
		}
		std::cout << node->GetValue() << "\n";

		// Attempts to print the left child last 
		PrintNode(node->GetLeftChild(), space);
	}

	/// <summary>
	/// Swaps two key values between two different nodes.
	/// </summary>
	/// <param name="node1">A node that will be switching key values with node2.</param>
	/// <param name="node2">A node that will be switching key values with node1.</param>
	void SwapValues(BSNode<Type>* node1, BSNode<Type>* node2)
	{
		if (node1 == node2)
		{
			std::cout << "Cannot switch values between the same node.\n\n";
			return;
		}
		else if (node1 == nullptr || node2 == nullptr)
		{
			std::cout << "Cannot switch the value of a null pointer.\n\n";
			return;
		}

		// Swaps the values in place
		node1->SetValue(node1->GetValue() + node2->GetValue());
		node2->SetValue(node1->GetValue() - node2->GetValue());
		node1->SetValue(node1->GetValue() - node2->GetValue());
	}


	/// <summary>
	/// Deletes a node, and all nodes within that node's subtrees, from the tree.
	/// </summary>
	/// <param name="delNode">The root node of the tree (or subtree) to be deleted.</param>
	void DeleteNodes(BSNode<Type>* delNode)
	{
		// If the node being checked is null, immediately exit the function
		if (delNode == nullptr)
		{
			return;
		}

		// Does a depth-first, post-ordered search through tree for nodes to delete
		DeleteNodes(delNode->GetLeftChild());
		DeleteNodes(delNode->GetRightChild());

		// Once the search is complete, deletes this node
		delete delNode;
	}

	/// <summary>
	/// Updates the height value of each node in the subtree under the starting node.
	/// </summary>
	/// <param name="startNode">The root of the tree (or subtree) to update the heights of.</param>
	void UpdateNodeHeights(BSNode<Type>* startNode)
	{
		// If the node being checked is null, immediately exit the function
		if (startNode == nullptr)
		{
			return;
		}

		// Use the height of the starting node as a starting height value
		int height = startNode->GetHeight();

		// Do a breadth-first search through the tree
		if (startNode->GetLeftChild() != nullptr)
		{
			// Adjust the height and recursively search for child nodes
			startNode->GetLeftChild()->SetHeight(height + 1);
			UpdateNodeHeights(startNode->GetLeftChild());
		}
		if (startNode->GetRightChild() != nullptr)
		{
			// Adjust the height and recursively search for child nodes
			startNode->GetRightChild()->SetHeight(height + 1);
			UpdateNodeHeights(startNode->GetRightChild());
		}
	}

public:
	/// <summary>
	/// Default constructor.
	/// </summary>
	BSTree() 
	{ 
		root = nullptr;
	}
	
	/// <summary>
	/// Default destructor.
	/// </summary>
	~BSTree() { }

	/// <summary>
	/// Accessor for the pointer to the root node.
	/// </summary>
	/// <returns>The pointer to the root node of this tree. 
	/// Returns a nullptr if there is no root.</returns>
	BSNode<Type>* GetRoot()
	{
		return root;
	}

	/// <summary>
	/// Determines whether or not the tree is empty.
	/// </summary>
	/// <returns>If the tree is empty, returns true. Otherwise, returns false.</returns>
	/// <param name="verbose">Whether or not to output status messages to the console.</param>
	bool IsEmpty(bool verbose = false)
	{
		// Tree is empty
		if (root == nullptr)
		{
			if (verbose)
			{
				std::cout << "There are no nodes in the tree.\n\n";
			}
			return true;
		}
		// Tree is not empty
		return false;
	}

	/// <summary>
	/// Inserts a value into the tree.
	/// </summary>
	/// <param name="newValue">The new value to be inserted into the tree.</param>
	/// <param name="verbose">Whether or not to output status messages to the console.</param>
	void Insert(Type newValue, bool verbose = true)
	{
		BSNode<Type>* newNode = new BSNode<Type>();
		BSNode<Type>* nodeToCheck = root;
		int height = 0;

		// Create a new node
		while (newNode->GetValue() == NULL)
		{
			// If the node being checked is null, this is where the new node will be inserted
			if (nodeToCheck == nullptr)
			{
				newNode->SetValue(newValue);
				newNode->SetHeight(height);
				// If the tree has no root node, set the new node as the root
				if (IsEmpty())
				{
					root = newNode;
				}
				// If the tree does have a root node, assigns this node as a child of its parent node
				else
				{
					if (newValue > newNode->GetParent()->GetValue())
					{
						newNode->GetParent()->SetRightChild(newNode);
					}
					else if (newValue < newNode->GetParent()->GetValue())
					{
						newNode->GetParent()->SetLeftChild(newNode);
					}

				}

				// Suppresses console output is verbose is false
				if (verbose)
				{
					std::cout << "Successfully inserted " << newValue << " into the tree.\n\n";
				}
				return;
			}
			// Value already exists in the tree
			/* A manual comparison is used here because using Find duplicates the searching 
			 * already done by Insert
			 */
			else if (newValue == nodeToCheck->GetValue())
			{
				// Suppresses console output is verbose is false
				if (verbose)
				{
					std::cout << "Insertion failed. This value already exists in the tree.\n\n";
				}
				return;
			}
			// Smaller values get inserted further down the left branch
			else if (newValue < nodeToCheck->GetValue())
			{
				newNode->SetParent(nodeToCheck);
				nodeToCheck = nodeToCheck->GetLeftChild();
				height++;
			}
			// Larger values get inserted further down the right branch
			else if (newValue > nodeToCheck->GetValue())
			{
				newNode->SetParent(nodeToCheck);
				nodeToCheck = nodeToCheck->GetRightChild();
				height++;
			}
			// Unexpected behavior (if this ever shows up in the console window, I screwed up)
			else
			{
				std::cout << "Unexpected condition.\n\n";
			}
		}

		// Attempt to balance the tree
	}

	/// <summary>
	/// Attempts to find a node containing the given value.
	/// </summary>
	/// <param name="valueToFind">The value to attempt to find in the tree.</param>
	/// <param name="verbose">Whether or not to output status messages to the console.</param>
	/// <returns>If the value is found, returns a pointer to the node object where 
	/// the value is stored. Otherwise, returns a null pointer.</returns>
	BSNode<Type>* Find(Type valueToFind, bool verbose = true)
	{
		// If there are no nodes in the tree, returns nullptr and displays an error message
		if (IsEmpty(verbose))
		{
			return nullptr;
		}

		// Starts the search at the root node
		BSNode<Type>* currentNode = root;

		// Uses a binary search to attempt to find the value
		while (currentNode != nullptr)
		{
			Type currentValue = currentNode->GetValue();

			// The value was found in the current node
			if (currentValue == valueToFind)
			{
				break;
			}
			// The value is smaller than the current node's value
			else if (valueToFind < currentValue)
			{
				// Continue the search down the left branch
				currentNode = currentNode->GetLeftChild();
			}
			// The value is larger than the current node's value
			else if (valueToFind > currentValue)
			{
				// Continue the search down the right branch
				currentNode = currentNode->GetRightChild();
			}
			// The value was not found in the tree
			else
			{
				currentNode = nullptr;
			}
		}

		// Verbose mode will output success/failure messages to the console
		if (verbose)
		{
			std::cout << "Value \"" << valueToFind << "\" ";
			if (currentNode == nullptr)
			{
				std::cout << "not found in the tree.\n";
			}
			else
			{
				std::cout << "found at address " << currentNode << ".\n\n";
			}
		}
		return currentNode;
	}

	/// <summary>
	/// Finds the minimum (smallest) value stored in the tree.
	/// </summary>
	/// <param name="valueToFind">The value to search for within the tree.</param>
	/// <param name="verbose">Whether or not to output status messages to the console.</param>
	/// <returns>The minimum (smallest) value stored in the tree.</returns>
	Type Minimum(bool verbose = true)
	{
		// Returns a null value and displays a error message if the tree is empty
		if (IsEmpty(true))
		{
			return NULL;
		}

		Type value = MinNode(root)->GetValue();

		std::cout << "The smallest value stored in the tree is " << value << ".\n\n";
		return value;
	}

	/// <summary>
	/// Finds the maximum (largest) value stored in the tree.
	/// </summary>
	/// <param name="valueToFind">The value to search for within the tree.</param>
	/// <param name="verbose">Whether or not to output status messages to the console.</param>
	/// <returns>The maximum (largest) value stored in the tree.</returns>
	Type Maximum(bool verbose = true)
	{
		// Returns a null value and displays a error message if the tree is empty
		if (IsEmpty(true))
		{
			return NULL;
		}

		Type value = MaxNode(root)->GetValue();

		std::cout << "The largest value stored in the tree is " << value << ".\n\n";
		return value;
	}

	/// <summary>
	/// Deletes a node from the tree.
	/// </summary>
	/// <param name="delValue">The key value of the node to be deleted.</param>
	/// <param name="verbose">Whether or not to output status messages to the console.</param>
	void Delete(Type delValue, bool verbose = true)
	{
		BSNode<Type>* delNode = Find(delValue, false);

		// If the value isn't found in the tree, display an error message and exit function
		if (delNode == nullptr)
		{
			if (verbose)
			{
				std::cout << "Value \"" << delValue << "\" not found in the tree.\n\n";
			}
			return;
		}
		// The node is a leaf (has no children)
		else if (delNode->GetLeftChild() == nullptr && delNode->GetRightChild() == nullptr)
		{
			// The node is the root node and the only node in the tree
			if (delNode == root)
			{
				root = nullptr;
			}
			else if (delNode == delNode->GetParent()->GetLeftChild())
			{
				delNode->GetParent()->SetLeftChild(nullptr);
			}
			else if (delNode == delNode->GetParent()->GetRightChild())
			{
				delNode->GetParent()->SetRightChild(nullptr);
			}
		}
		// The node has two children
		else if (delNode->GetLeftChild() != nullptr && delNode->GetRightChild() != nullptr)
		{
			// The successor node is the minimum value in the delNode's right subtree
			BSNode<Type>* successor = MinNode(delNode->GetRightChild());

			// The node being deleted has no left subtree - bring the right child up one level
			if (successor == delNode->GetRightChild())
			{
				delNode->GetParent()->SetRightChild(delNode->GetRightChild());
				delNode->GetRightChild()->SetParent(delNode->GetParent());
				delNode->GetRightChild()->SetLeftChild(delNode->GetLeftChild());
				UpdateNodeHeights(delNode->GetParent());
			}
			/* Swaps the values of the delNode and succcessor node, 
			 * and sets the successor node as the node to be deleted */
			else
			{
				SwapValues(delNode, successor);
				successor->GetParent()->SetLeftChild(nullptr);
				delNode = successor;
			}
		}
		// The node has only has a single child
		else if (delNode->GetLeftChild() != nullptr && delNode->GetRightChild() == nullptr)
		{
			// Link the deletion node's parent to the deletion node's left child
			if (delNode == delNode->GetParent()->GetLeftChild())
			{
				delNode->GetParent()->SetLeftChild(delNode->GetLeftChild());
				delNode->GetLeftChild()->SetParent(delNode->GetParent());
			}
			else if (delNode == delNode->GetParent()->GetRightChild())
			{
				delNode->GetParent()->SetRightChild(delNode->GetLeftChild());
				delNode->GetLeftChild()->SetParent(delNode->GetParent());
			}
			UpdateNodeHeights(delNode->GetParent());
		}
		else if (delNode->GetLeftChild() == nullptr && delNode->GetRightChild() != nullptr)
		{
			// Link the deletion node's parent to the deletion node's right child
			if (delNode == delNode->GetParent()->GetLeftChild())
			{
				delNode->GetParent()->SetLeftChild(delNode->GetRightChild());
				delNode->GetRightChild()->SetParent(delNode->GetParent());
			}
			else if (delNode == delNode->GetParent()->GetRightChild())
			{
				delNode->GetParent()->SetRightChild(delNode->GetRightChild());
				delNode->GetRightChild()->SetParent(delNode->GetParent());
			}
			UpdateNodeHeights(delNode->GetParent());
		}
		// Unexpected behavior (if this ever shows up in the console window, I screwed up)
		else
		{
			std::cout << "Unexpected condition.\n\n";
		}

		delete delNode;

		if (verbose)
		{
			std::cout << "Value \"" << delValue << "\" deleted from the tree.\n\n";
		}
	}

	/// <summary>
	/// Deletes all the nodes from the tree (or subtree).
	/// </summary>
	/// <param name="verbose">Whether or not to output status messages to the console.</param>
	void DeleteAll(bool verbose = true)
	{
		// Displays a error message and exits the function if the tree is empty
		if (IsEmpty(verbose))
		{
			return;
		}

		DeleteNodes(root);

		// Gotta prevent those null reference exceptions
		root = nullptr;

		if (verbose)
		{
			std::cout << "All nodes deleted from the tree.\n\n";
		}
	}

	/// <summary>
	/// Prints the tree to the console (right branches are on top).
	/// </summary>
	void Print() 
	{
		// If the tree is empty, display an error message and exit the function
		if (IsEmpty(true))
		{
			return;
		}

		// Print the contents of the tree
		PrintNode(root, 0);
		std::cout << "\n";
	}
};

#endif //!BSTREE_H