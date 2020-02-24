/*****************************************************************************
 * AUTHOR 	  		: Nick Reardon
 * Assignment #5	: Binary Trees
 * CLASS			: CS1D
 * SECTION			: MW - 2:30p
 * DUE DATE			: 02 / 19 / 20
 *****************************************************************************/
#ifndef _LINKEDBINARYTREE_H_
#define _LINKEDBINARYTREE_H_
#include <exception>
#include <sstream>
#include <string>
#include <queue>
#include "Except.h"

enum ERROR_TYPE
{
	DEFUALT,
	FULL,
	EMPTY
};

struct Trunk
{
	Trunk* prev;
	std::string str;

	Trunk(Trunk* prev, std::string str)
	{
		this->prev = prev;
		this->str = str;
	}
};

template <class Type>
struct Node
{
	Type value;

	Node<Type>* parent;

	Node<Type>* left;
	Node<Type>* right;

	Node<Type>(const Type& newValue, Node<Type>* parentNode, Node<Type>* leftNode, Node<Type>* rightNode)
	{
		value = newValue;

		parent = parentNode;

		left = leftNode;
		right = rightNode;
	}

	Node<Type>(const Type& newValue, Node<Type>* leftNode, Node<Type>* rightNode)
	{
		value = newValue;

		left = leftNode;
		right = rightNode;
	}

};

template <class Type>
class LinkedBinaryTree
{
private:
	Node<Type>* root;

	int capacity;
	int currentSize;


protected:
	void insertRecursion(const Type& newValue, Node<Type>* node)
	{
		if (newValue == node->value)
		{
			Node<Type>* tempPtr = new Node<Type>(newValue, node, node->left, nullptr);

			if (node->left != nullptr)
			{
				node->left->parent = tempPtr;
			}

			node->left = tempPtr;

			tempPtr = nullptr;

		}
		else if (newValue > node->value)
		{
			if (node->right == nullptr)
			{
				node->right = new Node<Type>(newValue, node, nullptr, nullptr);
			}
			else
			{
				insertRecursion(newValue, node->right);
			}
		}
		else
		{
			if (node->left == nullptr)
			{
				node->left = new Node<Type>(newValue, node, nullptr, nullptr);
			}
			else
			{
				insertRecursion(newValue, node->left);
			}
		}
	}

	void destroyRecursion(Node<Type>* node)
	{
		if (node != nullptr)
		{
			destroyRecursion(node->left);
			destroyRecursion(node->right);
			delete node;
		}
	}

	Type* searchRecursion(const Type& searchValue, const Node<Type>* node) const
	{
		if (searchValue == node->value)
		{
			return node;
		}
		else
		{
			if (searchValue > node->value)
			{
				if (searchValue == node->right->value)
				{
					return node->right;
				}
				else
				{
					searchRecursion(searchValue, node->right);
				}
			}
			else
			{
				if (searchValue == node->left->value)
				{
					return node->left;
				}
				else
				{
					searchRecursion(searchValue, node->left);
				}
			}
		}
	}

	void InOrder_Recursion(const Node<Type>* node, std::ostream& output) const
	{
		if (root == nullptr)
		{
			throw(Except_runtime_error_class("Tree is empty - Nothing to print", EMPTY, 5));
		}
		else if(node != nullptr)
		{

			InOrder_Recursion(node->left, output);

			output << node->value << "  ";

			InOrder_Recursion(node->right, output);

		}
	}

	void PostOrder_Recursion(const Node<Type>* node, std::ostream& output) const
	{
		if (root == nullptr)
		{
			throw(Except_runtime_error_class("Tree is empty - Nothing to print", EMPTY, 5));
		}
		if (node != nullptr)
		{
			PostOrder_Recursion(node->left, output);

			PostOrder_Recursion(node->right, output);

			output << node->value << "  ";
		}
			
	}

	void PreOrder_Recursion(const Node<Type>* node, std::ostream& output) const
	{
		if (root == nullptr)
		{
			throw(Except_runtime_error_class("Tree is empty - Nothing to print", EMPTY, 5));
		}
		if (node != nullptr)
		{
			output << node->value << "  ";

			PreOrder_Recursion(node->left, output);

			PreOrder_Recursion(node->right, output);

		}
	}

	void BreadthFirst_Recursion(std::queue<Node<Type>*>& queue, const Node<Type>* node, std::ostream& output) const
	{
		if (root == nullptr)
		{
			throw(Except_runtime_error_class("Tree is empty - Nothing to print", EMPTY, 5));
		}
		if (node != nullptr)
		{
			output << node->value << "  ";

			if (node->left != nullptr)
			{
				queue.push(node->left);
			}

			if (node->right != nullptr)
			{
				queue.push(node->right);
			}

			queue.pop();

			if (!queue.empty())
			{
				BreadthFirst_Recursion(queue, queue.front(), output);
			}
		}
	}



