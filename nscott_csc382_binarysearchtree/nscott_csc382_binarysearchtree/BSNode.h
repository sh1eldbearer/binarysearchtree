#ifndef BSNode_h
#define BSNode_h

/*																								  */

template<typename Type>
class BSNode
{
private:
	Type value;									// The value held by this node
	BSNode<Type>* leftChildPtr = nullptr;		// Pointer to the left child node of this node
	BSNode<Type>* rightChildPtr = nullptr;		// Pointer to the right child node of this node
public:
	BSNode(Type initValue = NULL) : value(initValue) { }		// Constructor
	~BSNode();													// Destructor

	Type GetValue()		// Returns the value stored in this node
	{
		return value;
	}

	template<typename Type>
	void SetValue(Type newValue)	// Changes the value stored in this node
	{
		value = newValue;
	}

	BSNode<Type>* GetLeftChildPtr()		// Returns the memory address of this node's left child
	{
		return leftChildPtr;
	}

	template<typename Type>
	void SetLeftChildPtr(Type* newPtr)		// Changes which node is this node's left child
	{
		leftChildPtr = newPtr;
	}

	BSNode<Type>* GetRightChildPtr()	// Returns the memory address of this node's right child
	{
		return rightChildPtr;
	}

	template<typename Type>
	void SetRightChildPtr(Type* newPtr)		// Changes which node is this node's left child
	{
		rightChildPtr = newPtr;
	}

	BSNode<Type>* InsertNode(BSNode<Type>* nodeToCheck, Type newValue)		// Inserts a new node 
	{
		// If the node being checked is null, creates a new node to occpy that spot on the tree
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
		}
		else if (newValue > nodeToCheck->GetValue())
		{
			// Move down the tree along the right branch (runs recursively until an avaiable node is found)
			nodeToCheck->SetRightChildPtr(InsertNode(nodeToCheck->GetRightChildPtr(), newValue));
		}

		return nodeToCheck;
	}
};

#endif