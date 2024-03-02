# Tasks:
# L01
 * The code presents 3 direct sorting methods(BubbleSort,SelectionSort,InsertionSort)
 BubbleSort- The function BubbleSort takes an array of maximum MAX_SIZE elements and its size and sorts it ascending
 according to the following principle: each set of adjacent pairs are checked,from left ti right, and if the order is
 not the desired one(ascending in our case) the two elements are swapped. We also check if the array is already sorted
 after the first itteration in order to improve the efficiency.
 SelectionSort- The function SelectionSort takes an array of maximum MAX_SIZE elements and its size and sorts it ascending
 according to the following principle: We search in the unsorted array the minimum value and place it at the end of the
 sorted array only if it isn't already there(we avoid swapping it with itself)
 InsertionSort- The function InsertionSort takes an array of maximum MAX_SIZE elements and its size and sorts it ascending
 according to the following principle: We know that an 1 element array is always sorted, so we can start by analyzing
 the second element, and place it in the correct order according to the sub-array already sorted. This process is 
 repeteated until the desired sorted array.

 * Charts interpretation: The Average case->In the average case according to the Atr chart we can draw the following
 conclusion: SS<IS<BS (BS graph is increasing the fastest, then IS and the SS), the same conclusion can be drawn in
 the other two cases(Worst,Best). According to the Comp chart we can draw the following conclusion: BS<IS<SS.
 The Comp in the Best and Worst case can be visualised in the charts present in project folder.
 According to the sum of the Comp and Atr operations we can draw the following conclusions:
 1)In average IS<SS<BS (regarding the graph growth, IS graph increases the slowest)
 2)In the best case the conclusion is the same
 3)In worst case SS<IS<BS (regarding the graph growth, SS graph increases the slowest)
 The conclusions drawn above are true for the below implementation of the sorting algorithms.

  # L02
The 3 required algorithms to implement are the following:

* BuilHeapBottomUp->The idea behind this algorithm is that we know from the beginning all the elements in the array from which we want to construct a heap
 (in place). So we choose the first place where it is possible to encounter values that are not where they belong(at the last non-leaf node) and we call Heapify 
 for each node starting from there up to the root. Heapify works in the following manner: it tries to add a new element to two existing sub-heaps and make a
 bigger one from the elements mentioned above.
 
* BuildHeapTopDown->The idea behind this algorithm is that we don't know from the beggining all the elements that will be part of our final heap, so we have to
 take them one by one and insert them in the newly created heap. The insertion works by putting the element as the last leaf, and by applying heapify2 on the
 newly added element in order to buuble it up in the right place.
 
* HeapSort->The idea behind the algorithm is that we start with a Max-Heap. After we have the Max-Heap created we do the following: take the root(which is also
 the maximum value in the array) and swap it with the last leaf, then decrease the size of the array for wich we will restore it's heap property. In this
 manner we sort in place, no additional space is required.
 
 * Charts interpretation: As we have already expected we can see that in the average case the method of building a Max(Min)
 Heap by using the BottomUp approach is more efficienct than buildin a Max(Min) Heap by using the TopDown approach(The
 combined graph(comp+atr) increases faster for the TopDown method than for the BottomUp method).

  # L03
* The QSort algorithm presented below works as follows: We start with the whole array to be sorted and we try to find the
pivot position(the final position of the pivot for this step) and the pivot value. In the following steps we will
apply the same idea on the sub-arrays located on pivot's left and right side recursevly.  
 * Comparing QSort with HeapSort by generating the graphs we can observe that HeapSort's graph increases faster than QS's
 graph, so it is less efficient.  
 * I couldn't really compare QSort in the three cases(worst,best,average) because the computer couldn't handle such big
 input sizes for each case(but, analysing the obtained graphs we can cocnlude that there is a difference depending
 on the input format)

  # L04
* The function mergeKSortedLists returns a pointer to the head of the already merged list. The idea behind the algorithm
 uses some principles already presented in the last labs. We take k sorted lists and at each step we extract the smallest
 element from the head of each list(if the list isn't empty yet) and we insert it in the final merged list. We have to
 remember from which list did we extract the element in order to change the head of the list in that specific list.
* An efficient method of finding the minnimum element from the first elements of the lists is by using a MinHeap.

* As we can see in the graphs generated by function generatecases1() the number of operations increases as k increases.
* So larger the number of k random sorted lists, larger the number of operations.

  # L05
  

  # L06
  

  # L07
  

  # L08
  

  # L09
  

  # L10
  

  # L11

  
