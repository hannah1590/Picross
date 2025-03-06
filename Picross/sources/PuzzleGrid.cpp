#include "PuzzleGrid.h"

bool operator<(Color const& lhs, Color const& rhs)
{
	return (lhs.r < rhs.r) && (lhs.g < rhs.g) && (lhs.b < rhs.b);
}

bool operator!=(Color const& lhs, Color const& rhs)
{
	return std::abs(lhs.r - rhs.r) > 10 && std::abs(lhs.g - rhs.g) > 10 && std::abs(lhs.b - rhs.b) > 10;
}

void PuzzleGrid::setUpColorMaps()
{
	Rectangle tileRect;
	tileRect.width = gridRect.width / gridSize / tilePadding;
	tileRect.height = tileRect.width; // only square textures 

	for (int i = 0; i < gridSize; i++)
	{
		std::vector<std::pair<int, int>> rowColorMap; // first is color value in hex, second is frequency of color
		std::vector<std::pair<int, int>> colColorMap; // first is color value in hex, second is frequency of color

		std::pair<int, int> lastRowColor = std::make_pair(ColorToInt(BLANK), 0);
		std::pair<int, int> lastColColor = std::make_pair(ColorToInt(BLANK), 0);
		for (int j = 0; j < gridSize; j++)
		{
			tileRect.x = (j * tileRect.width * tilePadding) + ((SCREEN_WIDTH / 2) - (gridRect.width / 2));
			tileRect.y = (i * tileRect.height * tilePadding) + ((SCREEN_HEIGHT / 2) - (gridRect.height / 2));
			PuzzleTile* tile = new PuzzleTile(tileRect, texture->getTextureTileAt((i * gridSize) + j)->getColor(), (i * gridSize) + j);
			tiles.push_back(tile);

			// Setting up row color frequency
			int currentColor = ColorToInt(texture->getTextureTileAt((i * gridSize) + j)->getColor());
			if (lastRowColor.first == currentColor)
			{
				rowColorMap[lastRowColor.second].second += 1;
			}
			else
			{
				rowColorMap.push_back(std::make_pair(currentColor, 1));
				lastRowColor.first = currentColor;
				lastRowColor.second = rowColorMap.size() - 1;
			}

			// Setting up col color frequency
			currentColor = ColorToInt(texture->getTextureTileAt((j * gridSize) + i)->getColor());
			if (lastColColor.first == currentColor)
			{
				colColorMap[lastColColor.second].second += 1;
			}
			else
			{
				colColorMap.push_back(std::make_pair(currentColor, 1));
				lastColColor.first = currentColor;
				lastColColor.second = colColorMap.size() - 1;
			}
		}
		colorMaps.push_back(rowColorMap);
		colorMaps.push_back(colColorMap);
	}
}

void PuzzleGrid::drawColorMaps(int barWidth, int barLength)
{
	int width = 10;
	int height = 10;
	int barIndex = 0;
	
	for (auto i : colorMaps)
	{
		int rectX;
		int rectY;
		if (barIndex % 2 == 0)
		{
			rectX = (SCREEN_WIDTH / 2 - (gridRect.width) / 2) - (barLength);
			rectY = (SCREEN_HEIGHT / 2 - (gridRect.height) / 2) + (barWidth * (barIndex / 2) * tilePadding);
			DrawRectangle(rectX, rectY, barLength, barWidth, LIGHTGRAY);
		}
		else
		{
			rectX = (SCREEN_WIDTH / 2 - (gridRect.width) / 2) + (barWidth * (barIndex / 2) * tilePadding);
			rectY = (SCREEN_HEIGHT / 2 - (gridRect.height) / 2) - (barLength);
			DrawRectangle(rectX, rectY, barWidth, barLength, LIGHTGRAY);
		}
		
		int colorIndex = 0;
		for (auto j : i)
		{
			if (GetColor(j.first) != WHITE)
			{
				int x;
				int y;
				if (barIndex % 2 == 0)
				{
					x = rectX + (width * colorIndex * tilePadding);
					y = rectY + ((barWidth - width) / 2);
				}
				else
				{
					x = rectX + ((barWidth - width) / 2);
					y = rectY + (height * colorIndex * tilePadding);
				}
				DrawRectangle(x, y, width, height, GetColor(j.first));
				DrawText(std::to_string(j.second).c_str(), x + (width / 4), y, 10, BLACK);
				colorIndex++;
			}
		}
		barIndex++;
	}
}

void PuzzleGrid::drawGrid()
{
	for (PuzzleTile* tile : tiles)
	{
		tile->drawTile();
	}
}