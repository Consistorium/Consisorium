#pragma once

#include <string>
#include <fstream>
#include <filesystem/dirent.h>
#include <sstream>
#include <vector>

namespace Utils {

	inline std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
		std::stringstream ss(s);
		std::string item;
		while (std::getline(ss, item, delim)) {
			if (!item.empty())
			{
				elems.push_back(item);
			}
		}
		return elems;
	}

	inline std::vector<std::string> split(const std::string &s, char delim) {
		std::vector<std::string> elems;
		split(s, delim, elems);
		return elems;
	}

	inline std::vector<std::string> getDirectoryContents(const std::string &path)
	{
		std::vector<std::string> result;

		struct DIR *directory;
		struct dirent *dir;
		directory = opendir(path.c_str());
		if (directory)
		{
			while ((dir = readdir(directory)) != nullptr)
			{
				std::string s(dir->d_name);
				result.push_back(s);
			}

			closedir(directory);
		}

		return result;
	}

	inline std::vector<std::string> getFileContents(const std::string& path)
	{
		std::vector<std::string> result;
		std::ifstream file(path);
		std::string line;

		while (std::getline(file, line))
		{
			result.push_back(line);
		}

		return result;
	}
}