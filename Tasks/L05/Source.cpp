/*Borz Robert-Ionut Group 30424
*/
#include <iostream>
#include <string.h>
#include <cstring> 
#include <random>
#include "Profiler.h"

using namespace std;

#define HashTableSize_N 9973 //close prime number to 10000
#define MAX_ARRAY_SIZE 10000
#define HashTableSize_Demo 19

//function that returns a random string using all the letters in the english alphabet(including capital letters)
//Not my code, because it is not the interest of this lab
string random_string(size_t length)
{
	const string CHARACTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

	random_device random_device;
	mt19937 generator(random_device());
	uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);

	string random_string;

	for (size_t i = 0; i < length; ++i)
	{
		random_string += CHARACTERS[distribution(generator)];
	}

	return random_string;
}

typedef struct
{
	int id;
	char name[30];
	bool was_removed;
} Entry;

typedef struct
{
	int steps;
	bool found;
	int index;
} effort;

void copyArray(int v[MAX_ARRAY_SIZE], int v1[MAX_ARRAY_SIZE], int n)
{
	for (int i = 0; i < n; i++)
		v1[i] = v[i];
}

int countHT(Entry HT[HashTableSize_N], int HashTableSize)
{
	int elements = 0;
	for (int i = 0; i < HashTableSize; i++)
	{
		if (HT[i].id != -1)
			elements++;
	}
	return elements;
}

void printHT(Entry HT[HashTableSize_N], int HashTableSize)
{
	for (int i = 0; i < HashTableSize; i++)
	{
		if (HT[i].id != -1)
			cout << HT[i].id << " " << HT[i].name << endl;
		else
			cout << HT[i].id << endl;
	}

}

void HashingFunction(Entry HashTable[HashTableSize_N], int HashTableSize, Entry v[MAX_ARRAY_SIZE], int n)
{
	for (int i = 0; i < n; i++)
	{
		//we compute the hash value
		int hash_value = v[i].id % HashTableSize;

		if (HashTable[hash_value].id == -1)//-1 is a flag that tells us if the slot is empty or not
		{
			HashTable[hash_value].id = v[i].id;
			strcpy_s(HashTable[hash_value].name, v[i].name);
		}
		else
		{//if there is a collision we must itterate through all possible quadratic values
			for (int j = 1; j < HashTableSize; j++)
			{
				//computing the new values
				int hash_value_qp = (hash_value + j * j) % HashTableSize;
				if (HashTable[hash_value_qp].id == -1)
				{
					HashTable[hash_value_qp].id = v[i].id;
					strcpy_s(HashTable[hash_value_qp].name, v[i].name);
					break;

				}
			}

		}

	}
}

effort search(Entry HashTable[HashTableSize_N], int HashTableSize, int key)
{
	effort elem;
	elem.steps = 0;
	elem.found = false;
	elem.index = 0;

	int hash_value = key % HashTableSize;
	int hash_value_qp;

	if (HashTable[hash_value].id == key)
	{
		elem.steps = 1;
		elem.found = true;
		elem.index = hash_value;

	}
	else
	{
		//while inserting the element in the HT there was a collision with another element or the item isn't in the
		//HT
		for (int j = 1; j < HashTableSize; j++)
		{
			elem.steps++;
			//computing the new values(trying to search the key in some possible places where we probably inserted it)
			hash_value_qp = (hash_value + j * j) % HashTableSize;
			if (HashTable[hash_value_qp].id == key)
			{
				elem.found = true;
				elem.index = hash_value_qp; //we keep the index for each found element because we might
				break;                     //might need it if we want to delete
			}
			if (HashTable[hash_value_qp].id == -1)
			{
				if (HashTable[hash_value_qp].was_removed == false)
				{
					break;
				}

			}

		}
	}

	return elem;
}

void Delete(Entry HashTable[HashTableSize_N], int HashTableSize, int key)
{
	effort is_in_HT;
	is_in_HT = search(HashTable, HashTableSize, key);
	if (is_in_HT.found == true)
	{
		//cout << is_in_HT.index << endl;
		HashTable[is_in_HT.index].id = -1;
		HashTable[is_in_HT.index].was_removed = true;

		strcpy_s(HashTable[is_in_HT.index].name, "removed");

	}
}

