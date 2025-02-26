#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <iostream>
#include <set>
#include <algorithm>
#include <map>

#define SCREEN_WIDTH (1600)
#define SCREEN_HEIGHT (900)

#define WINDOW_TITLE "Picross"

class ColorComparer
{
public:
    ColorComparer()
    {
        r = 255;
        g = 255;
        b = 255;
        a = 255;

        color.r = r;
        color.g = g;
        color.b = b;
        color.a = a;
    }

    ColorComparer(int r, int g, int b, int a)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;

        color.r = r;
        color.g = g;
        color.b = b;
        color.a = a;
    }


    bool operator==(ColorComparer const& rhs)
    {
        return (r == rhs.r) && (g == rhs.g) && (b == rhs.b);
    }

    int r;
    int g;
    int b;
    int a;
    Color color;
};

bool operator<(ColorComparer const& lhs, ColorComparer const& rhs)
{
    return (lhs.r < rhs.r) && (lhs.g < rhs.g) && (lhs.b < rhs.b);
}

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);
    SetExitKey(0);

    const int ROWS = 25;
    const int COLS = 25;
    const float PADDING = 1.5;
    const int COLOR_AMOUNT = 25;
    
    Image image = LoadImage(ASSETS_PATH"test.jpg");
    Texture baseTexture = LoadTextureFromImage(image);

    //Image grayscale = ImageFromChannel(image, 0);
    //Texture grayTexture = LoadTextureFromImage(grayscale);

    Texture textures[ROWS * COLS];
    ColorComparer avgColors[ROWS * COLS];
    float width = image.width;
    float height = image.height;
    
    Color totalAvg;
    totalAvg.r = 0;
    totalAvg.g = 0;
    totalAvg.b = 0;
    totalAvg.a = 0;

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            Rectangle rect;
            rect.width = width / COLS;
            rect.height = height / ROWS;
            rect.x = j * rect.width;
            rect.y = i * rect.height;

            Image cropped = ImageFromImage(image, rect);
            Texture2D texture = LoadTextureFromImage(cropped);

            Color avgColor;
            int r = 0;
            int g = 0;
            int b = 0;
            int a = 0;

            for (int y = 0; y < cropped.height; y++)
            {
                for (int x = 0; x < cropped.width; x++)
                {
                    Color currentColor = GetImageColor(cropped, x, y);
                    
                    r += currentColor.r;
                    g += currentColor.g;
                    b += currentColor.b;
                    a += currentColor.a;
                }
            }
            r /= (cropped.width) * (cropped.height);
            g /= (cropped.width) * (cropped.height);
            b /= (cropped.width) * (cropped.height);
            a /= (cropped.width) * (cropped.height);
            avgColors[(i * COLS) + j] = ColorComparer(r,g,b,a);
            textures[(i * COLS) + j] = texture;
        }
    }
    // Make a histogram
    // Convert image to black and white by averaging the RGB values
    // determine size of image
    // determine max intensity
    // set the values for the histogram
    // compute the frequency (between 0 and max)
    // 

    //std::sort(std::begin(avgColors), std::end(avgColors));
    /*std::map<int, ColorComparer> colorMap;

    int index = 0;
    
    while (index < std::size(avgColors))
    {
        ColorComparer current = avgColors[index];

    }*/

    std::set<ColorComparer> imageColors{ std::begin(avgColors), std::end(avgColors) };
    std::cout << imageColors.size() << std::endl;
    GuiLoadStyle(ASSETS_PATH"style_bluish.rgs");
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {

                Texture2D texture = textures[(i * COLS) + j];
                const int rectX = (j * texture.width * PADDING) + (SCREEN_WIDTH / 2 - image.width / 2);
                const int rectY = (i * texture.height * PADDING) + (SCREEN_HEIGHT / 2 - image.height / 2);
                DrawRectangle(rectX, rectY, texture.width, texture.height, avgColors[(i * COLS) + j].color);
            }
        }

        int index = 0;
        int width = 40;
        int height = 40;
        for (ColorComparer const& color : imageColors)
        {
            if (index % (imageColors.size() / COLOR_AMOUNT) == 0)
            {
                const int rectX = (index * width);
                const int rectY = (SCREEN_HEIGHT - height);
                DrawRectangle(rectX, rectY, width, height, color.color);
            }
            
            index++;
        }

        DrawTexture(baseTexture, 20, 20, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
