#ifndef GOOGLE_HASH_CODE_2022_C___PROCESSINGSERVICE_H
#define GOOGLE_HASH_CODE_2022_C___PROCESSINGSERVICE_H

#include "../models/LinkedList.h"
#include "../models/Skill.h"
#include "../models/Person.h"
#include "../models/Project.h"

class ProcessingService {
public:
    LinkedList<std::string> process(LinkedList<std::string> inputContent) const;
};


#endif //GOOGLE_HASH_CODE_2022_C___PROCESSINGSERVICE_H