	void Print2DUtil(const Node<Type>* branch, int space, std::ostream& output) const
	{
		// Base case  
		if (branch == NULL)
			return;

		// Increase distance between levels  
		space += 10;

		// Process right child first  
		Print2DUtil(branch->right, space, output);

		// Print current node after space  
		// count  
		output << '\n';
		for (int i = 10; i < space; i++)
		{
			output << " ";
		}
			
		output << branch->value << "\n";

		// Process left child  
		Print2DUtil(branch->left, space, output);
	}

	// Helper function to print branches of the binary tree
	void showTrunks(Trunk* p, std::ostream& output)
	{
		if (p == nullptr)
			return;

		showTrunks(p->prev, output);

		output << p->str;
	}

	// Recursive function to print binary tree
	// It uses inorder traversal
	void printTreeHelper(Node<Type>* node, Trunk* prev, bool isLeft, std::ostream& output)
	{
		if (node == nullptr)
			return;

		std::string prev_str = "    ";
		Trunk* trunk = new Trunk(prev, prev_str);

		printTreeHelper(node->right, trunk, true, output);

		if (!prev)
			trunk->str = "---";
		else if (isLeft)
		{
			trunk->str = ".---";
			prev_str = "   |";
		}
		else
		{
			trunk->str = "`---";
			prev->str = prev_str;
		}

		showTrunks(trunk, output);
		output << node->value << '\n';

		if (prev)
			prev->str = prev_str;
		trunk->str = "   |";

		printTreeHelper(node->left, trunk, false, output);
	}


public:

	LinkedBinaryTree<Type>()
	{
		root = nullptr;
		currentSize = 0;
	}

	//LinkedBinaryTree<Type>(const LinkedBinaryTree<Type>& otherTree);

	~LinkedBinaryTree()
	{
		destroy();
	}

	void destroy()
	{
		destroyRecursion(root);
		root = nullptr;
		currentSize = 0;
	}

	//bool empty() const;
	//bool full() const;
	//int size() const;

	void insert(const Type& newValue)
	{
		if (root == nullptr)
		{
			root = new Node<Type>(newValue, nullptr, nullptr, nullptr);
		}
		else
		{
			insertRecursion(newValue, root);
		}

		currentSize++;
	}

	Type* search(const Type& searchValue) const
	{
		search(searchValue, root);
	}

	void printAll(std::ostream& output) const;

	void Traversal_InOrder(std::ostream& output) const
	{
		output << "In Order Traversal:" << '\n';
		InOrder_Recursion(root, output);
		output << "\n\n";
	}


	void Traversal_PostOrder(std::ostream& output) const
	{
		output << "Post Order Traversal:" << '\n';
		PostOrder_Recursion(root, output);
		output << "\n\n";
	}

	void Traversal_PreOrder(std::ostream& output) const
	{
		output << "Pre Order Traversal:" << '\n';
		PreOrder_Recursion(root, output);
		output << "\n\n";
	}

	void Traversal_BreadthFirst(std::ostream& output) const
	{
		std::queue<Node<Type>*> queue;

		queue.push(root);

		output << "Breadth First Traversal:" << '\n';
		BreadthFirst_Recursion(queue, root, output);
		output << "\n\n";
	}

	void Print2D(std::ostream& output) const
	{
		Print2DUtil(root, 0, output);
	}



	void printTree(std::ostream& output) const
	{
		printTreeHelper(root, nullptr, false, output);
		output << "\n\n";
	}

	void PrintLevelByLevel(std::ostream& output) const
	{
		if (root == nullptr)
		{
			throw(Except_runtime_error_class("Tree is empty - Nothing to print", EMPTY, 5));
		}

		output << "Level By Level:" << '\n';

		std::queue<Node<Type>*> queue;

		int levelNodes = 0;

		queue.push(root);

		while (!queue.empty()) 
{

			levelNodes = queue.size();

			while (levelNodes > 0) 
			{
				Node<Type>* temp = queue.front();

				output << temp->value << "  ";

				if (temp->left != nullptr)
				{
					queue.push(temp->left);
				}

				if (temp->right != nullptr) 
				{
					queue.push(temp->right);
				}

				queue.pop();

				levelNodes--;
			}
			output << '\n';
		}

		output << "\n";
	}

		

};


#endif // !_LINKEDBINARYTREE_H_
