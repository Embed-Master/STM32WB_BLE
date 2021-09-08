#pragma once

#include "Types.h"

class List
{
public:
	struct Node
	{
		struct Node * next;
		struct Node * prev;
	};

	static void removeNode(Node * node);
	static void removeHead(Node * listHead, Node ** node);
	static void insertTail(Node * listHead, Node * node);
	static void insertHead(Node * listHead, Node * node);
	static bool empty(Node * listHead);
	static void initHead(Node *listHead);
};