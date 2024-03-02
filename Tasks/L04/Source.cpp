/*Borz Robert-Ionut 30424
* The function mergeKSortedLists returns a pointer to the head of the already merged list. The idea behind the algorithm
* uses some principles already presented in the last labs. We take k sorted lists and at each step we extract the smallest
* element from the head of each list(if the list isn't empty yet) and we insert it in the final merged list. We have to
* remember from which list did we extract the element in order to change the head of the list in that specific list.
* An efficient method of finding the minnimum element from the first elements of the lists is by using a MinHeap.
*
* As we can see in the graphs generated by function generatecases1() the number of operations increases as k increases.
* So larger the number of k random sorted lists, larger the number of operations.
*/
#include <iostream>
#include "Profiler.h"

#define STEP_SIZE 100
#define STEP_SIZE_SMALL 10
#define MAX_SIZE 10000
#define MAX_SIZE_SMALL 500
#define MAX_ARRAY_SIZE 10000

using namespace std;

Profiler p("L04");

// struct needed in order to store the list from which we have extracted the element
typedef struct Record {
	int key;
	int in_which_list;
};

#pragma region LinkedListsFunctions

typedef struct TNode {
	int key;
	int in_which_list;
	struct TNode* next;
}Node;

struct List {
	Node* head;
	Node* tail;
};

void print(Node* head)
{
	Node* p = head;
	while (p != NULL)
	{
		printf("%d ", p->key);
		p = p->next;
	}

}

void InsertLast(struct List* list, int key)
{
	Node* NewNode = (Node*)malloc(sizeof(Node));
	NewNode->key = key;
	NewNode->next = NULL;
	if (list->tail != NULL)
	{
		list->tail->next = NewNode;

	}
	else
	{
		list->head = NewNode;
	}


	list->tail = NewNode;

}

#pragma endregion

#pragma region BuildMinHeap
void Heapify(Record v[MAX_ARRAY_SIZE], int n, int i, int size)
{
	Operation opCompHeapify1 = p.createOperation("CompHeapify1", size);
	Operation opAtrHeapify1 = p.createOperation("AtrHeapify1", size);

	int smallest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < n && v[left].key < v[smallest].key)
	{
		smallest = left;
	}
	if (left < n)
	{
		opCompHeapify1.count();
	}
	if (right < n && v[right].key < v[smallest].key)
	{
		smallest = right;
	}
	if (right < n)
	{
		opCompHeapify1.count();
	}
	if (smallest != i)
	{
		swap(v[i], v[smallest]);
		opAtrHeapify1.count(3);
		Heapify(v, n, smallest, size);//Recursevly heapify the affected part of the "sub-tree"

	}
}

void BuildMinHeapBottomUp(Record v[MAX_ARRAY_SIZE], int n, int size)
{

	int startIndex = (n / 2) - 1;// Index of last non-leaf node 
	for (int i = startIndex; i >= 0; i--)
	{
		Heapify(v, n, i, size);
	}

}
#pragma endregion

struct TNode* mergeKSortedLists(List* lists[500], int k, int n, int problem_size)
{
	int size = 0;
	List* merged_list = (struct List*)malloc(sizeof(merged_list));
	merged_list->head = NULL;
	merged_list->tail = NULL;
	Record v1[MAX_SIZE_SMALL];

	for (int i = 0; i < n; i++)
	{
		size = 0;
		for (int j = 0; j < k; j++)
		{
			if (lists[j]->head != NULL)
			{
				v1[size].key = lists[j]->head->key;
				v1[size].in_which_list = j;
				size++;
			}

		}

		BuildMinHeapBottomUp(v1, size, problem_size);

		InsertLast(merged_list, v1[0].key);

		lists[v1[0].in_which_list]->head = lists[v1[0].in_which_list]->head->next;

	}
	return merged_list->head;
}


#pragma region Testing
void generatecases1()
{//as we have 3 fixed values for k and n starts from 100 ang goes up to 10000, we won't encounter the case when 
 //n%k!=0 
	TNode* merged_l = NULL;
	int k0 = 5, k1 = 10, k2 = 100, k, v[MAX_ARRAY_SIZE];

	struct List* lists[500];

	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
			k = k0;
		else if (i == 1)
			k = k1;
		else
			k = k2;

		for (int j = STEP_SIZE; j <= MAX_SIZE; j = j + STEP_SIZE)
		{

			for (int t = 0; t < k; t++)
			{
				FillRandomArray(v, j / k, 0, 10000, false, 1);
				lists[t] = (struct List*)malloc(sizeof(lists[t]));
				lists[t]->head = NULL;
				lists[t]->tail = NULL;

				for (int l = 0; l < j / k; l++)
				{
					InsertLast(lists[t], v[l]);

				}

			}
			merged_l = mergeKSortedLists(lists, k, j, j);

		}
		if (k == 5)
		{
			p.addSeries("MergeKSortedLists_k=5", "CompHeapify1", "AtrHeapify1");

		}
		else if (k == 10)
		{
			p.addSeries("MergeKSortedLists_k=10", "CompHeapify1", "AtrHeapify1");

		}
		else
		{
			p.addSeries("MergeKSortedLists_k=100", "CompHeapify1", "AtrHeapify1");

		}
	}

	p.createGroup("Comparison", "MergeKSortedLists_k=5", "MergeKSortedLists_k=10", "MergeKSortedLists_k=100");
	p.reset();


}

