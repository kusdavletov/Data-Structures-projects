#include "minheap.h"

/**
 * Assignment 5 for CSE221 Data Structures
 *
 * 2015. 11. 2
 *
 */


// Destructor
MinHeap::~MinHeap()
{
    if (heapArray != NULL)
    delete[] heapArray;
    if (mapVidxToArray != NULL)
    delete[] mapVidxToArray;
}

void
MinHeap::PushUp(unsigned int k)
{
    while (k > 1 && heapArray[k >> 1] > heapArray[k])
    {
        std :: swap (mapVidxToArray[heapArray[k >> 1].vidx], mapVidxToArray[heapArray[k].vidx]);
        std :: swap (heapArray[k >> 1], heapArray[k]);
        k >>= 1;
    }
}

void
MinHeap::PushDown(unsigned int k)
{
    k <<= 1;
    while (k <= size)
    {
        if (k < size && heapArray[k ^ 1] < heapArray[k]) k ^= 1;
        if (heapArray[k] >= heapArray[k >> 1]) break;
        std :: swap (mapVidxToArray[heapArray[k >> 1].vidx], mapVidxToArray[heapArray[k].vidx]);
        std :: swap (heapArray[k >> 1], heapArray[k]);
        k <<= 1;
    }
}

void
MinHeap::Push(const heapElem& e)
{
	heapArray[++size] = e;
	mapVidxToArray[e.vidx] = size;
	PushUp (size);
}

const heapElem &
MinHeap::Top()
{
	return heapArray[1];
}

void
MinHeap::Pop()
{
	std :: swap (mapVidxToArray[heapArray[1].vidx], mapVidxToArray[heapArray[size].vidx]);
    std :: swap (heapArray[1], heapArray[size]);
    --size;
    PushDown (1);
}

void MinHeap::Modify(const heapElem& e)
{
    unsigned int k = mapVidxToArray[e.vidx];
    heapArray[k] = e;
    PushDown (k);
    PushUp (k);
}

bool MinHeap::IsEmpty()
{
	return (size == 0);
}

bool MinHeap::NotEmpty()
{
    return (size != 0);
}
