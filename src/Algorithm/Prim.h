/*
 * @Author: ccysam
 * @E-Mail: ccysam@hotmail.com
 * @Date: 2022-12-14 00:12:17
 * @LastEditTime: 2022-12-19 16:04:19
 * @Description:
 * @Copyright: Copyright (c) ${now_year} by ccysam, All Rights Reserved.
 */

#pragma once
#ifndef __PRIM_H__
#define __PRIM_H__

#include "Algorithm.h"
#include <algorithm>
#include <list>
#include <queue>

#define INF 65536

namespace Prim
{
    using namespace Algorithm;

    typedef struct Graph
    {
        int V, E;

        std::list<int_pair> *adj;

        Graph() {}

        Graph(int V);

        void addEdge(int start, int end, int weight);

        Graph2Show getGraph();

        MST Prim();
    } Graph;

    class Algorithm
    {
    private:
        Graph graph;
        MST mst;
        Graph2Show g2s;

    public:
        float time_spend = 0.0f;

        Algorithm(int v, int e);

        void setGraph(Graph graph);

        void addEdge(int start, int end, int weight);

        Graph getGraph();

        MST getResult();

        Graph2Show showGraph();
    };

} // namespace Prim

#endif