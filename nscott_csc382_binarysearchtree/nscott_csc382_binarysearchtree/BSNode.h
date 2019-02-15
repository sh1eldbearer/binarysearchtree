#ifndef BSNODE_H
#define BSNODE_H

template<typename Type>
class BSNode
{
private:
	Type value;	// The value held by this node
	int height;	// The height this node resides at in the tree
	BSNode<Type>* parent = nullptr;	// Pointer to the parent node of this node
	BSNode<Type>* leftChild = nullptr;	// Pointer to the left child node of this node
	BSNode<Type>* rightChild = nullptr;	// Pointer to the right child node of this node
public:
	/// <summary>
	/// Default constructor
	/// </summary>
	/// <param name="initValue">The initial value to be stored in this node. 
	/// Defaults to NULL.</param>
	/// <param name="height">The height this node resides at in the tree. 
	Defaults to 0.</param>
	/// <returns></returns>
	BSNode(Type initValue = NULL, int height = -1) : value(initValue), height(height + 1) { }		// Constructor

	Type GetValue()		// Returns the value stored in this node
	{
		return value;
	}

	void SetValue(Type newValue)	// Changes the value stored in this node
	{
		value = newValue;
	}

	int GetHeight()		// Returns the height this node resides at in the tree
	{
		return height;
	}

	void SetHeight(int newHeight)		// Changes the height this node resides at in the tree
	{
		height = newHeight;
	}

	BSNode<Type>* GetParent()	// Returns the memory address of this node's parent
	{
		return parent;
	}

	void SetParent(BSNode<Type>* newPtr)		// Changes which node is this node's parent
	{
		parent = newPtr;
	}

	BSNode<Type>* GetLeftChild()		// Returns the memory address of this node's left child
	{
		return leftChild;
	}

	void SetLeftChild(BSNode<Type>* newPtr)		// Changes which node is this node's left child
	{
		leftChild = newPtr;
	}

	BSNode<Type>* GetRightChild()	// Returns the memory address of this node's right child
	{
		return rightChild;
	}

	void SetRightChild(BSNode<Type>* newPtr)		// Changes which node is this node's left child
	{
		rightChild = newPtr;
	}
};

#endif