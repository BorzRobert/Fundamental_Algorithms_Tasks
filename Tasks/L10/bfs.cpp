/*Borz Robert-Ionut 30424
* The code written by me is lead by the TODO sections of the requested functions:
*   get_neighbors:->The idea of the algorithm is that we check each possible neighbor to see if it is valid(valid means it
   is not a wall and it is on the grid).
*   bfs:->The idea of the implementation is that we use a queue in order to keep track of our nodes and their status. The
   nodes in the queue are GRAY(under visitation,they were white before being in the queue) and they will become BLACK after
   we finish our traversal(we also set the distance from the source for each node).
*   print_bfs_tree:->The idea of the implementation is identical with the one in L06, the only additional thing that we get
	is a repr array, in order to print the position of the node on the grid.
	performance:->As you can see in bfs() function we already count the number of operations, so performance just generates
	test samples for bfs function in the two following manners: 1)constant nr. of node and variable nr. of edges
																2)constant number of edges and variable number of nodes
*   The obtained graphs are the expected ones, showing a linear effort(because it is a traversal).
*   shortest_path:->The idea of the implementation is that we use the bfs algorithm in order to check if we can reach the
    destination node, if we can we will reconstruct the path from de destination to the source and reverse the order in 
	order to obtain the in betwwen nodes between source and destination and we will put them in the path array.
*
*/
#include <stdlib.h>
#include <string.h>
#include "bfs.h"

int get_neighbors(const Grid* grid, Point p, Point neighb[])
{
	// TODO: fill the array neighb with the neighbors of the point p and return the number of neighbors
	// the point p will have at most 4 neighbors (up, down, left, right)
	// avoid the neighbors that are outside the grid limits or fall into a wall
	// note: the size of the array neighb is guaranteed to be at least 4

	int index = 0;
	//we will check each possible neighbor position
	if (grid->mat[p.row + 1][p.col] == 0 && (p.row + 1) <= grid->rows - 1)//right neighbor
	{
		neighb[index].col = p.col;
		neighb[index].row = p.row + 1;
		index++;
	}
	if (grid->mat[p.row - 1][p.col] == 0 && (p.row - 1) >= 0)//left neighbor
	{
		neighb[index].col = p.col;
		neighb[index].row = p.row - 1;
		index++;
	}
	if (grid->mat[p.row][p.col - 1] == 0 && (p.col - 1) >= 0)//up neighbor
	{
		neighb[index].col = p.col - 1;
		neighb[index].row = p.row;
		index++;
	}
	if (grid->mat[p.row][p.col + 1] == 0 && (p.col + 1) <= grid->cols - 1)//down neighbor
	{
		neighb[index].col = p.col + 1;
		neighb[index].row = p.row;
		index++;
	}

	return index;
}

void grid_to_graph(const Grid* grid, Graph* graph)
{
	//we need to keep the nodes in a matrix, so we can easily refer to a position in the grid
	Node* nodes[MAX_ROWS][MAX_COLS];
	int i, j, k;
	Point neighb[4];

	//compute how many nodes we have and allocate each node
	graph->nrNodes = 0;
	for (i = 0; i < grid->rows; ++i) {
		for (j = 0; j < grid->cols; ++j) {
			if (grid->mat[i][j] == 0) {
				nodes[i][j] = (Node*)malloc(sizeof(Node));
				memset(nodes[i][j], 0, sizeof(Node)); //initialize all fields with 0/NULL
				nodes[i][j]->position.row = i;
				nodes[i][j]->position.col = j;
				++graph->nrNodes;
			}
			else {
				nodes[i][j] = NULL;
			}
		}
	}
	graph->v = (Node**)malloc(graph->nrNodes * sizeof(Node*));
	k = 0;
	for (i = 0; i < grid->rows; ++i) {
		for (j = 0; j < grid->cols; ++j) {
			if (nodes[i][j] != NULL) {
				graph->v[k++] = nodes[i][j];
			}
		}
	}

	//compute the adjacency list for each node
	for (i = 0; i < graph->nrNodes; ++i) {
		graph->v[i]->adjSize = get_neighbors(grid, graph->v[i]->position, neighb);
		if (graph->v[i]->adjSize != 0) {
			graph->v[i]->adj = (Node**)malloc(graph->v[i]->adjSize * sizeof(Node*));
			k = 0;
			for (j = 0; j < graph->v[i]->adjSize; ++j) {
				if (neighb[j].row >= 0 && neighb[j].row < grid->rows &&
					neighb[j].col >= 0 && neighb[j].col < grid->cols &&
					grid->mat[neighb[j].row][neighb[j].col] == 0) {
					graph->v[i]->adj[k++] = nodes[neighb[j].row][neighb[j].col];
				}
			}
			if (k < graph->v[i]->adjSize) {
				//get_neighbors returned some invalid neighbors
				graph->v[i]->adjSize = k;
				graph->v[i]->adj = (Node**)realloc(graph->v[i]->adj, k * sizeof(Node*));
			}
		}
	}
}

