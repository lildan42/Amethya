#pragma once

#include "pch.h"
#include "SpriteCollection.h"

namespace Resources {
	struct SpriteCollection;

	class ResourceManager {
	private:
		const std::string TEXTURE_LOCATION = "Resources/textures.json";
		std::map<std::string, SpriteCollection> spriteCollections;

		ResourceManager();

		void loadTextures();

	public:
		static bool parseJsonFile(std::string path, rapidjson::Document& document);

		ResourceManager(const ResourceManager&) = delete;
		void operator =(const ResourceManager&) = delete;

		sf::Sprite& getSprite(std::string texture, size_t index);

		static ResourceManager& getInstance();
	};
}