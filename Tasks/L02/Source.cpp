/*Borz Robert-Ionut 30424
*The 3 required algorithms to implement are the following:
* 
* BuilHeapBottomUp->The idea behind this algorithm is that we know from the beginning all the elements in the array from which we want to construct a heap
* (in place). So we choose the first place where it is possible to encounter values that are not where they belong(at the last non-leaf node) and we call Heapify 
* for each node starting from there up to the root. Heapify works in the following manner: it tries to add a new element to two existing sub-heaps and make a
* bigger one from the elements mentioned above.
* 
* BuildHeapTopDown->The idea behind this algorithm is that we don't know from the beggining all the elements that will be part of our final heap, so we have to
* take them one by one and insert them in the newly created heap. The insertion works by putting the element as the last leaf, and by applying heapify2 on the
* newly added element in order to buuble it up in the right place.
* 
* HeapSort->The idea behind the algorithm is that we start with a Max-Heap. After we have the Max-Heap created we do the following: take the root(which is also
* the maximum value in the array) and swap it with the last leaf, then decrease the size of the array for wich we will restore it's heap property. In this
* manner we sort in place, no additional space is required.
* 
* Charts interpretation: As we have already expected we can see that in the average case the method of building a Max(Min)
* Heap by using the BottomUp approach is more efficienct than buildin a Max(Min) Heap by using the TopDown approach(The
* combined graph(comp+atr) increases faster for the TopDown method than for the BottomUp method).
*/
#include <iostream>
#include "Profiler.h"

#define MAX_ARRAY_SIZE 10000
#define STEP_SIZE 100
#define MAX_SIZE 10000

Profiler p("L02");

using namespace std;

void PrintArray(int v[MAX_ARRAY_SIZE], int n)
{
	for (int i = 0; i < n; i++)
		cout << v[i] << " ";
}

void copyArray(int v[MAX_ARRAY_SIZE], int v1[MAX_ARRAY_SIZE], int n)
{
	for (int i = 0; i < n; i++)
		v1[i] = v[i];
}

void Heapify(int v[MAX_ARRAY_SIZE], int n, int i)
{
	Operation opCompHeapify1 = p.createOperation("CompHeapify1", n);
	Operation opAtrHeapify1 = p.createOperation("AtrHeapify1", n);

	int biggest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < n && v[left] > v[biggest])
	{
		biggest = left;
	}
	if (left < n)
	{
		opCompHeapify1.count();
	}
	if (right < n && v[right] > v[biggest])
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
		Heapify(v, n, biggest);//Recursevly heapify the affected part of the "sub-tree"

	}
}

void BuildHeapBottomUp(int v[MAX_ARRAY_SIZE], int n)
{

	int startIndex = (n / 2) - 1;// Index of last non-leaf node 
	for (int i = startIndex; i >= 0; i--)
	{
		Heapify(v, n, i);
	}

}

void heapify2(int v[MAX_ARRAY_SIZE], int n, int i, int size)
{
	Operation opCompHeapify2 = p.createOperation("CompHeapify2", size);
	Operation opAtrHeapify2 = p.createOperation("AtrHeapify2", size);

	int parent = (i - 1) / 2;// Find parent

	opCompHeapify2.count();
	if (v[parent] > 0)
	{
		opCompHeapify2.count();
		if (v[i] > v[parent])
		{
			opAtrHeapify2.count(3);
			swap(v[i], v[parent]);
			heapify2(v, n, parent, size);// Recursively heapify the parent node
		}
	}
}

void insertElement(int v[MAX_ARRAY_SIZE], int n, int key, int size)
{
	n = n + 1; //increase the size of the array

	v[n - 1] = key; //insert the element with the given keyu at the enf of the array
	heapify2(v, n, n - 1, size); //heapify the new node


}

void BuildHeapTopDown(int v[MAX_ARRAY_SIZE], int n, int v1[MAX_ARRAY_SIZE])
{
	int p = 0;
	for (int i = 0; i < n; i++)
	{
		insertElement(v1, p, v[i], n);
		p++;
	}
}

void HeapSort(int v[MAX_ARRAY_SIZE], int n)
{
	BuildHeapBottomUp(v, n);
	for (int i = n - 1; i >= 1; i--)
	{
		swap(v[0], v[i]);
		n--;
		Heapify(v, n, 0);
	}
}

void generatecases()
{
	int v[MAX_ARRAY_SIZE], v1[MAX_ARRAY_SIZE], v_aux[MAX_ARRAY_SIZE], k = 5, i, j;
	for (j = STEP_SIZE; j <= MAX_SIZE; j = j + STEP_SIZE)
	{
		for (i = 0; i < k; i++)
		{
			FillRandomArray(v, j, 0, 10000, 0, 0);
			copyArray(v, v1, j);
			BuildHeapBottomUp(v, j);
			BuildHeapTopDown(v1, j, v_aux);
		}
	}
	p.divideValues("CompHeapify1", 5);
	p.divideValues("AtrHeapify1", 5);

	p.divideValues("CompHeapify2", 5);
	p.divideValues("AtrHeapify2", 5);

	p.addSeries("Atr+CompHeapify1", "CompHeapify1", "AtrHeapify1");
	p.addSeries("Atr+CompHeapify2", "CompHeapify2", "AtrHeapify2");

	p.createGroup("Comp_Comparison", "CompHeapify1", "CompHeapify2");
	p.createGroup("Atr_Comparison", "AtrHeapify1", "AtrHeapify2");
	p.createGroup("AtrCompComparison", "Atr+CompHeapify1", "Atr+CompHeapify2");

	p.showReport();
}

void demo1() //exemplifies the corectness of BuildHeapBottomUp for a hard coded example
{
	int v[8] = { 2,7,9,1,3,2,10,4 };
	int n = sizeof(v) / sizeof(v[0]);
	BuildHeapBottomUp(v, n);
	cout << "The MaxHeap(BottomUp) seen as an array:";
	PrintArray(v, n);

}

void demo2() //exemplifies the corectness of HeapSort for a hard coded example
{
	int v[8] = { 2,7,9,1,3,2,10,4 };
	int n = sizeof(v) / sizeof(v[0]);
	HeapSort(v, n);
	cout << "The sorted array:";
	PrintArray(v, n);
}

void demo3() //exemplifies the corectness of BuildHeapTopDown for a hard coded example
{
	int v[9] = { 2,7,9,1,3,2,10,4,20 }, v1[9];
	int n = sizeof(v) / sizeof(v[0]);
	BuildHeapTopDown(v, n, v1);
	cout << "The MaxHeap(TopDown) seen as an array:";
	PrintArray(v1, n);
}
int main()
{
	demo1();
	cout << "\n";
	demo2();
	cout << "\n";
	demo3();
	generatecases();
}