void generatecases1()
{
	string name_string;
	float filling_factors[5] = { 0.8, 0.85, 0.9, 0.95, 0.99 };
	int n, v[MAX_ARRAY_SIZE], v2[MAX_ARRAY_SIZE], m = 3000;
	Entry HashTable[HashTableSize_N], v1[MAX_ARRAY_SIZE];

	cout << "*Uniform selection of the elements*" << endl;

	for (int i = 0; i < 5; i++)
	{
		for (int i = 0; i < HashTableSize_N; i++)//initialising the HashTable with "-1" in order to mark that all the
		{                                       //slots are available+ we mark each slot as from there wasn't deleted
			HashTable[i].id = -1;              //anything yet(will help us while trying to find something after deleting)
			HashTable[i].was_removed = false;
		}



		n = HashTableSize_N * filling_factors[i];

		FillRandomArray(v, n, 0, 10000, false, 0);
		copyArray(v, v2, n);

		for (int j = 0; j < n; j++)
		{
			v1[j].id = v[j];
			name_string = random_string(10);
			strcpy_s(v1[j].name, name_string.c_str());

		}
		HashingFunction(HashTable, HashTableSize_N, v1, n);

		//for half of the elements that are going to be searched we have to make sure that they are not present
		//in the HT, so we will try to search elements st that  20000>=element>10000

		//NOT FOUND SECTION

		effort eff_per_one_search;
		float sum_of_eff_not_found = 0;
		float average_eff_not_found;
		int max_eff_not_found = 0;

		FillRandomArray(v, m / 2, 10001, 20000, false, 0);

		for (int i = 0; i < m / 2; i++)
		{
			eff_per_one_search = search(HashTable, HashTableSize_N, v[i]);

			if (eff_per_one_search.steps > max_eff_not_found)
				max_eff_not_found = eff_per_one_search.steps;

			sum_of_eff_not_found += eff_per_one_search.steps;

		}

		average_eff_not_found = sum_of_eff_not_found / (m / 2);

		//FOUND SECTION
		/*The commented code is a deprecated version
		effort eff_per_one_search_found;
		float sum_of_eff_found = 0;
		float average_eff_found;
		int max_eff_found = 0;

		for (int i = 0; i < m / 6; i++) //searching elements that were added in the first m/6 additions
		{

			eff_per_one_search_found = search(HashTable, HashTableSize_N, v2[i]);

			if (eff_per_one_search_found.steps > max_eff_found)
				max_eff_found = eff_per_one_search_found.steps;

			sum_of_eff_found += eff_per_one_search_found.steps;
		}

		for (int i = n / 2; i < (n / 2) + (m / 12); i++)//searching elements that were added somewhere in the middle(middle's right)
		{

			eff_per_one_search_found = search(HashTable, HashTableSize_N, v2[i]);

			if (eff_per_one_search_found.steps > max_eff_found)
				max_eff_found = eff_per_one_search_found.steps;

			sum_of_eff_found += eff_per_one_search_found.steps;
		}

		for (int i = (n / 2) - 1; i >= (n / 2) - (m / 12); i--)//(middle's left)
		{

			eff_per_one_search_found = search(HashTable, HashTableSize_N, v2[i]);

			if (eff_per_one_search_found.steps > max_eff_found)
				max_eff_found = eff_per_one_search_found.steps;

			sum_of_eff_found += eff_per_one_search_found.steps;
		}

		for (int i = n - 1; i >= n - (m / 6); i--) //searching elements that were added in the last m/6 additions
		{

			eff_per_one_search_found = search(HashTable, HashTableSize_N, v2[i]);

			if (eff_per_one_search_found.steps > max_eff_found)
				max_eff_found = eff_per_one_search_found.steps;

			sum_of_eff_found += eff_per_one_search_found.steps;
		}
		*/

		effort eff_per_one_search_found;
		float sum_of_eff_found = 0;
		float average_eff_found;
		int max_eff_found = 0;
		int step = HashTableSize_N / (m / 2);

		for (int i = 0; i < n; i = i + step)//we search at every sixth position to ensure a diverse searching are
		{

			eff_per_one_search_found = search(HashTable, HashTableSize_N, v2[i]);

			if (eff_per_one_search_found.steps > max_eff_found)
				max_eff_found = eff_per_one_search_found.steps;

			sum_of_eff_found += eff_per_one_search_found.steps;
		}

		average_eff_found = sum_of_eff_found / (m / 2);


		if (i == 0)
		{
			cout << "filling factor || " << "average found || " << "max effort found || " << "average not found || " << "max effort not found" << endl;
		}

		cout << filling_factors[i] << " ||" << average_eff_found << "||" << max_eff_found << " ||" << average_eff_not_found << "||" << max_eff_not_found << endl;

	}
}

