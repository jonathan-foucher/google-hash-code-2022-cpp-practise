#ifndef GOOGLE_HASH_CODE_2022_C___PROCESSINGSERVICE_H
#define GOOGLE_HASH_CODE_2022_C___PROCESSINGSERVICE_H

#include "../models/Skill.h"
#include "../models/Person.h"
#include "../models/Project.h"

class ProcessingService {
public:
    int score = 0;
    std::vector<Person> persons;
    std::vector<Project> projects;
    int actualDay = 0;
    int projectOrderId = 1;

    std::vector<std::string> process(std::vector<std::string> inputContent);

    void fileContentToObjects(std::vector<std::string> content);

    void simulate();

    std::vector<std::string> formatResults();
};


#endif //GOOGLE_HASH_CODE_2022_C___PROCESSINGSERVICE_H
