#include "../../../../Include/Trambo/SceneNodes/mapLayerNode.h"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <cassert>
#include <string>


namespace trmb
{

MapLayerNode::MapLayerNode(const Map &map, std::size_t layerIndex)
: mMap(map)
, mLayerIndex(layerIndex)
{
}

void MapLayerNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
	const Layer &layer = mMap.mLayers.at(mLayerIndex);
	std::vector<int>::const_iterator gidIter = layer.mTiles.begin(); // ALW - The GID specifies a tile in the tileset

	for (int column = 0; column < layer.mHeight; ++column)
	{
		for (int row = 0; row < layer.mWidth; ++row)
		{
			assert(("ALW - Logic Error: There are not enough GIDs (tiles) to populate the map!", gidIter != layer.mTiles.end()));
			
			const int blankTile = 0;
			if (*gidIter != blankTile) // ALW - A GID of zero is not meant to be drawn.
			{
				std::size_t tilesetIndex = getTilesetIndex(*gidIter);
				const int tileWidth = mMap.mTilesets.at(tilesetIndex).mTileWidth;
				int tilesetWidthInTiles = mMap.mTilesets.at(tilesetIndex).mWidth / tileWidth;

				int gid = *gidIter - getGidOffset(*gidIter);
				int left = (gid - 1) % tilesetWidthInTiles;
				int top = (gid - 1) / tilesetWidthInTiles;

				const int tileHeight = mMap.mTilesets.at(tilesetIndex).mTileHeight;
				sf::IntRect rect(left * tileWidth, top * tileHeight, tileWidth, tileHeight);
				sf::Sprite sprite(mMap.mTilesetTextures.at(tilesetIndex), rect);
				sprite.setPosition(sf::Vector2f(static_cast<float>(row) * tileWidth, static_cast<float>(column) * tileHeight));

				target.draw(sprite);
			}
			++gidIter;
		}
	}
}

int MapLayerNode::getGidOffset(int gid) const
{
	// ALW - Determine the offset of the gid.
	assert(("ALW - Logic Error: A gid of zero should have been skipped!", gid != 0));

	int offset = 0;
	for (const auto &tileset : mMap.mTilesets)
	{
		if (tileset.mFirstGid <= gid && gid <= tileset.mLastGid)
		{
			offset = tileset.mFirstGid - 1;
			break;
		}
	}

	return offset;
}

std::size_t MapLayerNode::getTilesetIndex(int gid) const
{
	// ALW - Determine the index for the tileset that the gid belongs to.
	assert(("ALW - Logic Error: A gid of zero should have been skipped!", gid != 0));

	std::size_t index = 0;
	for (const auto &tileset : mMap.mTilesets)
	{
		if (tileset.mFirstGid <= gid && gid <= tileset.mLastGid)
		{
			break;
		}

		++index;
	}

	return index;
}

} // namespace trmb
