#ifndef TRAMBO_TILESET_H
#define TRAMBO_TILESET_H

#include <string>

namespace trmb
{

class Tileset
{
							friend class Map;
							friend class MapLayerNode;


public:
							Tileset(std::string name, std::string source, int width, int height, int tileWidth, 
								int tileHeight, int firstGid);


private:
	std::string				mName;
	std::string				mSource;
	int						mWidth;
	int						mHeight;
	int						mTileWidth;
	int						mTileHeight;
	int						mFirstGid;
	int						mLastGid;
	int						mWidthInTiles;
};

} // namespace trmb

#endif
