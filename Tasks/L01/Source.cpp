/*Borz Robert-Ionut, Group 30424
* L01-Assignement
* The code below presents 3 direct sorting methods(BubbleSort,SelectionSort,InsertionSort)
* BubbleSort- The function BubbleSort takes an array of maximum MAX_SIZE elements and its size and sorts it ascending
* according to the following principle: each set of adjacent pairs are checked,from left ti right, and if the order is
* not the desired one(ascending in our case) the two elements are swapped. We also check if the array is already sorted
* after the first itteration in order to improve the efficiency.
* SelectionSort- The function SelectionSort takes an array of maximum MAX_SIZE elements and its size and sorts it ascending
* according to the following principle: We search in the unsorted array the minimum value and place it at the end of the
* sorted array only if it isn't already there(we avoid swapping it with itself)
* InsertionSort- The function InsertionSort takes an array of maximum MAX_SIZE elements and its size and sorts it ascending
* according to the following principle: We know that an 1 element array is always sorted, so we can start by analyzing
* the second element, and place it in the correct order according to the sub-array already sorted. This process is 
* repeteated until the desired sorted array.
*
* Charts interpretation: The Average case->In the average case according to the Atr chart we can draw the following
* conclusion: SS<IS<BS (BS graph is increasing the fastest, then IS and the SS), the same conclusion can be drawn in
* the other two cases(Worst,Best). According to the Comp chart we can draw the following conclusion: BS<IS<SS.
* The Comp in the Best and Worst case can be visualised in the charts present in project folder.
* According to the sum of the Comp and Atr operations we can draw the following conclusions:
* 1)In average IS<SS<BS (regarding the graph growth, IS graph increases the slowest)
* 2)In the best case the conclusion is the same
* 3)In worst case SS<IS<BS (regarding the graph growth, SS graph increases the slowest)
* The conclusions drawn above are true for the below implementation of the sorting algorithms.
*
*/

#include <iostream>
#include "Profiler.h"

#define ARRAY_MAX_SIZE 10000
#define MAX_SIZE 10000
#define STEP_SIZE 100

using namespace std;

Profiler p("L01");

void BubbleSort(int v[ARRAY_MAX_SIZE], int n)
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

void SelectionSort(int v[ARRAY_MAX_SIZE], int n)
{
	Operation opAtrSelection = p.createOperation("AtrSelection", n);
	Operation opCompSelection = p.createOperation("CompSelection", n);

	int i, j, minnimum_index;

	for (i = 0; i < n - 1; i++)
	{
		minnimum_index = i;
		for (j = i + 1; j < n; j++)
		{
			opCompSelection.count();
			if (v[j] < v[minnimum_index])
				minnimum_index = j;
		}

		if (minnimum_index != i)
		{
			swap(v[minnimum_index], v[i]);
			opAtrSelection.count(3);
		}

	}
}

void InsertionSort(int v[ARRAY_MAX_SIZE], int n)
{
	Operation opAtrInsertion = p.createOperation("AtrInsertion", n);
	Operation opCompInsertion = p.createOperation("CompInsertion", n);

	int i, aux, j;
	for (i = 1; i < n; i++)
	{
		aux = v[i];
		opAtrInsertion.count();
		j = i - 1;

		while (j >= 0 && v[j] > aux)
		{
			opCompInsertion.count();
			v[j + 1] = v[j];
			opAtrInsertion.count();
			j--;
		}
		opCompInsertion.count(); //for the case when j!=0;
		if (j + 1 != i)
		{
			v[j + 1] = aux;
			opAtrInsertion.count();
		}

	}


}

void copyArray(int v[ARRAY_MAX_SIZE], int v1[ARRAY_MAX_SIZE], int n)
{
	for (int i = 0; i < n; i++)
		v1[i] = v[i];
}

