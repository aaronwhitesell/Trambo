#include "../../../../Include/Trambo/Localize/localize.h"


namespace trmb
{

Localize::Localize()
: mLanguage("en")
{
}

Localize& Localize::getInstance()
{
	static Localize mInstance;
	return mInstance;
}

std::string Localize::getLanguage() const
{
	return mLanguage;
}

std::string Localize::getString(const std::string& name) const
{
	tinyxml2::XMLDocument config;
	loadFile(config);
	return lookup(config, name);
}

void Localize::setFilePath(const std::string& filePath)
{
	mFilePath = filePath;
}

void Localize::setLanguage(const std::string& language)
{
	mLanguage = language;
}

void Localize::loadFile(tinyxml2::XMLDocument& config) const
{
	if (config.LoadFile(mFilePath.c_str()) != tinyxml2::XML_NO_ERROR)
	{
		throw std::runtime_error("TinyXML2 - Failed to load " + mFilePath);
	}
}

std::string Localize::lookup(tinyxml2::XMLDocument &config, const std::string& name) const
{
	tinyxml2::XMLElement* text = config.FirstChildElement("text");
	if (text == nullptr)
		throw std::runtime_error("TinyXML2 - The text element cannot be found. File: " + mFilePath);

	tinyxml2::XMLElement* language = text->FirstChildElement(mLanguage.c_str());
	if (language == nullptr)
		throw std::runtime_error("TinyXML2 - The language element cannot be found. File: " + mFilePath);

	tinyxml2::XMLElement* strName = language->FirstChildElement(name.c_str());
	if (strName == nullptr)
		throw std::runtime_error("TinyXML2 - The " + name + " element cannot be found. File: " + mFilePath);

	const char* localizedString = strName->Attribute("attribute");
	if (localizedString == nullptr)
		throw std::runtime_error("TinyXML2 - The " + name + " attribute cannot be found. File: " + mFilePath);

	return localizedString;
}

} // namespace trmb
