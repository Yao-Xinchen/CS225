//
// Created by Yao Xinchen on 2024/2/26.
//

#ifndef CS225_STICKERSHEET_H
#define CS225_STICKERSHEET_H

#include "Image.h"

namespace cs225
{
    class StickerSheet
    {
    public:
        StickerSheet(const Image& picture, unsigned max);
        ~StickerSheet();
        StickerSheet(const StickerSheet& other);
        const StickerSheet& operator=(const StickerSheet& other);
        void changeMaxStickers(unsigned max);
        int addSticker(Image& sticker, unsigned x, unsigned y);
        bool translate(unsigned index, unsigned x, unsigned y);
        void removeSticker(unsigned index);
        Image* getSticker(unsigned index);
        Image render() const;

    private:
        struct Sticker
        {
            uint x;
            uint y;
            std::shared_ptr<Image> image;

            Sticker();
            Sticker(const Sticker& other);
            Sticker& operator=(const Sticker& other);
        };

        std::shared_ptr<Image> base;
        std::vector<Sticker> stickers;
    };
} // cs225

#endif //CS225_STICKERSHEET_H
