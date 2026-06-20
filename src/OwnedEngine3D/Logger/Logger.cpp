#include "OwnedEngine3D/Logger/Logger.h"
#include <ctime>

std::unique_ptr<Logger> Logger::m_instance = nullptr;

void Logger::SetLog(std::unique_ptr<Logger> logger)
{
	m_instance = std::move(logger);
}

std::string Logger::CurrentDate()
{
	time_t timestamp = time(NULL);
	tm datetime = *localtime(&timestamp);

	char buffer[50];
	size_t size = strftime(buffer, sizeof(buffer), "%B%e %Y", &datetime);

	return std::string(buffer, size);
}

std::string Logger::CurrentTime()
{
	time_t timestamp = time(NULL);
	tm datetime = *localtime(&timestamp);

	char buffer[50];
	size_t size = strftime(buffer, sizeof(buffer), "%H:%M:%S", &datetime);

	return std::string(buffer, size);
}