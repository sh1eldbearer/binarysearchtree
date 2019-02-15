#ifndef BSNODE_H
#define BSNODE_H

template<typename Type>
class BSNode
{
private:
	Type value;	// The value held by this node
	int height;	// The height this node resides at in the tree
	BSNode<Type>* parent;	// A pointer to the parent node of this node
	BSNode<Type>* leftChild;	// A pointer to the left child node of this node
	BSNode<Type>* rightChild;	// A pointer to the right child node of this node
public:
	/// <summary>
	/// Default constructor.
	/// </summary>
	BSNode()
	{ 
		value = NULL;
		height = -1;
		parent = nullptr;
		leftChild = nullptr;
		rightChild = nullptr;
	}

	/// <summary>
	/// Default destructor.
	/// </summary>
	~BSNode() { }

	/// <summary>
	/// Accessor for the key value stored in this node.
	/// </summary>
	/// <returns>The key value stored in this node.</returns>
	Type GetValue()
	{
		return value;
	}

	/// <summary>
	/// Changes the value stored in this node.
	/// </summary>
	/// <param name="newValue">The new value to be stored in this node.</param>
	void SetValue(Type newValue)
	{
		value = newValue;
	}

	/// <summary>
	/// Accessor for the height of this node in the tree.
	/// </summary>
	/// <returns>Returns the height this node resides at in the tree.</returns>
	int GetHeight()
	{
		return height;
	}

	/// <summary>
	/// Changes the height this node resides at in the tree.
	/// </summary>
	/// <param name="newValue">The new height at which this node resides in the tree.</param>
	void SetHeight(int newHeight)
	{
		height = newHeight;
	}

	/// <summary>
	/// Accessor for the pointer to this node's parent node.
	/// </summary>
	/// <param name="newValue"></param>
	/// <returns>Returns a pointer to the node that is this node's parent.</returns>
	BSNode<Type>* GetParent()
	{
		return parent;
	}

	/// <summary>
	/// Changes which node is this node's parent node.
	/// </summary>
	/// <param name="newValue">The pointer to be set as this node's parent.</param>
	void SetParent(BSNode<Type>* newPtr)
	{
		parent = newPtr;
	}

	/// <summary>
	/// Accessor for the pointer to this node's left child node.
	/// </summary>
	/// <returns>Returns a pointer to the node that is this node's left child node.</returns>
	BSNode<Type>* GetLeftChild()
	{
		return leftChild;
	}

	/// <summary>
	/// Changes which node is this node's left child node.
	/// </summary>
	/// <param name="newValue">The pointer to be set as this node's left child node.</param>
	void SetLeftChild(BSNode<Type>* newPtr)
	{
		leftChild = newPtr;
	}

	/// <summary>
	/// Accessor for the pointer to this node's right child node.
	/// </summary>
	/// <returns>Returns a pointer to the node that is this node's right child node.</returns>
	BSNode<Type>* GetRightChild()
	{
		return rightChild;
	}

	/// <summary>
	/// Changes which node is this node's right child node.
	/// </summary>
	/// <param name="newValue">The pointer to be set as this node's right child node.</param>
	void SetRightChild(BSNode<Type>* newPtr)
	{
		rightChild = newPtr;
	}
};

#endif