#include "../../../../Include/Trambo/Tiles/layer.h"

using namespace trmb;

Layer::Layer(std::string name, uint width, uint height, std::vector<uint> tiles)
: mName(name)
, mWidth(width)
, mHeight(height)
, mTiles(tiles)
{
}