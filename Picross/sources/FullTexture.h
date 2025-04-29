#pragma once
#include "TextureTile.h"

#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <cmath>

class FullTexture
{
public:
	FullTexture() {};
	FullTexture(Image image, int gridSize, int maxColor) :
		image(image), gridSize(gridSize), maxColor(maxColor)
	{
		width = image.width;
		height = image.height;

		spliceImage();
		sortFrequency();
	}

	~FullTexture()
	{
		for (TextureTile* tile : textures)
		{
			delete tile;
			tile = nullptr;
		}
		textures.clear();
		grayFrequency.clear();
		sortedFrequency.clear();
	}

    void spliceImage();
    void sortFrequency();
	Color getClosestColorVal(int loc); 	// Find color that most closely matches one of the high frequency values for texture at location

    TextureTile* getTextureTileAt(int index) { return textures[index]; }
    Color getColorFromSortedFrequency(int index) { return textures[sortedFrequency[index].second]->getColor(); }
    int getSortedFrequencySize() { return sortedFrequency.size(); }

private:
	std::vector<TextureTile*> textures;

	Image image;
	int gridSize;
	int maxColor;

	std::map<float, int> grayFrequency; // first is gray value, second is pos in vector for first occurance
    std::vector<std::pair<int, int>> sortedFrequency;
	float width;
	float height;
};