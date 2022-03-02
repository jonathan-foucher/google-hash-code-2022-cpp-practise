#include <iostream>
#include "services/FileService.h"
#include "services/ProcessingService.h"
#include <filesystem>
#include <vector>

using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

int main() {
    std::string inputPath = R"(../resources/input-files)";
    std::string outputPath = R"(../resources/output-files)";
    FileService fileService;

    std::vector<std::filesystem::directory_entry> files;
    for (const auto &dirEntry: recursive_directory_iterator(inputPath)) {
        files.push_back(dirEntry);
    }

    sort(files.begin(), files.end(), [](const std::filesystem::directory_entry &dirEntryA, const std::filesystem::directory_entry &dirEntryB) -> bool {
        return dirEntryA.path().filename().compare(dirEntryB.path().filename()) < 0;
    });

    std::for_each(files.begin(), files.end(), [fileService, outputPath](const std::filesystem::directory_entry &dirEntry) -> void {
        std::string fileName = dirEntry.path().filename();
        std::cout << "processing file : " + fileName << std::endl;
        std::vector<std::string> inputContent = FileService::readFile(dirEntry.path());

        ProcessingService processingService;
        std::vector<std::string> outputContent = processingService.process(inputContent);

        FileService::writeFile(outputPath + "/" + fileName.substr(0, fileName.size() - 4) + "_result.txt", outputContent);
        std::cout << fileName + " done" << std::endl;
    });

    return 0;
}
