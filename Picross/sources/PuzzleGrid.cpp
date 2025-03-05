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
	for (int i = 0; i < gridSize; i++)
	{
		std::vector<std::pair<int, int>> rowColorMap; // first is color value in hex, second is frequency of color
		std::vector<std::pair<int, int>> colColorMap; // first is color value in hex, second is frequency of color

		std::pair<int,int> lastRowColor = std::make_pair(ColorToInt(texture->getTextureTileAt(i * gridSize)->getColor()), 0);
		std::pair<int, int> lastColColor = std::make_pair(ColorToInt(texture->getTextureTileAt(gridSize + i)->getColor()), 0);
		rowColorMap.push_back(std::make_pair(lastRowColor.first, 1));
		colColorMap.push_back(std::make_pair(lastColColor.first, 1));
		for (int j = 0; j < gridSize; j++)
		{
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

void PuzzleGrid::drawRowColorMap(int x, int y, int containLength, int containWidth, int mapIndex)
{
	int width = 10;
	int height = 10;
	int index = 0;
	for (auto i : colorMaps[mapIndex])
	{
		if (GetColor(i.first) != WHITE)
		{
			int rectX = x + (width * index * 1.2);
			int rectY = y + ((containLength - width) / 2);
			DrawRectangle(rectX, rectY, width, height, GetColor(i.first));
			DrawText(std::to_string(i.second).c_str(), rectX + (width / 4), rectY, 10, BLACK);
			index++;
		}
	}
}

void PuzzleGrid::drawColColorMap(int x, int y, int containLength, int containWidth, int mapIndex)
{
	int width = 10;
	int height = 10;
	int index = 0;
	for (auto i : colorMaps[mapIndex])
	{
		if (GetColor(i.first) != WHITE)
		{
			int rectX = x + ((containWidth - width) / 2);
			int rectY = y + (height * index * 1.2);
			DrawRectangle(rectX, rectY, width, height, GetColor(i.first));
			DrawText(std::to_string(i.second).c_str(), rectX + (width / 4), rectY, 10, BLACK);
			index++;
		}
	}
}