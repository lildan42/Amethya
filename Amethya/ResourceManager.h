#pragma once

#include "pch.h"

namespace Resources {
	static const std::string RESOURCE_DIR = "Resources";

	class ResourceManager {
	private:
		ResourceManager();

	public:
		static rapidjson::Document parseJsonFile(std::string path);

		ResourceManager(const ResourceManager&) = delete;
		void operator =(const ResourceManager&) = delete;

		static ResourceManager& getInstance();
	};
}