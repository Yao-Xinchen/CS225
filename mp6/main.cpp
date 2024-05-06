#include <iostream>
#include <set>
#include <vector>

#include "cs225/PNG.h"
#include "maptiles.h"
#include "mosaiccanvas.h"
#include "sourceimage.h"
#include "util/util.h"

#include <thread>
#include <mutex>

using namespace std;
using namespace util;
using namespace cs225;

void makePhotoMosaic(const string& inFile, const string& tileDir, int numTiles,
    int pixelsPerTile, const string& outFile);

vector<TileImage> getTiles(string tileDir);

bool hasImageExtension(const string& fileName);

namespace opts
{
    bool help = false;
}

chrono::time_point<chrono::system_clock> start;

int main(int argc, const char** argv)
{
    start = std::chrono::system_clock::now();

    string inFile = "";
    string tileDir = "mp5_pngs/";
    string numTilesStr = "100";
    string pixelsPerTileStr = "50";
    string outFile = "mosaic.png";

    OptionsParser optsparse;
    optsparse.addArg(inFile);
    optsparse.addArg(tileDir);
    optsparse.addArg(numTilesStr);
    optsparse.addArg(pixelsPerTileStr);
    optsparse.addArg(outFile);
    optsparse.addOption("help", opts::help);
    optsparse.addOption("h", opts::help);
    optsparse.parse(argc, argv);
    auto parse_end = std::chrono::system_clock::now();
    cout << "Parse end: " << std::chrono::duration_cast<std::chrono::seconds>(parse_end - start).count() << endl;

    if (opts::help)
    {
        cout << "Usage: " << argv[0]
                << " background_image.png tile_directory/ [number of tiles] "
                "[pixels per tile] [output_image.png]"
                << endl;
        return 0;
    }

    if (inFile == "")
    {
        cout << "Usage: " << argv[0]
                << " background_image.png tile_directory/ [number of tiles] "
                "[pixels per tile] [output_image.png]"
                << endl;
        return 1;
    }

    auto mosaic_start = std::chrono::system_clock::now();
    cout << "Mosaic start: " << std::chrono::duration_cast<std::chrono::seconds>(mosaic_start - start).count() << endl;
    makePhotoMosaic(inFile, tileDir, lexical_cast<int>(numTilesStr),
        lexical_cast<int>(pixelsPerTileStr), outFile);
    auto mosaic_end = std::chrono::system_clock::now();
    cout << "Mosaic end: " << std::chrono::duration_cast<std::chrono::seconds>(mosaic_end - start).count() <<
            endl;

    auto end = std::chrono::system_clock::now();
    auto elapsed_seconds = end - start;
    cout << "Elapsed time: " << std::chrono::duration_cast<std::chrono::seconds>(elapsed_seconds).count() << "s" <<
            endl;
    return 0;
}

void makePhotoMosaic(const string& inFile, const string& tileDir, int numTiles,
    int pixelsPerTile, const string& outFile)
{
    PNG inImage;
    inImage.readFromFile(inFile);
    SourceImage source(inImage, numTiles);
    vector<TileImage> tiles = getTiles(tileDir);

    auto tile_end = std::chrono::system_clock::now();
    cout << "Tile end: " << std::chrono::duration_cast<std::chrono::seconds>(tile_end - start).count() << endl;

    if (tiles.empty())
    {
        cerr << "ERROR: No tile images found in " << tileDir << endl;
        exit(2);
    }

    MosaicCanvas::enableOutput = true;
    MosaicCanvas* mosaic = mapTiles(source, tiles);
    // cerr << endl;

    auto map_end = std::chrono::system_clock::now();
    cout << "Map end: " << std::chrono::duration_cast<std::chrono::seconds>(map_end - start).count() << endl;

    if (mosaic == NULL)
    {
        cerr << "ERROR: Mosaic generation failed" << endl;
        exit(3);
    }

    PNG result = mosaic->drawMosaic(pixelsPerTile);
    cerr << "Saving Output Image... " << endl;
    auto draw_end = std::chrono::system_clock::now();
    cout << "Draw end: " << std::chrono::duration_cast<std::chrono::seconds>(draw_end - start).count() << endl;
    result.writeToFile(outFile);
    cerr << "Done" << endl;
    delete mosaic;
    auto save_end = std::chrono::system_clock::now();
    cout << "Save end: " << std::chrono::duration_cast<std::chrono::seconds>(save_end - start).count() << endl;
}

