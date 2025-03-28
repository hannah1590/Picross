#pragma once
#include "PuzzleTile.h"
#include "FullTexture.h"
#include <string>
#include <unordered_map>

#define SCREEN_WIDTH (1600)
#define SCREEN_HEIGHT (900)

class PuzzleGrid
{
public:
	PuzzleGrid(FullTexture& text, int size, Rectangle rect, float padding) :
		texture(&text), gridSize(size), gridRect(rect), tilePadding(padding)
	{ 
		setUpColorMaps();
	}

	void setUpColorMaps();
	void drawColorMaps(int barWidth, int barLength);
	void drawGrid();
	void setUpColorSelect(int width, int height);
	void drawColorSelection();

	PuzzleTile* getTileAtPoint(Vector2 point);

private:
	std::vector<PuzzleTile*> tiles;
	std::vector<PuzzleTile*> colorSelect; // all colors in the puzzle displayed at the bottom of the screen
	std::vector<std::vector<std::pair<int, int>>> colorMaps; // even numbers are rows, odd are columns; first int is color in hex, second is frequency
	FullTexture* texture;

	int gridSize;
	float tilePadding;
	Rectangle gridRect;
};