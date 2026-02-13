#include "Map.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#if defined(_WIN32) || defined(_WIN64)
#define strdup _strdup
#endif

bool Map_Initialize(Map* ppMap)
{
	if (!ppMap)
	{
		return (false);
	}

	// Initialize with everything to Zero and NULL
	*ppMap = calloc(1, sizeof(SMap));
	Map map = *ppMap;

	if (map == NULL)
	{
		printf("Failed to Allocate Map Memory\n");
		return (false);
	}

	return (true);
}

void Map_Destroy(Map* ppMap)
{
	if (!ppMap || !*ppMap)
	{
		return;
	}

	Map_Clear(*ppMap);

	free(*ppMap);
	*ppMap = NULL;
}

bool Map_Insert(Map map, char* key, void* value)
{
	if (map == NULL)
	{
		return (false);
	}

	if (key == NULL || value == NULL)
	{
		printf("Trying to insert wrong data! %p - %p", key, value);
		return (false);
	}

	// first Check Map Head
	if (map->headNode == NULL)
	{
		// Initialize Zero Head
		MapNode newHead = calloc(1, sizeof(SMapNode));
		if (newHead == NULL)
		{
			printf("Failed to allocate head memory\n");
			return (false);
		}

		newHead->szKey = strdup(key);
		if (newHead->szKey == NULL)
		{
			printf("Failed to allocate head key memory\n");
			free(newHead);
			return (false);
		}

		// assign value
		newHead->pValue = value;
		newHead->pos = 'h';
		map->headNode = newHead;
		map->elementsCount++;

		return (true); // return Here
	}

	// Find the new head location in the map
	MapNode currentNode = map->headNode;
	MapNode parentNode = NULL;
	int cmp = 0;

	while (currentNode != NULL)
	{
		parentNode = currentNode;
		cmp = strcmp(key, currentNode->szKey);
		if (cmp == 0) // keys match, update
		{
			currentNode->pValue = value;
			return (true);
		}
		
		currentNode = cmp > 0 ? currentNode->rightNode : currentNode->leftNode;
	}

	// create new room to insert
	MapNode newNode = calloc(1, sizeof(SMapNode));
	if (newNode == NULL)
	{
		printf("Failed to allocate new node memory\n");
		return (false);
	}

	newNode->szKey = strdup(key);
	if (newNode->szKey == NULL)
	{
		printf("Failed to allocate new node key memory\n");
		free(newNode);
		return (false);
	}

	newNode->pValue = value;
	newNode->parentNode = parentNode;

	// attach node
	if (cmp > 0)
	{
		newNode->pos = 'r';
		parentNode->rightNode = newNode;
	}
	else
	{
		newNode->pos = 'l';
		parentNode->leftNode = newNode;
	}

	map->elementsCount++;

	return (true);
}

void* Map_Find(Map map, char* key)
{
	if (map == NULL)
	{
		return (NULL);
	}

	if (key == NULL)
	{
		printf("Trying to search for wrong data! %p", key);
		return (NULL);
	}

	MapNode currentNode = map->headNode;
	int cmp = 0;

	while (currentNode != NULL)
	{
		cmp = strcmp(key, currentNode->szKey);
		if (cmp == 0) // keys match, update
		{
			return (currentNode->pValue);
		}

		currentNode = cmp > 0 ? currentNode->rightNode : currentNode->leftNode;
	}

	return (NULL);
}

void* Map_FindNode(Map map, char* key)
{
	if (map == NULL)
	{
		return (NULL);
	}

	if (key == NULL)
	{
		printf("Trying to search for wrong data! %p", key);
		return (NULL);
	}

	MapNode currentNode = map->headNode;
	int cmp = 0;

	while (currentNode != NULL)
	{
		cmp = strcmp(key, currentNode->szKey);
		if (cmp == 0) // keys match, update
		{
			return (currentNode);
		}

		currentNode = cmp > 0 ? currentNode->rightNode : currentNode->leftNode;
	}

	return (NULL);
}

void Map_Delete(Map map, char* key)
{
}

void Map_Clear(Map map)
{
	if (map == NULL)
	{
		return;
	}

	Map_ClearRecursive(map, map->headNode);
}

void Map_ClearRecursive(Map map, MapNode node)
{
	if (node == NULL)
	{
		return;
	}

	Map_ClearRecursive(map, node->leftNode);
	Map_ClearRecursive(map, node->rightNode);

	free(node->szKey);
	free(node);
}