void free_graph(Graph* graph)
{
	if (graph->v != NULL) {
		for (int i = 0; i < graph->nrNodes; ++i) {
			if (graph->v[i] != NULL) {
				if (graph->v[i]->adj != NULL) {
					free(graph->v[i]->adj);
					graph->v[i]->adj = NULL;
				}
				graph->v[i]->adjSize = 0;
				free(graph->v[i]);
				graph->v[i] = NULL;
			}
		}
		free(graph->v);
		graph->v = NULL;
	}
	graph->nrNodes = 0;
}

void bfs(Graph* graph, Node* s, Operation* op)
{
	// TOOD: implement the BFS algorithm on the graph, starting from the node s
	// at the end of the algorithm, every node reachable from s should have the color BLACK
	// for all the visited nodes, the minimum distance from s (dist) and the parent in the BFS tree should be set
	// for counting the number of operations, the optional op parameter is received
	// since op can be NULL (when we are calling the bfs for display purposes), you should check it before counting:
	// if(op != NULL) op->count();

	s->color = COLOR_GRAY;//the distance and parent are already set to 0, respectively NULL
	Node* aux;
	Node* queue[10000];//we build a queue that is capabale of holding Node*
	int start = 0;//initially the queue is empty
	int end = 0;
	queue[start] = s;//we add the "root" in the queue
	if (op != NULL)
		op->count();
	end++;
	if (op != NULL)
		op->count();//count the comparison(condition of while)
	while (start != end)
	{
		aux = queue[end - 1];
		if (op != NULL)
			op->count();
		end--;
		for (int j = 0; j < aux->adjSize; j++)
		{
			if (op != NULL)
				op->count();
			if (aux->adj[j]->color == COLOR_WHITE)
			{
				aux->adj[j]->color = COLOR_GRAY;//under visitation color
				aux->adj[j]->dist = aux->dist + 1;
				aux->adj[j]->parent = aux;
				for (int i = end; i > start; i--)//we shift elements to be able to enque
				{
					queue[i] = queue[i - 1];
				}
				queue[start] = aux->adj[j];
				end++;
				if (op != NULL)
					op->count(3);

			}
		}
		aux->color = COLOR_BLACK;//after we finished with a node, we make in black

	}
}

void prettyPrint(int* p, int n, int parent, int level, Point* repr)//reccursive function for pretty print(from L06)
{//the thing that differs in comparison with L06 implementation is that we print the node representation not its index
	for (int i = 0; i < n; i++)
	{
		if (p[i] == parent)
		{
			for (int j = 0; j < level; j++)//we indent by 7
			{
				printf(" ");
			}
			printf("(%i, %i)\n", repr[i].row, repr[i].col);//
			prettyPrint(p, n, i, level + 7, repr);
		}
	}
}

void print_bfs_tree(Graph* graph)
{
	//first, we will represent the BFS tree as a parent array
	int n = 0; //the number of nodes
	int* p = NULL; //the parent array
	Point* repr = NULL; //the representation for each element in p

	//some of the nodes in graph->v may not have been reached by BFS
	//p and repr will contain only the reachable nodes
	int* transf = (int*)malloc(graph->nrNodes * sizeof(int));
	for (int i = 0; i < graph->nrNodes; ++i) {
		if (graph->v[i]->color == COLOR_BLACK) {
			transf[i] = n;
			++n;
		}
		else {
			transf[i] = -1;
		}
	}
	if (n == 0) {
		//no BFS tree
		free(transf);
		return;
	}

	int err = 0;
	p = (int*)malloc(n * sizeof(int));
	repr = (Point*)malloc(n * sizeof(Node));
	for (int i = 0; i < graph->nrNodes && !err; ++i) {
		if (graph->v[i]->color == COLOR_BLACK) {
			if (transf[i] < 0 || transf[i] >= n) {
				err = 1;
			}
			else {
				repr[transf[i]] = graph->v[i]->position;
				if (graph->v[i]->parent == NULL) {
					p[transf[i]] = -1;
				}
				else {
					err = 1;
					for (int j = 0; j < graph->nrNodes; ++j) {
						if (graph->v[i]->parent == graph->v[j]) {
							if (transf[j] >= 0 && transf[j] < n) {
								p[transf[i]] = transf[j];
								err = 0;
							}
							break;
						}
					}
				}
			}
		}
	}
	free(transf);
	transf = NULL;

	if (!err) {
		// TODO: pretty print the BFS tree
		// the parrent array is p (p[k] is the parent for node k or -1 if k is the root)
		// when printing the node k, print repr[k] (it contains the row and column for that point)
		// you can adapt the code for transforming and printing multi-way trees from the previous labs
		prettyPrint(p, n, -1, 0, repr);
	}

	if (p != NULL) {
		free(p);
		p = NULL;
	}
	if (repr != NULL) {
		free(repr);
		repr = NULL;
	}
}

