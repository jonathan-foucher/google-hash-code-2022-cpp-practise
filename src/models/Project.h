#ifndef GOOGLE_HASH_CODE_2022_C___PROJECT_H
#define GOOGLE_HASH_CODE_2022_C___PROJECT_H

#include <string>
#include "Skill.h"
#include "Person.h"
#include "LinkedList.h"

class Project {
public:
    std::string name;
    int duration;
    int score;
    int bestBefore;
    LinkedList<Skill> roles;
    LinkedList<Person> contributors;
    int progression = 0;
    int orderId = 0;
    bool isInProgress = false;

    Project();

    Project(const std::string &name, int duration, int score, int bestBefore, const LinkedList<Skill> &roles);

    bool isFinished();

    int calculateActualScore(int actualDay);

    int getCompletedScore(int actualDay);
};


#endif //GOOGLE_HASH_CODE_2022_C___PROJECT_H
