//Copyright Sam Collier 2022

//************************************************************************************
//Heavily influenced by 
//Chapter 2 of SFML Game Development by Artur Moreira, Henrik V. Hansson, and Jan Haller
//************************************************************************************

#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <map>

// holds resources in one place, in memory
// taking advantage of smart ptrs for RAII
// so no need to bother about new delete pairs
template <typename Resource, typename Identifier>
class ResourceHolder
{
	public:
		void load(Identifier id, const std::string &fileName);

		// overload get so it can be used in a const/read-only context

		// compiler lets these be overloaded because one has const at the end
		// which means that it is flagged not to modify this object
		// so when we get a const ref to a res holder you get back a const ref to a resource
		const Resource& get(Identifier id) const;
		Resource& get(Identifier id); 

	private:
		std::map<Identifier,std::unique_ptr<Resource>> resourceMap;
};

// forward declare resources here to be used for typedefs
namespace sf
{
	class Texture;
	class Font;
	class SoundBuffer;
};



template<typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string &fileName)
{
	// Initialize instance of resource, store in smrt ptr
	std::unique_ptr<Resource> resource(new Resource());
	// attempt to load from filePath
	if(!resource->loadFromFile(fileName))
	{
		std::cout << "<<<CRITICAL ERROR>>> FAILED TO LOAD FILE: " << fileName << std::endl;
	}
	// insert id/resource pair into our map of resources
	resourceMap.insert(std::make_pair(id,std::move(resource)));
}

template<typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
	auto found = resourceMap.find(id);
	return *found->second;
}

template<typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
	auto found = resourceMap.find(id);
	return *found->second;
}

