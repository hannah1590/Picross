#pragma once
#include "raylib.h"

class PuzzleTile
{
public:
	PuzzleTile(Color tileColor, int gridPos) :
		tileColor(tileColor), gridPos(gridPos)
	{ }

	Color getColor() { return tileColor; }

private:
	Color tileColor;
	int gridPos;
};