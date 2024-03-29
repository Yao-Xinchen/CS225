#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../lab_intro.h"
#include "../cs225/PNG.h"
#include "../cs225/HSLAPixel.h"

PNG createRainbowPNG()
{
    PNG png(360, 100);
    for (unsigned x = 0; x < png.width(); x++)
    {
        for (unsigned y = 0; y < png.height(); y++)
        {
            HSLAPixel* pixel = png.getPixel(x, y);
            pixel->h = x;
            pixel->s = y / 100.0;
            pixel->l = 0.5;
        }
    }
    return png;
}

PNG createWatermark()
{
    PNG png(360, 100);
    for (unsigned x = 0; x < png.width(); x++)
    {
        for (unsigned y = 0; y < png.height(); y++)
        {
            HSLAPixel* pixel = png.getPixel(x, y);
            if (y >= 10 && y <= 30) { pixel->l = 1; }
            else { pixel->l = 0; }
        }
    }
    return png;
}


TEST_CASE("createSpotlight", "[weight=1]")
{
    PNG png = createRainbowPNG();
    PNG result = createSpotlight(png, 100, 50);

    SECTION("Spotlight does not modify the center pixel")
    {
        REQUIRE(png.getPixel(100, 50)->h == result.getPixel(100, 50)->h);
        REQUIRE(png.getPixel(100, 50)->s == result.getPixel(100, 50)->s);
        REQUIRE(png.getPixel(100, 50)->l == result.getPixel(100, 50)->l);
        REQUIRE(png.getPixel(100, 50)->a == result.getPixel(100, 50)->a);
    }

    SECTION("Spotlight creates a completely dark pixel >200 pixels away")
    {
        REQUIRE(result.getPixel(320, 50)->l == 0);
    }

    SECTION("Spotlight is correct at 20 pixels away from center")
    {
        REQUIRE(png.getPixel(100, 50 + 20)->l * 0.9 == result.getPixel(100, 50 + 20)->l);
    }

    SECTION("Spotlight is correct at 5 pixels away from center")
    {
        REQUIRE(png.getPixel(100 + 3, 50 + 4)->l * 0.975 == result.getPixel(100 + 3, 50 + 4)->l);
    }
}


TEST_CASE("illinify", "[weight=1]")
{
    PNG png = createRainbowPNG();
    PNG result = illinify(png);

    SECTION("After illinify, image contains only orange and blue hues")
    {
        for (unsigned x = 0; x < result.width(); x++)
        {
            for (unsigned y = 0; y < result.height(); y++)
            {
                if (result.getPixel(x, y)->h != 11 && result.getPixel(x, y)->h != 216)
                {
                    FAIL("The hue of (" << x << "," << y <<") is " << result.getPixel(x, y)->h <<
                        ", not Illini orange or blue.");
                }
            }
        }
    }

    SECTION("Pixels closest to blue become blue")
    {
        REQUIRE(result.getPixel(200, 4)->h == 216);
        REQUIRE(result.getPixel(210, 12)->h == 216);
        REQUIRE(result.getPixel(220, 23)->h == 216);
        REQUIRE(result.getPixel(230, 44)->h == 216);
    }

    SECTION("Pixels closest to orange become orange")
    {
        REQUIRE(result.getPixel(10, 4)->h == 11);
        REQUIRE(result.getPixel(30, 12)->h == 11);
        REQUIRE(result.getPixel(40, 23)->h == 11);
        REQUIRE(result.getPixel(40, 44)->h == 11);
    }

    SECTION("Hue wrap-arounds are correct (ex: h=359 is closer to orange than blue)")
    {
        REQUIRE(result.getPixel(330, 4)->h == 11);
        REQUIRE(result.getPixel(340, 12)->h == 11);
        REQUIRE(result.getPixel(350, 23)->h == 11);
    }
}


TEST_CASE("watermark", "[weight=1]")
{
    PNG png = createRainbowPNG();
    PNG wm = createWatermark();

    PNG result = watermark(png, wm);

    SECTION("Pixels without watermark are unchanged")
    {
        REQUIRE(png.getPixel(100, 50)->l == result.getPixel(100, 50)->l);
        REQUIRE(png.getPixel(200, 80)->l == result.getPixel(200, 80)->l);
    }

    SECTION("Pixels with watermark are changed")
    {
        REQUIRE(png.getPixel(100, 15)->l + 0.2 == result.getPixel(100, 15)->l);
        REQUIRE(png.getPixel(200, 25)->l + 0.2 == result.getPixel(200, 25)->l);
    }
}
