/*
 * @Author: ccysam
 * @E-Mail: ccysam@hotmail.com
 * @Date: 2022-12-14 00:12:22
 * @LastEditTime: 2022-12-19 16:04:40
 * @Description:  Algorithm Part of the Curriculum Design
 * @Copyright: Copyright (c) 2022 by ccysam, All Rights Reserved.
 */
#include "Prim.h"
namespace Prim
{
    Graph::Graph(int V)
    {
        this->V = V;
        adj = new std::list<int_pair>[V];
    }

    void Graph::addEdge(int start, int end, int weight)
    {
        adj[start].push_back(std::make_pair(end, weight));
        adj[end].push_back(std::make_pair(start, weight));
    }

    Graph2Show Graph::getGraph()
    {
        Graph2Show r(this->V, this->E);
        std::vector<std::pair<int_pair, float>> paths;
        return r;
    }

    MST Graph::Prim()
    {
        MST r(V, E);

        std::priority_queue<int_pair, std::vector<int_pair>, std::greater<int_pair>> pq;

        int src = 0;

        std::vector<int> key(V, INF);

        std::vector<int> parent(V, -1);

        std::vector<bool> inMST(V, false);

        pq.push(std::make_pair(0, src));
        key[src] = 0;

        while (!pq.empty())
        {
            int u = pq.top().second;
            pq.pop();

            if (inMST[u] == true)
            {
                continue;
            }

            inMST[u] = true;

            std::list<int_pair>::iterator it;
            for (it = adj[u].begin(); it != adj[u].end(); it++)
            {
                int v = (*it).first;
                int weight = (*it).second;
                if (inMST[v] == false && key[v] > weight)
                {
                    key[v] = weight;
                    pq.push(std::make_pair(key[v], v));
                    parent[v] = u;
                }
            }
        }

        for (int i = 1; i < V; i++)
        {
            r.Paths.push_back({{parent[i], i}, 0.1f});
        }

        return r;
    }

    Algorithm::Algorithm(int v, int e)
    {
        graph = Graph(v);
        g2s = Result(v, e);
    }

    void Algorithm::setGraph(Graph graph)
    {
        this->graph = graph;
    }

    void Algorithm::addEdge(int start, int end, int weight)
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
        mst = graph.Prim();
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