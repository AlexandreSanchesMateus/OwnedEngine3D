#include "OwnedEngine3D/File.h"
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/writer.h>
#include <fstream>

namespace fileutil {
	rapidjson::Document ReadJsonFile(const std::filesystem::path& path)
	{
		std::ifstream stream;
		stream.open(path, std::ios::in);

		if (!stream.is_open())
			throw std::runtime_error("[FileUtilities] ReadJsonFile: Failed to open file at " + path.string());

		rapidjson::IStreamWrapper isw(stream);
		rapidjson::Document doc;
		doc.ParseStream(isw);
		stream.close();

		if (doc.HasParseError())
			throw std::runtime_error("[FileUtilities] ReadJsonFile: Failed to parse properties. code " + doc.GetParseError());

		return std::move(doc);
	}

	void WriteJsonFile(const std::filesystem::path& path, const rapidjson::Document& document)
	{
		std::ofstream stream;
		stream.open(path, std::ios::out);

		rapidjson::OStreamWrapper osw(stream);
		rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
		document.Accept(writer);
	}
}