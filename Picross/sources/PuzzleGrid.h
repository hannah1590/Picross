#pragma once
#include "PuzzleTile.h"
#include "FullTexture.h"
#include <string>
#include <unordered_map>

class PuzzleGrid
{
public:
	PuzzleGrid(FullTexture& text, int size):
		texture(&text), gridSize(size)
	{ 
		setUpColorMaps();
	}

	void setUpColorMaps();
	void drawRowColorMap(int x, int y, int containLength, int containWidth, int mapIndex);
	void drawColColorMap(int x, int y, int containLength, int containWidth, int mapIndex);

private:
	//std::vector<PuzzleTile*> tiles;
	std::vector<std::vector<std::pair<int, int>>> colorMaps; // even numbers are rows, odd are columns; first int is color in hex, second is frequency
	FullTexture* texture;

	int gridSize;
};