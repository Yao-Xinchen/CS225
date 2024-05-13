/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

#include <limits>

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    auto min_weight = std::numeric_limits<int>::max();
    Edge min_edge;

    // init all as unvisited
    for (const auto& vertex: graph.getVertices())
        graph.setVertexLabel(vertex, "UNEXPLORED");
    for (const auto& edge: graph.getEdges())
        graph.setEdgeLabel(edge.source, edge.dest, "UNEXPLORED");

    // traverse graph
    for (const auto& vertex: graph.getVertices())
    {
        for (const auto& neighbor: graph.getAdjacent(vertex))
        {
            const auto edge = graph.getEdge(vertex, neighbor);
            if (edge.weight < min_weight)
            {
                min_weight = edge.weight;
                min_edge = edge;
            }
        }
    }

    // label min edge
    graph.setEdgeLabel(min_edge.source, min_edge.dest, "MIN");
    return min_weight;
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    std::unordered_map<Vertex, Vertex> parent;
    std::unordered_map<Vertex, int> distance;
    std::queue<Vertex> to_visit;

    // initialize distance
    for (const auto& vertex: graph.getVertices())
    {
        distance[vertex] = std::numeric_limits<int>::max();
    }

    distance[start] = 0;
    to_visit.push(start);

    // traverse graph
    while (!to_visit.empty())
    {
        auto current = to_visit.front();
        to_visit.pop();

        for (const auto& neighbor: graph.getAdjacent(current))
        {
            if (distance[neighbor] == std::numeric_limits<int>::max())
            {
                distance[neighbor] = distance[current] + 1;
                parent[neighbor] = current;
                to_visit.push(neighbor);
            }
        }
    }

    // label edges
    auto current = end;
    while (current != start)
    {
        graph.setEdgeLabel(current, parent[current], "MINPATH");
        current = parent[current];
    }

    return distance[end];
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    DisjointSets dsets;
    auto edges = graph.getEdges();

    // initialize disjoint sets
    for (const auto& vertex: graph.getVertices())
    {
        dsets.addelements(static_cast<int>(vertex));
    }

    // sort edges
    auto comp = [](const Edge& a, const Edge& b) { return a.weight < b.weight; };
    std::sort(edges.begin(), edges.end(), comp);

    // iterate over edges
    for (const auto& edge: edges)
    {
        auto source = static_cast<int>(edge.source);
        auto dest = static_cast<int>(edge.dest);
        // if the edge doesn't create a cycle
        if (dsets.find(source) != dsets.find(dest))
        {
            dsets.setunion(source, dest);
            graph.setEdgeLabel(source, dest, "MST");
        }
    }
}
