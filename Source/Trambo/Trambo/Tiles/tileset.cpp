#include "../../../../Include/Trambo/Tiles/tileset.h"

#include <cassert>
#include <math.h>


namespace trmb
{

Tileset::Tileset(std::string name, std::string source, int width, int height, int tileWidth, int tileHeight, int firstGid)
: mName(name)
, mSource(source)
, mWidth(width)
, mHeight(height)
, mTileWidth(tileWidth)
, mTileHeight(tileHeight)
, mFirstGid(firstGid)
{
	float widthInTiles = static_cast<float>(mWidth) / static_cast<float>(mTileWidth);
	float heightInTiles = static_cast<float>(mHeight) / static_cast<float>(mTileHeight);
	assert(widthInTiles == floor(widthInTiles));	// ALW - Tileset width should be evenly divided by tile width
	assert(heightInTiles == floor(heightInTiles));	// ALW - Tileset height should be evenly divided by tile height

	mWidthInTiles = static_cast<int>(widthInTiles);
	mLastGid = mWidthInTiles * static_cast<int>(heightInTiles) + mFirstGid - 1;
}

} // namespace trmb
