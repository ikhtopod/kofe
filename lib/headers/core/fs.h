#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
#include <filesystem>


namespace filesystem {

std::string GetContentFile(const std::filesystem::path& path);

}

#endif // FILESYSTEM_H
