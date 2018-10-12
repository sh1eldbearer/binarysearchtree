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
	
	template<typename Type>
	void SetValue(Type newValue)	// Changes the value stored in this node
	{

	}

	BSNode<Type>* GetLeftChildPtr()		// Returns the memory address of this node's left child
	{

	}

	template<typename Type>
	void SetLeftChildPtr(Type* newPtr)		// Changes which node is this node's left child
	{

	}

	BSNode<Type>* GetRightChildPtr()	// Returns the memory address of this node's right child
	{

	}

	template<typename Type>
	void SetRightChildPtr(Type* newPtr)		// Changes which node is this node's left child
	{

	}
};

#endif