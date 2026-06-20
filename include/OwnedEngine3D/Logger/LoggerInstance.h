#pragma once
#include "OwnedEngine3D/Export.h"
#include "OwnedEngine3D/Logger/Logger.h"
#include <iostream>
#include <fstream>

class OWNED_ENGINE_API ConsoleLogger : public Logger
{
private:
	void Write(const std::string& message) override;
	void WriteWarning(const std::string& message) override;
	void WriteError(const std::string& message) override;
};


class OWNED_ENGINE_API FileLogger : public Logger
{
public:
	explicit FileLogger(const std::string& file);
	~FileLogger() override;

private:
	void Write(const std::string& message) override;
	void WriteWarning(const std::string& message) override;
	void WriteError(const std::string& message) override;

	std::ofstream m_file;
};