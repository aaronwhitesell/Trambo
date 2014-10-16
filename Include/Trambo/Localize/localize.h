#ifndef TRAMBO_LOCALIZE_H
#define TRAMBO_LOCALIZE_H

#include "../../../3rdParty/TinyXML2/tinyxml2.h"

#include <string>


namespace trmb
{

class Localize
{
public:
						Localize(const Localize&) = delete;		// disallow copy constructor
	Localize&			operator=(const Localize&) = delete;	// disallow assignment operator

	static Localize&	getInstance();
	std::string		    getString(const std::string& name) const;

	void				setFilePath(const std::string& filePath);
	void				setLanguage(const std::string& language);


private:
	explicit			Localize();								// available only to members and friends
	void				loadFile(tinyxml2::XMLDocument& config) const;
	std::string			lookup(tinyxml2::XMLDocument& config, const std::string& name) const;


private:
	std::string			mFilePath;
	std::string			mLanguage;
};

} // namespace trmb

#endif
