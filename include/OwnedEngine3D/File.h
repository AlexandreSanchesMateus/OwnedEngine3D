#pragma once

#include <string>
#include <filesystem>
#include <rapidjson/document.h>

namespace paths
{
	inline const std::filesystem::path Assets = "assets";
	inline const std::filesystem::path Configs = Assets / "configs";
	inline const std::filesystem::path Shaders = Assets / "shaders";
	inline const std::filesystem::path CompiledShaders = Shaders / "compiled";
	inline const std::filesystem::path Textures = Assets / "textures";
}

namespace fileutil {
	rapidjson::Document ReadJsonFile(const std::filesystem::path& path);
	void WriteJsonFile(const std::filesystem::path& path, const rapidjson::Document& document);
}