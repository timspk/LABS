#include "Tree.h"
#include <iostream>

int main() {
	int intBuff;

	Tree<double>* operTree = new Tree<double>(0);
	std::cout << "Enter count of values for binary tree: ";
	std::cin >> intBuff;

	operTree = operTree->balanced(intBuff);

	operTree->DrawT();

	operTree->print_vert();

	std::cout << "Direct view: ";
	operTree->view_direct();
	std::cout << std::endl;
	std::cout << "Symetric view: ";
	operTree->view_symmetric();
	std::cout << std::endl;
	std::cout << "Reverse view: ";
	operTree->view_reverse();
	std::cout << std::endl;

	operTree = operTree->create_bst_from_balanced_tree();

	operTree->print_vert();

	operTree->DrawT();

	operTree->insert_left(14.6);

	operTree->insert_right(15.7);

	operTree->get_right()->insert_left(75.2);

	operTree->DrawT();

	return 0;
}
