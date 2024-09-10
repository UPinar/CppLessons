#include "file.h"
#include <stdexcept>

std::ofstream create_text_file(const std::string filename)
{
	std::ofstream ofs{ filename };

	if (!ofs) {
		throw std::runtime_error{ filename + " can not be created!" };
	}
	return ofs;
}
// stream classes can not be copied but move. (Move only classes) 
// Because of ofs is a automatic duration object move semantics will be applied.


std::ifstream open_text_file(const std::string filename)
{
	std::ifstream ifs{ filename };

	if (!ifs) {
		throw std::runtime_error{ filename + " can not be opened!" };
	}
	return ifs;
}

std::ofstream create_binary_file(const std::string filename)
{
	std::ofstream ofs{ filename, std::ios::binary };

	if (!ofs) {
		throw std::runtime_error{ filename + " can not be created!" };
	}
	return ofs;
}
std::ifstream open_binary_file(const std::string filename)
{
	std::ifstream ifs{ filename, std::ios::binary };

	if (!ifs) {
		throw std::runtime_error{ filename + " can not be opened!" };
	}
	return ifs;
}