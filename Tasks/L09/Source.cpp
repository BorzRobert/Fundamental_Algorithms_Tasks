/*Borz Robert-Ionut Group 30424
* The algorithm below implements efficiently the base operations for disjoint sets and the Kruskal's Algorithm
* 
The base operations for disjoint sets:
* MAKE_SET(int key)->allocates a node, sets its characteristics and returns the newly created node.
* FIND_SET(TNode* x)->returns the representative of the set that x is included in.
* UNION(TNode* x, TNode* y)->creates a bigger set containing all the elements from the 2 disjoint sets, it follows a
* union by rank approach(we try to avoid unbalancing the tree more than is needed).
*  
KRUSKAL's Alg:
* Follows a Greedy approach. We take as input a set of edges, we sort them(ascending) efficiently using HeapSort(from L03)
* and then we itterate through the set of edges and we check if our edge doesn't close a cycle. If it doesn't close a cycle
* it will be part of our MST. The itteration will stop when the MST will be copmplete.
*/
#include <iostream>
#include "Profiler.h"

#define MAX_EDGES 35000
#define MAX_VERTICES 10000
#define MAX_SIZE 8700
#define STEP_SIZE 100

using namespace std;

Profiler p("L09");

struct TNode//our node structure
{
	int key;
	int rank;
	TNode* parent;
};

struct edge {//struct used in order to help us to store all information needed for an weighted edge

	int weight;
	int source;
	int destination;

};

void Heapify(edge v[MAX_EDGES], int n, int i, int test_size)
{//function taken from L03
	Operation opCompHeapify1 = p.createOperation("CompHeapify1", test_size);
	Operation opAtrHeapify1 = p.createOperation("AtrHeapify1", test_size);

	int biggest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < n && v[left].weight > v[biggest].weight)
	{
		biggest = left;
	}
	if (left < n)
	{
		opCompHeapify1.count();
	}
	if (right < n && v[right].weight > v[biggest].weight)
	{
		biggest = right;
	}
	if (right < n)
	{
		opCompHeapify1.count();
	}
	if (biggest != i)
	{
		swap(v[i], v[biggest]);
		opAtrHeapify1.count(3);
		Heapify(v, n, biggest, test_size);//Recursevly heapify the affected part of the "sub-tree"

	}
}

void BuildHeapBottomUp(edge v[MAX_EDGES], int n, int test_size)
{//function taken from L03

	int startIndex = (n / 2) - 1;// Index of last non-leaf node
	for (int i = startIndex; i >= 0; i--)
	{
		Heapify(v, n, i, test_size);
	}

}

void HeapSort(edge v[MAX_EDGES], int n, int test_size)
{//function taken from L03
	Operation operation = p.createOperation("Operation_ext", test_size);
	BuildHeapBottomUp(v, n, test_size);
	for (int i = n - 1; i >= 1; i--)
	{
		operation.count(3);
		swap(v[0], v[i]);
		n--;
		Heapify(v, n, 0, test_size);
	}
}

TNode* MAKE_SET(int key, int size)
{//we allocate a node of type TNode* and we set its characteristics
	Operation opMake = p.createOperation("opMake", size);
	TNode* node = (TNode*)malloc(sizeof(TNode));
	node->key = key;
	node->rank = 0;
	node->parent = node;
	opMake.count(2);

	return node;
}

TNode* FIND_SET(TNode* x, int size)
{
	Operation opFind = p.createOperation("opFind", size);
	TNode* node;
	TNode* node_compresion;
	TNode* aux;

	node = x;
	node_compresion = x;

	while (node->parent != node)
	{
		opFind.count(2);//if we enter the while we count the comparison+assignation
		node = node->parent;//node will point to the root(the representative of the disjoint set)
	}
	if (node->parent == node)
		opFind.count();//if it doesn't enter the while we must count the comparison

	while (node_compresion->parent != node_compresion)
	{
		aux = node_compresion;
		node_compresion->parent = node;//we assure the path compresion tehnique
		node_compresion = aux->parent;
		opFind.count(4);//if we enter the while we count the comparison+assignation

	}
	if (node_compresion->parent == node_compresion)
		opFind.count();//if it doesn't enter the while we must count the comparison

	return node;
}

void UNION(TNode* x, TNode* y, int size)
{
	Operation opUnion = p.createOperation("opUnion", size);
	TNode* x1;
	TNode* y1;

	x1 = FIND_SET(x, size);
	y1 = FIND_SET(y, size);
	//we analyze 3 possible cases
	opUnion.count();
	//1:tree 1 height>tree 2 height
	if (x1->rank > y1->rank)
	{
		y1->parent = x1;
		opUnion.count();
	}
	opUnion.count();
	//2:tree 1 height<tree 2 height
	if (x1->rank < y1->rank)
	{
		x1->parent = y1;
		opUnion.count();
	}
	opUnion.count();
	//3:tree 1 height=tree 2 height
	if (x1->rank == y1->rank)
	{
		y1->parent = x1;
		x1->rank++;
		opUnion.count();
	}
}

