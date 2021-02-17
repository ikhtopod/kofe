#include "misc/fs.h"

#include "app_exceptions.h"

#include <sstream>
#include <fstream>


namespace filesystem {

namespace fs = std::filesystem;

std::string GetContentFile(const std::filesystem::path& path) {
    if (!fs::exists(path) || fs::is_directory(path) || !fs::is_regular_file(path)) return {};

    std::ifstream file {};
    file.exceptions(std::ios::failbit | std::ios::badbit);

    std::ostringstream result {};

    try {
        file.open(path, std::ios::in);
        result << file.rdbuf();
    } catch (const std::exception& e) {
        file.close();
        throw FilesystemException { "Cannot open file " + path.string() + ": " + e.what() };
    } catch (...) {
        file.close();
        throw;
    }

    file.close();

    return result.str();
}

} // namespace filesystem
