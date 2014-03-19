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
	// Forward declares for resource holders
	class Texture;
	class Font;
	class Shader;
	class SoundBuffer;
}

namespace Textures
{
	// Forward declares for TextureHolder
	enum ID : unsigned int;
}

namespace Fonts
{
	// Forward declares for FontHolder
	enum ID : unsigned int;
}

namespace Shaders
{
	// Forward declares for ShaderHolder
	enum ID : unsigned int;
}

namespace SoundEffect
{
	// Forward declares for SoundBufferHolder
	enum ID : unsigned int;
}

namespace trmb
{
	// Forward declares for resource holders
	template <typename Resource, typename Identifier>
	class ResourceHolder;

	typedef ResourceHolder<sf::Texture, Textures::ID>			TextureHolder;
	typedef ResourceHolder<sf::Font, Fonts::ID>					FontHolder;
	typedef ResourceHolder<sf::Shader, Shaders::ID>				ShaderHolder;
	typedef ResourceHolder<sf::SoundBuffer, SoundEffect::ID>	SoundBufferHolder;
}

#endif
