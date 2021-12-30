#include "ResourceManager.h"

using namespace rapidjson;
namespace fs = std::filesystem;

namespace Resources {

	ResourceManager::ResourceManager() {
		this->loadTextures();
	}

	void ResourceManager::loadTextures() {
		Document textures;

		if (!this->parseJsonFile(TEXTURE_LOCATION, textures)) {
			std::cerr << "Unable to load textures." << std::endl;
			return;
		}

		for (auto it = textures.MemberBegin(); it != textures.MemberEnd(); it++) {
			//TODO error handling

			std::string fileLocation = it->value["location"].GetString();

			const auto& [spriteCollection, inserted] = this->spriteCollections.emplace(it->name.GetString(), SpriteCollection(fileLocation));

			if (!inserted) {
				std::cerr << "Unable to load textures." << std::endl;
				return;
			}

			for (const auto& spriteInfo : it->value["sprites"].GetArray()) {
				sf::Sprite sprite;

				auto rectArr = spriteInfo["rect"].GetArray();
				auto colorArr = spriteInfo["color"].GetArray();

				sprite.setTextureRect(sf::IntRect(rectArr[0].GetInt(), rectArr[1].GetInt(), rectArr[2].GetInt(), rectArr[3].GetInt()));
				sprite.setColor(sf::Color(colorArr[0].GetInt(), colorArr[1].GetInt(), colorArr[2].GetInt(), colorArr[3].GetInt()));

				spriteCollection->second.addSprite(sprite);
			}
		}
	}

	sf::Sprite& ResourceManager::getSprite(std::string texture, size_t index) {
		if (this->spriteCollections.find(texture) == this->spriteCollections.end()) {
			std::cerr << "Texture by the name of " << texture << " does not exist." << std::endl;
		}

		return this->spriteCollections[texture][index];
	}

	ResourceManager& ResourceManager::getInstance() {
		static ResourceManager instance;
		return instance;
	}

	bool ResourceManager::parseJsonFile(std::string path, Document& document) {
		if (!fs::exists(path)) {
			std::cerr << "File " << path << " does not exist." << std::endl;
			return false;
		}

		std::ifstream inputStream;
		inputStream.open(path, std::ios::in);

		std::stringstream contentBuffer;
		contentBuffer << inputStream.rdbuf();

		document.Parse(contentBuffer.str().c_str());

		return document.IsObject();
	}
}