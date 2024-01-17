#include <iostream>
#include <cmath>
#include <cstdlib>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "lab_intro.h"

using namespace cs225;

/**
 * Returns an image that has been transformed to grayscale.
 *
 * The saturation of every pixel is set to 0, removing any color.
 *
 * @return The grayscale image.
 */
PNG grayscale(PNG image)
{
    /// This function is already written for you so you can see how to
    /// interact with our PNG class.
    for (auto x = 0; x < static_cast<int>(image.width()); x++)
    {
        for (auto y = 0; y < static_cast<int>(image.height()); y++)
        {
            HSLAPixel* pixel = image.getPixel(x, y);

            // `pixel` is a pointer to the memory stored inside of the PNG `image`,
            // which means you're changing the image directly.  No need to `set`
            // the pixel since you're directly changing the memory of the image.
            pixel->s = 0;
        }
    }

    return image;
}


/**
 * Returns an image with a spotlight centered at (`centerX`, `centerY`).
 *
 * A spotlight adjusts the luminance of a pixel based on the distance the pixel
 * is away from the center by decreasing the luminance by 0.5% per 1 pixel euclidean
 * distance away from the center.
 *
 * For example, a pixel 3 pixels above and 4 pixels to the right of the center
 * is a total of `sqrt((3 * 3) + (4 * 4)) = sqrt(25) = 5` pixels away and
 * its luminance is decreased by 2.5% (0.975x its original value).  At a
 * distance over 200 pixels away, the luminance will always 0.
 *
 * The modified PNG is then returned.
 *
 * @param image A PNG object which holds the image data to be modified.
 * @param centerX The center x coordinate of the crosshair which is to be drawn.
 * @param centerY The center y coordinate of the crosshair which is to be drawn.
 *
 * @return The image with a spotlight.
 */
PNG createSpotlight(PNG image, const int centerX, const int centerY)
{
    auto dist = [](const int x1, const int y1, const int x2, const int y2) -> double
    {
        return std::sqrt(std::pow(x1 - x2, 2) + std::pow(y2 - y1, 2));
    };

    auto lumi = [](const double l, const double d) -> double
    {
        return l * std::max(1 - d * 0.005, 0.0);
    };

    for (auto x = 0; x < static_cast<int>(image.width()); x++)
    {
        for (auto y = 0; y < static_cast<int>(image.height()); y++)
        {
            const auto pixel = image.getPixel(x, y);
            pixel->l = lumi(pixel->l, dist(x, y, centerX, centerY));
        }
    }
    return image;
}


/**
 * Returns a image transformed to Illini colors.
 *
 * The hue of every pixel is set to the a hue value of either orange or
 * blue, based on if the pixel's hue value is closer to orange than blue.
 *
 * @param image A PNG object which holds the image data to be modified.
 *
 * @return The illinify'd image.
**/
PNG illinify(PNG image)
{
    for (int x = 0; x < static_cast<int>(image.width()); x++)
    {
        for (int y = 0; y < static_cast<int>(image.height()); y++)
        {
            constexpr double max_hue = 360;
            constexpr double blue_hue = 216;
            constexpr double orange_hue = 11;

            HSLAPixel* pixel = image.getPixel(x, y);
            const double hue = pixel->h;

            double orange_diff = std::min(std::abs(hue - orange_hue), max_hue - std::abs(hue - orange_hue));
            double blue_diff = std::min(std::abs(hue - blue_hue), max_hue - std::abs(hue - blue_hue));

            pixel->h = orange_diff < blue_diff ? orange_hue : blue_hue;
        }
    }

    return image;
}


/**
* Returns an immge that has been watermarked by another image.
*
* The luminance of every pixel of the second image is checked, if that
* pixel's luminance is 1 (100%), then the pixel at the same location on
* the first image has its luminance increased by 0.2.
*
* @param firstImage  The first of the two PNGs.
* @param secondImage The second of the two PNGs.
*
* @return The watermarked image.
*/
PNG watermark(PNG firstImage, PNG secondImage)
{
    for (auto x = 0; x < static_cast<int>(firstImage.width()); x++)
    {
        for (auto y = 0; y < static_cast<int>(firstImage.height()); y++)
        {
            HSLAPixel* firstPixel = firstImage.getPixel(x, y);
            const HSLAPixel* secondPixel = secondImage.getPixel(x, y);

            if (secondPixel->l == 1.0)
            {
                firstPixel->l = std::min(firstPixel->l + 0.2, 1.0);
            }
        }
    }
    return firstImage;
}
