#include <iostream>
#include "models/LinkedList.h"
#include "services/FileService.h"
#include "services/ProcessingService.h"
#include <filesystem>

using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

int main() {
    std::string inputPath = R"(../resources/input-files)";
    std::string outputPath = R"(../resources/output-files)";
    FileService fileService;
    ProcessingService processingService;

    LinkedList<std::filesystem::directory_entry> files;
    for (const auto &dirEntry: recursive_directory_iterator(inputPath)) {
        files.add(dirEntry);
    }

    files.sort([](const std::filesystem::directory_entry &dirEntryA, const std::filesystem::directory_entry &dirEntryB) -> bool {
        return dirEntryA.path().filename().compare(dirEntryB.path().filename()) < 0;
    }).forEach([fileService, outputPath, processingService](const std::filesystem::directory_entry &dirEntry) -> void {
        std::string fileName = dirEntry.path().filename();
        std::cout << "processing file : " + fileName << std::endl;
        LinkedList<std::string> inputContent = fileService.readFile(dirEntry.path());

        LinkedList<std::string> outputContent = processingService.process(inputContent);

        fileService.writeFile(outputPath + "/" + fileName.substr(0, fileName.size() - 4) + "_result.txt", outputContent);
        std::cout << fileName + " done" << std::endl;
    });

    return 0;
}
