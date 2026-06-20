#pragma once
#include "OwnedEngine3D/Export.h"
#include <string>
#include <memory>
#include <format>

class OWNED_ENGINE_API Logger
{
public:
	Logger() = default;
	virtual ~Logger() = default;

	Logger(const Logger&) = default;
	Logger(Logger&&) = default;

	static void SetLog(std::unique_ptr<Logger> logger);
	static std::string CurrentDate();
	static std::string CurrentTime();

	template<typename... Args>
	static void Log(std::format_string<Args...> fmt, Args&&... args);
	template<typename... Args>
	static void LogWarning(std::format_string<Args...> fmt, Args&&... args);
	template<typename... Args>
	static void LogError(std::format_string<Args...> fmt, Args&&... args);

private:
	virtual void Write(const std::string& message) = 0;
	virtual void WriteWarning(const std::string& message) = 0;
	virtual void WriteError(const std::string& message) = 0;

	static std::unique_ptr<Logger> m_instance;
};



template<typename... Args>
void Logger::Log(std::format_string<Args...> fmt, Args&&... args)
{
	if (m_instance)
		m_instance->Write(std::format(fmt, std::forward<Args>(args)...));
}

template<typename... Args>
void Logger::LogWarning(std::format_string<Args...> fmt, Args&&... args)
{
	if (m_instance)
		m_instance->WriteWarning(std::format(fmt, std::forward<Args>(args)...));
}

template<typename... Args>
void Logger::LogError(std::format_string<Args...> fmt, Args&&... args)
{
	if (m_instance)
		m_instance->WriteError(std::format(fmt, std::forward<Args>(args)...));
}