#ifndef GOOGLE_HASH_CODE_2022_C___PERSON_H
#define GOOGLE_HASH_CODE_2022_C___PERSON_H

#include <vector>
#include "Skill.h"

class Person {
public:
    std::string name;
    std::vector<Skill> skills;
    bool isAvailable = true;

    Person();

    Person(std::string name, std::vector<Skill> skills);

    bool hasSkill(const std::string &skillName, int skillLevel);
};

#endif //GOOGLE_HASH_CODE_2022_C___PERSON_H
