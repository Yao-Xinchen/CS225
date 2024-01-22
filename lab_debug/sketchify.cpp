#include <cstdlib>
#include <cmath>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
using namespace cs225;

// sets up the output image
PNG* setupOutput(const unsigned w, const unsigned h)
{
    const auto image = new PNG(w, h);
    return image;
}

// Returns my favorite color
HSLAPixel* myFavoriteColor(double saturation)
{
    const auto pixel = new HSLAPixel(280, saturation, 0.5); // hue can be changed
    return pixel;
}

void sketchify(std::string inputFile, std::string outputFile)
{
    // Load in.png
    const auto original = new PNG();

    original->readFromFile(inputFile);
    const unsigned width = original->width();
    const unsigned height = original->height();

    // Create out.png
    PNG* output = setupOutput(width, height);

    // Load our favorite color to color the outline
    const auto myPixel = myFavoriteColor(0.75); // saturation can be changed

    // Go over the whole image, and if a pixel differs from that to its upper
    // left, color it my favorite color in the output
    for (unsigned y = 1; y < height; y++)
    {
        for (unsigned x = 1; x < width; x++)
        {
            // Calculate the pixel difference
            const auto prev = original->getPixel(x - 1, y - 1);
            const auto curr = original->getPixel(x, y);
            const double diff = std::fabs(curr->h - prev->h);

            // If the pixel is an edge pixel,
            // color the output pixel with my favorite color
            HSLAPixel* currOutPixel = output->getPixel(x, y);
            if (diff > 20)
            {
                *currOutPixel = *myPixel;
            }
        }
    }

    // Save the output file
    output->writeToFile(outputFile);

    // Clean up memory
    delete myPixel;
    delete output;
    delete original;
}
