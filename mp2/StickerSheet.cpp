//
// Created by Yao Xinchen on 2024/2/26.
//

#include "StickerSheet.h"

using namespace cs225;

StickerSheet::StickerSheet(const Image& picture, unsigned int max)
{
    this->base = make_shared<Image>(picture);
    this->stickers = std::vector<Sticker>(max);
}

StickerSheet::~StickerSheet() = default;

StickerSheet::StickerSheet(const StickerSheet& other)
{
    // copy base
    this->base = make_shared<Image>(*other.base);

    // copy stickers
    this->stickers = std::vector<Sticker>(other.stickers.size());
    for (size_t i = 0; i < other.stickers.size(); i++)
    {
        if (other.stickers[i].image != nullptr)
        {
            this->stickers[i] = other.stickers[i];
        }
    }
}

const StickerSheet& StickerSheet::operator=(const StickerSheet& other)
{
    if (this != &other)
    {
        // copy base
        this->base = make_shared<Image>(*other.base);

        // copy stickers
        this->stickers = std::vector<Sticker>(other.stickers.size());
        for (size_t i = 0; i < other.stickers.size(); i++)
        {
            if (other.stickers[i].image != nullptr)
            {
                this->stickers[i] = other.stickers[i];
            }
        }
    }
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned int max)
{
    this->stickers.resize(max);
}

int StickerSheet::addSticker(Image& sticker, unsigned int x, unsigned int y)
{
    // find the first empty slot
    for (size_t i = 0; i < stickers.size(); i++)
    {
        if (stickers[i].image == nullptr)
        {
            stickers[i].x = x;
            stickers[i].y = y;
            stickers[i].image = std::make_shared<Image>(sticker);
            return static_cast<int>(i);
        }
    }
    return -1;
}

bool StickerSheet::translate(unsigned int index, unsigned int x, unsigned int y)
{
    for (size_t i = 0; i < stickers.size(); i++)
    {
        if (i == index)
        {
            stickers[i].x = x;
            stickers[i].y = y;
            return true;
        }
    }
    return false;
}

void StickerSheet::removeSticker(unsigned int index)
{
    stickers.erase(stickers.begin() + index);
}

Image* StickerSheet::getSticker(unsigned int index)
{
    if (index < stickers.size())
    {
        return stickers[index].image.get();
    }
    return nullptr;
}

Image StickerSheet::render() const
{
    uint width = base->width();
    uint height = base->height();
    for (const auto& sticker : stickers)
    {
        if (sticker.image == nullptr) continue;

        if (sticker.x + sticker.image->width() > width) width = sticker.x + sticker.image->width();
        if (sticker.y + sticker.image->height() > height) height = sticker.y + sticker.image->height();
    }
    auto result = *base;
    result.resize(width, height);

    for (const auto& sticker : stickers)
    {
        if (sticker.image == nullptr) continue;

        for (uint i = 0; i < sticker.image->width(); i++)
        {
            for (uint j = 0; j < sticker.image->height(); j++)
            {
                auto pixel = sticker.image->getPixel(i, j);
                if (pixel->a != 0)
                {
                    auto base_pixel = result.getPixel(sticker.x + i, sticker.y + j);
                    *base_pixel = *sticker.image->getPixel(i, j);
                }
            }
        }
    }
    return result;
}

StickerSheet::Sticker::Sticker() : x(0), y(0)
{
    this->image = nullptr;
}

StickerSheet::Sticker::Sticker(const Sticker& other) : x(other.x), y(other.y)
{
    this->image = std::make_shared<Image>(*other.image);
}

StickerSheet::Sticker& StickerSheet::Sticker::operator=(const Sticker& other)
{
    if (this != &other)
    {
        this->x = other.x;
        this->y = other.y;
        this->image = std::make_shared<Image>(*other.image);
    }
    return *this;
}
