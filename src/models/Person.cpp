#include "Person.h"
#include <utility>

Person::Person() = default;

Person::Person(std::string name, const LinkedList<Skill> &skills) : name(std::move(name)), skills(skills) {}

bool Person::hasSkill(const std::string& skillName, int skillLevel) {
    int i = 0;
    while (skills.size > i) {
        if(skills[i]->name == skillName && skills[i]->level >= skillLevel) {
            return true;
        }
    }
    return false;
}