void generatecases2()
{/*In this case n is fixed(10000) and k is variable(10-500) with an increase of 10, so we can encounter the case
 when n%k!=0, so we have to do something in order not to lose elements. The idea is that we place in first k-1 lists
 int(n/k) elements and in the last list we place int(n/k)+remaining(nr_of_elements_in_last_list)
 */
	TNode* merged_l = NULL;
	int v[MAX_SIZE];
	int computed_number;
	int nr_of_elements_in_last_list;
	struct List* lists[500];

	for (int i = STEP_SIZE_SMALL; i <= MAX_SIZE_SMALL; i = i + STEP_SIZE_SMALL)
	{

		for (int t = 0; t < i; t++)
		{



			if (MAX_SIZE % i == 0)
			{
				FillRandomArray(v, MAX_SIZE / i, 0, MAX_SIZE, false, 1);
				lists[t] = (struct List*)malloc(sizeof(lists[t]));
				lists[t]->head = NULL;
				lists[t]->tail = NULL;

				for (int l = 0; l < MAX_SIZE / i; l++)
					InsertLast(lists[t], v[l]);

			}
			else
			{
				if (t != i - 1)
				{
					FillRandomArray(v, MAX_SIZE / i, 0, MAX_SIZE, false, 1);
					lists[t] = (struct List*)malloc(sizeof(lists[t]));
					lists[t]->head = NULL;
					lists[t]->tail = NULL;

					for (int l = 0; l < MAX_SIZE / i; l++)
						InsertLast(lists[t], v[l]);
				}
				else
				{
					computed_number = (MAX_SIZE / i);
					nr_of_elements_in_last_list = computed_number + MAX_SIZE - i * computed_number;
					FillRandomArray(v, nr_of_elements_in_last_list, 0, MAX_SIZE, false, 1);
					lists[t] = (struct List*)malloc(sizeof(lists[t]));
					lists[t]->head = NULL;
					lists[t]->tail = NULL;

					for (int l = 0; l < nr_of_elements_in_last_list; l++)
						InsertLast(lists[t], v[l]);


				}
			}
		}

		merged_l = mergeKSortedLists(lists, i, MAX_SIZE, i);

	}
	p.addSeries("MergeKSortedLists_k=variable", "CompHeapify1", "AtrHeapify1");
	p.showReport();
}
#pragma endregion

void demo()
{
	TNode* merged_list;
	List* lists[3];

	lists[0] = (struct List*)malloc(sizeof(lists[0]));
	lists[1] = (struct List*)malloc(sizeof(lists[1]));
	lists[2] = (struct List*)malloc(sizeof(lists[2]));

	lists[0]->head = NULL;
	lists[0]->tail = NULL;
	lists[1]->head = NULL;
	lists[1]->tail = NULL;
	lists[2]->head = NULL;
	lists[2]->tail = NULL;

	//Inserting in each lists the demo elelements as follows: lists[0]: 9 11 17 20, lists[1]: 0,3,5, lists[2]: 99 100 112
	InsertLast(lists[0], 9);
	InsertLast(lists[0], 11);
	InsertLast(lists[0], 17);
	InsertLast(lists[0], 20);

	InsertLast(lists[1], 0);
	InsertLast(lists[1], 3);
	InsertLast(lists[1], 5);

	InsertLast(lists[2], 99);
	InsertLast(lists[2], 100);
	InsertLast(lists[2], 112);

	cout << "list[0]=";
	print(lists[0]->head);
	cout << endl;
	cout << "list[1]=";
	print(lists[1]->head);
	cout << endl;
	cout << "list[2]=";
	print(lists[2]->head);
	cout << endl;


	merged_list = mergeKSortedLists(lists, 3, 10, 10);
	cout << "merged_list=";
	print(merged_list);
}


int main()
{
	//demo();
	//generatecases1();
	generatecases2();



}