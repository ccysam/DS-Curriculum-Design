/*
 * @Author: ccysam
 * @E-Mail: ccysam@hotmail.com
 * @Date: 2022-12-13 22:24:38
 * @LastEditTime: 2022-12-19 16:08:47
 * @Description: Algorithm Part of the Curriculum Design
 * @Copyright: Copyright (c) 2022 by ccysam, All Rights Reserved.
 */

#include "Kruskal.h"

namespace Kruskal
{
    Graph::Graph(int V, int E)
    {
        this->V = V;
        this->E = E;
        weight = 0.0;
    }

    void Graph::addEdge(int start, int end, float weight)
    {
        edges.push_back({weight, {start, end}});
        this->weight += weight;
    }

    Graph2Show Graph::getGraph()
    {
        Graph2Show r(this->V, this->E);
        std::vector<std::pair<int_pair, float>> paths;
        std::vector<std::pair<float, int_pair>>::iterator it;
        for (it = edges.begin(); it != edges.end(); it++)
        {
            paths.push_back({it->second, it->first});
        }
        r.setPaths(paths);
        r.Weight = weight;
        return r;
    }

    MST Graph::kruskalMST()
    {
        // The Result

        MST r(V, E);
        float mst_wt = 0;

        // Sort all edges
        sort(edges.begin(), edges.end());

        // Create disjoint sets
        DisjointSets ds(V);

        // Iterate through all edges
        std::vector<std::pair<float, int_pair>>::iterator it;
        for (it = edges.begin(); it != edges.end(); it++)
        {
            int u = it->second.first;
            int v = it->second.second;

            int set_u = ds.find(u);
            int set_v = ds.find(v);

            // Avoid to create Cycle
            if (set_u != set_v)
            {
                // Add to the Result MST
                r.Paths.push_back({{u, v}, it->first});

                // Update the MST weight
                mst_wt += it->first;

                // Merge two sets
                ds.merge(set_u, set_v);
            }
        }
        r.Weight = mst_wt;
        return r;
    }

    DisjointSets::DisjointSets(int n)
    {
        // Allocate memory
        this->n = n;
        parent = new int[n + 1];
        rnk = new int[n + 1];

        // Initialize the disjoint sets with rank 0
        for (int i = 0; i <= n; i++)
        {
            rnk[i] = 0;
            parent[i] = i;
        }
    }

    int DisjointSets::find(int x)
    {
        // Make the parent of the node in the path from x --> parent[x] point to parent[x]
        if (x != parent[x])
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void DisjointSets::merge(int x, int y)
    {
        x = find(x);
        y = find(y);

        // Make sure trees are smallest
        if (rnk[x] > rnk[y])
        {
            parent[y] = x;
        }
        else
        {
            parent[x] = y;
        }
        if (rnk[x] == rnk[y])
        {
            rnk[y]++;
        }
    }

    Algorithm::Algorithm(int v, int e)
    {
        graph = Graph(v, e);
        g2s = Result(v, e);
    }

    void Algorithm::setGraph(Graph graph)
    {
        this->graph = graph;
    }

    void Algorithm::addEdge(int start, int end, float weight)
    {
        this->graph.addEdge(start, end, weight);
    }

    Graph Algorithm::getGraph()
    {
        return graph;
    }

    MST Algorithm::getResult()
    {
        float start = clock();
        mst = graph.kruskalMST();
        float end = clock();
        time_spend = end - start;
        return mst;
    }

    Graph2Show Algorithm::showGraph()
    {
        g2s = graph.getGraph();
        return g2s;
    }

}