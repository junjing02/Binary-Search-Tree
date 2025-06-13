#include <iostream>
#include <fstream>
#include <algorithm>
#include "BST.h"


using namespace std;


BST::BST() {
	root = NULL;
	count = 0;
}


bool BST::empty() {
	if (count == 0) return true;
	return false;
}


int BST::size() {
	return count;
}


void BST::preOrderPrint() {
	if (root == NULL) return;// handle special case
	else preOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::preOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;
	cur->item.print(cout);
	preOrderPrint2(cur->left);
	preOrderPrint2(cur->right);
}


void BST::inOrderPrint(ostream &out) {
	if (root == NULL) return;// handle special case
	else inOrderPrint2(root, out);// do normal process
	out << endl;
}


void BST::inOrderPrint2(BTNode *cur, ostream &out) {

	if (cur == NULL) return;

	inOrderPrint2(cur->left, out);
	cur->item.print(out);
	inOrderPrint2(cur->right, out);
}


void BST::postOrderPrint() {
	if (root == NULL) return;// handle special case
	else postOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::postOrderPrint2(BTNode *cur) {
	if (cur == NULL) return;
	postOrderPrint2(cur->left);
	postOrderPrint2(cur->right);
	cur->item.print(cout);
}



int BST::countNode() {
	int	counter = 0;
	if (root == NULL) return 0;
	countNode2(root, counter);
	return counter;
}


void BST::countNode2(BTNode *cur, int &count) {
	if (cur == NULL) return;
	countNode2(cur->left, count);
	countNode2(cur->right, count);
	count++;
}


bool BST::findGrandsons(type grandFather) {
	if (root == NULL) return false;
	return (fGS2(grandFather, root));
}


bool BST::fGS2(type grandFather, BTNode *cur) {
	if (cur == NULL) return false;
	//if (cur->item == grandFather) {
	if (cur->item.compare2(grandFather)){

		fGS3(cur, 0);// do another TT to find grandsons
		return true;
	}
	if (fGS2(grandFather, cur->left)) return true;
	return fGS2(grandFather, cur->right);
}


void BST::fGS3(BTNode *cur, int level) {
	if (cur == NULL) return;
	if (level == 2) {
		cur->item.print(cout);
		return;  // No need to search downward
	}
	fGS3(cur->left, level + 1);
	fGS3(cur->right, level + 1);
}



void BST::topDownLevelTraversal() {
	BTNode			*cur;
	Queue		    q;


	if (empty()) return; 	// special case
	q.enqueue(root);	// Step 1: enqueue the first node
	while (!q.empty()) { 	// Step 2: do 2 operations inside
		q.dequeue(cur);
		if (cur != NULL) {
			cur->item.print(cout);

			if (cur->left != NULL)
				q.enqueue(cur->left);

			if (cur->right != NULL)
				q.enqueue(cur->right);
		}
	}
}

//insert for BST
bool BST::insert(type newItem) {
	BTNode	*cur = new BTNode(newItem);
	if (!cur) return false;		// special case 1
	if (root == NULL) {
		root = cur;
		count++;
		return true; 			// special case 2
	}
	insert2(root, cur);			// normal
	count++;
	return true;
}


void BST::insert2(BTNode *cur, BTNode *newNode) {
	//if (cur->item > newNode->item) {
	if (cur->item.compare1(newNode->item)){
		if (cur->left == NULL)
			cur->left = newNode;
		else
			insert2(cur->left, newNode);
	}
	else {
		if (cur->right == NULL)
			cur->right = newNode;
		else
			insert2(cur->right, newNode);
	}
}



bool BST::remove(type item) {
	if (root == NULL) return false; 		// special case 1: tree is empty
	return remove2(root, root, item); 		// normal case
}

bool BST::remove2(BTNode *pre, BTNode *cur, type item) {

	// Turn back when the search reaches the end of an external path
	if (cur == NULL) return false;

	// normal case: manage to find the item to be removed
	//if (cur->item == item) {
	if (cur->item.compare2(item)){
		if (cur->left == NULL || cur->right == NULL)
			case2(pre, cur);	// case 2 and case 1: cur has less than 2 sons
		else
			case3(cur);		// case 3, cur has 2 sons
		count--;				// update the counter
		return true;
	}

	// Current node does NOT store the current item -> ask left sub-tree to check
	//if (cur->item > item)
	if (cur->item.compare1(item))
		return remove2(cur, cur->left, item);

	// Item is not in the left subtree, try the right sub-tree instead
	return remove2(cur, cur->right, item);
}


void BST::case2(BTNode *pre, BTNode *cur) {

	// special case: delete root node
	if (pre == cur) {
		if (cur->left != NULL)	// has left son?
			root = cur->left;
		else
			root = cur->right;

		free(cur);
		return;
	}

	if (pre->right == cur) {		// father is right son of grandfather? 
		if (cur->left == NULL)			// father has no left son?
			pre->right = cur->right;			// connect gfather/gson
		else
			pre->right = cur->left;
	}
	else {						// father is left son of grandfather?
		if (cur->left == NULL)			// father has no left son? 
			pre->left = cur->right;				// connect gfather/gson
		else
			pre->left = cur->left;
	}

	free(cur);					// remove item
}


void BST::case3(BTNode *cur) {
	BTNode		*is, *isFather;

	// get the IS and IS_parent of current node
	is = isFather = cur->right;
	while (is->left != NULL) {
		isFather = is;
		is = is->left;
	}

	// copy IS node into current node
	cur->item = is->item;

	// Point IS_Father (grandfather) to IS_Child (grandson)
	if (is == isFather)
		cur->right = is->right;		// case 1: There is no IS_Father    
	else
		isFather->left = is->right;	// case 2: There is IS_Father

	// remove IS Node
	free(is);
}








int BST::height(BTNode* cur)
{
	if (cur == NULL)
	{
		return -1;
	}
	int left = height(cur->left);
	int right = height(cur->right);

	return ((left > right) ? left : right) + 1;
}


bool BST::deepestNodes()
{
	if (empty())
	{
		cout << endl;
		cout << "Tree is empty" << endl;
		return false;
	}
	deepestNodes2(root, height(root));
	cout << endl;
	return true;
}

void BST::deepestNodes2(BTNode* cur, int level)
{
	if (cur == NULL)
	{
		return;
	}
	if (level == 0)
	{
		cout << cur->item.id << "\t";
	}
	else
	{
		deepestNodes2(cur->left, level - 1);
		deepestNodes2(cur->right, level - 1);
	}
}


void BST::inOrderPrintDesc(ostream& out) {
	if (root == NULL) return;// handle special case
	else inOrderPrintDesc2(root, out);// do normal process
	out << endl;
}


void BST::inOrderPrintDesc2(BTNode* cur, ostream& out) {

	if (cur == NULL) return;

	inOrderPrintDesc2(cur->right, out);
	cur->item.print(out);
	inOrderPrintDesc2(cur->left, out);
}

bool BST::display(int order, int source)
{
	if (root == NULL)
	{
		cout << "Tree is empty" << endl;
		return false;
	}

	if (source == 1)
	{
		system("cls");

		if (order == 1)
		{
			cout << endl << endl << "*****************************************************" << endl;
			cout << "\tStudent Info in ASCENDING ORDER" << endl;
			cout << "*****************************************************" << endl;
			inOrderPrint(cout);
		}
		else
		{
			cout << endl << endl << "*****************************************************" << endl;
			cout << "\tStudent Info in DESCENDING ORDER" << endl;
			cout << "*****************************************************" << endl;
			inOrderPrintDesc(cout);
		}
	}
	else
	{
		ofstream outfile("student_info.txt");

		cout << endl;
		cout << "Successfully displayed in student_info.txt" << endl << endl;

		if (!outfile.is_open())
		{
			return false;
		}

		if (order == 1)
		{
			outfile << endl << endl << "*****************************************************" << endl;
			outfile << "\tStudent Info in ASCENDING ORDER" << endl;
			outfile << "*****************************************************" << endl;
			inOrderPrint(outfile);
			outfile << "*****************************************************" << endl << endl;
			outfile << endl;
		}
		else
		{
			outfile << endl << endl << "*****************************************************" << endl;
			outfile << "\tStudent Info in DESCENDING ORDER" << endl;
			outfile << "*****************************************************" << endl;
			inOrderPrintDesc(outfile);
			outfile << "*****************************************************" << endl << endl;
			outfile << endl;
		}
	}
	return true;
}


bool BST::CloneSubtree(BST t1, type item)
{
	bool found = false;
	if (t1.empty())
	{
		cout << "Tree is empty" << endl;
		return false;
	}
	CloneSubtree2(t1.root, item, found);
	if (!found)
	{
		cout << "Student ID not found" << endl;
		return false;
	}

	return true;

}

void BST::CloneSubtree2(BTNode* cur, type item, bool &found)
{
	if (cur == NULL)
	{
		return;
	}
	if (cur->item.compare2(item))
	{
		CloneSubtree3(cur);
		found = true;
	}
	else
	{
		if (cur->item.compare1(item))
		{
			CloneSubtree2(cur->left, item, found);
		}
		else
		{
			CloneSubtree2(cur->right, item, found);
		}
	}
}

void BST::CloneSubtree3(BTNode* cur)
{
	if (cur == NULL)
	{
		return;
	}
	insert(cur->item);

	CloneSubtree3(cur->left);
	CloneSubtree3(cur->right);
}

void BST::clear()
{
	while (root != NULL)
	{
		remove(root->item);
	}
}

bool BST::printLevelNodes()
{
	if (root == NULL)
	{
		cout << "Tree is empty" << endl;
		return false;
	}
	int level = height(root);

	for (int i = 0; i <= level; i++)
	{
		cout << "Level " << i + 1  << " nodes: ";
		printLevelNodes2(root, i);
		cout << endl;
	}
	cout << endl;
	return true;
}

void BST::printLevelNodes2(BTNode* cur, int level)
{
	if (cur == NULL)
	{
		return;
	}
	if (level == 0)
	{
		cout << cur->item.id << "\t";
	}
	else
	{
		printLevelNodes2(cur->left, level - 1);
		printLevelNodes2(cur->right, level - 1);
	}
}

bool BST::printPath()
{
	if (root == NULL)
	{
		cout << "Tree is empty" << endl;
		return false;
	}
	cout << "Below are all the external paths for the tree:" << endl << endl;

	int path[20], count = 0;
	printPath2(root, path, count);
	cout << endl;
	return true;
}

void BST::printPath2(BTNode* cur, int path[], int count)
{
	if (cur == NULL)
	{
		return;
	}
	
	path[count] = cur->item.id;
	count++;

	if (cur->left == NULL && cur->right == NULL)
	{
		for (int i = 0; i < count; i++)
		{
			cout << path[i] << "\t";
		}
		cout << endl;
	}
	else
	{
		printPath2(cur->left, path, count);
		printPath2(cur->right, path, count);
	}


}