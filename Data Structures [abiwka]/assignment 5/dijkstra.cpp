# include "dijkstra.h"
# include <iostream>
# include <cstdlib>
# include <cstdio>
/**
  * Assignment 5 for CSE221 Data Structures
  *
  * 2015. 11. 2
  *
  */

Dijkstra::~Dijkstra()
{
    if (u != NULL)
    delete[] u;
    if (d != NULL)
    delete[] d;
    if (p != NULL)
    delete[] p;
    if (mheap != NULL)
    delete mheap;
    if (u != NULL)
    delete[] adjList;
}

void
Dijkstra::ReadGraph(const char* file)
{
    int from, to;
    double cost;

    std :: freopen 	(file, "r", stdin);
    std :: cin >> N >> M;

    adjList = new graphNode    [N];
      mheap = new MinHeap      (N);
          p = new unsigned int [N];
          d = new double       [N];
          u = new bool         [N];

    for (int i = 0; i < M; ++i)
    {
        std :: cin >> from >> to >> cost;
        adjList[from].link = new graphNode (to, cost, adjList[from].link);
    }
}

double
Dijkstra::FindPath(const unsigned int v0, const unsigned int v1)
{
    for (int i = 0; i < N; ++i)
    {
        d[i] = 0.0;
        p[i] = 0;
        u[i] = false;
    }

    u[v0] = true;
    mheap -> Push (heapElem (v0, d[v0]));
    int from, to;
    double cost;

    while (mheap -> NotEmpty ())
    {
        from = mheap -> Top ().vidx;

        if (from == v1) break;

        mheap -> Pop ();

        for (graphNode *i = adjList[from].link; i != 0; i = i -> link)
        {
            to = i -> idx;
            cost = i -> weight;
            if (!u[to] || d[to] > d[from] + cost)
            {
                if (mheap -> IsInHeap (heapElem (to, d[to])))
                    mheap -> Modify (heapElem (to, d[from] + cost));
                else
                    mheap -> Push (heapElem (to, d[from] + cost));

                d[to] = d[from] + cost;
                p[to] = from;
                u[to] = true;
            }
        }
    }

    if (!u[v1])
    {
        std :: cout << "no path\n";
        return 0.0;
    }

    int *path = new int [N], n = 0;

    for (int v = v1; v != v0; v = p[v])
        path[n++] = v;

    std :: cout << v0;
    for (int i = n - 1; i >= 0; --i)
        std :: cout << ',' << path[i];
    std :: cout << "\n";

    return d[v1];
}
