#include "dijkstra.h"
#include "heap.h"

void dijkstra(const WDigraph &graph, int startVertex, unordered_map<int, PIL> &tree)
{
    BinaryHeap<PIL, long long> events;
    events.insert(PIL(startVertex, startVertex), 0);
    while(events.size() > 0)
    {
        HeapItem<PIL, long long> node = events.min();
        events.popMin();
        long long v = node.item.second;
        if(tree.find(v) == tree.end())
        {
            tree[v] = node.item;
            for (auto iter = graph.neighbours(v); iter != graph.endIterator(v); iter++)
            {
                long long w = *iter;
                PIL next = PIL(v, w);
                long long cost = node.key + graph.getCost(v, w);
                events.insert(next, cost);
            }
        }

    }
}
