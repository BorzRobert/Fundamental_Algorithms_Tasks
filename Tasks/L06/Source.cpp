/*Borz Robert-Ionut Group 30424
*  For R2 I have used an additional struct named Rep2 containing the node, the list of children of type Rep2, the
* number of children and a boolean in order to mark the root when encountered. The method T1 does the transformations
* in O(n) with the help of the additional struct. The additional memory needed is represented by the array children which
* holds elements(references to the elements) of the type Rep2(without it it would have been really hard to respect the O(n)
* restriction).
*  The idea of the algorithm is the following: traverse one single time the parent vector and assign the values in the
* new array of Rep2 type accordingly(of course an initialization is needed).
* 
*  For R3 I have used an additional struct named Rep3 containing the node and two pointers to the firstChild and to
* the nextSibling of the node. The methos T2 does the transformations in O(n) with the help of the additional structure.
*  The additional memory is represented by the memory that is occupied by the allocation of the nodes.
* The idea of the algorithm is the following: we take the MWT created previously, starting from the root and we
*  create a new node of type Rep3 for each node of type Rep2 and we link appropriately the node's pointers.
* 
*/

#include <iostream>

using namespace std;

#define MAX_NR_OF_CHILDREN 10
#define MAX_ARRAY_SIZE 100

void printArray(int v[MAX_ARRAY_SIZE], int n)
{
	for (int i = 0; i < n; i++)
		cout << v[i] << " ";
}

typedef struct Rep2 //helper structure used in order to achive T1 in O(n)
{
	int node;
	Rep2* children[MAX_NR_OF_CHILDREN];
	int nrOfChildren;
	bool isRoot;
};

typedef struct Rep3 //helper structure used in order to achieve T2
{
	int node;
	Rep3* firstChild;
	Rep3* nextSibling;
};

Rep2* findRoot(Rep2* v[MAX_ARRAY_SIZE], int n)
{
	for (int i = 1; i <= n; i++) //find the root in order to pass it to T2(root,v1)
	{
		if (v[i]->isRoot == true)
			return v[i];

	}
}

void T1(int v[MAX_ARRAY_SIZE], int n, Rep2* v1[MAX_ARRAY_SIZE])
{
	for (int i = 1; i <= n; i++)//initialization of the elements of the new representation
	{
		v1[i] = new Rep2;
		v1[i]->nrOfChildren = 0;
		v1[i]->isRoot = false;
		for (int j = 0; j < MAX_NR_OF_CHILDREN; j++)
		{
			v1[i]->children[j] = new Rep2;
		}
	}

	for (int i = 0; i < n; i++)
	{

		v1[i + 1]->node = i + 1; //each node's value is equal with index+1 because the array starts form 0 but
		                        //we don't have the value 0 in our tree
		if (v[i] != -1)
		{

			v1[v[i]]->children[v1[v[i]]->nrOfChildren]->node = i + 1;//children identification
			v1[v[i]]->nrOfChildren++;

		}
		else
		{
			v1[i + 1]->isRoot = true;//root identification
		}

	}

	for (int i = 1; i <= n; i++)
	{
		//cout << v1[i]->node << ": " << "number of children: " << v1[i]->nrOfChildren << " |"; //in order to check the content
		if (v1[i]->nrOfChildren != 0)                                                          //of each node(regarding key and
		{                                                                                     //children uncomment the 5 expresions
			//int p = v1[i]->nrOfChildren;
			//for (int j = 0; j < p; j++)
				//cout << v1[i]->children[j]->node << " ";

		}
		//cout << endl;
	}

}

void prettyPrintT1(Rep2* v1[MAX_ARRAY_SIZE], int n)//we simply print the previously created tree(by T1)
{                                                 //by starting from the root and printing "nicely" 
	cout << "* PrettyPrintT1 *" << endl;         //each node.

	for (int i = 1; i <= n; i++)
	{
		if (v1[i]->isRoot == true)
		{
			cout << v1[i]->node << endl;
			int p = v1[i]->nrOfChildren;
			for (int j = 0; j < p; j++)
			{
				cout << "    " << v1[i]->children[j]->node << endl;
				int l = v1[v1[i]->children[j]->node]->nrOfChildren;
				for (int k = 0; k < l; k++)
				{
					cout << "       " << v1[v1[i]->children[j]->node]->children[k]->node << endl;
				}
			}

		}
	}


}

Rep3* T2(Rep2* myNode, Rep2* v1[MAX_ARRAY_SIZE])
{
	Rep3* newNode = new Rep3;  //we create the new node of type Rep3*
	Rep3* lastConvertedChild;
	Rep3* v;
	newNode->node = myNode->node;
	newNode->firstChild = NULL;
	newNode->nextSibling = NULL;

	if (v1[myNode->node]->nrOfChildren > 0)
	{
		newNode->firstChild = T2(v1[myNode->node]->children[0],v1);

		lastConvertedChild = newNode->firstChild;  //we make the links between the created nodes as follows:
                                                  //firstChild is node's first child(if it exists) and next sibling is the node's
		int p = v1[myNode->node]->nrOfChildren;  //next child(if it exists).If some of the elements(firstChild or nextSibling) does             
		for (int j = 1; j < p; j++)             //not exist, the pointers will point to NULL
		{
			v = T2(v1[myNode->node]->children[j],v1);
			lastConvertedChild->nextSibling = v;
			lastConvertedChild = v;
		}

	}

	return newNode;//and return the root

}

void prettyPrintT2(Rep3* root, int level)//we print the tree somehow like in a BST, but we don't reffer
{                                       // to left and right but to firstChild and nextSibling
	if (root != NULL)                  //level is used in order to print the needed spaces
	{
		for (int i = 0; i < level; i++)
			cout << " ";
		cout << root->node;
		cout << endl;

		prettyPrintT2(root->firstChild, level+3 );
		prettyPrintT2(root->nextSibling, level );

	}

}

int main()
{
	int R1[9] = { 2,7,5,2,7,7,-1,5,2 };
	Rep2* R2[10];
	Rep2* root;
	Rep3* R3;
	int n = sizeof(R1) / sizeof(R1[0]);
	root = NULL;

	cout << "* PrettyPrintT0 *" << endl;
	printArray(R1, n);
	cout << endl;

	T1(R1, n, R2);
	prettyPrintT1(R2, n);
	cout << endl;

	cout << "* PrettyPrintT2 *" << endl;
	root = findRoot(R2, n);
	R3 = T2(root,R2);
	prettyPrintT2(R3, 0);

}