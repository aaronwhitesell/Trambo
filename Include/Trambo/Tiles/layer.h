#ifndef TRAMBO_LAYER_H
#define TRAMBO_LAYER_H

#include <string>
#include <vector>


namespace trmb
{

class Layer
{
							friend class MapLayerNode;


public:
							Layer(std::string name, int width, int height, std::vector<int> tiles);


private:
	std::string				mName;
	int						mWidth;
	int						mHeight;

	std::vector<int>		mTiles;		// ALW - Tile gids
};

} // namespace trmb

#endif
