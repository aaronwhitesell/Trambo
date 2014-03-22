#ifndef TRAMBO_RESOURCE_HOLDER_H
#define TRAMBO_RESOURCE_HOLDER_H

#include <cassert>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>


namespace trmb
{

template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
	void					load(Identifier id, const std::string& filename);

	template <typename Parameter>
	void					load (Identifier id, const std::string& filename, const Parameter& secondParam);

	Resource&				get(Identifier id);
	const Resource&			get(Identifier id) const;


private:
	void					insertResource(Identifier id, std::unique_ptr<Resource> resource);


private:
	std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

#include "resourceHolder.inl"

} // namespace trmb


// Define the most common types of resource holders
namespace sf
{
	class Texture;
	class Font;
	class Shader;
	class SoundBuffer;
}

namespace Textures
{
	enum class ID;
}

namespace Fonts
{
	enum class ID;
}

namespace Shaders
{
	enum class ID;
}

namespace SoundEffects
{
	enum class ID;
}

namespace trmb
{
	template <typename Resource, typename Identifier>
	class ResourceHolder;

	typedef ResourceHolder<sf::Texture, Textures::ID>			TextureHolder;
	typedef ResourceHolder<sf::Font, Fonts::ID>					FontHolder;
	typedef ResourceHolder<sf::Shader, Shaders::ID>				ShaderHolder;
	typedef ResourceHolder<sf::SoundBuffer, SoundEffects::ID>	SoundBufferHolder;
}

#endif
