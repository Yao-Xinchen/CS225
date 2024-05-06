/**
 * @file mosaiccanvas.h
 */

#include <iostream>
#include <sys/stat.h>
#include <errno.h>
#include <cstdlib>
#include <thread>

#include "mosaiccanvas.h"
#include "util/util.h"

using namespace std;
using namespace util;

bool MosaicCanvas::enableOutput = false;

/**
 * Constructor.
 *
 * @param theRows Number of rows to divide the canvas into
 * @param theColumns Number of columns to divide the canvas into
 */
MosaicCanvas::MosaicCanvas(int theRows, int theColumns)
    : rows(theRows), columns(theColumns)
{
    // if ((theRows < 1) || (theColumns < 1)) {
    //     cerr << "Error: Cannot set non-positive rows or columns" << endl;
    //     exit(-1);
    // }

    myImages.resize(rows * columns);
}

/**
 * Retrieve the number of rows of images
 *
 * @return The number or rows in the mosaic, or -1 on error
 */
int MosaicCanvas::getRows() const
{
    return rows;
}

/**
 * Retrieve the number of columns of images
 *
 * @return The number of columns in the mosaic, or -1 or error
 */
int MosaicCanvas::getColumns() const
{
    return columns;
}

void MosaicCanvas::setTile(int row, int column, TileImage* i)
{
    // if (enableOutput) {
    //     cerr << "\rPopulating Mosaic: setting tile ("
    //          << row << ", " << column
    //          << ")" << string(20, ' ') << "\r";
    //     cerr.flush();
    // }
    myImages[row * columns + column] = i;
}

const TileImage& MosaicCanvas::getTile(int row, int column)
{
    return images(row, column);
}

// Function to be run on each thread
void MosaicCanvas::drawTiles(PNG& mosaic, int startRow, int endRow,
    int width, int height,
    int columns, int rows,
    bool enableOutput)
{
    for (int row = startRow; row < endRow; ++row)
    {
        if (enableOutput)
        {
            cerr << "\rDrawing Mosaic: resizing tiles ("
                    << (row * columns + 1) << "/" << (rows * columns)
                    << ")" << string(20, ' ') << "\r";
            cerr.flush();
        }
        for (int col = 0; col < columns; ++col)
        {
            int startX = divide(width * col, columns);
            int endX = divide(width * (col + 1), columns);
            int startY = divide(height * row, rows);
            int endY = divide(height * (row + 1), rows);

            if (endX - startX != endY - startY)
                cerr << "Error: resolution not constant: x: " << (endX - startX)
                        << " y: " << (endY - startY) << endl;

            images(row, col).paste(mosaic, startX, startY, endX - startX);
        }
    }
}

PNG MosaicCanvas::drawMosaic(int pixelsPerTile)
{
    if (pixelsPerTile <= 0)
    {
        cerr << "ERROR: pixelsPerTile must be > 0" << endl;
        exit(-1);
    }

    int width = columns * pixelsPerTile;
    int height = rows * pixelsPerTile;

    // Create the image
    PNG mosaic(width, height);

    // Create list of drawable tiles
    vector<thread> threads;
    size_t numThreads = std::thread::hardware_concurrency();
    size_t chunkSize = rows / numThreads;

    for (size_t i = 0; i < numThreads; ++i)
    {
        size_t startRow = i * chunkSize;
        size_t endRow = (i == numThreads - 1) ? rows : startRow + chunkSize;
        threads.emplace_back([this, &mosaic, startRow, endRow, width, height] {
            this->drawTiles(mosaic, startRow, endRow, width, height, columns, rows, enableOutput);
        });
    }
    for (auto& th: threads) th.join();

    if (enableOutput)
    {
        cerr << "\r" << string(60, ' ');
        cerr << "\rDrawing Mosaic: resizing tiles ("
                << (rows * columns) << "/" << (rows * columns) << ")" << endl;
        cerr.flush();
    }

    return mosaic;
}