void generatecases2()
{
	string name_string;
	float filling_factors[5] = { 0.8, 0.85, 0.9, 0.95, 0.99 };
	int n, v[MAX_ARRAY_SIZE], v2[MAX_ARRAY_SIZE], m = 3000;
	Entry HashTable[HashTableSize_N], v1[MAX_ARRAY_SIZE];

	cout << "*Non-uniform selection of the elements*" << endl;

	for (int i = 0; i < 5; i++)
	{
		for (int i = 0; i < HashTableSize_N; i++)//initialising the HashTable with "-1" in order to mark that all the
		{                                       //slots are available+ we mark each slot as from there wasn't deleted
			HashTable[i].id = -1;              //anything yet(will help us while trying to find something after deleting)
			HashTable[i].was_removed = false;
		}

		n = HashTableSize_N * filling_factors[i];

		FillRandomArray(v, n, 0, 10000, false, 0);
		copyArray(v, v2, n);

		for (int j = 0; j < n; j++)
		{
			v1[j].id = v[j];
			name_string = random_string(10);
			strcpy_s(v1[j].name, name_string.c_str());

		}
		HashingFunction(HashTable, HashTableSize_N, v1, n);

		//for half of the elements that are going to be searched we have to make sure that they are not present
		//in the HT, so we will try to search elements st that  20000>=element>10000

		//NOT FOUND SECTION

		effort eff_per_one_search;
		float sum_of_eff_not_found = 0;
		float average_eff_not_found;
		int max_eff_not_found = 0;

		FillRandomArray(v, m / 2, 10001, 20000, false, 0);

		for (int i = 0; i < m / 2; i++)
		{
			eff_per_one_search = search(HashTable, HashTableSize_N, v[i]);

			if (eff_per_one_search.steps > max_eff_not_found)
				max_eff_not_found = eff_per_one_search.steps;

			sum_of_eff_not_found += eff_per_one_search.steps;

		}

		average_eff_not_found = sum_of_eff_not_found / (m / 2);

		//FOUND SECTION

		effort eff_per_one_search_found;
		float sum_of_eff_found = 0;
		float average_eff_found;
		int max_eff_found = 0;

		for (int i = 0; i < m/2; i++) //searching the first(or last) m/2 added elements(Non-uniform)
		{

			eff_per_one_search_found = search(HashTable, HashTableSize_N, v2[i]);

			if (eff_per_one_search_found.steps > max_eff_found)
				max_eff_found = eff_per_one_search_found.steps;

			sum_of_eff_found += eff_per_one_search_found.steps;
		}

		average_eff_found = sum_of_eff_found / (m / 2);

		if (i == 0)
		{
			cout << "filling factor || " << "average found || " << "max effort found || " << "average not found || " << "max effort not found" << endl;
		}

		cout << filling_factors[i] << " ||" << average_eff_found << "||" << max_eff_found << " ||" << average_eff_not_found << "||" << max_eff_not_found << endl;

	}
}

