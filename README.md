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
* The comments are already present in the code.

  # L06
* For R2 I have used an additional struct named Rep2 containing the node, the list of children of type Rep2, the
 number of children and a boolean in order to mark the root when encountered. The method T1 does the transformations
 in O(n) with the help of the additional struct. The additional memory needed is represented by the array children which
 holds elements(references to the elements) of the type Rep2(without it it would have been really hard to respect the O(n)
 restriction).
*  The idea of the algorithm is the following: traverse one single time the parent vector and assign the values in the
 new array of Rep2 type accordingly(of course an initialization is needed).
 
*  For R3 I have used an additional struct named Rep3 containing the node and two pointers to the firstChild and to
 the nextSibling of the node. The methos T2 does the transformations in O(n) with the help of the additional structure.
*  The additional memory is represented by the memory that is occupied by the allocation of the nodes.
* The idea of the algorithm is the following: we take the MWT created previously, starting from the root and we
  create a new node of type Rep3 for each node of type Rep2 and we link appropriately the node's pointers.
  

  # L07
* The code implements the following operations: BUILD_TREE,OS_SELECT,OS_DELETE with their additional helper
 functions.
* BUILD_TREE: builds an augmented PBT(balanced+augmented Binary Search Tree) with the help of an additional function 
 called postorderAUG, the complexity of the algorithm being O(n) for both, so the total complexity is still O(n)
* OS_SELECT: works on the following priciple->using the dimension of the nodes it searches through the tree deciding
 if the node with the given rank is either on the left or on the right side of the current node
* OS_DELETE: deletes the nodes like in a normal BST and toghether with the function fixBranch fixes the affected
 branch depending on the type of node deleted(node with 2 childre/node with 1 child or no children)

  # L08
  * PART I:
* The first part implements the inorder traversal of an already built binary tree(built using BUILD_TREE function) in 2 different ways:
 by using reccursion and by not using reccursion + using a stack(FIFO principle). The reccursive implementation has already been
 discused. The itterative implementation uses a stack, starts from the root, visits its left subtree and prints(for the demo) the 
 nodes in an inorder manner continuing with the right subtree.
 
* PART II:
* The second part implements QuickSortHybrid(the hybridisation is achieved using itterative InsertionSort from Lab01). The hybridisation
 is based on a threshold(30 for the demo and variable in order to find the best value for an input of 10000 numbers). For a certain size
 previously chosen(threshold) and less, we will use InsertionSort and from values greater or equal we will use QuickSort from Lab03. The
 implementation with further explanations can be seen in QuickSorthybrid.
  

  # L09
* The algorithm implements efficiently the base operations for disjoint sets and the Kruskal's Algorithm
 
* The base operations for disjoint sets:
* MAKE_SET(int key)->allocates a node, sets its characteristics and returns the newly created node.
* FIND_SET(TNode* x)->returns the representative of the set that x is included in.
* UNION(TNode* x, TNode* y)->creates a bigger set containing all the elements from the 2 disjoint sets, it follows a
 union by rank approach(we try to avoid unbalancing the tree more than is needed).  
* KRUSKAL's Alg:
* Follows a Greedy approach. We take as input a set of edges, we sort them(ascending) efficiently using HeapSort(from L03)
 and then we itterate through the set of edges and we check if our edge doesn't close a cycle. If it doesn't close a cycle
 it will be part of our MST. The itteration will stop when the MST will be copmplete.

  # L10
* The code written by me is lead by the TODO sections of the requested functions:
*   get_neighbors:->The idea of the algorithm is that we check each possible neighbor to see if it is valid(valid means it
   is not a wall and it is on the grid).
*   bfs:->The idea of the implementation is that we use a queue in order to keep track of our nodes and their status. The
   nodes in the queue are GRAY(under visitation,they were white before being in the queue) and they will become BLACK after
   we finish our traversal(we also set the distance from the source for each node).
* print_bfs_tree:->The idea of the implementation is identical with the one in L06, the only additional thing that we get
	is a repr array, in order to print the position of the node on the grid.
	performance:->As you can see in bfs() function we already count the number of operations, so performance just generates
	test samples for bfs function in the two following manners: 1)constant nr. of node and variable nr. of edges
																2)constant number of edges and variable number of nodes
*   The obtained graphs are the expected ones, showing a linear effort(because it is a traversal).
*   shortest_path:->The idea of the implementation is that we use the bfs algorithm in order to check if we can reach the
    destination node, if we can we will reconstruct the path from de destination to the source and reverse the order in 
	order to obtain the in betwwen nodes between source and destination and we will put them in the path array.
  # L11
  *  DFS:-the algorithm is implemented in a recursive manner, we use an enum in order to keep track of the node's color. A node
  that is unvisited should be white, a node that is under visitation should be gray and a node that has already been visited
  should be black. In order for the algorithm to be able to perform on graphs that are not connected we use an additional
  function that ensures that every connected component will be analysed by DFS.
*  TOPOLOGICAL_SORT:-the idea behind the algorithm is based on DFS, while testing the algorithm we make sure that our graph
 is a DAG(otherwise a topological sort won't exist). After performing DFS on the graph we sort efficiently our nodes by
 finish time and by doing this we obtain a topologocal order(which is not unique).
*  TRAJAN:-the idea behind the algorithm is to find the strongly connected components in a directed graph using only one DFS
 traversal. The implementation is the one presented in the course.
*  DFS Analysis:-The complexity of the algorithm is O(V+E), so the obtained graphs in the 2 required cases are linear as we
 have already expected.

  
