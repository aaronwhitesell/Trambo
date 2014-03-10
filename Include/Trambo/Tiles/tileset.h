#ifndef TRAMBO_TILESET_H
#define TRAMBO_TILESET_H

#include "../types.h"

#include <string>

namespace trmb
{

class Tileset
{
public:
							Tileset(std::string name, std::string source, uint width, uint height, uint tileWidth, 
								uint tileHeight, uint firstGid);


private:
	std::string				mName;
	std::string				mSource;
	uint                    mWidth;
	uint                    mHeight;
	uint					mTileWidth;
	uint					mTileHeight;
	uint					mFirstGid;
	uint					mLastGid;
	uint					mWidthInTiles;
};

} // namespace trmb

#endif
