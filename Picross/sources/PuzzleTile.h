#pragma once
#include "raylib.h"
#include <cmath>
#include <string>

enum TileState {
	EMPTY,
	COLORED,
	EITHER
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
		correctState = EITHER;

		selectorTile = false;
	}

	PuzzleTile(Rectangle& rect, Color& tileColor, int gridPos, bool selectorTile) :
		rect(rect), tileColor(tileColor), gridPos(gridPos), selectorTile(selectorTile)
	{ 
		currentState = EMPTY;
		currentColor = WHITE;

		if (std::abs(tileColor.r - WHITE.r) > 10 && std::abs(tileColor.g - WHITE.g) > 10 && std::abs(tileColor.b - WHITE.b) > 10)
			correctState = EITHER;
		else
			correctState = COLORED;
	}

	void drawTile();
	void drawCorrect();

	bool isColliding(Vector2 pos);

	bool isCorrect();

	void setState(TileState state) { currentState = state; }
	TileState getState() { return currentState; }
	void setColor(Color color, bool pressed, Color firstColor);
	Color getColor() { return tileColor; }
	int getGridPos() { return gridPos; }
	Rectangle getRect() { return rect; }

	Color getCurrentColor() { return currentColor; }

	bool isSelector() { return selectorTile; }

	void setPressed(bool p) { pressed = p; }
	bool getPressed() { return pressed; }
private:
	Rectangle rect;
	Color tileColor;
	Color currentColor;
	int gridPos;

	TileState currentState;
	TileState correctState;

	bool selectorTile;
	bool pressed;
};