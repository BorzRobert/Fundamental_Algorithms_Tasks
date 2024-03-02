/*Borz Robert-Ionut, Group 30424
 *The QSort algorithm presented below works as follows: We start with the whole array to be sorted and we try to find the
pivot position(the final position of the pivot for this step) and the pivot value. In the following steps we will
apply the same idea on the sub-arrays located on pivot's left and right side recursevly.
 *Comparing QSort with HeapSort by generating the graphs we can observe that HeapSort's graph increases faster than QS's
 graph, so it is less efficient.
 *I couldn't really compare QSort in the three cases(worst,best,average) because the computer couldn't handle such big
 input sizes for each case(but, analysing the obtained graphs we can cocnlude that there is a difference depending
 on the input format)
*/


#include <iostream>
#include "Profiler.h"

#define MAX_ARRAY_SIZE 10000
#define STEP_SIZE 100
#define MAX_SIZE 10000

#define STEP_SIZE_R 50
#define MAX_SIZE_R 2000


Profiler p("L03");

using namespace std;

void copyArray(int v[MAX_ARRAY_SIZE], int v1[MAX_ARRAY_SIZE], int size)
{
	for (int i = 0; i < size; i++)
		v1[i] = v[i];
}

void printArray(int v[MAX_ARRAY_SIZE], int n)
{
	for (int i = 0; i < n; i++)
		cout << v[i] << " ";
}

int partition(int v[MAX_ARRAY_SIZE], int low, int high, int size)
{
	Operation operation = p.createOperation("QuickSort", size);

	int pivot = v[high];
	int i = low - 1;
	for (int j = low; j < high; j++) {
		if (v[j] <= pivot)
		{
			i++;
			swap(v[i], v[j]);
			operation.count(3);
		}
	}
	swap(v[i + 1], v[high]);
	operation.count(3);

	return i + 1;

}

int partition1(int v[MAX_ARRAY_SIZE], int start, int end)
{
	int x = v[(start + end) / 2];
	int i = start;
	int j = end;
	do
	{
		while (v[i] < x)
			i++;
		while (v[j] > x)
			j--;
		if (i <= j)
		{
			swap(v[i], v[j]);
			i++;
			j--;
		}
	} while (j<i);
	
	return i;
}

int QuickSelect(int v[MAX_ARRAY_SIZE], int start, int end, int i)
{
	if (start == end)
		return v[start];
	int q = partition1(v, start, end);
	int k = q - start + 1;
	if (i == k)
		return v[end];
	else if (i < k)
		return QuickSelect(v, start, q - 1, i);
	else
		return QuickSelect(v, q + 1, end, i - k);

}

void QuickSort(int v[MAX_ARRAY_SIZE], int start, int end, int size)
{
	if (start < end)
	{
		int pivot = partition(v, start, end, size);
		QuickSort(v, start, pivot - 1, size);
		QuickSort(v, pivot + 1, end, size);

	}
}

void Heapify(int v[MAX_ARRAY_SIZE], int n, int i, int test_size)
{
	Operation opCompHeapify1 = p.createOperation("CompHeapify1", test_size);
	Operation opAtrHeapify1 = p.createOperation("AtrHeapify1", test_size);

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
		Heapify(v, n, biggest, test_size);//Recursevly heapify the affected part of the "sub-tree"

	}
}

void BuildHeapBottomUp(int v[MAX_ARRAY_SIZE], int n, int test_size)
{

	int startIndex = (n / 2) - 1;// Index of last non-leaf node 
	for (int i = startIndex; i >= 0; i--)
	{
		Heapify(v, n, i, test_size);
	}

}

void HeapSort(int v[MAX_ARRAY_SIZE], int n, int test_size)
{
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

void BubbleSort(int v[MAX_ARRAY_SIZE], int n)
{
	Operation opAtrBubble = p.createOperation("AtrBubble", n);
	Operation opCompBubble = p.createOperation("CompBubble", n);

	int i, j;
	bool isSorted = false; //flag in order to check if the array is already sorted
	for (i = 0; i < n - 1; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			opCompBubble.count();
			if (v[i] > v[j])
			{
				opAtrBubble.count(3);
				swap(v[i], v[j]);
				isSorted = true;
			}
		}
		opCompBubble.count();
		if (isSorted == false)
			break;
	}

}

