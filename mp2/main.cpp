#include "Image.h"
#include "StickerSheet.h"

using namespace cs225;

int main()
{
    const auto base = []()
    {
        Image base_;
        base_.readFromFile("resource/mygo.png");
        return base_;
    }();

    auto rana = []()
    {
        Image sticker_;
        sticker_.readFromFile("resource/kaname_rana.png");
        return sticker_;
    }();

    auto soyo = []()
    {
        Image sticker_;
        sticker_.readFromFile("resource/nagasaki_soyo.png");
        return sticker_;
    }();

    auto tomori = []()
    {
        Image sticker_;
        sticker_.readFromFile("resource/takamatsu_tomori.png");
        return sticker_;
    }();

    auto anon = []()
    {
        Image sticker_;
        sticker_.readFromFile("resource/chihaya_anon.png");
        return sticker_;
    }();

    auto taki = []()
    {
        Image sticker_;
        sticker_.readFromFile("resource/shiina_taki.png");
        return sticker_;
    }();

    auto sheet = StickerSheet(base, 5);
    sheet.addSticker(rana, 435, 1800);
    sheet.addSticker(soyo, 435 + 180, 1800);
    sheet.addSticker(tomori, 435 + 180 * 2, 1800);
    sheet.addSticker(anon, 435 + 180 * 3, 1800);
    sheet.addSticker(taki, 435 + 180 * 4, 1800);

    sheet.render().writeToFile("myImage.png");

    return 0;
}
