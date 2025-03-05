#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <cmath>

#define SCREEN_WIDTH (1600)
#define SCREEN_HEIGHT (900)

#define WINDOW_TITLE "Picross"

class TextureTile
{
public:
    TextureTile() = default;

    TextureTile(Image& image)
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

//private:
    Texture2D texture;
    Color imageColor;
    Vector3 hsv; // x = hue, s = saturation, v = value
    int frequency;
};

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);
    SetExitKey(0);

    const int ROWS = 50;
    const int COLS = 50;
    const float PADDING = 1; // used to expand space in between tiles
    const int COLOR_AMOUNT = 10; // max colors allowed in puzzle
    
    Image image = LoadImage(ASSETS_PATH"test.jpg");
    Texture2D baseTexture = LoadTextureFromImage(image);

    TextureTile* textures[ROWS * COLS];
    std::map<float, int> grayFrequency; // first is gray value, second is pos in array for first occurance
    float width = image.width;
    float height = image.height;

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
            textures[(i * COLS) + j] = new TextureTile(cropped);

            // Calculate highest frequency value occuring throughout the image 
            float value = textures[(i * COLS) + j]->hsv.z;
            if (value < 0.95 && grayFrequency.find(value) != grayFrequency.end())
            {
                textures[grayFrequency[value]]->frequency += 1;
            }
            else if (value < 0.95)
            {
                grayFrequency.emplace(value, (i * COLS) + j);
            }
        }
    }

    // Used to hold frequency and texture arr locations for future sorting
    std::vector<std::pair<int, int>> holderVec(grayFrequency.size()); // first is frequency, second is loc in text arr
    for (auto i : grayFrequency)
    {
        holderVec.push_back(std::make_pair(textures[i.second]->frequency, i.second));
    }

    int index = 0;    
    std::vector<std::pair<int, int>> sortedFrequency; // first is frequency, second is loc in text arr
    sortedFrequency.push_back(std::make_pair(holderVec[0].first, holderVec[0].second));
    // Eliminates values that are similar to other values
    for (int i = 1; i < holderVec.size(); i++)
    {
        float currentVal = textures[holderVec[i].second]->hsv.z;
        float comparedVal = textures[holderVec[index].second]->hsv.z;
        if (!(comparedVal + 0.2 > currentVal && comparedVal - 0.2 < currentVal))
        {
            sortedFrequency.push_back(std::make_pair(holderVec[i].first, holderVec[i].second));
            index = i;
        }
    }

    // Sort so that those with higher frequency are at the beginning
    std::sort(sortedFrequency.begin(), sortedFrequency.end(), std::greater<std::pair<int, int>>());
    if (sortedFrequency.size() > COLOR_AMOUNT)
        sortedFrequency.resize(COLOR_AMOUNT);

    GuiLoadStyle(ASSETS_PATH"style_bluish.rgs");
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                int loc = (i * COLS) + j;
                TextureTile textureTile = *textures[loc];
                Color color = textureTile.imageColor;

                if (textureTile.hsv.z < 0.95) // ignores white values
                {
                    // Find color that most closely matches one of the high frequency values
                    float smallestDist = 1;
                    for (auto i : sortedFrequency)
                    {
                        float currentDist = abs(textures[i.second]->hsv.z - textureTile.hsv.z);
                        if (currentDist < smallestDist)
                        {
                            smallestDist = currentDist;
                            color = textures[i.second]->imageColor;
                        }
                    }
                }

                // Draw colored rectangle
                Texture2D texture = textureTile.texture;
                const int rectX = (j * texture.width * PADDING) + (SCREEN_WIDTH / 2 - image.width / 2);
                const int rectY = (i * texture.height * PADDING) + (SCREEN_HEIGHT / 2 - image.height / 2);
                DrawRectangle(rectX, rectY, texture.width, texture.height, color);
            }
        }

        // Display colors being used in limited color picture
        int index = 0;
        int width = 40;
        int height = 40;
        for (auto i : sortedFrequency)
        {
            const int rectX = (index * width);
            const int rectY = (SCREEN_HEIGHT - height);
            DrawRectangle(rectX, rectY, width, height, textures[i.second]->imageColor);

            index++;
        }

        DrawTexture(baseTexture, 20, 20, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