int shortest_path(Graph* graph, Node* start, Node* end, Node* path[])
{
	// TODO: compute the shortest path between the nodes start and end in the given graph
	// the nodes from the path, should be filled, in order, in the array path
	// the number of nodes filled in the path array should be returned
	// if end is not reachable from start, return -1
	// note: the size of the array path is guaranteed to be at least 1000
	Node* path_aux[1000];//auxiliary array of Node* in order to invert the initially obtained result
	Node* aux;//aux variable to traverse backwards from end to start
	int index = 0,t=0;
	bfs(graph, start, NULL);//we apply bfs to set the parents and to color the nodes
	aux = end->parent;
	if (end->color != COLOR_BLACK)//if the node hasn't been reached by bfs->there is no path between start and end
	{
		return -1;
	}
	else
	{
		while (aux != start)//we go from end to start and store the nodes in between
		{
			path_aux[index] = aux;
			index++;
			aux = aux->parent;
			

		}
		for (int j = index - 1; j >= 0; j--)//we reverse the order of the nodes, in order to obtained the nodes in between
		{                                   //from start to end
			path[t] = path_aux[j];
			t++;
		}
		return index;
	}
}

void performance()
{
	int n, i;
	Profiler p("bfs");

	// vary the number of edges
	for (n = 1000; n <= 4500; n += 100) {
		Operation op = p.createOperation("bfs-edges", n);
		Graph graph;
		graph.nrNodes = 100;
		//initialize the nodes of the graph
		graph.v = (Node**)malloc(graph.nrNodes * sizeof(Node*));
		for (i = 0; i < graph.nrNodes; ++i) {
			graph.v[i] = (Node*)malloc(sizeof(Node));
			memset(graph.v[i], 0, sizeof(Node));
			graph.v[i]->adj = new Node * [graph.nrNodes];//we have to initialize the array of neighbours too
		}
		// TODO: generate n random edges
		// make sure the generated graph is connected
		for (int i = 0; i < graph.nrNodes - 1; i++)
		{
			graph.v[i]->adj[graph.v[i]->adjSize] = graph.v[i + 1];
			graph.v[i]->adjSize++;
		}

		graph.v[graph.nrNodes - 1]->adj[0] = graph.v[0];
		//until here we have placed nrNodes edges-->we have to place (n-nrNodes) more edges
		int l = graph.nrNodes;
		for (int i = 0; i < graph.nrNodes - 1; i++)
		{
			for (int j = i + 2; j < graph.nrNodes; j++)
			{
				if (l >= n)
					goto exit;
				graph.v[i]->adj[graph.v[i]->adjSize] = graph.v[j];
				graph.v[i]->adjSize++;
				l++;

			}
		}
	exit:

		bfs(&graph, graph.v[0], &op);
		free_graph(&graph);
	}

	// vary the number of vertices
	for (n = 100; n <= 200; n += 10) {
		Operation op = p.createOperation("bfs-vertices", n);
		Graph graph;
		graph.nrNodes = n;
		//initialize the nodes of the graph
		graph.v = (Node**)malloc(graph.nrNodes * sizeof(Node*));
		for (i = 0; i < graph.nrNodes; ++i) {
			graph.v[i] = (Node*)malloc(sizeof(Node));
			memset(graph.v[i], 0, sizeof(Node));
			graph.v[i]->adj = new Node * [graph.nrNodes];//we have to initialize the array of neighbours too
		}

		// TODO: generate 4500 random edges
		// make sure the generated graph is connected
		for (int i = 0; i < graph.nrNodes - 1; i++)
		{
			graph.v[i]->adj[graph.v[i]->adjSize] = graph.v[i + 1];
			graph.v[i]->adjSize++;
		}

		graph.v[graph.nrNodes - 1]->adj[0] = graph.v[0];

		//until here we have placed nrNodes edges-->we have to place (4500-nrNodes) more edges
		int l = graph.nrNodes;
		for (int i = 0; i < graph.nrNodes - 1; i++)
		{
			for (int j = i + 2; j < graph.nrNodes; j++)
			{
				if (l >= 4500)
					goto exit1;
				graph.v[i]->adj[graph.v[i]->adjSize] = graph.v[j];
				graph.v[i]->adjSize++;
				l++;

			}
		}
	exit1:

		bfs(&graph, graph.v[0], &op);
		free_graph(&graph);
	}

	p.showReport();
}
