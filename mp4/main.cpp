#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main()
{
    // - The code below assumes you have an Animation called `animation`
    // - The code provided below produces the `myFloodFill.png` file you must
    //   submit Part 3 of this assignment -- uncomment it when you're ready.

    /*
    PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
    lastFrame.writeToFile("myFloodFill.png");
    animation.write("myFloodFill.gif");
    */

    // read image
    auto png = PNG();
    png.readFromFile("MetaTeam.png");
    const auto w = png.width();
    const auto h = png.height();

    // create flood filled image and traversals
    auto image = FloodFilledImage(png);
    auto outer = DFS(png, Point(0, 0), 0.1);
    auto left = BFS(png, Point(w / 3, h / 5), 1.0);
    auto right = BFS(png, Point(2 * w / 3, h / 5), 1.0);

    // outer
    const auto deep_blue = HSLAPixel(216, 0.8, 0.18);
    auto solid = SolidColorPicker(deep_blue);

    // inner
    constexpr double orange_h = 11;
    auto wave = MyColorPicker(0.15, 0.1, orange_h);

    // add flood fills
    image.addFloodFill(outer, solid);
    image.addFloodFill(left, wave);
    image.addFloodFill(right, wave);

    // output
    auto animation = image.animate(1000);
    animation.write("MetaTeam.gif");

    return 0;
}
