#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "PuzzleGrid.h"

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
    Texture2D baseTexture = LoadTextureFromImage(image);

    FullTexture fullTexture(image, GRID_SIZE, COLOR_AMOUNT);

    GuiLoadStyle(ASSETS_PATH"style_bluish.rgs");
    ImageResize(&image, IMAGE_SIZE, IMAGE_SIZE);

    Rectangle gridRect;
    gridRect.x = (SCREEN_WIDTH / 2 - (image.width * PADDING) / 2);
    gridRect.y = (SCREEN_HEIGHT / 2 - (image.height * PADDING) / 2);
    gridRect.width = image.width * PADDING;
    gridRect.height = image.height * PADDING;

    PuzzleGrid puzzleGrid(fullTexture, GRID_SIZE, gridRect, PADDING);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw background rectangle
        const int rectX = (SCREEN_WIDTH / 2) - ((image.width * PADDING) / 2) - NUM_BAR_SIZE;
        const int rectY = (SCREEN_HEIGHT / 2) - ((image.height * PADDING) / 2) - NUM_BAR_SIZE;
        DrawRectangle(rectX, rectY, image.width * PADDING + NUM_BAR_SIZE, image.height * PADDING + NUM_BAR_SIZE, GRAY);
        
        // Draw puzzle grid
        puzzleGrid.drawColorMaps(image.width / GRID_SIZE, NUM_BAR_SIZE);
        puzzleGrid.drawGrid();

        // Display colors being used in limited color picture
        int index = 0;
        int width = 40;
        int height = 40;

        const int colorBarX = (SCREEN_WIDTH / 2) - ((fullTexture.getSortedFrequencySize() - 1) * width * PADDING) - 10 * PADDING;
        const int colorBarY = (SCREEN_HEIGHT - (height + 40));
        DrawRectangle(colorBarX, colorBarY, fullTexture.getSortedFrequencySize() * width * PADDING + 20, height + 20, GRAY);
        for (int i = 0; i < fullTexture.getSortedFrequencySize(); i++)
        {
            const int rectX = (SCREEN_WIDTH / 2) - (index * width * PADDING);
            const int rectY = (SCREEN_HEIGHT - (height + 30));
            DrawRectangle(rectX, rectY, width, height, fullTexture.getColorFromSortedFrequency(i));
            index++;
        }

        DrawTexture(baseTexture, 20, 20, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
