/*Borz Robert-Ionut Group 30424
*  DFS:-the algorithm is implemented in a recursive manner, we use an enum in order to keep track of the node's color. A node
*  that is unvisited should be white, a node that is under visitation should be gray and a node that has already been visited
*  should be black. In order for the algorithm to be able to perform on graphs that are not connected we use an additional
*  function that ensures that every connected component will be analysed by DFS.
*  TOPOLOGICAL_SORT:-the idea behind the algorithm is based on DFS, while testing the algorithm we make sure that our graph
* is a DAG(otherwise a topological sort won't exist). After performing DFS on the graph we sort efficiently our nodes by
* finish time and by doing this we obtain a topologocal order(which is not unique).
*  TRAJAN:-the idea behind the algorithm is to find the strongly connected components in a directed graph using only one DFS
* traversal. The implementation is the one presented in the course.
*  DFS Analysis:-The complexity of the algorithm is O(V+E), so the obtained graphs in the 2 required cases are linear as we
* have already expected.
*/
#include <iostream>
#include <stack>
#include "Profiler.h"

#define MAX_GRAPH_SIZE 1000
#define STEP_SIZE_EDGES 100
#define STEP_SIZE_VERTICES 10

using namespace std;

Profiler p("L11");
int index = 0;
int nrComponents = 0;

int _time = 0;
int connected_components = 0;

enum COLORS {//Enum for color representation
	WHITE, GRAY, BALCK
};

struct Node {//Node representation
	int key;
	COLORS color;
	int discovery;
	int finish;
	Node* next;
	Node* parent;
	//
	int index;
	int lowLink;
	bool onStack;
	int comp;
};

Node* _stack[MAX_GRAPH_SIZE];//Stack for TARJAN alg.
int stack_index = 0;

struct List {//List representation
	Node* head;
	Node* tail;
};

struct Graph {//Graph representation
	int size;
	List* v;
};

int minn(int a, int b)
{
	if (a <= b)
		return a;
	else
		return b;
}

void Heapify(Graph* graph, int n, int i, int test_size)
{

	int biggest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < n && graph->v[left].head->finish > graph->v[biggest].head->finish)
	{
		biggest = left;
	}

	if (right < n && graph->v[right].head->finish > graph->v[biggest].head->finish)
	{
		biggest = right;
	}

	if (biggest != i)
	{
		swap(graph->v[i].head, graph->v[biggest].head);
		Heapify(graph, n, biggest, test_size);//Recursevly heapify the affected part of the "sub-tree"
	}
}

void BuildHeapBottomUp(Graph* graph, int n, int test_size)
{

	int startIndex = (n / 2) - 1;// Index of last non-leaf node 
	for (int i = startIndex; i >= 0; i--)
	{
		Heapify(graph, n, i, test_size);
	}

}

void HeapSort(Graph* graph, int n, int test_size)//Taken from L03(Including Heapify and BuildHeapBottomUp)
{
	BuildHeapBottomUp(graph, n, test_size);
	for (int i = n - 1; i >= 1; i--)
	{
		swap(graph->v[0].head, graph->v[i].head);
		n--;
		Heapify(graph, n, 0, test_size);
	}
}

Node* newNode(int key)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->key = key;
	node->next = NULL;

	return node;
}

Graph* newGraph(int size)
{
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	graph->size = size;
	graph->v = (List*)malloc(size * sizeof(List));
	//we allocate memory for our graph and initialise it
	for (int i = 0; i < size; i++)
	{
		graph->v[i].head = newNode(i);
		graph->v[i].tail = graph->v[i].head;
		graph->v[i].head->color = WHITE;
		graph->v[i].head->parent = newNode(-1);
	}
	return graph;
}

void addEdgeDirected(Graph* graph, int source, int destination)
{//adding an edge means inserting a node in the list where the list head is the source(the edge is directed)
	Node* aux = newNode(destination);
	if (graph->v[source].head->next == NULL)
	{
		graph->v[source].head->next = aux;
	}
	else
	{
		graph->v[source].tail->next = aux;
	}
	graph->v[source].tail = aux;

}

void printList(Node* head)
{
	Node* aux = head;
	while (aux != NULL)
	{
		if (aux == head)
		{
			cout << aux->key << "->";
		}
		else
			cout << aux->key << " ";
		aux = aux->next;
	}
}

void printGraph(Graph* graph)
{
	for (int i = 0; i < graph->size; i++)
	{
		printList(graph->v[i].head);
		cout << endl;
	}
}

void prettyPrint(int* array, int size, int parent, int level)//Function taken from L10
{
	for (int i = 0; i < size; i++)
	{
		if (array[i] == parent)
		{
			for (int j = 0; j < level; j++)
				cout << " ";
			cout << i << endl;
			prettyPrint(array, size, i, level + 3);
		}
	}
}

