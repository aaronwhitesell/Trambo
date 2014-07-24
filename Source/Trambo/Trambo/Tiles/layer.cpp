#include "../../../../Include/Trambo/Tiles/layer.h"


namespace trmb
{

Layer::Layer(std::string name, int width, int height, std::vector<int> tiles)
: mName(name)
, mWidth(width)
, mHeight(height)
, mTiles(tiles)
{
}

} // namespace trmb
