//
// Created by Yao Xinchen on 2024/2/26.
//

#include "Image.h"
#include <functional>

void cs225::Image::lighten()
{
    auto lighten_pixel = [](HSLAPixel* pixel)
    {
        pixel->l + 0.1 > 1 ? pixel->l = 1 : pixel->l += 0.1;
    };

    iterate_with(lighten_pixel);
}

void cs225::Image::lighten(double amount)
{
    auto lighten_pixel = [amount](HSLAPixel* pixel)
    {
        pixel->l + amount > 1 ? pixel->l = 1 : pixel->l += amount;
    };

    iterate_with(lighten_pixel);
}

void cs225::Image::darken()
{
    auto darken_pixel = [](HSLAPixel* pixel)
    {
        pixel->l - 0.1 < 0 ? pixel->l = 0 : pixel->l -= 0.1;
    };

    iterate_with(darken_pixel);
}

void cs225::Image::darken(double amount)
{
    auto darken_pixel = [amount](HSLAPixel* pixel)
    {
        pixel->l - amount < 0 ? pixel->l = 0 : pixel->l -= amount;
    };

    iterate_with(darken_pixel);
}

void cs225::Image::saturate()
{
    auto saturate_pixel = [](HSLAPixel* pixel)
    {
        pixel->s + 0.1 > 1 ? pixel->s = 1 : pixel->s += 0.1;
    };

    iterate_with(saturate_pixel);
}

void cs225::Image::saturate(double amount)
{
    auto saturate_pixel = [amount](HSLAPixel* pixel)
    {
        pixel->s + amount > 1 ? pixel->s = 1 : pixel->s += amount;
    };

    iterate_with(saturate_pixel);
}

void cs225::Image::desaturate()
{
    auto desaturate_pixel = [](HSLAPixel* pixel)
    {
        pixel->s - 0.1 < 0 ? pixel->s = 0 : pixel->s -= 0.1;
    };

    iterate_with(desaturate_pixel);
}

void cs225::Image::desaturate(double amount)
{
    auto decrease = [amount](HSLAPixel* pixel)
    {
        pixel->s - amount < 0 ? pixel->s = 0 : pixel->s -= amount;
    };

    iterate_with(decrease);
}

void cs225::Image::grayscale()
{
    auto grayscale_pixel = [](HSLAPixel* pixel)
    {
        pixel->s = 0;
    };

    iterate_with(grayscale_pixel);
}

void cs225::Image::rotateColor(double degrees)
{
    auto rotate_pixel = [degrees](HSLAPixel* pixel)
    {
        pixel->h = std::fmod(pixel->h + degrees, 360);
        pixel->h = pixel->h < 0 ? pixel->h + 360 : pixel->h;
    };

    iterate_with(rotate_pixel);
}

void cs225::Image::illinify()
{
    auto illinify_pixel = [](HSLAPixel* pixel)
    {
        constexpr double max_hue = 360;
        constexpr double blue_hue = 216;
        constexpr double orange_hue = 11;

        double orange_diff = std::min(std::abs(pixel->h - orange_hue), max_hue - std::abs(pixel->h - orange_hue));
        double blue_diff = std::min(std::abs(pixel->h - blue_hue), max_hue - std::abs(pixel->h - blue_hue));

        pixel->h = orange_diff < blue_diff ? orange_hue : blue_hue;
    };

    iterate_with(illinify_pixel);
}

void cs225::Image::scale(double factor)
{
    auto backup = *this;

    this->resize(static_cast<uint>(this->width() * factor),
                 static_cast<uint>(this->height() * factor));

    for (uint i = 0; i < this->width(); i++)
    {
        for (uint j = 0; j < this->height(); j++)
        {
            auto pixel = this->getPixel(i, j);
            auto x = static_cast<int>(i / factor);
            auto y = static_cast<int>(j / factor);
            *pixel = *backup.getPixel(x, y);
        }
    }
}

void cs225::Image::scale(uint w, uint h)
{
    auto backup = *this;

    this->resize(w, h);

    for (uint i = 0; i < this->width(); i++)
    {
        for (uint j = 0; j < this->height(); j++)
        {
            auto pixel = this->getPixel(i, j);
            auto x = static_cast<int>(i * backup.width() / this->width());
            auto y = static_cast<int>(j * backup.height() / this->height());
            *pixel = *backup.getPixel(x, y);
        }
    }
}

void cs225::Image::iterate_with(const std::function<void(HSLAPixel* pixel)>& f)
{
    for (uint i = 0; i < this->width(); i++)
    {
        for (uint j = 0; j < this->height(); j++)
        {
            auto pixel = this->getPixel(i, j);
            f(pixel);
        }
    }
}
