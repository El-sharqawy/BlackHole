#ifndef __LIST_H__
#define __LIST_H__

#include <stdbool.h>
#include <stdint.h>

typedef void(*fnFunc)(void* data, void* context);
// Returns 1 if a > b, 0 if equal, -1 if a < b
typedef int (*fnCompare)(void* a, void* b);

typedef struct SListNode
{
	void* data;
	struct SListNode* next; // Next Element
} SListNode;

typedef struct SListNode* ListNode;

typedef struct SList
{
	ListNode rootNode; // First Element
	ListNode tailNode; // Last Element
	size_t elementsCount;
} SList;

typedef struct SList* List;

bool List_Initialize(List* ppList);
void List_Destroy(List* ppList);
void List_Clear(List list);

bool List_Insert(List list, void* value);
bool List_InsertStart(List list, void* value);
bool List_InsertAt(List list, void* value, int index);

ListNode List_FindNode(List list, void* value);
void* List_Find(List list, int index);
void* List_Get(List list, int index);

bool List_RemoveIndex(List list, int index);
bool List_Remove(List list, void* value);

void List_ForEach(List list, fnFunc function, void* context);
void List_Sort(List list, fnCompare compareFunc);

#endif // __LIST_H__
