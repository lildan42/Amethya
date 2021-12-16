#include "ResourceManager.h"

using namespace rapidjson;
namespace fs = std::filesystem;

namespace Resources {
	ResourceManager::ResourceManager() {}

	ResourceManager& ResourceManager::getInstance() {
		static ResourceManager instance;
		return instance;
	}

	Document ResourceManager::parseJsonFile(std::string path) {
		Document document;

		fs::path fullPath = RESOURCE_DIR + "/" + path;

		if (!fs::exists(fullPath)) {
			std::cerr << "File " << fullPath << " does not exist." << std::endl;
			return document;
		}

		std::ifstream inputStream;
		inputStream.open(fullPath, std::ios::in);

		std::stringstream contentBuffer;
		contentBuffer << inputStream.rdbuf();

		document.Parse(contentBuffer.str().c_str());

		return document;
	}
}