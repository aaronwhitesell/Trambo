#ifndef TRAMBO_LAYER_H
#define TRAMBO_LAYER_H

#include "../types.h"

#include <string>
#include <vector>

namespace trmb
{

class Layer
{
public:
							Layer(std::string name, uint width, uint height, std::vector<uint> tiles); 

private:
	std::string				mName;
	uint					mWidth;
	uint					mHeight;

	std::vector<uint>		mTiles;		// ALW - Tile gids
};

} // namespace trmb

#endif
