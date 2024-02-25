#pragma once
#include<exception>
#include<string>

class SongException :public std::exception
{
public:
	SongException(const std::string& msg) :message(msg) {}
	const char* what() const noexcept override
	{
		return message.c_str();
	}

private:
	std::string message;

};