void generateCases1()//average case
{
	int v[ARRAY_MAX_SIZE], v1[ARRAY_MAX_SIZE], k = 5;
	for (int j = 0; j < k; j++)
	{
		for (int i = STEP_SIZE; i <= MAX_SIZE; i = i + STEP_SIZE)
		{
			FillRandomArray(v, i, 0, 10000, false, 0);
			copyArray(v, v1, i);

			BubbleSort(v, i);
			p.addSeries("Atr+CompBubble", "AtrBubble", "CompBubble");

			copyArray(v1, v, i);
			SelectionSort(v1, i);
			p.addSeries("Atr+CompSelection", "AtrSelection", "CompSelection");

			InsertionSort(v, i);
			p.addSeries("Atr+CompInsertion", "AtrInsertion", "CompInsertion");


		}
	}
	p.divideValues("Atr+CompBubble", 5);
	p.divideValues("AtrBubble", 5);
	p.divideValues("CompBubble", 5);

	p.divideValues("Atr+CompSelection", 5);
	p.divideValues("AtrSelection", 5);
	p.divideValues("CompSelection", 5);

	p.divideValues("Atr+CompInsertion", 5);
	p.divideValues("AtrInsertion", 5);
	p.divideValues("CompInsertion", 5);

	p.createGroup("SortingAlgsInAverage", "Atr+CompBubble", "Atr+CompSelection", "Atr+CompInsertion");
	p.createGroup("CompAlgsInAverage", "CompBubble", "CompSelection", "CompInsertion");
	p.createGroup("AtrAlgsInAverage", "AtrBubble", "AtrSelection", "AtrInsertion");


	p.showReport();

}

void generateCases2()//best case
{
	int v[ARRAY_MAX_SIZE], v1[ARRAY_MAX_SIZE];
	for (int i = STEP_SIZE; i <= MAX_SIZE; i = i + STEP_SIZE)
	{
		FillRandomArray(v, i, 0, 10000, false, 1);
		copyArray(v, v1, i);

		BubbleSort(v, i);
		p.addSeries("Atr+CompBubble", "AtrBubble", "CompBubble");

		copyArray(v1, v, i);
		SelectionSort(v1, i);
		p.addSeries("Atr+CompSelection", "AtrSelection", "CompSelection");

		InsertionSort(v, i);
		p.addSeries("Atr+CompInsertion", "AtrInsertion", "CompInsertion");

	}

	p.createGroup("SortingAlgsInBest", "Atr+CompBubble", "Atr+CompSelection", "Atr+CompInsertion");
	p.createGroup("CompAlgsInBest", "CompBubble", "CompSelection", "CompInsertion");
	p.createGroup("AtrAlgsInBest", "AtrBubble", "AtrSelection", "AtrInsertion");

	p.showReport();

}

void generateCases3()//worst case
{
	int v[ARRAY_MAX_SIZE], v1[ARRAY_MAX_SIZE];
	for (int i = STEP_SIZE; i <= MAX_SIZE; i = i + STEP_SIZE)
	{
		FillRandomArray(v, i, 0, 10000, false, 2);
		copyArray(v, v1, i);

		BubbleSort(v, i);
		p.addSeries("Atr+CompBubble", "AtrBubble", "CompBubble");

		copyArray(v1, v, i);
		SelectionSort(v1, i);
		p.addSeries("Atr+CompSelection", "AtrSelection", "CompSelection");

		InsertionSort(v, i);
		p.addSeries("Atr+CompInsertion", "AtrInsertion", "CompInsertion");
	}

	p.createGroup("SortingAlgsInWorst", "Atr+CompBubble", "Atr+CompSelection", "Atr+CompInsertion");
	p.createGroup("CompAlgsInWorst", "CompBubble", "CompSelection", "CompInsertion");
	p.createGroup("AtrAlgsInWorst", "AtrBubble", "AtrSelection", "AtrInsertion");

	p.showReport();
}

void demo1()
{
	int v[11] = { 1, 3, 0, 99, 17, 11, 23, 2, 6, 14, 1 };
	int n = sizeof(v) / sizeof(v[0]);
	BubbleSort(v, n);
	cout << "Demo for BubbleSort:";
	for (int i = 0; i < n; i++)
		cout << v[i] << " ";
}
void demo2()
{
	int v[11] = { 1, 3, 0, 99, 17, 11, 23, 2, 6, 14, 1 };
	int n = sizeof(v) / sizeof(v[0]);
	SelectionSort(v, n);
	cout << "Demo for SelectionSort:";
	for (int i = 0; i < n; i++)
		cout << v[i] << " ";
}

void demo3()
{
	int v[11] = { 1, 3, 0, 99, 17, 11, 23, 2, 6, 14, 1 };
	int n = sizeof(v) / sizeof(v[0]);
	InsertionSort(v, n);
	cout << "Demo for InsertionSort:";
	for (int i = 0; i < n; i++)
		cout << v[i] << " ";
}





int main()
{
	demo1();
	cout << "\n";
	demo2();
	cout << "\n";
	demo3();
	generateCases1();
	generateCases2();
	generateCases3();

}