#include <stdlib.h>
#include "linkedlist.h"

void addLast(void * pData, struct element ** pHead, struct element ** pTail)
{
	struct element * pNewElement = (struct element *) malloc (sizeof(struct element));
	pNewElement->pData = pData;
	pNewElement->pNext = NULL;
	// printf("fkyou\n");	
	if((*pHead) == NULL)
	{
		// printf("you r supposed to be here jackass.\n");
		pNewElement->pNext = (*pHead);
		(*pTail) = (*pHead) = pNewElement;
	}
	else 
	{
		// printf("you in the wrong block dickhead\n");
		pNewElement->pNext = NULL;
		(*pTail)->pNext = pNewElement;
		(*pTail) = pNewElement;
	}
}

void addFirst(void * pData, struct element ** pHead, struct element ** pTail)
{
	struct element * pNewElement = (struct element *) malloc (sizeof(struct element));
	pNewElement->pData = pData;
	pNewElement->pNext = NULL;
	
	if((*pHead) == NULL)
	{	
		pNewElement->pNext = (*pHead);
		(*pTail) = (*pHead) = pNewElement;
	}
	else 
	{
		pNewElement->pNext = (*pHead);
		(*pHead) = pNewElement;
	}
}

void * removeFirst(struct element ** pHead, struct element ** pTail)
{
	void * pData = NULL;
	struct element * pTemp = NULL;
	if((*pHead) != NULL)
	{
		pTemp = (*pHead);
		(*pHead) = (*pHead)->pNext;
		if((*pHead) == NULL)
			(*pTail) = NULL;
		pData =  pTemp->pData;
		free(pTemp);
	}
	return pData;
}
