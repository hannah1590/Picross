#include "PuzzleTile.h"

void PuzzleTile::drawTile()
{
	if (!selectorTile)
	{
		switch (currentState)
		{
		case EMPTY:
			DrawRectangle(rect.x, rect.y, rect.width, rect.height, WHITE);
			break;
		case COLORED:
			DrawRectangle(rect.x, rect.y, rect.width, rect.height, currentColor);
			break;
		case CROSSED:
			DrawRectangle(rect.x, rect.y, rect.width, rect.height, RED);
			break;
		}
	}
	else
		DrawRectangle(rect.x, rect.y, rect.width, rect.height, tileColor);
}

bool operator==(Color const& lhs, Color const& rhs)
{
	return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b;
}

void PuzzleTile::setColor(Color color)
{
	if (currentColor == color)
	{
		currentColor = WHITE;
		currentState = EMPTY;
	}
	else if (color == RED)
	{
		currentColor = color;
		currentState = CROSSED;
	}
	else
	{
		currentColor = color;
		currentState = COLORED;
	}
}

bool operator<=(Vector2 const& lhs, Vector2 const& rhs)
{
	return lhs.x <= rhs.x && lhs.y <= rhs.y;
}

bool operator>=(Vector2 const& lhs, Vector2 const& rhs)
{
	return lhs.x >= rhs.x && lhs.y >= rhs.y;
}

bool PuzzleTile::isColliding(Vector2 pos)
{
	Vector2 minBound;
	minBound.x = rect.x;
	minBound.y = rect.y;
	Vector2 maxBound;
	maxBound.x = rect.x + rect.width;
	maxBound.y = rect.y + rect.height;
	if (pos <= maxBound && pos >= minBound)
	{
		return true;
	}
	return false;
}