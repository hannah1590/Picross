#pragma once
#include "raylib.h"
#include <cmath>
#include <string>

enum TileState {
	EMPTY,
	COLORED,
	CROSSED
};

class PuzzleTile
{
public:
	PuzzleTile()
	{
		rect.x = 0;
		rect.y = 0;
		rect.width = 0;
		rect.height = 0;
		tileColor = WHITE;
		currentColor = WHITE;
		gridPos = 0;
		
		currentState = EMPTY;
		correctState = CROSSED;

		selectorTile = false;
	}

	PuzzleTile(Rectangle& rect, Color& tileColor, int gridPos, bool selectorTile) :
		rect(rect), tileColor(tileColor), gridPos(gridPos), selectorTile(selectorTile)
	{ 
		currentState = EMPTY;
		currentColor = WHITE;

		if (std::abs(tileColor.r - WHITE.r) > 10 && std::abs(tileColor.g - WHITE.g) > 10 && std::abs(tileColor.b - WHITE.b) > 10)
			correctState = CROSSED;
		else
			correctState = COLORED;
	}

	void drawTile();

	bool isColliding(Vector2 pos);

	bool isCorrect() { return currentState == correctState; }

	void setState(TileState state) { currentState = state; }
	TileState getState() { return currentState; }
	void setColor(Color color);
	Color getColor() { return tileColor; }
	int getGridPos() { return gridPos; }
	Rectangle getRect() { return rect; }

	bool isSelector() { return selectorTile; }
private:
	Rectangle rect;
	Color tileColor;
	Color currentColor;
	int gridPos;

	TileState currentState;
	TileState correctState;

	bool selectorTile;
};