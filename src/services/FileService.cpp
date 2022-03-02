#include <vector>
#include "FileService.h"

std::vector<std::string> FileService::readFile(const std::string &filePath) {
    std::vector<std::string> content;
    std::string text;
    std::ifstream file(filePath);

    while (getline(file, text)) {
        content.push_back(text);
    }

    file.close();
    return content;
}

void FileService::writeFile(const std::string &filePath, std::vector<std::string> content) {
    std::ofstream file(filePath);

    std::for_each(content.begin(), content.end(), [&file](std::string s) -> void {
        file << s << std::endl;
    });

    file.close();
}
