#pragma once
class FilePath
{
private:
	std::map<std::string, std::string> path;

public:
	FilePath();
	std::string getPath(std::string& key);
};

