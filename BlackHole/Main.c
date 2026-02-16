#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MemoryManager/MemoryManager.h"

#include "Map/Map.h"
#include "List/List.h"
int compare(int* a, int* b)
{
	if (*a > *b)
	{
		return 1;
	}
	else
	{
		return -1;
	}

	return (0);
}

int main()
{
	printf("We are all alone on life's journey, held captive by the limitations of human consciousness.\n");

	MemoryManager memManager;
	if (MemoryManager_Initialize(&memManager) == false)
	{
		return (EXIT_FAILURE);
	}

	List list;
	List_Initialize(&list);

	int a = 10;
	int b = 65;
	int c = 80;
	int d = 13;
	int e = 5;

	List_InsertStart(list, &a);
	List_InsertStart(list, &b);
	List_InsertStart(list, &c);
	List_InsertStart(list, &d);
	List_InsertStart(list, &e);

	// int* search = List_Find(list, 4);
	ListNode node = List_FindNode(list, &a);

	if (node)
	{
		//printf("found node value: %d\n", *search);
		printf("value: %d\n", *(int*)list->rootNode->data);

	}
	else
	{
		printf("failed to find node\n");
	}

	List_Print(list);

	List_Sort(list, compare, true);

	List_Print(list);

	List_Destroy(&list);

	MemoryManager_DumpLeaks();
	MemoryManager_Destroy(&memManager);

	return (EXIT_SUCCESS);
}