void DFS_VISIT_NO_PRINT(Graph* graph, Node* u, int size)
{
	Operation op = p.createOperation("DFS_VISIT", size);
	Node* aux = u->next;
	op.count();
	_time = _time + 1;
	u->discovery = _time;
	u->color = GRAY;//nodes under visitation take the color GRAY
	//cout << u->key << " "; //here we don't print, we will print in DFS, and DFS_visit which are identical excepting
	if (aux == NULL)         //the fact that there the printing part is not commented(so we use these functions to avoid  
		op.count();          //printing unnecessary stuff while analysing performance)
	while (aux != NULL)
	{
		op.count(2);
		if (graph->v[aux->key].head->color == WHITE)
		{
			graph->v[aux->key].head->parent = u;
			op.count();
			DFS_VISIT_NO_PRINT(graph, graph->v[aux->key].head, size);

		}
		aux = aux->next;
		op.count();
	}
	u->color = BALCK;
	_time = _time + 1;
	u->finish = _time;
	//cout << u->key << "[d:" << u->discovery << " f:" << u->finish << "] "; //uncoment in order to display in reverse
																		 //order of traversal but with discovery and finish
}

void DFS_NO_PRINT(Graph* graph, int size)
{//This function is written in order for the algorith to be able to run on graphs which are not connected
//so we will obtain the DFS traversal on each connected component(we also keep track of the discovery,finish time and we 
//also count the number of connected components in a graph).
	Operation op1 = p.createOperation("DFS", size);
	_time = 0;
	connected_components = 0;
	for (int i = 0; i < graph->size; i++)
	{
		op1.count();
		if (graph->v[i].head->color == WHITE)
		{
			connected_components++;
			DFS_VISIT_NO_PRINT(graph, graph->v[i].head, size);
		}
	}
}

void DFS_VISIT(Graph* graph, Node* u)
{//IDENTICAL WITH DFS_VISIT_NO_PRINT(+printing section)
	Node* aux = u->next;
	_time = _time + 1;
	u->discovery = _time;
	u->color = GRAY;
	cout << u->key << " ";
	while (aux != NULL)
	{
		if (graph->v[aux->key].head->color == WHITE)
		{
			graph->v[aux->key].head->parent = u;
			DFS_VISIT(graph, graph->v[aux->key].head);

		}
		aux = aux->next;
	}
	u->color = BALCK;
	_time = _time + 1;
	u->finish = _time;
	//cout << u->key << "[d:" << u->discovery << " f:" << u->finish << "] "; //uncoment in order to display in reverse
																		 //order of traversal but with discovery and finish
}

void DFS(Graph* graph)
{// IDENTICAL WITH DFS_VISIT(+printing section)
	_time = 0;
	connected_components = 0;
	for (int i = 0; i < graph->size; i++)
	{
		if (graph->v[i].head->color == WHITE)
		{
			connected_components++;
			DFS_VISIT(graph, graph->v[i].head);
			cout << endl;
		}
	}
}

void TOPOLOGICAL_SORT(Graph* graph)
{//in demo_TS we already made sure that a topological sort exists(the graph is a DAG)
	cout << "*DFS traversal of the graph:" << endl;
	DFS(graph);//we call the DFS function in order to set the discovery and finish time of each node
	HeapSort(graph, graph->size, graph->size);//we sort efficiently by finish time(ascending)
	cout << "One possible topological sort of the nodes:" << endl;
	for (int i = graph->size - 1; i >= 0; i--)
		cout << graph->v[i].head->key << " ";//we print the nodes sorted previously in reverse order
	cout << endl;
}

void STRONG_CONNECT(Graph* graph, Node* u)
{
	u->index = index;
	u->lowLink = index;
	index++;
	_stack[stack_index] = u;
	stack_index++;
	u->onStack = true;
	Node* aux = u->next;
	while (aux != NULL)
	{
		if (graph->v[aux->key].head->index == -1)
		{
			STRONG_CONNECT(graph, graph->v[aux->key].head);
			u->lowLink = minn(u->lowLink, graph->v[aux->key].head->lowLink);
		}
		else if (graph->v[aux->key].head->onStack)
		{
			u->lowLink = minn(u->lowLink, graph->v[aux->key].head->index);
		}
		aux = aux->next;
	}
	if (u->lowLink == u->index)
	{
		nrComponents++;
		do
		{
			aux = _stack[stack_index - 1];
			stack_index--;
			aux->onStack = false;
			aux->comp = nrComponents;
		} while (aux != u);
	}
}

void TARJAN(Graph* graph)
{//The algorith is implemented as in the course
	index = 0;
	stack_index = 0;
	nrComponents = 0;
	for (int i = 0; i < graph->size; i++)
	{//Initialisation of the graph's nodes
		graph->v[i].head->index = -1;
		graph->v[i].head->lowLink = -1;
		graph->v[i].head->onStack = false;
		graph->v[i].head->comp = 0;
	}
	for (int i = 0; i < graph->size; i++)
	{
		if (graph->v[i].head->index == -1)
			STRONG_CONNECT(graph, graph->v[i].head);
	}
}

