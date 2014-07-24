#include "../../../../Include/Trambo/Tiles/map.h"

#include <cassert>


namespace trmb
{

Map::Map()
{
}

Map::Map(const std::string& filename)
{
	read(filename);
	loadTilesetTextures();
}

void Map::read(const std::string& filename)
{
	tinyxml2::XMLDocument config;
	loadFile(filename, config);
	readMap(config);
	readTilesets(config);
	readLayers(config);
}

void Map::loadFile(const std::string& filename, tinyxml2::XMLDocument& config)
{
	if (config.LoadFile(filename.c_str()) != tinyxml2::XML_NO_ERROR)
	{
		throw std::runtime_error("TinyXML2 - Failed to load " + filename);
	}
}

void Map::readMap(tinyxml2::XMLDocument& config)
{
	tinyxml2::XMLElement* map = config.FirstChildElement("map");
	if (!map)
	{
		// ALW - There is no map to read! This must be a incorrectly formatted TMX file.
		assert(map);
	}

	mWidth      = map->IntAttribute("width");
	mHeight     = map->IntAttribute("height");
	mTileWidth  = map->IntAttribute("tilewidth");
	mTileHeight = map->IntAttribute("tileheight");
}

void Map::readTilesets(tinyxml2::XMLDocument& config)
{
	tinyxml2::XMLElement* tileset = config.FirstChildElement("map")->FirstChildElement("tileset");
	if (!tileset)
	{
		// ALW - There must be at least one tileset! This must be a incorrectly formatted TMX file.
		assert(tileset);
	}

	for (; tileset != nullptr; tileset = tileset->NextSiblingElement("tileset"))
	{
		int firstGid       = tileset->IntAttribute("firstgid");
		std::string name   = tileset->Attribute("name");
		int tileWidth      = tileset->IntAttribute("tilewidth");
		int tileHeight     = tileset->IntAttribute("tileheight");
		std::string source = tileset->FirstChildElement("image")->Attribute("source");
		int width          = tileset->FirstChildElement("image")->IntAttribute("width");
		int height         = tileset->FirstChildElement("image")->IntAttribute("height");

		mTilesets.push_back(Tileset(name, source, width, height, tileWidth, tileHeight, firstGid));
	}
}

void Map::readLayers(tinyxml2::XMLDocument& config)
{
	tinyxml2::XMLElement* layer = config.FirstChildElement("map")->FirstChildElement("layer");
	if (!layer)
	{
		// ALW - There must be at least one layer! This must be a incorrectly formatted TMX file.
		assert(layer);
	}

	for (; layer != nullptr; layer = layer->NextSiblingElement("layer"))
	{
		std::string name = layer->Attribute("name");  
		int width        = layer->IntAttribute("width");
		int height       = layer->IntAttribute("height");
		
		std::vector<int> tiles;
		tinyxml2::XMLElement* tile = layer->FirstChildElement("data")->FirstChildElement("tile");
		for (; tile != nullptr; tile = tile->NextSiblingElement("tile"))
			tiles.push_back(tile->IntAttribute("gid"));
	
		mLayers.push_back(Layer(name, width, height, tiles));
	}
}

void Map::loadTilesetTextures()
{
	// ALW - Tileset textures are loaded here only once, instead of loading them
	// ALW - multiple times in each instance of the MapLayerNode class.
	std::string path = "Data/Textures/";

	sf::Texture texture;
	for (auto const &tileset : mTilesets)
	{
		texture.loadFromFile(path + tileset.mName + ".png");
		mTilesetTextures.push_back(texture);
	}
}

} // namespace trmb
