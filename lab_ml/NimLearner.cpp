#include "NimLearner.h"


/**
 * Constructor to create a game of Nim with `startingTokens` starting tokens.
 *
 * This function creates a graph, `g_` representing all of the states of a
 * game of Nim with vertex labels "p#-X", where:
 * - # is the current player's turn; p1 for Player 1, p2 for Player2
 * - X is the tokens remaining at the start of a player's turn
 *
 * For example:
 *   "p1-4" is Player 1's turn with four (4) tokens remaining
 *   "p2-8" is Player 2's turn with eight (8) tokens remaining
 *
 * All legal moves between states are created as edges with initial weights
 * of 0.
 *
 * @param startingTokens The number of starting tokens in the game of Nim.
 */
NimLearner::NimLearner(unsigned startingTokens) : g_(true)
{
    len = startingTokens;

    // create vertices
    for (uint i = 0; i <= startingTokens; i++)
    {
        auto p1 = g_.insertVertex("p1-" + std::to_string(i));
        auto p2 = g_.insertVertex("p2-" + std::to_string(i));
        p1s.push_back(p1);
        p2s.push_back(p2);
    }
    startingVertex_ = p1s[startingTokens];

    // create edges
    for (uint i = 1; i <= startingTokens; i++)
    { // p1-i to p2-(i-1)
        g_.insertEdge(p1s[i], p2s[i - 1]);
        g_.setEdgeWeight(p1s[i], p2s[i - 1], 0);
    }
    for (uint i = 2; i <= startingTokens; i++)
    { // p1-i to p2-(i-2)
        g_.insertEdge(p1s[i], p2s[i - 2]);
        g_.setEdgeWeight(p1s[i], p2s[i - 2], 0);
    }
    for (uint i = 1; i <= startingTokens; i++)
    { // p2-i to p1-(i-1)
        g_.insertEdge(p2s[i], p1s[i - 1]);
        g_.setEdgeWeight(p2s[i], p1s[i - 1], 0);
    }
    for (uint i = 2; i <= startingTokens; i++)
    { // p2-i to p1-(i-2)
        g_.insertEdge(p2s[i], p1s[i - 2]);
        g_.setEdgeWeight(p2s[i], p1s[i - 2], 0);
    }
}

/**
 * Plays a random game of Nim, returning the path through the state graph
 * as a vector of `Edge` classes.  The `origin` of the first `Edge` must be
 * the vertex with the label "p1-#", where # is the number of starting
 * tokens.  (For example, in a 10 token game, result[0].origin must be the
 * vertex "p1-10".)
 *
 * @returns A random path through the state space graph.
 */
std::vector<Edge> NimLearner::playRandomGame() const
{
    std::vector<Edge> path;
    Vertex currentVertex = startingVertex_;
    while (true)
    {
        auto neighbors = g_.getAdjacent(currentVertex);
        if (neighbors.empty()) break;
        auto next = neighbors[rand() % neighbors.size()];
        path.push_back(g_.getEdge(currentVertex, next));
        currentVertex = next;
    }
    return path;
}


/*
 * Updates the edge weights on the graph based on a path through the state
 * tree.
 *
 * If the `path` has Player 1 winning (eg: the last vertex in the path goes
 * to Player 2 with no tokens remaining, or "p2-0", meaning that Player 1
 * took the last token), then all choices made by Player 1 (edges where
 * Player 1 is the source vertex) are rewarded by increasing the edge weight
 * by 1 and all choices made by Player 2 are punished by changing the edge
 * weight by -1.
 *
 * Likewise, if the `path` has Player 2 winning, Player 2 choices are
 * rewarded and Player 1 choices are punished.
 *
 * @param path A path through the a game of Nim to learn.
 */
void NimLearner::updateEdgeWeights(const std::vector<Edge>& path)
{
    const auto winner = path.back().dest;
    // if player 1 wins, reward player 1 and punish player 2
    auto reward = g_.getVertexLabel(winner)[1] == '2' ? 1 : -1;
    for (const auto& edge : path)
    {
        const auto weight = g_.getEdgeWeight(edge.source, edge.dest);
        g_.setEdgeWeight(edge.source, edge.dest, weight + reward);
        reward *= -1;
    }
}


/**
 * Returns a constant reference to the state space graph.
 *
 * @returns A constant reference to the state space graph.
 */
const Graph& NimLearner::getGraph() const
{
    return g_;
}