void generatecases3()
{
	cout << "* Evaluation of the search operation after deletion of some elements *" << endl;
	string name_string;
	int n, v[MAX_ARRAY_SIZE], v2[MAX_ARRAY_SIZE], m = 3000;
	float nr_of_items_after_deletion;
	Entry HashTable[HashTableSize_N], v1[MAX_ARRAY_SIZE];

	for (int i = 0; i < HashTableSize_N; i++)//initialising the HashTable with "-1" in order to mark that all the
	{                                       //slots are available+ we mark each slot as from there wasn't deleted
		HashTable[i].id = -1;              //anything yet(will help us while trying to find something after deleting)
		HashTable[i].was_removed = false;
	}

	n = HashTableSize_N * 0.99;

	FillRandomArray(v, n, 0, 10000, false, 0);
	copyArray(v, v2, n);

	for (int j = 0; j < n; j++)
	{
		v1[j].id = v[j];
		name_string = random_string(10);
		strcpy_s(v1[j].name, name_string.c_str());

	}

	HashingFunction(HashTable, HashTableSize_N, v1, n);

	cout << "Number of elements in the HashTable: ";
	cout << countHT(HashTable, HashTableSize_N) << endl;

	int nr_of_items_to_be_deleted = 0.19 * n;

	cout << "Number of elements to be deleted: ";
	cout << nr_of_items_to_be_deleted << endl;

	for (int i = 0; i < HashTableSize_N; i = i + (n / nr_of_items_to_be_deleted))
	{
		Delete(HashTable, HashTableSize_N, HashTable[i].id);
	}

	cout << "Number of elements after deletion: ";
	cout << countHT(HashTable, HashTableSize_N) << endl;

	nr_of_items_after_deletion = countHT(HashTable, HashTableSize_N);

	cout << "The new filling factor: ";
	cout << nr_of_items_after_deletion / HashTableSize_N << endl;

	//NOT FOUND SECTION

	effort eff_per_one_search;
	float sum_of_eff_not_found = 0;
	float average_eff_not_found;
	int max_eff_not_found = 0;

	FillRandomArray(v, m / 2, 10001, 20000, false, 0);

	for (int i = 0; i < m / 2; i++)
	{
		eff_per_one_search = search(HashTable, HashTableSize_N, v[i]);

		if (eff_per_one_search.steps > max_eff_not_found)
			max_eff_not_found = eff_per_one_search.steps;

		sum_of_eff_not_found += eff_per_one_search.steps;

	}

	average_eff_not_found = sum_of_eff_not_found / (m / 2);

	//FOUND SECTION
	/*Deprecated version of code
	effort eff_per_one_search_found;
	float sum_of_eff_found = 0;
	float average_eff_found;
	int max_eff_found = 0;

	for (int i = 0; i < m / 6; i++) //searching elements that were added in the first m/6 additions
	{

		eff_per_one_search_found = search(HashTable, HashTableSize_N, v2[i]);

		if (eff_per_one_search_found.steps > max_eff_found)
			max_eff_found = eff_per_one_search_found.steps;

		sum_of_eff_found += eff_per_one_search_found.steps;
	}

	for (int i = n / 2; i < (n / 2) + (m / 12); i++)//searching elements that were added somewhere in the middle(middle's right)
	{

		eff_per_one_search_found = search(HashTable, HashTableSize_N, v2[i]);

		if (eff_per_one_search_found.steps > max_eff_found)
			max_eff_found = eff_per_one_search_found.steps;

		sum_of_eff_found += eff_per_one_search_found.steps;
	}

	for (int i = (n / 2) - 1; i >= (n / 2) - (m / 12); i--)//(middle's left)
	{

		eff_per_one_search_found = search(HashTable, HashTableSize_N, v2[i]);

		if (eff_per_one_search_found.steps > max_eff_found)
			max_eff_found = eff_per_one_search_found.steps;

		sum_of_eff_found += eff_per_one_search_found.steps;
	}

	for (int i = n - 1; i >= n - (m / 6); i--) //searching elements that were added in the last m/6 additions
	{

		eff_per_one_search_found = search(HashTable, HashTableSize_N, v2[i]);

		if (eff_per_one_search_found.steps > max_eff_found)
			max_eff_found = eff_per_one_search_found.steps;

		sum_of_eff_found += eff_per_one_search_found.steps;
	}
	*/

	effort eff_per_one_search_found;
	float sum_of_eff_found = 0;
	float average_eff_found;
	int max_eff_found = 0;
	int step = HashTableSize_N / (m / 2);

	for (int i = 0; i < n; i = i + step)//we search at every sixth position to ensure a diverse searching are
	{

		eff_per_one_search_found = search(HashTable, HashTableSize_N, v2[i]);

		if (eff_per_one_search_found.steps > max_eff_found)
			max_eff_found = eff_per_one_search_found.steps;

		sum_of_eff_found += eff_per_one_search_found.steps;
	}

	average_eff_found = sum_of_eff_found / (m / 2);



	cout << "filling factor || " << "average found || " << "max effort found || " << "average not found || " << "max effort not found" << endl;


	cout << nr_of_items_after_deletion / HashTableSize_N << " ||" << average_eff_found << "||" << max_eff_found << " ||" << average_eff_not_found << "||" << max_eff_not_found << endl;

}

