#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <iostream>

#define SCREEN_WIDTH (1600)
#define SCREEN_HEIGHT (900)

#define WINDOW_TITLE "Picross"

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);
    SetExitKey(0);

    const int ROWS = 20;
    const int COLS = 20;
    const float PADDING = 1;
    
    Image image = LoadImage(ASSETS_PATH"test.jpg");
    Texture baseTexture = LoadTextureFromImage(image);
    Texture textures[ROWS * COLS];
    Color avgColors[ROWS * COLS];
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
            avgColor.r = r;
            avgColor.g = g;
            avgColor.b = b;
            avgColor.a = a;
            avgColors[(i * ROWS) + j] = avgColor;
            textures[(i * ROWS) + j] = texture;
        }
    }

    GuiLoadStyle(ASSETS_PATH"style_bluish.rgs");
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {

                Texture2D texture = textures[(i * ROWS) + j];
                /*
                const int textureX = (j * texture.width * PADDING);
                const int textureY = (i * texture.height * PADDING);
                DrawTexture(texture, textureX, textureY, WHITE);
                */
                const int rectX = (j * texture.width * PADDING) + (SCREEN_WIDTH / 2 - image.width / 2);
                const int rectY = (i * texture.height * PADDING) + (SCREEN_HEIGHT / 2 - image.height / 2);
                DrawRectangle(rectX, rectY, texture.width, texture.height, avgColors[(i * ROWS) + j]);
            }
        }

        DrawTexture(baseTexture, 20, 20, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
