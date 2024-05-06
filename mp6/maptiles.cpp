/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
#include <thread>

using namespace std;
using color = Point<3>;

extern std::chrono::time_point<std::chrono::system_clock> start;

color convertToLAB(HSLAPixel pixel)
{
    color result(pixel.h / 360, pixel.s, pixel.l);
    return result;
}

void setTiles(const KDTree<3>& tree, map<color, int>& tile_avg_map, vector<TileImage>& theTiles,
    const SourceImage& theSource, MosaicCanvas* canvas, int startRow, int endRow)
{
    for (int row = startRow; row < endRow; ++row)
    {
        for (int col = 0; col < theSource.getColumns(); ++col)
        {
            auto tile = get_match_at_idx(tree, tile_avg_map, theTiles, theSource, row, col);
            canvas->setTile(row, col, tile);
        }
    }
}

MosaicCanvas* mapTiles(const SourceImage& theSource,
    vector<TileImage>& theTiles)
{
    // create a vector of points and a map of points to tile images
    vector<color> tile_colors;
    map<color, int> tile_avg_map; // [tile_color, tile_index]
    for (auto& tile: theTiles)
    {
        const auto avg = tile.getAverageColor();
        auto avg_color = convertToLAB(avg);
        tile_colors.push_back(avg_color);
        tile_avg_map[avg_color] = static_cast<int>(&tile - &theTiles[0]);
    }

    auto calc_avg_end = std::chrono::system_clock::now();
    cout << "Calc avg end: " << std::chrono::duration_cast<std::chrono::seconds>(calc_avg_end - start).count() << endl;

    auto tree = KDTree<3>(tile_colors);
    auto rows = theSource.getRows();
    auto cols = theSource.getColumns();
    auto canvas = new MosaicCanvas(rows, cols);
    vector<thread> threads;
    size_t numThreads = std::thread::hardware_concurrency();
    size_t chunkSize = theSource.getRows() / numThreads;
    for (size_t i = 0; i < numThreads; ++i)
    {
        size_t startRow = i * chunkSize;
        size_t endRow = (i == numThreads - 1) ? theSource.getRows() : startRow + chunkSize;
        threads.emplace_back(setTiles, ref(tree), ref(tile_avg_map), ref(theTiles), ref(theSource), canvas, startRow,
            endRow);
    }
    for (auto& th: threads) th.join();

    auto set_tile_end = std::chrono::system_clock::now();
    cout << "Set tile end: " << std::chrono::duration_cast<std::chrono::seconds>(set_tile_end - start).count() << endl;

    return canvas;
}

TileImage* get_match_at_idx(const KDTree<3>& tree,
    map<color, int>& tile_avg_map,
    vector<TileImage>& theTiles,
    const SourceImage& theSource,
    int row, int col)
{
    // Create a tile which accurately represents the source region we'll be
    // using
    HSLAPixel avg = theSource.getRegionColor(row, col);
    color region_avg = convertToLAB(avg);
    color nearestPoint = tree.findNearestNeighbor(region_avg);

    // Check to ensure the point exists in the map
    const auto it = tile_avg_map.find(nearestPoint);
    if (it == tile_avg_map.end())
        cerr << "Didn't find " << region_avg << " / " << nearestPoint << endl;

    // Find the index
    int index = tile_avg_map[nearestPoint];
    return &theTiles[index];
}
