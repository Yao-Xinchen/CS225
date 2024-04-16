/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

Point<3> convertToLAB(HSLAPixel pixel)
{
    Point<3> result(pixel.h / 360, pixel.s, pixel.l);
    return result;
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    using PT = Point<3>;

    // create a vector of points and a map of points to tile images
    vector<PT> points;
    map<PT, int> tile_avg_map;
    for (auto& tile : theTiles)
    {
        const auto avg = tile.getAverageColor();
        auto avgPoint = convertToLAB(avg);
        points.push_back(avgPoint);
        tile_avg_map[avgPoint] = static_cast<int>(&tile - &theTiles[0]);
    }

    auto tree = KDTree<3>(points);
    auto rows = theSource.getRows();
    auto cols = theSource.getColumns();
    auto canvas = new MosaicCanvas(rows, cols);
    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            auto tile = get_match_at_idx(tree, tile_avg_map, theTiles, theSource, row, col);
            canvas->setTile(row, col, tile);
        }
    }
    return canvas;
}

TileImage* get_match_at_idx(const KDTree<3>& tree,
                            map<Point<3>, int> tile_avg_map,
                            vector<TileImage>& theTiles,
                            const SourceImage& theSource, int row,
                            int col)
{
    // Create a tile which accurately represents the source region we'll be
    // using
    HSLAPixel avg = theSource.getRegionColor(row, col);
    Point<3> avgPoint = convertToLAB(avg);
    Point<3> nearestPoint = tree.findNearestNeighbor(avgPoint);

    // Check to ensure the point exists in the map
    map<Point<3>, int>::iterator it = tile_avg_map.find(nearestPoint);
    if (it == tile_avg_map.end())
        cerr << "Didn't find " << avgPoint << " / " << nearestPoint << endl;

    // Find the index
    int index = tile_avg_map[nearestPoint];
    return &theTiles[index];
}
