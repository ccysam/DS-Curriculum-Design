/*
 * @Author: ccysam
 * @E-Mail: ccysam@hotmail.com
 * @Date: 2022-12-13 22:10:20
 * @LastEditTime: 2022-12-19 16:08:03
 * @Description: Header file of the Algorithm Part of the Curriculum Design
 * @Copyright: Copyright (c) 2022 by ccysam, All Rights Reserved.
 */

#pragma once
#ifndef __KRSK_H_
#define __KRSK_H_

#include "Algorithm.h"
#include <algorithm>

namespace Kruskal
{
    using namespace Algorithm;

    // Structure of Graph
    typedef struct Graph
    {
        int V, E;
        float weight;
        std::vector<std::pair<float, int_pair>> edges;

        Graph() {}

        // Constructor
        Graph(int V, int E);

        // Functions

        // Add an edge to the graph
        void addEdge(int start, int end, float weight);

        // Get the show graph of this graph
        Graph2Show getGraph();

        // Function to find MST using Kurskal's MST algorithm
        MST kruskalMST();

    } Graph;

    // Structure of Disjoint Sets
    typedef struct DisjointSets
    {
        int *parent, *rnk;
        int n;

        // Constructor
        DisjointSets(int n);

        // Functions

        // Find the parent of a node 'x'
        // Path Compression
        int find(int x);

        // Union bt rank
        void merge(int x, int y);
    } DisjointSets;

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

        void addEdge(int start, int end, float weight);

        Graph getGraph();

        MST getResult();

        Graph2Show showGraph();
    };
} // namespace Kruskal

#endif