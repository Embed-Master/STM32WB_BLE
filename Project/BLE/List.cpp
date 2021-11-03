#include "List.hpp"
#include "CoreSettings.h"

void List::removeNode(Node * node)
{
	uint primask_bit = __get_PRIMASK();// backup PRIMASK bit
	__disable_irq();// Disable all interrupts by setting PRIMASK bit on Cortex
	(node->prev)->next = node->next;
	(node->next)->prev = node->prev;
	__set_PRIMASK(primask_bit);// Restore PRIMASK bit
}

void List::removeHead(Node * listHead, Node ** node)
{
	uint primask_bit = __get_PRIMASK();// backup PRIMASK bit
	__disable_irq();// Disable all interrupts by setting PRIMASK bit on Cortex
	*node = listHead->next;
	removeNode(listHead->next);
	__set_PRIMASK(primask_bit);// Restore PRIMASK bit
}

void List::insertTail(Node * listHead, Node * node)
{
	uint primask_bit = __get_PRIMASK();// backup PRIMASK bit
	__disable_irq();// Disable all interrupts by setting PRIMASK bit on Cortex
	node->next = listHead;
	node->prev = listHead->prev;
	listHead->prev = node;
	(node->prev)->next = node;
	__set_PRIMASK(primask_bit);// Restore PRIMASK bit
}

void List::insertHead(Node * listHead, Node * node)
{
	uint primask_bit = __get_PRIMASK();// backup PRIMASK bit
	__disable_irq();// Disable all interrupts by setting PRIMASK bit on Cortex
	node->next = listHead->next;
	node->prev = listHead;
	listHead->next = node;
	(node->next)->prev = node;
	__set_PRIMASK(primask_bit);// Restore PRIMASK bit
}

bool List::empty(Node * listHead)
{
	uint primask_bit = __get_PRIMASK();// backup PRIMASK bit
	__disable_irq();// Disable all interrupts by setting PRIMASK bit on Cortex
	bool result = listHead->next == listHead;
	__set_PRIMASK(primask_bit);// Restore PRIMASK bit
	return result;
}

void List::initHead(Node *listHead)
{
	listHead->next = listHead;
	listHead->prev = listHead;
}