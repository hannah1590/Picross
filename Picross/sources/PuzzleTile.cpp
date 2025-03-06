#include "PuzzleTile.h"

void PuzzleTile::drawTile()
{
	DrawRectangle(rect.x, rect.y, rect.width, rect.height, tileColor);
	switch (currentState)
	{
	case EMPTY:
		//DrawRectangle(rect.x, rect.y, rect.width, rect.height, WHITE);
		break;
	case COLORED:
		//DrawRectangle(rect.x, rect.y, rect.width, rect.height, currentColor);
		break;
	case CROSSED:
		//DrawRectangle(rect.x, rect.y, rect.width, rect.height, RED);
		break;
	}
}