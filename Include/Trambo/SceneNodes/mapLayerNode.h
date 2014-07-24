#ifndef TRAMBO_MAP_LAYER_NODE_H
#define TRAMBO_MAP_LAYER_NODE_H

#include "sceneNode.h"
#include "../Tiles/map.h"


namespace sf
{
	class RenderStates;
	class RenderTarget;
}

namespace trmb
{

class MapLayerNode : public SceneNode
{
public:
						MapLayerNode(const Map &map, std::size_t layerIndex);
						MapLayerNode(const MapLayerNode &) = delete;
	MapLayerNode &		operator=(const MapLayerNode &) = delete;


private:
	virtual void		drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

	int					getGidOffset(int gid) const;
	std::size_t			getTilesetIndex(int gid) const;


private:
	const Map			&mMap;
	const std::size_t	mLayerIndex;
};

} // namespace trmb

#endif
