#include "FullTexture.h"

void FullTexture::spliceImage()
{
    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {
            Rectangle rect;
            rect.width = width / gridSize;
            rect.height = height / gridSize;
            rect.x = j * rect.width;
            rect.y = i * rect.height;

            Image cropped = ImageFromImage(image, rect);
            textures.push_back(new TextureTile(cropped));

            // Calculate highest frequency value occuring throughout the image 
            float value = textures[(i * gridSize) + j]->getValue();
            if (value < 0.95 && grayFrequency.find(value) != grayFrequency.end())
            {
                textures[grayFrequency[value]]->addFrequency();
            }
            else if (value < 0.95)
            {
                grayFrequency.emplace(value, (i * gridSize) + j);
            }
        }
    }
}

void FullTexture::sortFrequency()
{
    // Used to hold frequency and texture vector locations for future sorting
    std::vector<std::pair<int, int>> holderVec(grayFrequency.size()); // first is frequency, second is loc in text vector
    for (auto i : grayFrequency)
    {
        holderVec.push_back(std::make_pair(textures[i.second]->getFrequency(), i.second));
    }

    int index = 0;
    sortedFrequency.push_back(std::make_pair(holderVec[0].first, holderVec[0].second));
    // Eliminates values that are similar to other values
    for (int i = 1; i < holderVec.size(); i++)
    {
        float currentVal = textures[holderVec[i].second]->getValue();
        float comparedVal = textures[holderVec[index].second]->getValue();
        if (!(comparedVal + 0.2 > currentVal && comparedVal - 0.2 < currentVal))
        {
            sortedFrequency.push_back(std::make_pair(holderVec[i].first, holderVec[i].second));
            index = i;
        }
    }

    // Sort so that those with higher frequency are at the beginning
    std::sort(sortedFrequency.begin(), sortedFrequency.end(), std::greater<std::pair<int, int>>());
    if (sortedFrequency.size() > maxColor)
        sortedFrequency.resize(maxColor);

    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {
            textures[(i * gridSize) + j]->setColor(getClosestColorVal((i * gridSize) + j));
        }
    }
}

Color FullTexture::getClosestColorVal(int loc)
{
    TextureTile textureTile = *textures[loc];
    Color color = textureTile.getColor();

    if (textureTile.getValue() != 1) // ignores white values
    {
        float smallestDist = 10;
        for (auto i : sortedFrequency)
        {
            float currentDist = abs(textures[i.second]->getValue() - textureTile.getValue());
            if (currentDist < smallestDist)
            {
                smallestDist = currentDist;
                color = textures[i.second]->getColor();
            }
        }
    }

    return color;
}