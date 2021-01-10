#include "Encrypt.h"
size_t Encrypt::Readable_text(const std::string& text)
{
	std::hash<std::string> encrypt;
	return encrypt(text);
}