void demo1()//demo for the insert and search operation
{
	Entry v[10] = { {200,"a"},{15,"b"},{73,"c"},{0,"d"},{11,"e"},{97,"f"},{1222,"g"},{98,"h"},{102,"i"},{3,"j"} };
	int n = sizeof(v) / sizeof(v[0]);
	Entry HashTableDemo[HashTableSize_Demo];
	effort op;

	for (int i = 0; i < HashTableSize_Demo; i++)
	{
		HashTableDemo[i].id = -1;
		HashTableDemo[i].was_removed = false;

	}

	cout << "* Demo for the insert and search operations using the required data structure. *" << endl;
	cout << "The entries to be inserted in the HashTable are:" << endl;
	for (int i = 0; i < n; i++)
	{
		if (i == n - 1)
			cout << v[i].id << " " << v[i].name << " " << endl;
		else
			cout << v[i].id << " " << v[i].name << ",";
	}

	cout << "The size of the HashTable is:";
	cout << HashTableSize_Demo << endl;


	HashingFunction(HashTableDemo, HashTableSize_Demo, v, n);
	printHT(HashTableDemo, HashTableSize_Demo);

	cout << "We search for 200" << endl;
	op = search(HashTableDemo, HashTableSize_Demo, 200);
	if (op.found == true)
		cout << "The element was found by visiting " << op.steps << " cell/cells" << endl;
	else
		cout << "The element wasn't found after looking in " << op.steps << " cell/cells" << endl;

	cout << "We search for 5" << endl;
	op = search(HashTableDemo, HashTableSize_Demo, 5);
	if (op.found == true)
		cout << "The element was found by visiting " << op.steps << " cell/cells" << endl;
	else
		cout << "The element wasn't found after looking in " << op.steps << " cell/cells" << endl;

}

void demo2()
{
	Entry v[10] = { {200,"a"},{15,"b"},{73,"c"},{0,"d"},{11,"e"},{97,"f"},{1222,"g"},{98,"h"},{102,"i"},{3,"j"} };
	int n = sizeof(v) / sizeof(v[0]);
	Entry HashTableDemo[HashTableSize_Demo];
	effort op;

	for (int i = 0; i < HashTableSize_Demo; i++)
	{
		HashTableDemo[i].id = -1;
		HashTableDemo[i].was_removed = false;

	}

	cout << "* Demo for delete operation in a hash table. *" << endl;
	cout << "The size of the HashTable is:";
	cout << HashTableSize_Demo << endl;

	HashingFunction(HashTableDemo, HashTableSize_Demo, v, n);
	printHT(HashTableDemo, HashTableSize_Demo);

	cout << "We want to delete the Entry with the id=15" << endl;
	Delete(HashTableDemo, HashTableSize_Demo, 15);
	printHT(HashTableDemo, HashTableSize_Demo);

	cout << "We want to find the Entry with the id=11" << endl;
	op = search(HashTableDemo, HashTableSize_Demo, 11);
	if (op.found == true)
		cout << "We found it at index=" << op.index << endl;
	else
		cout << "Couldn't find it" << endl;

}

int main()
{
	generatecases1();
	generatecases2();
	generatecases3();
	demo1();
	demo2();
}