/*Borz Robert-Ionut Group 30424
* The code below implements the following operations: BUILD_TREE,OS_SELECT,OS_DELETE with their additional helper
* functions.
* BUILD_TREE: builds an augmented PBT(balanced+augmented Binary Search Tree) with the help of an additional function 
* called postorderAUG, the complexity of the algorithm being O(n) for both, so the total complexity is still O(n)
* OS_SELECT: works on the following priciple->using the dimension of the nodes it searches through the tree deciding
* if the node with the given rank is either on the left or on the right side of the current node
* OS_DELETE: deletes the nodes like in a normal BST and toghether with the function fixBranch fixes the affected
* branch depending on the type of node deleted(node with 2 childre/node with 1 child or no children)
*/
#include <iostream>
#include "Profiler.h"

#define level 5 
#define MAX_ARRAY_SIZE 10000
#define MAX_SIZE 10000
#define STEP_SIZE 100

using namespace std;

Profiler p("L07");

typedef struct TNode//our node structure  for implementing the augmented balanced BST
{
	int key;
	int dim;
	TNode* left;
	TNode* right;
	TNode* parent;
};

TNode* newNode(int key)//creating a new node
{
	TNode* node = (TNode*)malloc(sizeof(TNode));
	node->key = key;
	node->dim = 1;
	node->left = NULL;
	node->right = NULL;

	return node;
}

void prettyPrint(TNode* root, int space)//the function pretty prints our tree,by adding the needed spaces
{                                      //similar with the print from the last lab
	if (root == NULL)
		return;

	space += level;

	prettyPrint(root->right, space);

	cout << endl;
	for (int i = level; i < space; i++)
		cout << " ";
	if (root->parent != NULL)
		cout << root->key << " [" << root->dim << "]" << "[p=" << root->parent->key << "]" << endl;
	else
		cout << root->key << " [" << root->dim << "] " << "[p=NULL]" << endl;

	prettyPrint(root->left, space);
}

TNode* BUILD_TREE(int v[MAX_ARRAY_SIZE], int start, int end, int size)
{
	Operation opCreate = p.createOperation("opCreate", size);

	if (start > end) //stop condition
		return NULL;

	int middle = (start + end) / 2; //we select the median

	opCreate.count();
	TNode* root = newNode(v[middle]);

	opCreate.count(2);
	root->left = BUILD_TREE(v, start, middle - 1, size);// we apply a D&C strategy by dividing the array in half    
	root->right = BUILD_TREE(v, middle + 1, end, size);//recursevly until reaching ending condition

	return root;
}

void postorderAUG(TNode* root, int size)//we traverse the tree in a postorder approach in order to calculate each node's dimension
{
	Operation opDimAsign = p.createOperation("opDimAsign", size);
	if (root == NULL)
		return;

	postorderAUG(root->left, size);
	postorderAUG(root->right, size);

	//for each node we verify the number of children and the dimension in order to calculate the node's dimension
	if (root->left != NULL)           //post order approach
	{
		//if our node has a left child, our node's dimension will increase
	   //by child dimension(dim[parent]+=dim[child_left])
		root->dim = root->dim + root->left->dim;
		root->left->parent = root; //in the same time we set the parent pointer for each node
		opDimAsign.count(2);

	}
	if (root->right != NULL)
	{
		//same as in the previous case, but now we search for right child
	   //(dim[parent]+=dim[child_right])
		root->dim = root->dim + root->right->dim;
		root->right->parent = root;//in the same time we set the parent pointer for each node
		opDimAsign.count(2);
	}

}

void fixBranch(TNode* node)
{
	TNode* t = node;
	while (t != NULL)
	{
		t->dim--;
		t = t->parent;
	}
}

TNode* findMinP(TNode* root)//we go as far left as possible in our tree with the given root
{
	TNode* p;
	p = root;

	while (p->left != NULL)
	{
		p = p->left;

	}

	return p;
}

void transplant(TNode** root, TNode* u, TNode* v, int size)
{ //transplant replaces the subtree rooted at node u with the 
 //subtree rooted at node v, node u’s parent becomes node v’s 
//parent, and u’s parent ends up having v as its appropriate child.

	Operation opTransplant = p.createOperation("opTransplant", size);
	if (u == NULL)
		return;
	else
	{
		opTransplant.count();
		if (u->parent == NULL)
		{
			*root = v;
			opTransplant.count();
		}

		else
		{
			opTransplant.count();
			if (u->parent->left == u)
			{
				u->parent->left = v;
				opTransplant.count();
			}

			else
			{
				u->parent->right = v;
				opTransplant.count();
			}

		}
	}
	if (v != NULL)
	{
		v->parent = u->parent;
		opTransplant.count();
	}

}

