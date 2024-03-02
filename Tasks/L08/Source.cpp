/*Borz Robert-Ionut Group 30424
* PART I:
* The first part implements the inorder traversal of an already built binary tree(built using BUILD_TREE function) in 2 different ways:
* by using reccursion and by not using reccursion + using a stack(FIFO principle). The reccursive implementation has already been
* discused. The itterative implementation uses a stack, starts from the root, visits its left subtree and prints(for the demo) the 
* nodes in an inorder manner continuing with the right subtree.
* 
* PART II:
* The second part implements QuickSortHybrid(the hybridisation is achieved using itterative InsertionSort from Lab01). The hybridisation
* is based on a threshold(30 for the demo and variable in order to find the best value for an input of 10000 numbers). For a certain size
* previously chosen(threshold) and less, we will use InsertionSort and from values greater or equal we will use QuickSort from Lab03. The
* implementation with further explanations can be seen in QuickSorthybrid.
*/
#include <iostream>
#include "Profiler.h"
#include <stack>

#define MAX_ARRAY_SIZE 10000
#define MAX_SIZE 10000
#define STEP_SIZE 100
#define THRES_HOLD 30

using namespace std;

Profiler p("L08");

typedef struct TNode//our node structure
{
	int key;
	TNode* left;
	TNode* right;
};

TNode* newNode(int key)//creating a new node
{
	TNode* node = (TNode*)malloc(sizeof(TNode));
	node->key = key;
	node->left = NULL;
	node->right = NULL;

	return node;
}

TNode* BUILD_TREE(int v[MAX_ARRAY_SIZE], int start, int end, int size)
{
	Operation opCreate = p.createOperation("opCreate", size);

	if (start > end) //stop condition
		return NULL;

	int random = rand() % (end - start + 1) + start; //pick a random number between start and end

	opCreate.count();
	TNode* root = newNode(v[random]);

	opCreate.count(2);
	root->left = BUILD_TREE(v, start, random - 1, size);// we apply a D&C strategy by dividing the array in half    
	root->right = BUILD_TREE(v, random + 1, end, size);//recursevly until reaching ending condition

	return root;
}

void printArray(int v[MAX_ARRAY_SIZE], int n)
{
	for (int i = 0; i < n; i++)
		cout << v[i] << " ";
}

void copyArray(int v[MAX_ARRAY_SIZE], int v1[MAX_ARRAY_SIZE], int n)
{
	for (int i = 0; i < n; i++)
		v1[i] = v[i];
}

void inorder_rec(TNode* root, int size)
{
	Operation opInRec = p.createOperation("opInRec", size);

	if (root == NULL)
		return;

	else
	{
		inorder_rec(root->left, size);//recursion on left branch
		opInRec.count();
		//cout << root->key << " ";
		inorder_rec(root->right, size);//recursion on the right branch
	}
	

}

void inorder_rec_demo(TNode* root, int size)
{//used just for demo purposes, identical with inorder_rec+printing the node 
	Operation opInRec = p.createOperation("opInRec", size);

	if (root == NULL)
		return;

	else
	{
		inorder_rec_demo(root->left, size);
		opInRec.count();
		cout << root->key << " ";
		inorder_rec_demo(root->right, size);
	}


}

void inorder_itt(TNode* root, int size)
{
	Operation opInItt = p.createOperation("opInItt", size);
	
	stack<TNode*> stack;
	TNode* current=root;

	while (current != NULL || stack.empty() == false)
	{
		//reach the left most node of the current Node
		while (current != NULL)
		{
			stack.push(current);
			current = current->left;
		}

		//current will be NULL at this point
		current = stack.top();
		stack.pop();

		//cout << current->key << " ";
		opInItt.count();
		//we have visited the node and the node's left subtree, all that remainde is the right subtree
		current = current->right;

	}
}

void inorder_itt_demo(TNode* root, int size)
{//used just for demo purposes, identical with inorder_itt+printing the node 
	Operation opInItt = p.createOperation("opInItt", size);

	stack<TNode*> stack;
	TNode* current = root;

	while (current != NULL || stack.empty() == false)
	{

		while (current != NULL)
		{
			stack.push(current);
			current = current->left;
		}


		current = stack.top();
		stack.pop();

		cout << current->key << " ";
		opInItt.count();

		current = current->right;

	}
}

void InsertionSort(int v[MAX_ARRAY_SIZE], int n,int size)
{//explained in Lab01
	Operation opInsertion = p.createOperation("opInsertion", size);
	

	int i, aux, j;
	for (i = 1; i < n; i++)
	{
		aux = v[i];
		opInsertion.count();
		j = i - 1;

		while (j >= 0 && v[j] > aux)
		{
			opInsertion.count();
			v[j + 1] = v[j];
			opInsertion.count();
			j--;
		}
		opInsertion.count(); //for the case when j!=0;
		if (j + 1 != i)
		{
			v[j + 1] = aux;
			opInsertion.count();
		}

	}

}

int partition1(int v[MAX_ARRAY_SIZE], int low, int high, int size)
{
	Operation operation1 = p.createOperation("QuickSort1", size);

	int pivot = v[high];
	int i = low - 1;
	for (int j = low; j < high; j++) {
		if (v[j] <= pivot)
		{
			i++;
			swap(v[i], v[j]);
			operation1.count(3);
		}
	}
	swap(v[i + 1], v[high]);
	operation1.count(3);

	return i + 1;

}

