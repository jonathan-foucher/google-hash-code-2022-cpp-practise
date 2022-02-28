#ifndef GOOGLE_HASH_CODE_2022_C___PROCESSINGSERVICE_H
#define GOOGLE_HASH_CODE_2022_C___PROCESSINGSERVICE_H

#include "../utils/LinkedList.h"
#include "../models/Skill.h"
#include "../models/Person.h"
#include "../models/Project.h"

class ProcessingService {
public:
    int score = 0;
    LinkedList<Person> persons;
    LinkedList<Project> projects;
    int actualDay = 0;
    int projectOrderId = 1;

    LinkedList<std::string> process(LinkedList<std::string> inputContent);

    void fileContentToObjects(LinkedList<std::string> content);

    void simulate();

    LinkedList<std::string> formatResults();
};


#endif //GOOGLE_HASH_CODE_2022_C___PROCESSINGSERVICE_H