TNode* OS_DELETE(TNode* root, TNode* deleted, int size)
{
	Operation opDelete = p.createOperation("opDelete", size);

	if (deleted == NULL)//if the node we want to delete does not exist
		return root;

	if (deleted->left == NULL)//if our node doesn't have a left child, we replace the node with its right child
	{                        //which may or may not exist(it can be also NULL)
		transplant(&root, deleted, deleted->right, size);
	}

	else if (deleted->right == NULL)//node's left child isn't NULL but right is, so we replace the node with 
	{                              //its left child
		transplant(&root, deleted, deleted->left, size);
	}
	else {
		opDelete.count();
		TNode* succ = findMinP(deleted->right);//lies in deleted right sub-tree and it has no left child
		opDelete.count();
		if (deleted->right != succ)
		{
			transplant(&root, succ, succ->right, size);
			succ->right = deleted->right;
			succ->right->parent = succ;
			opDelete.count(2);
		}
		transplant(&root, deleted, succ, size); //If succ is deleted right child, then we replace delete_node by succ.
		succ->left = deleted->left;
		succ->left->parent = succ;
		opDelete.count(2);
	}
	return root;

}

TNode* OS_SELECT(TNode* root, int i, int size)
{
	Operation opSelect = p.createOperation("opSelect", size);
	int r;
	opSelect.count();
	if (root->left != NULL)
		r = root->left->dim + 1;
	else
		r = 1;

	if (i == r)
		return root;
	else
	{
		if (i < r)
			return OS_SELECT(root->left, i,size);
		else
			return OS_SELECT(root->right, i - r,size);
	}
}

void generatecases1()
{
	for (int i = 0; i <= 5; i++)//we repeat 5 times in order to obtain more accurate results
	{

		for (int j = STEP_SIZE; j <= MAX_SIZE; j = j + STEP_SIZE)//we vary the size between 100-10000
		{

			int v[MAX_ARRAY_SIZE];
			TNode* root;
			TNode* selected;

			FillRandomArray(v, STEP_SIZE, 1, STEP_SIZE, true, 1);

			root = BUILD_TREE(v, 0, j, j);
			root->parent = NULL;
			postorderAUG(root, j);

			FillRandomArray(v, STEP_SIZE, 1, STEP_SIZE, true, 2);

			for (int i = 0; i < STEP_SIZE; i++)
			{

				selected = OS_SELECT(root, v[i],j);

				//if node has exactly one child or no children
				if ((selected->right != NULL && selected->left == NULL) || (selected->right == NULL && selected->left != NULL) || (selected->right == NULL && selected->left == NULL))
					fixBranch(selected);
				else
				{
					TNode* p = findMinP(selected->right);
					fixBranch(p);
					p->dim = selected->dim;

				}

				root = OS_DELETE(root, selected, j);

			}

		}

	}
	p.addSeries("Delete", "opTransplant", "opDelete");
	p.addSeries("Total1", "Delete", "opCreate");
	p.addSeries("Total2", "Total1", "opDimAsign");
	p.addSeries("Total", "Total2", "opSelect");
	
	p.divideValues("Total", 5);
	p.showReport();

}

void demo1()
{
	int v[11] = { 1,2,3,4,5,6,7,8,9,10,11 };
	TNode* root;
	TNode* selected;
	int n = sizeof(v) / sizeof(v[0]);

	root = BUILD_TREE(v, 0, 10, n);
	root->parent = NULL;
	postorderAUG(root, n);

	cout << "* PrettyPrint *" << endl;
	prettyPrint(root, 0);

	int k[3];
	//we have to pick the numbers to be in a decreasing order because we want to avoid the attempt to delete
	//a number with a rank being already inexistent(ex: we delete any rank except 11 and then we want to delete 11,
	//the program will crash because after deleting one item the maximum rank is 10, in our particular case)
	FillRandomArray(k, 3, 1, 11, true, 2);
	for (int i = 0; i < 3; i++)
	{
		selected = OS_SELECT(root, k[i],11);
		cout << "The element with the rank " << k[i] << " is: " << selected->key << endl;

		//if node has exactly one child or none
		if ((selected->right != NULL && selected->left == NULL) || (selected->right == NULL && selected->left != NULL) || (selected->right == NULL && selected->left == NULL))
			fixBranch(selected);
		else//if the node has 2 children
		{
			TNode* p = findMinP(selected->right);
			fixBranch(p);
			p->dim = selected->dim;

		}

		root = OS_DELETE(root, selected, 3);

		prettyPrint(root, 0);

	}

}



int main()
{
	demo1();
	generatecases1();

}