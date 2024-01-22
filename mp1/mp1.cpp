#include "cs225/PNG.h"
#include <string>

void rotate(std::string inputFile, std::string outputFile)
{
    auto input_image = cs225::PNG();
    input_image.readFromFile(inputFile);
    auto output_image = cs225::PNG(input_image.width(), input_image.height());

    const auto width = static_cast<int>(input_image.width());
    const auto height = static_cast<int>(input_image.height());

    for (auto x = 0; x < width; x++)
    {
        for (auto y = 0; y < height; y++)
        {
            const auto input = input_image.getPixel(x, y);
            const auto output = output_image.getPixel(width - x - 1, height - y - 1);
            *output = *input;
        }
    }

    output_image.writeToFile(outputFile);
}
