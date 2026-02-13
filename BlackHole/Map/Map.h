#ifndef __MAP_H__
#define __MAP_H__

#include <stdint.h>
#include <stdbool.h>

typedef struct SMapNode* MapNode;
typedef struct SMap* Map;

typedef void(*MapDestructorFunc)();

typedef struct SMapNode
{
	char* szKey;
	void* pValue;

	char pos; // r - l - h (right, left, head)

	MapNode leftNode; // Alphabetically smaller
	MapNode rightNode; // Alphabetically larger

	// parent node
	MapNode parentNode;
} SMapNode;

typedef struct SMap
{
	MapNode headNode;
	size_t elementsCount;
	MapDestructorFunc destructor;
} SMap;

bool Map_Initialize(Map* ppMap);
void Map_Destroy(Map* ppMap);

bool Map_Insert(Map map, char* key, void* value);
void* Map_Find(Map map, char* key);
void* Map_FindNode(Map map, char* key);

void Map_Delete(Map map, char* key);
void Map_Clear(Map map);
void Map_ClearRecursive(Map map, MapNode node);

#endif // __MAP_H__