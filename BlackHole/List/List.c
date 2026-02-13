#include "List.h"
#include "../MemoryManager/MemoryManager.h"
#include "../Stdafx.h"

bool List_Initialize(List* ppList)
{
	if (ppList == NULL)
	{
		return (false);
	}

	*ppList = engine_new_zero(SList, 1, MEM_TAG_ENGINE);
	List list = *ppList;

	if (list == NULL)
	{
		return (false);
	}

	return (true);
}

void List_Destroy(List* ppList)
{
	if (ppList == NULL || *ppList == NULL)
	{
		return;
	}

	List list = *ppList;

	List_Clear(list);

	engine_delete(list);

	*ppList = NULL;
}

void List_Clear(List list)
{
	if (list == NULL)
	{
		return;
	}

	ListNode curr = list->rootNode;
	while(curr != NULL)
	{
		ListNode next = curr->next;
		engine_free(curr);
		curr = next;
	}

	list->rootNode = NULL;
	list->tailNode = NULL;
	list->elementsCount = 0;
}

bool List_Insert(List list, void* value)
{
	ListNode newNode = engine_new_zero(SListNode, 1, MEM_TAG_ENGINE);
	if (newNode == NULL)
	{
		return (false);
	}

	newNode->data = value;
	if (list->rootNode == NULL)
	{
		list->rootNode = newNode;
		list->tailNode = newNode; // Track the end
	}
	else
	{
		list->tailNode->next = newNode;
		list->tailNode = newNode;
	}
	list->elementsCount++;

	return (true);
}

bool List_InsertStart(List list, void* value)
{
	ListNode newNode = engine_new_zero(SListNode, 1, MEM_TAG_ENGINE);
	if (newNode == NULL)
	{
		return (false);
	}

	newNode->data = value;
	newNode->next = list->rootNode;
	list->rootNode = newNode;

	if (list->tailNode == NULL)
	{
		list->tailNode = newNode;
	}

	list->elementsCount++;

	return (true);
}

bool List_InsertAt(List list, void* value, int index)
{
	if (index < 0 || index > list->elementsCount)
	{
		return (false);
	}
	
	if (index == 0) // First
	{
		return List_InsertStart(list, value);
	}

	if (index == list->elementsCount) // last 
	{
		return List_Insert(list, value);
	}

	ListNode newNode = engine_new_zero(SListNode, 1, MEM_TAG_ENGINE);
	if (newNode == NULL)
	{
		return (false);
	}

	newNode->data = value;

	ListNode prev = list->rootNode;

	// 2. Find the node BEFORE the target index (index - 1)
	for (int32_t i = 0; i < index - 1; i++)
	{
		prev = prev->next;
	}

	newNode->next = prev->next;
	prev->next = newNode;

	list->elementsCount++;
	return (true);
}

ListNode List_FindNode(List list, void* value)
{
	ListNode curr = list->rootNode;
	while (curr != NULL)
	{
		if (value == curr->data)
		{
			return (curr);
		}

		curr = curr->next;
	}

	return (NULL);
}

void* List_Find(List list, int index)
{
	if (index < 0 || index >= list->elementsCount)
	{
		return NULL;
	}

	ListNode curr = list->rootNode;
	for (int32_t i = 0; i < index; i++)
	{
		curr = curr->next;
	}

	return (curr->data);
}

void* List_Get(List list, int index)
{
	if (index < 0 || index >= list->elementsCount)
	{
		return NULL;
	}

	ListNode curr = list->rootNode;
	for (int i = 0; i < index; i++)
	{
		curr = curr->next;
	}

	return curr->data; // Return the data, not the node!
}

bool List_RemoveIndex(List list, int index)
{
	if (index < 0 || index >= list->elementsCount)
	{
		return (false);
	}

	ListNode curr = list->rootNode;
	ListNode prev = NULL;

	for (int i = 0; i < index; i++)
	{
		prev = curr;
		curr = curr->next;
	}

	if (prev == NULL)
	{
		list->rootNode = curr->next;
	}
	else
	{
		prev->next = curr->next;
	}

	if (curr == list->tailNode)
	{
		list->tailNode = prev;
	}

	engine_delete(curr);
	list->elementsCount--;
	return (true);
}

bool List_Remove(List list, void* value)
{
	ListNode curr = NULL;
	ListNode prev = NULL;

	for (curr = list->rootNode; curr != NULL; curr = curr->next)
	{
		if (curr->data == value) // found
		{
			break;
		}

		prev = curr;
	}

	if (curr == NULL)
	{
		printf("Failed to find the element in the list\n");
		return (false);
	}

	if (prev == NULL)
	{
		list->rootNode = curr->next;
	}
	else
	{
		prev->next = curr->next;
	}

	if (curr == list->tailNode)
	{
		list->tailNode = prev;
	}

	engine_delete(curr);
	list->elementsCount--;
	return (true);
}

void List_ForEach(List list, fnFunc function, void* context)
{
	if (list == NULL || function == NULL)
	{
		return;
	}

	ListNode curr = list->rootNode;
	while (curr != NULL) 
	{
		ListNode next = curr->next;

		// Pass the data AND the extra info (like dt or camera)
		function(curr->data, context);
		curr = next;
	}
}

void List_Sort(List list, fnCompare compareFunc)
{
	if (list == NULL || compareFunc == NULL)
	{
		return;
	}

	if (list->elementsCount < 2)
	{
		return;
	}

	bool swapped;
	do
	{
		swapped = false;
		ListNode curr = list->rootNode;

		while (curr != NULL && curr->next != NULL)
		{
			if (compareFunc(curr->data, curr->next->data) > 0)
			{
				// Swap the data pointers
				void* temp = curr->data;
				curr->data = curr->next->data;
				curr->next->data = temp;

				swapped = true;
			}

			curr = curr->next;
		}
	} while (swapped == true);
}

