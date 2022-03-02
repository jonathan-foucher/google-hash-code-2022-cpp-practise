#ifndef GOOGLE_HASH_CODE_2022_C___FILESERVICE_H
#define GOOGLE_HASH_CODE_2022_C___FILESERVICE_H

#include <fstream>
#include <vector>

class FileService {
public:
    static std::vector<std::string> readFile(const std::string &filePath);

    static void writeFile(const std::string &filePath, std::vector<std::string> content);
};


#endif //GOOGLE_HASH_CODE_2022_C___FILESERVICE_H
