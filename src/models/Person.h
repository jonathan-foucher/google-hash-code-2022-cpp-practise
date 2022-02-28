#ifndef GOOGLE_HASH_CODE_2022_C___PERSON_H
#define GOOGLE_HASH_CODE_2022_C___PERSON_H

#include "../utils/LinkedList.h"
#include "Skill.h"

class Person {
public:
    std::string name;
    LinkedList<Skill> skills;
    bool isAvailable = true;

    Person();

    Person(std::string name, const LinkedList<Skill> &skills);

    bool hasSkill(const std::string& skillName, int skillLevel);
};

#endif //GOOGLE_HASH_CODE_2022_C___PERSON_H
