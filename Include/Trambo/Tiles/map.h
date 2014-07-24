#ifndef TRAMBO_MAP_H
#define TRAMBO_MAP_H

#include "layer.h"
#include "tileset.h"

#include "../../../Source/3rdParty/TinyXML2/tinyxml2.h"

#include <SFML/Graphics/Texture.hpp>

#include <string>
#include <vector>


namespace trmb
{

class Map
{
							friend class MapLayerNode;


public:
							Map();
	explicit				Map(const std::string& filename);
							Map(const Map &) = delete;
	Map &					operator=(const Map &) = delete;

	void					read(const std::string& filename);


private:
	void					loadFile(const std::string& filename, tinyxml2::XMLDocument& config);
	void					readMap(tinyxml2::XMLDocument& config);
	void					readTilesets(tinyxml2::XMLDocument& config);
	void                    readLayers(tinyxml2::XMLDocument& config);

	void					loadTilesetTextures();


private:
	int							mWidth;
	int							mHeight;
	int							mTileWidth;
	int							mTileHeight;

	std::vector<Tileset>		mTilesets;
	std::vector<Layer>			mLayers;

	std::vector<sf::Texture>	mTilesetTextures;
};

} // namespace trmb

#endif
