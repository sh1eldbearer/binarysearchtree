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
public:
	BSTree() {}		// Constructor
	~BSTree() {}	// Destructor

	BSNode<Type>* GetRootPtr()		// Returns the memory address of the root node
	{

	}

	template<typename Type>
	void SetRootPtr(Type* newPtr)		// Changes which node is the tree's root node
	{

	}

	template<typename Type>
	BSNode<Type>* CreateNode(Type nodeValue)	// Creates a new node in the tree
	{

	}

	template<typename Type>
	BSNode<Type>* FindNode(Type findValue)	// Attempts to find a node containing the given value
	{

	}

	template<typename Type>
	void DeleteNode(BSNode<Type>* nodePtr)	// Deletes a node from the tree
	{

	}

	Type MaxValue()		// Finds the largest value stored in the tree
	{

	}
};

#endif