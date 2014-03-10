#ifndef TRAMBO_MAP_H
#define TRAMBO_MAP_H

#include "layer.h"
#include "tileset.h"
#include "../types.h"

#include "../../../Source/3rdParty/TinyXML2/tinyxml2.h"

#include <string>
#include <vector>

namespace trmb
{

class Map
{
public:
	void					read(const std::string& filename);


private:
	void					loadFile(const std::string& filename, tinyxml2::XMLDocument& config);
	void					readMap(tinyxml2::XMLDocument& config);
	void					readTilesets(tinyxml2::XMLDocument& config);
	void                    readLayers(tinyxml2::XMLDocument& config);


private:
	uint					mWidth;
	uint					mHeight;
	uint					mTileWidth;
	uint					mTileHeight;

	std::vector<Tileset>	mTilesets;
	std::vector<Layer>		mLayers;
};

} // namespace trmb

#endif
