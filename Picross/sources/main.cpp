#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "PuzzleGrid.h"
#include <fstream>

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

    const int BASE_IMAGE_SIZE = 255;
    const int IMAGE_SIZE = 300;
    
    Image image = LoadImage(ASSETS_PATH"hatsunemiku.jpg");
    Texture2D baseTexture = LoadTextureFromImage(image);

    FullTexture* fullTexture = new FullTexture(image, GRID_SIZE, COLOR_AMOUNT);

    GuiLoadStyle(ASSETS_PATH"style_bluish.rgs");
    Font font = GuiGetFont();
    font.baseSize = 10;
    GuiSetFont(font);
    ImageResize(&image, IMAGE_SIZE, IMAGE_SIZE);

    Rectangle gridRect;
    gridRect.x = (SCREEN_WIDTH / 2 - (image.width * PADDING) / 2);
    gridRect.y = (SCREEN_HEIGHT / 2 - (image.height * PADDING) / 2);
    gridRect.width = image.width * PADDING;
    gridRect.height = image.height * PADDING;

    PuzzleGrid* puzzleGrid = new PuzzleGrid(*fullTexture, GRID_SIZE, gridRect, PADDING);

    puzzleGrid->setUpColorSelect(40, 40);

    Color currentColorSelected = RED;

    Rectangle autoCompleteRec;
    autoCompleteRec.x = 1400;
    autoCompleteRec.y = 50;
    autoCompleteRec.width = 100;
    autoCompleteRec.height = 50;

    Rectangle loadRec;
    loadRec.x = 50;
    loadRec.y = 800;
    loadRec.width = 100;
    loadRec.height = 50;

    bool autoComplete = false;
    std::unordered_map<int, PuzzleTile*> hoveredTiles;
    bool pressed = false;
    Color firstColor = WHITE;
    int index = 0;

    bool exitWindow = false;
    bool showMessageBox = false;
    char textInput[256] = { 0 };
    while (!exitWindow)
    {
        exitWindow = WindowShouldClose();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw background rectangle
        const int rectX = (SCREEN_WIDTH / 2) - ((image.width * PADDING) / 2) - NUM_BAR_SIZE;
        const int rectY = (SCREEN_HEIGHT / 2) - ((image.height * PADDING) / 2) - NUM_BAR_SIZE;
        DrawRectangle(rectX, rectY, image.width * PADDING + NUM_BAR_SIZE, image.height * PADDING + NUM_BAR_SIZE, GRAY);
        
        // Draw puzzle grid
        puzzleGrid->drawColorMaps(image.width / GRID_SIZE, NUM_BAR_SIZE);
        if (!autoComplete)
            puzzleGrid->drawGrid();
        else
            puzzleGrid->drawCorrectGrid();

        // Display colors being used in limited color picture
        puzzleGrid->drawColorSelection();

        DrawTexture(baseTexture, 20, 20, WHITE);

        if (IsMouseButtonUp(0))
        {
            hoveredTiles.clear();
            pressed = false;
            index = 0;
        }

        if (IsMouseButtonDown(0))
        {
            index++;
            if (index > 1)
                pressed = true;
            Vector2 mousePos;
            mousePos.x = GetMouseX();
            mousePos.y = GetMouseY();
            PuzzleTile* currentTile = puzzleGrid->getTileAtPoint(mousePos);
            if (currentTile != nullptr && hoveredTiles.find(currentTile->getGridPos()) == hoveredTiles.end())
            {
                if (hoveredTiles.empty())
                    firstColor = currentTile->getCurrentColor();

                hoveredTiles.emplace(currentTile->getGridPos(), currentTile);
                if (currentTile != nullptr)
                {
                    if (currentTile->isSelector())
                        currentColorSelected = currentTile->getColor();
                    else
                        currentTile->setColor(currentColorSelected, pressed, firstColor);
                }
            }
        }

        if (GuiButton(autoCompleteRec, "Auto Complete"))
        {
            autoComplete = !autoComplete;
        }

        if (GuiButton(loadRec, "Load Image")) showMessageBox = true;
        if (showMessageBox)
        {
            Rectangle message;
            message.x = (float)GetScreenWidth() / 2 - 120;
            message.y = (float)GetScreenHeight() / 2 - 60;
            message.width = 240;
            message.height = 140;
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(RAYWHITE, 0.8f));
            int result = GuiTextInputBox(message, GuiIconText(ICON_FILE_OPEN,
                    "Load new image"), "Input image file name:", "Ok;Cancel", textInput, 255, NULL);

            if (result == 1)
            {
                std::string fileName(textInput);
                fileName = ASSETS_PATH + fileName;
                Image newImage = LoadImage(fileName.c_str());
                if (newImage.data != nullptr)
                {
                    image = newImage;
                    Rectangle img;
                    if (image.width > image.height)
                    {
                        img.x = (image.width - image.height) / 2;
                        img.y = 0;
                        img.width = image.height;
                        img.height = image.height;
                        ImageCrop(&image, img);
                    }
                    else if (image.width < image.height)
                    {
                        img.x = 0;
                        img.y = (image.height - image.width) / 2;
                        img.width = image.width;
                        img.height = image.width;
                        ImageCrop(&image, img);
                    }
                    ImageResize(&image, BASE_IMAGE_SIZE, BASE_IMAGE_SIZE); // must be a smaller square
                    baseTexture = LoadTextureFromImage(image);

                    delete fullTexture;
                    fullTexture = new FullTexture(image, GRID_SIZE, COLOR_AMOUNT);
                    ImageResize(&image, IMAGE_SIZE, IMAGE_SIZE);

                    gridRect.x = (SCREEN_WIDTH / 2 - (image.width * PADDING) / 2);
                    gridRect.y = (SCREEN_HEIGHT / 2 - (image.height * PADDING) / 2);
                    gridRect.width = image.width * PADDING;
                    gridRect.height = image.height * PADDING;

                    delete puzzleGrid;
                    puzzleGrid = new PuzzleGrid(*fullTexture, GRID_SIZE, gridRect, PADDING);
                    puzzleGrid->setUpColorSelect(40, 40);
                }
                else
                {
                    std::cout << "File not opened properly\n";
                }
            }

            if ((result == 0) || (result == 1) || (result == 2))
            {
                showMessageBox = false;
            }
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
