#include "Image.h"
#include "StickerSheet.h"

using namespace cs225;

int main()
{
    auto get_image = [](const std::string &path) {
        Image image;
        image.readFromFile(path);
        return image;
    };

    const auto base = get_image("resource/mygo.png");
    auto rana = get_image("resource/kaname_rana.png");
    auto soyo = get_image("resource/nagasaki_soyo.png");
    auto tomori = get_image("resource/takamatsu_tomori.png");
    auto anon = get_image("resource/chihaya_anon.png");
    auto taki = get_image("resource/shiina_taki.png");

    auto sheet = StickerSheet(base, 5);
    sheet.addSticker(rana, 435, 1800);
    sheet.addSticker(soyo, 435 + 180, 1800);
    sheet.addSticker(tomori, 435 + 180 * 2, 1800);
    sheet.addSticker(anon, 435 + 180 * 3, 1800);
    sheet.addSticker(taki, 435 + 180 * 4, 1800);

    sheet.render().writeToFile("myImage.png");

    return 0;
}
