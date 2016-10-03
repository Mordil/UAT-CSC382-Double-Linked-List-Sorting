#include <iostream>
#include <array>
#include <ctime>

#include "MyDoubleLinkedList.h"

using namespace std;

int main()
{
	// timers
	clock_t start;

	// initialization
	array<int, 25> startingArray = { 354, 246, 314, 164, 152, 420, 351, 10, 483, 395, 371, 143, 26, 94, 400, 458, 155, 307, 178, 425, 93, 124, 299, 74, 256 };
	MyDoubleLinkedList<int, int> myList;

	for (array<int, 25>::const_iterator i = startingArray.begin(); i < startingArray.end(); ++i)
	{
		myList.Insert(*i, *i);
	}

	/* SORTED (SORTED INSERT) */
	cout << "Creating List Unsorted and Sorting w/ Insertion";
	start = clock();

	MyDoubleLinkedList<int, int> myList2 = myList.Sorted();

	cout << "\n\nFinished Sorting by SortingInsert for 25 elements " << "(took " << (clock() - start) / (double) CLOCKS_PER_SEC << " seconds)\n\n";

	myList2.PrintContents();

	cout << "\n\n";

	/* SORTED (SELECTION INSERT) */
	cout << "Creating List Unsorted and Sorting w/ Selection";
	start = clock();

	MyDoubleLinkedList<int, int> myList3 = myList.SelectionSorted();

	cout << "\n\nFinished Sorting by SelectionSorting for 25 elements " << "(took " << (clock() - start) / (double) CLOCKS_PER_SEC << " seconds)\n\n";

	myList3.PrintContents();

	cout << "\n\n";

	system("pause");
	return 0;
}