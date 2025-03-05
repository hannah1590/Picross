#include "TextureTile.h";

TextureTile::TextureTile(Image& image)
{
    texture = LoadTextureFromImage(image);

    int r = 0;
    int g = 0;
    int b = 0;
    int a = 0;

    // Find average rgba value for the entire image
    for (int y = 0; y < image.height; y++)
    {
        for (int x = 0; x < image.width; x++)
        {
            Color currentColor = GetImageColor(image, x, y);
            r += currentColor.r;
            g += currentColor.g;
            b += currentColor.b;
            a += currentColor.a;
        }
    }
    r /= (image.width) * (image.height);
    g /= (image.width) * (image.height);
    b /= (image.width) * (image.height);
    a /= (image.width) * (image.height);
    imageColor.r = r;
    imageColor.g = g;
    imageColor.b = b;
    imageColor.a = a;
    hsv = ColorToHSV(imageColor);
    frequency = 0;
}