void KRUSKAL(edge x[MAX_EDGES], int nr_of_edges, int nr_of_nodes, edge MST_edges[MAX_EDGES], int& index)
{
	TNode* vertices[MAX_VERTICES];
	index = 0;

	for (int i = 0; i < nr_of_nodes; i++)//foreach vertex in our graph we make an individual disjoint set
		vertices[i] = MAKE_SET(i, nr_of_nodes);

	HeapSort(x, nr_of_nodes, nr_of_nodes);//we sort efficiently our edges(ascending by weight)

	for (int i = 0; i < nr_of_edges; i++)
	{
		if (index == nr_of_nodes - 1)//in case we already obtained the MST we don't have to check the remaining edges
			break;

		if (FIND_SET(vertices[x[i].source], nr_of_nodes) != FIND_SET(vertices[x[i].destination], nr_of_nodes))
		{
			MST_edges[index] = x[i];//we place our edge in MST edges array
			index++;
			UNION(vertices[x[i].source], vertices[x[i].destination], nr_of_nodes);

		}

	}

}


void demo1()
{
	TNode* set1;
	TNode* set2;
	TNode* set3;
	TNode* set4;
	TNode* set5;
	TNode* set6;
	TNode* set7;
	TNode* set8;
	TNode* aux;

	set1 = MAKE_SET(1, 8);
	set2 = MAKE_SET(2, 8);
	set3 = MAKE_SET(3, 8);
	set4 = MAKE_SET(4, 8);
	set5 = MAKE_SET(5, 8);
	set6 = MAKE_SET(6, 8);
	set7 = MAKE_SET(7, 8);
	set8 = MAKE_SET(8, 8);

	UNION(set1, set2, 8);
	UNION(set2, set3, 8);
	UNION(set3, set4, 8);
	/*
			> 1 <
		 /     /  \
	   4	  2    3
	*/
	UNION(set5, set6, 8);
	UNION(set6, set7, 8);
	UNION(set7, set8, 8);
	/*
			> 5 <
		 /     /  \
	   6	  7    8
	*/
	UNION(set1, set8, 8);
	/*

				- > 1    <
			   / /     /  \
			  / 4	    2    3
			> 5 <
		 /     /  \
	   6	  7    8
	*/
	aux = FIND_SET(set6, 8);
	aux = FIND_SET(set7, 8);
	aux = FIND_SET(set8, 8);
	/*

		   ----->1<-----
		   | | | | | | |
		   | | | | | | |
		   2 3 4 5 6 7 8

	*/
}

void demo2()
{
	TNode* vertices[MAX_VERTICES];
	int index;

	edge a[MAX_EDGES], b[MAX_EDGES];
	int size = 14;
	int nodes = 9;

	a[0] = { 4,0,1 };
	a[1] = { 11,1,7 };
	a[2] = { 8,2,7 };
	a[3] = { 7,7,8 };
	a[4] = { 1,6,7 };
	a[5] = { 6,6,8 };
	a[6] = { 2,2,8 };
	a[7] = { 8,1,2 };
	a[8] = { 2,5,6 };
	a[9] = { 4,2,5 };
	a[10] = { 7,2,3 };
	a[11] = { 9,3,4 };
	a[12] = { 10,4,5 };
	a[13] = { 14,3,5 };


	KRUSKAL(a, size, nodes, b, index);
	cout << "The vertices contained in the MST after aplying Kruskal are the following:" << endl;
	for (int i = 0; i < index; i++)
		cout << b[i].source << " " << b[i].destination << endl;
}

void generatecases()
{
	edge a[MAX_EDGES],MST_edges[MAX_EDGES];
	int index;

	for (int i = STEP_SIZE; i <= MAX_SIZE; i = i + STEP_SIZE)
	{
		for (int j = 0; j < i - 1; j++)
		{

			int random = (rand() % (100 - 1 + 1)) + 1;//generate random numbers [1,100]

			a[j].source = j;
			a[j].destination = j + 1;

		}
		a[i - 1].source = i - 1;
		a[i - 1].destination = 0;
		//until here we have i edges
		
		int l = i;
		
		//for (int j = 0; j < l; j++)
			//cout << a[j].source << " " << a[j].destination << endl;

		for (int j = 0; j < i - 2; j++)
		{
			
			for (int t = j + 2; t < i; t++)
			{
				if (l >= 4 * i)
					goto exit;


				int random = (rand() % (100 - 1 + 1)) + 1;//generate random numbers [1,100]

				a[l].source = j;
				a[l].destination = t;
				a[l].weight = random;
				l++;
			}
		}
exit:
	
		KRUSKAL(a, 4 * i, i, MST_edges, index);
	}
	/*p.addSeries("Total1", "CompHeapify1", "AtrHeapify1");
	p.addSeries("Total2", "Total1", "Operation_ext");
	p.addSeries("Total3", "Total2", "opMake");
	p.addSeries("Total4", "Total3", "opFind");
	p.addSeries("Total", "Total4", "opUnion");
	*/
	p.addSeries("Total1", "opMake", "opFind");
	p.addSeries("Total", "Total1", "opUnion");
	p.showReport();
	
}



int main()
{
	demo1();
	demo2();
	//generatecases();
}