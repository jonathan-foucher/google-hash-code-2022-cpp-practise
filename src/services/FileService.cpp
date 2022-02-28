#include "FileService.h"

LinkedList<std::string> FileService::readFile(const std::string &filePath) const {
    LinkedList<std::string> content;
    std::string text;
    std::ifstream file(filePath);

    while (getline(file, text)) {
        content.add(text);
    }

    file.close();
    return content;
}

void FileService::writeFile(const std::string &filePath, LinkedList<std::string> content) const {
    std::ofstream file(filePath);

    content.forEach([&file](std::string s) -> void {
        file << s << std::endl;
    });

    file.close();
}
