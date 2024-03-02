# Tasks:
# L01
The code presents 3 direct sorting methods(BubbleSort,SelectionSort,InsertionSort)
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

  # L02
