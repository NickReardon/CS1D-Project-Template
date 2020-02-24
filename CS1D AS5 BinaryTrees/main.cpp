/*****************************************************************************
 * AUTHOR 	  		: Nick Reardon
 * Assignment #5	: Binary Trees
 * CLASS			: CS1D
 * SECTION			: MW - 2:30p
 * DUE DATE			: 02 / 19 / 20
 *****************************************************************************/
#include "main.h"

using std::cout; using std::endl;
#include <stdio.h>

int main()
{

	/*
	 * HEADER OUTPUT
	 */
	PrintHeader(cout, "Prompt.txt");

	/********************************************************************/

	LinkedBinaryTree<int> bTree;

	std::ifstream iFile;
	iFile.open("Input.txt");

	
	int temp;
	while (iFile >> temp)
	{
		bTree.insert(temp);

		bTree.printTree(cout);

	}
	iFile.close();
	


	bTree.printTree(cout);

	bTree.PrintLevelByLevel(cout);

	bTree.Traversal_InOrder(cout);

	bTree.Traversal_PostOrder(cout);

	bTree.Traversal_PreOrder(cout);

	bTree.Traversal_BreadthFirst(cout);


	system("pause");
	return 0;
}
