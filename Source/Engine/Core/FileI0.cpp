#include "FileI0.h"

namespace F {
	std::string getFilePath()
	{
		return std::filesystem::current_path().string();
	}
}