void generatecases1()
{
	for (int j = 1000; j <= 4500; j = j + STEP_SIZE_EDGES)
	{
		Graph* graph;
		graph = newGraph(100);
		for (int i = 0; i < graph->size - 1; i++)
			addEdgeDirected(graph, i, i + 1);
		addEdgeDirected(graph, graph->size - 1, 0);
		//until here we have placed graph->size edges, we have to place j-(graph->size) edges
		int l = graph->size;
		for (int i = 0; i < graph->size - 1; i++)
		{
			for (int k = i + 2; k < graph->size; k++)
			{
				if (l >= j)
					goto exit;
				addEdgeDirected(graph, i, k);
				l++;
			}
		}
	exit:
		DFS_NO_PRINT(graph, j);
	}
	p.addSeries("DFS_variable_nr_of_edges", "DFS", "DFS_VISIT");
	p.showReport();
}

void generatecases2()
{
	for (int j = 100; j <= 200; j = j + STEP_SIZE_VERTICES)
	{
		Graph* graph;
		graph = newGraph(j);
		for (int i = 0; i < graph->size - 1; i++)
			addEdgeDirected(graph, i, i + 1);
		addEdgeDirected(graph, graph->size - 1, 0);
		//until here we have placed graph->size edges, we have to place 4500-(graph->size) edges
		int l = graph->size;
		for (int i = 0; i < graph->size - 1; i++)
		{
			for (int k = i + 2; k < graph->size; k++)
			{
				if (l >= 4500)
					goto exit;
				addEdgeDirected(graph, i, k);
				l++;
			}
		}
	exit:
		DFS_NO_PRINT(graph, j);
	}
	p.addSeries("DFS_variable_nr_of_vertices", "DFS", "DFS_VISIT");
	p.showReport();
}

void demo_DFS()
{
	cout << "*DEMO DFS*" << endl;
	int index = 0;
	Graph* graph;
	graph = newGraph(6);
	int parent[6];
	addEdgeDirected(graph, 0, 1);
	addEdgeDirected(graph, 0, 3);
	addEdgeDirected(graph, 1, 2);
	addEdgeDirected(graph, 1, 1);
	addEdgeDirected(graph, 2, 3);
	addEdgeDirected(graph, 3, 1);
	addEdgeDirected(graph, 4, 3);
	addEdgeDirected(graph, 4, 5);
	addEdgeDirected(graph, 5, 5);

	cout << "*Graph represented with adjacency lists:" << endl;
	printGraph(graph);
	cout << "*DFS traversal of the graph:" << endl;
	DFS(graph);
	cout << "Number of connected components:";
	cout << connected_components;
	cout << endl;
	for (int i = 0; i < graph->size; i++)
		parent[i] = graph->v[i].head->parent->key;
	cout << endl;
	prettyPrint(parent, 6, -1, 0);
}

void demo_TS()
{
	cout << "*DEMO TOPOLOGICAL SORT*" << endl;
	int index = 0;
	Graph* graph;
	graph = newGraph(6);
	int parent[6];
	addEdgeDirected(graph, 2, 3);
	addEdgeDirected(graph, 3, 1);
	addEdgeDirected(graph, 4, 0);
	addEdgeDirected(graph, 4, 1);
	addEdgeDirected(graph, 5, 2);
	addEdgeDirected(graph, 5, 0);

	cout << "*Graph represented with adjacency lists:" << endl;
	printGraph(graph);
	TOPOLOGICAL_SORT(graph);
}

void demo_Tarjan()
{
	cout << "*DEMO TARJAN ALG" << endl;
	Graph* graph;
	graph = newGraph(8);
	addEdgeDirected(graph, 0, 2);
	addEdgeDirected(graph, 1, 0);
	addEdgeDirected(graph, 1, 3);
	addEdgeDirected(graph, 2, 1);
	addEdgeDirected(graph, 2, 3);
	addEdgeDirected(graph, 2, 4);
	addEdgeDirected(graph, 3, 5);
	addEdgeDirected(graph, 4, 5);
	addEdgeDirected(graph, 4, 6);
	addEdgeDirected(graph, 5, 3);
	addEdgeDirected(graph, 5, 7);
	addEdgeDirected(graph, 6, 4);
	addEdgeDirected(graph, 6, 7);
	cout << "*Graph represented with adjacency lists:" << endl;
	printGraph(graph);
	TARJAN(graph);
	cout << "nrComponents:" << nrComponents << "\nindex:" << index << endl;

	cout << "Strongly connected components of the graph:" << endl;
	for (int i = 1; i <= nrComponents; i++)
	{
		for (int j = 0; j < graph->size; j++)
		{
			if (graph->v[j].head->comp ==i )
				cout << graph->v[j].head->key << " ";
		}
		cout << endl;
	}
}

int main()
{
	demo_DFS();
	demo_TS();
	demo_Tarjan();
	//generatecases1();
	//generatecases2();
}