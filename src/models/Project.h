#ifndef GOOGLE_HASH_CODE_2022_C___PROJECT_H
#define GOOGLE_HASH_CODE_2022_C___PROJECT_H

#include <string>
#include <vector>
#include "Skill.h"
#include "Person.h"

class Project {
public:
    std::string name;
    int duration{};
    int score{};
    int bestBefore{};
    std::vector<Skill> roles;
    std::vector<Person*> contributors;
    int progression = 0;
    int orderId = 0;
    bool isInProgress = false;

    Project();

    Project(std::string name, int duration, int score, int bestBefore, std::vector<Skill> roles);

    bool isFinished() const;

    int calculateActualScore(int actualDay) const;

    int getCompletedScore(int actualDay) const;
};


#endif //GOOGLE_HASH_CODE_2022_C___PROJECT_H
