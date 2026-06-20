#include "OwnedEngine3D/Logger/LoggerInstance.h"
#include <fmt/core.h>
#include <fmt/color.h>

void ConsoleLogger::Write(const std::string& message)
{
	fmt::print("Log [{}] : {}\n", CurrentTime(), message);
}

void ConsoleLogger::WriteWarning(const std::string& message)
{
	fmt::print(fmt::fg(fmt::color::yellow), "Warrning [{}] : {}\n", CurrentTime(), message);
}

void ConsoleLogger::WriteError(const std::string& message)
{
	fmt::print(fmt::fg(fmt::color::red), "Error [{}] : {}\n", CurrentTime(), message);
}

FileLogger::FileLogger(const std::string& file)
{
	m_file.open("logs/" + file, std::ios::out | std::ios::trunc);

	if (m_file.is_open())
		m_file << "##### Beginning of file - " << CurrentDate() << " #### \n";
}

FileLogger::~FileLogger()
{
	m_file.close();
}

void FileLogger::Write(const std::string& message)
{
	if (m_file.is_open())
		m_file << "Log [" << CurrentDate() << " - " << CurrentTime() << "] " << message << '\n';
}

void FileLogger::WriteWarning(const std::string& message)
{
	if (m_file.is_open())
		m_file << "Warning [" << CurrentDate() << " - " << CurrentTime() << "] " << message << '\n';
}

void FileLogger::WriteError(const std::string& message)
{
	if (m_file.is_open())
		m_file << "Error [" << CurrentDate() << " - " << CurrentTime() << "] " << message << '\n';
}