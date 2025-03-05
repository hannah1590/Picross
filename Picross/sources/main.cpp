#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "PuzzleGrid.h"

#define SCREEN_WIDTH (1600)
#define SCREEN_HEIGHT (900)

#define WINDOW_TITLE "Picross"

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);
    SetExitKey(0);

    const int GRID_SIZE = 25;
    const float PADDING = 1.2; // used to expand space in between tiles
    const int COLOR_AMOUNT = 10; // max colors allowed in puzzle
    const int NUM_BAR_SIZE = 200;

    const int IMAGE_SIZE = 300;
    
    Image image = LoadImage(ASSETS_PATH"test.jpg");
    ImageResize(&image, IMAGE_SIZE, IMAGE_SIZE);
    Texture2D baseTexture = LoadTextureFromImage(image);

    FullTexture fullTexture(image, GRID_SIZE, COLOR_AMOUNT);

    GuiLoadStyle(ASSETS_PATH"style_bluish.rgs");
    
    PuzzleGrid puzzleGrid(fullTexture, GRID_SIZE);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw background rectangle
        const int rectX = (SCREEN_WIDTH / 2) - ((baseTexture.width * PADDING) / 2) - NUM_BAR_SIZE;
        const int rectY = (SCREEN_HEIGHT / 2) - ((baseTexture.height * PADDING) / 2) - NUM_BAR_SIZE;
        DrawRectangle(rectX, rectY, baseTexture.width * PADDING + NUM_BAR_SIZE, baseTexture.height * PADDING + NUM_BAR_SIZE, GRAY);

        for (int i = 0; i < GRID_SIZE; i++)
        {
            // Draw row num bars
            float numRectSizeLength = baseTexture.width / GRID_SIZE;
            float numRectSizeWidth = NUM_BAR_SIZE;
            int numRectX = (SCREEN_WIDTH / 2 - (image.width * PADDING) / 2) - (numRectSizeWidth);
            int numRectY = (SCREEN_HEIGHT / 2 - (image.height * PADDING) / 2)  + (numRectSizeLength * i * PADDING);
            DrawRectangle(numRectX, numRectY, numRectSizeWidth, numRectSizeLength, LIGHTGRAY);

            puzzleGrid.drawRowColorMap(numRectX, numRectY, numRectSizeLength, numRectSizeWidth, i * 2);

            for (int j = 0; j < GRID_SIZE; j++)
            {
                // Draw col num bars
                numRectSizeLength = NUM_BAR_SIZE;
                numRectSizeWidth = baseTexture.width / (GRID_SIZE);
                numRectX = (SCREEN_WIDTH / 2 - (image.width * PADDING) / 2) + (numRectSizeWidth * j * PADDING);
                numRectY = (SCREEN_HEIGHT / 2 - (image.height * PADDING) / 2) - (numRectSizeLength);
                DrawRectangle(numRectX, numRectY, numRectSizeWidth, numRectSizeLength, LIGHTGRAY);

                puzzleGrid.drawColColorMap(numRectX, numRectY, numRectSizeLength, numRectSizeWidth, j * 2 + 1);

                int loc = (i * GRID_SIZE) + j;
                Texture2D texture = fullTexture.getTextureTileAt(loc)->getTexture();
                Color color = fullTexture.getTextureTileAt(loc)->getColor();

                // Draw colored rectangle
                const int rectX = (j * texture.width * PADDING) + (SCREEN_WIDTH / 2 - (image.width * PADDING) / 2);
                const int rectY = (i * texture.height * PADDING) + (SCREEN_HEIGHT / 2 - (image.height * PADDING) / 2);
                DrawRectangle(rectX, rectY, texture.width, texture.height, color);
            }
        }

        // Display colors being used in limited color picture
        int index = 0;
        int width = 40;
        int height = 40;
        for (int i = 0; i < fullTexture.getSortedFrequencySize(); i++)
        {
            const int rectX = (index * width);
            const int rectY = (SCREEN_HEIGHT - height);
            DrawRectangle(rectX, rectY, width, height, fullTexture.getColorFromSortedFrequency(i));

            index++;
        }

        DrawTexture(baseTexture, 20, 20, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
