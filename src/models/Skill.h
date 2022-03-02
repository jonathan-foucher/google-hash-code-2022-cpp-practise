#ifndef GOOGLE_HASH_CODE_2022_C___SKILL_H
#define GOOGLE_HASH_CODE_2022_C___SKILL_H

#include <string>

class Skill {
public:
    std::string name;
    int level = 0;

    Skill();

    Skill(std::string name, int level);
};


#endif //GOOGLE_HASH_CODE_2022_C___SKILL_H