std::mutex mtx; // mutex for critical section

// Function to be run on each thread
void loadImages(const vector<string>& imageFiles, size_t start, size_t end,
    vector<TileImage>& images, set<HSLAPixel>& avgColors)
{
    for (size_t i = start; i < end; ++i)
    {
        cerr << "\rLoading Tile Images... ("
                << (i + 1) << "/" << imageFiles.size()
                << ")" << string(20, ' ') << "\r";
        cerr.flush();
        PNG png;
        png.readFromFile(imageFiles.at(i));
        TileImage next(png);
        mtx.lock(); // entering critical section
        if (avgColors.count(next.getAverageColor()) == 0)
        {
            avgColors.insert(next.getAverageColor());
            images.push_back(next);
        }
        mtx.unlock(); // leaving critical section
    }
}

vector<TileImage> getTiles(string tileDir)
{
#if 1
    if (tileDir[tileDir.length() - 1] != '/')
        tileDir += '/';

    vector<string> allFiles = get_files_in_dir(tileDir);
    sort(allFiles.begin(), allFiles.end());

    vector<string> imageFiles;
    imageFiles.reserve(allFiles.size());
    for (size_t i = 0; i < allFiles.size(); i++)
        if (hasImageExtension(allFiles[i]))
            imageFiles.push_back(allFiles[i]);

    vector<TileImage> images;
    set<HSLAPixel> avgColors;
    vector<thread> threads;
    size_t numThreads = std::thread::hardware_concurrency();
    size_t chunkSize = imageFiles.size() / numThreads;

    for (size_t i = 0; i < numThreads; ++i)
    {
        size_t start = i * chunkSize;
        size_t end = (i == numThreads - 1) ? imageFiles.size() : start + chunkSize;
        threads.emplace_back(loadImages, ref(imageFiles), start, end, ref(images), ref(avgColors));
    }
    for (auto& th: threads) th.join();

    cerr << "\rLoading Tile Images... ("
            << imageFiles.size() << "/" << imageFiles.size()
            << ")";
    cerr << "... " << images.size() << " unique images loaded" << endl;
    cerr.flush();

    return images;
#else
    PNG temp;
    vector<TileImage> tiles;
    *temp(0, 0) = RGBAPixel(0,   0,   0);   tiles.push_back(TileImage(temp));
    *temp(0, 0) = RGBAPixel(0,   0,   127); tiles.push_back(TileImage(temp));
    *temp(0, 0) = RGBAPixel(0,   0,   255); tiles.push_back(TileImage(temp));
    *temp(0, 0) = RGBAPixel(0,   127, 0);   tiles.push_back(TileImage(temp));
    *temp(0, 0) = RGBAPixel(0,   255, 0);   tiles.push_back(TileImage(temp));
    *temp(0, 0) = RGBAPixel(127, 0,   0);   tiles.push_back(TileImage(temp));
    *temp(0, 0) = RGBAPixel(255, 0,   0);   tiles.push_back(TileImage(temp));
    *temp(0, 0) = RGBAPixel(0,   127, 127); tiles.push_back(TileImage(temp));
    *temp(0, 0) = RGBAPixel(0,   255, 255); tiles.push_back(TileImage(temp));
    *temp(0, 0) = RGBAPixel(127, 0,   127); tiles.push_back(TileImage(temp));
    *temp(0, 0) = RGBAPixel(255, 0,   255); tiles.push_back(TileImage(temp));
    *temp(0, 0) = RGBAPixel(127, 127, 0);   tiles.push_back(TileImage(temp));
    *temp(0, 0) = RGBAPixel(255, 255, 0);   tiles.push_back(TileImage(temp));
    return tiles;
#endif
}

bool hasImageExtension(const string& fileName)
{
    size_t dotpos = fileName.find_last_of(".");
    if (dotpos == string::npos)
        return false;
    string ext = toLower(fileName.substr(dotpos + 1));
    return (ext == "bmp" || ext == "png" || ext == "jpg" || ext == "gif"
            || ext == "tiff");
}