void BubbleSortRec(int v[MAX_ARRAY_SIZE], int n, int size)
{
	Operation opAtrBubbleRec = p.createOperation("AtrBubbleRec", size);
	Operation opCompBubbleRec = p.createOperation("CompBubbleRec", size);

	if (n == 1)
		return;

	bool flag = false;

	for (int i = 0; i < n - 1; i++)
	{
		opCompBubbleRec.count();
		if (v[i] > v[i + 1])
		{
			opAtrBubbleRec.count(3);
			swap(v[i], v[i + 1]);//the maximum element bubbles at the end of the array
			flag = true;
		}
	}
	opCompBubbleRec.count();
	if (flag == false)//if the array is already sorted,no more recursive call needed
		return;

	BubbleSortRec(v, n - 1, size);
}

void generatecases()//Worst and best for QS
{
	
	int i, j, k = 5, v[MAX_ARRAY_SIZE], v1[MAX_ARRAY_SIZE];
	for (i = 0; i < k; i++)
	{
		for (j = STEP_SIZE_R; j <= MAX_SIZE_R; j = j + STEP_SIZE_R)
		{
			FillRandomArray(v, j, 0, 10000, false, 1);
			QuickSort(v, 0, j - 1, j);
			
		}
	}
	p.divideValues("QuickSortWorst", k);


	p.reset();
}

void QS_vs_HS()
{
	//Average case analysis
	int i, j, k = 5, v[MAX_ARRAY_SIZE], v1[MAX_ARRAY_SIZE];
	for (i = 0; i < k; i++)
	{
		for (j = STEP_SIZE; j <= MAX_SIZE; j = j + STEP_SIZE)
		{
			FillRandomArray(v, j, 0, 10000, false, 0);
			copyArray(v, v1, j);
			QuickSort(v, 0, j - 1, j);
			HeapSort(v1, j, j);
		}
	}
	p.divideValues("QuickSort", k);

	p.divideValues("CompHeapify1", k);
	p.divideValues("AtrHeapify1", k);

	p.divideValues("Operation_ext", k);

	p.addSeries("Atr+CompHeapify1", "CompHeapify1", "AtrHeapify1");
	p.addSeries("HeapSort", "Atr+CompHeapify1", "Operation_ext");

	p.createGroup("QSvsHS", "HeapSort", "QuickSort");



	p.reset();

}

void BubbleRec_vs_Bubble()
{
	int i, j, k = 5, v[MAX_ARRAY_SIZE], v1[MAX_ARRAY_SIZE];


	for (i = 0; i < k; i++)
	{
		for (j = STEP_SIZE_R; j <= MAX_SIZE_R; j = j + STEP_SIZE_R)
		{
			//p.startTimer("BubbleSort", j); //uncomment in order to obtain execution times
			FillRandomArray(v, j, 0, 10000, false, 0);
			copyArray(v, v1, j);
			BubbleSort(v, j);
			//p.stopTimer("BubbleSort", j);
			//p.startTimer("BubbleSortRec", j); //uncomment in order to obtain execution times(it is not possible to count operations and running time simultaneously)
			BubbleSortRec(v1, j, j);
			//p.stopTimer("BubbleSortRec", j);


		}
	}
	p.divideValues("AtrBubble", k);
	p.divideValues("CompBubble", k);
	p.addSeries("BubbleSort", "AtrBubble", "CompBubble");

	p.divideValues("AtrBubbleRec", k);
	p.divideValues("CompBubbleRec", k);
	p.addSeries("BubbleSortRec", "AtrBubbleRec", "CompBubbleRec");

	p.createGroup("Bubble_vs_BubbleRec", "BubbleSort", "BubbleSortRec");
	
	p.reset();

}

void demo()
{
	int v[8] = { 2,7,9,1,3,2,10,4 };
	int n = sizeof(v) / sizeof(v[0]);
	QuickSort(v, 0, n - 1, n);
	cout << "QuickSort:";
	printArray(v, n);
	cout << endl;
}

void demo1()
{
	int v[8] = { 2,7,9,1,3,2,10,4 };
	int n = sizeof(v) / sizeof(v[0]);
	int desiredElement = QuickSelect(v, 0, n - 1, 3);
	cout << "The third element of the array is:";
	cout << desiredElement;
}

int main()
{
	demo();
	demo1();
	QS_vs_HS();
	BubbleRec_vs_Bubble();
	generatecases();

}