int partition2(int v[MAX_ARRAY_SIZE], int low, int high, int size)
{
	Operation operation2 = p.createOperation("QuickSort2", size);

	int pivot = v[high];
	int i = low - 1;
	for (int j = low; j < high; j++) {
		if (v[j] <= pivot)
		{
			i++;
			swap(v[i], v[j]);
			operation2.count(3);
		}
	}
	swap(v[i + 1], v[high]);
	operation2.count(3);

	return i + 1;

}

void QuickSort(int v[MAX_ARRAY_SIZE], int start, int end, int size)
{//Explained in Lab03
	if (start < end)
	{
		int pivot = partition1(v, start, end, size);
		QuickSort(v, start, pivot - 1, size);
		QuickSort(v, pivot + 1, end, size);

	}
}

void QuickSortHybrid(int v[MAX_ARRAY_SIZE], int start, int end, int size, int thresHold)
{
	while (start < end)
	{
		if (end - start + 1 < thresHold)
		{//if the size of the array is <TRESH_HOLD apply
        //insertion sort and stop reccursion
			InsertionSort(v, end - start + 1,size);
			break;
		}
		else
		{
			//we choose the pivot 
			int pivot = partition2(v, start, end, size);

			//we analyse the smaller arrays first
			if (pivot - start < end - pivot)//left side is smaller
			{
				QuickSortHybrid(v, start, pivot - 1,size,thresHold);
				start = pivot + 1;
			}
			else//right side is smaller
			{
				QuickSortHybrid(v, pivot + 1, end, size,thresHold);
				end = pivot - 1;
			}
		}
	}
}

void generatecases1()
{
	int v[MAX_ARRAY_SIZE];
	TNode* root;

	for (int i = STEP_SIZE; i <= MAX_SIZE; i = i + STEP_SIZE)
	{
		FillRandomArray(v, i, 1, 10000, false, 0);
		root = BUILD_TREE(v, 0, i - 1, i);
		
		inorder_rec(root, i);
		inorder_itt(root, i);

	}
	p.createGroup("Itterative_vs_Reccursive", "opInItt", "opInRec");
	p.showReport();
}

void generatecases2()
{
	int v[MAX_ARRAY_SIZE], v1[MAX_ARRAY_SIZE];

	for (int i = STEP_SIZE; i <= MAX_SIZE; i = i + STEP_SIZE)
	{
		FillRandomArray(v, i, 0, 10000, false, 0);
		copyArray(v, v1, i);

		QuickSort(v, 0, i - 1, i);
		QuickSortHybrid(v1, 0, i - 1, i,THRES_HOLD);
	}
	p.addSeries("QuickSortHybrid", "QuickSort2", "opInsertion");
	p.createGroup("QS_vs_QSH", "QuickSortHybrid", "QuickSort1");

	p.showReport();
}

void generatecases3()
{
	int v[MAX_ARRAY_SIZE],v1[MAX_ARRAY_SIZE];

	FillRandomArray(v, MAX_SIZE, 0, 10000, false, 0);
	copyArray(v, v1, MAX_SIZE);

	for (int i = 10; i <= 500; i++)
	{
		QuickSortHybrid(v, 0, MAX_SIZE - 1, i, i);
		copyArray(v1, v, MAX_SIZE);
	}
	p.addSeries("TreshHold", "QuickSort2", "opInsertion");
	p.showReport();
}

void generatecases4()
{
	int v[MAX_ARRAY_SIZE];

	for (int i = STEP_SIZE; i <= MAX_SIZE; i = i + STEP_SIZE)
	{
		p.startTimer("QuickSortHybrid", i);
		for (int j = 0; j < 5; j++)
		{
			FillRandomArray(v, i, 0, 10000, false, 0);
			QuickSortHybrid(v, 0, i - 1, i, THRES_HOLD);
		}
		p.stopTimer("QuickSortHybrid", i);
		
	}

	for (int i = STEP_SIZE; i <= MAX_SIZE; i = i + STEP_SIZE)
	{
		p.startTimer("QuickSort", i);
		for (int j = 0; j < 5; j++)
		{
			FillRandomArray(v, i, 0, 10000, false, 0);
			QuickSort(v, 0, i - 1, i);
		}
		p.stopTimer("QuickSort", i);

	}

	p.divideValues("QuickSortHybrid", 5);
	p.divideValues("QuickSort", 5);
	p.createGroup("QS_hybrid_vs_QS","QuickSortHybrid","QuickSort");
	p.showReport();
}

void demo1()
{
	int v[10] = { 2,5,7,3,0,1,19,29,100,23 };
	int n = sizeof(v) / sizeof(v[0]);
	
	TNode* root = BUILD_TREE(v, 0, n - 1,n);
	cout << "* Inorder Tree traversal reccursive *" << endl;
	inorder_rec_demo(root, n);
	cout << endl;
	cout << "* Inorder Tree traversal itterative *" << endl;
	inorder_itt_demo(root, n);
}

void demo2()
{
	int v[10] = { 2,5,7,3,0,1,19,29,100,23 };
	int n = sizeof(v) / sizeof(v[0]);

	cout << "* The initial array is: ";
	printArray(v,n);
	cout << endl;
	cout << "* The sorted array sorted with QuickSortHybrid is: ";
	QuickSortHybrid(v, 0, n - 1, n,THRES_HOLD);
	printArray(v, n);

}

int main()
{
	generatecases1();
generatecases2();
	generatecases3();
	generatecases4();
	demo1();
	cout << endl;
	demo2();
}