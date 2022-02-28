#ifndef GOOGLE_HASH_CODE_2022_C___FILESERVICE_H
#define GOOGLE_HASH_CODE_2022_C___FILESERVICE_H

#include <fstream>

#include "../models/LinkedList.h"

class FileService {
public:
    LinkedList<std::string> readFile(const std::string& filePath) const;

    void writeFile(const std::string& filePath, LinkedList<std::string> content) const;
};


#endif //GOOGLE_HASH_CODE_2022_C___FILESERVICE_H
