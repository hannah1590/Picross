#pragma once
#include "raylib.h"
#include <cmath>

enum TileState {
	EMPTY,
	COLORED,
	CROSSED
};

class PuzzleTile
{
public:
	PuzzleTile(Rectangle& rect, Color& tileColor, int gridPos) :
		rect(rect), tileColor(tileColor), gridPos(gridPos)
	{ 
		currentState = EMPTY;
		currentColor = WHITE;

		if (std::abs(tileColor.r - WHITE.r) > 10 && std::abs(tileColor.g - WHITE.g) > 10 && std::abs(tileColor.b - WHITE.b) > 10)
			correctState = CROSSED;
		else
			correctState = COLORED;
	}

	void drawTile();

	bool isCorrect() { return currentState == correctState; }

	void setState(TileState state) { currentState = state; }
	TileState getState() { return currentState; }
	void setColor(Color color) { tileColor = color; }
	Color getColor() { return tileColor; }
	int getGridPos() { return gridPos; }
private:
	Rectangle rect;
	Color tileColor;
	Color currentColor;
	int gridPos;

	TileState currentState;
	TileState correctState;
};