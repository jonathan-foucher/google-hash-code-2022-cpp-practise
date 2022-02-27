#include <iostream>
#include <functional>
#include "models/LinkedList.h"
#include "models/Skill.h"
#include "models/Person.h"


int main() {
    LinkedList<Skill> skills;

    Skill skill("C++", 2);
    skills.add(skill);

    Skill skill2("Python", 7);
    skills.add(skill2);

    Skill skill3("Java", 5);
    skills.add(skill3);

    Skill skill4("Javascript", 4);
    skills.add(skill4);

    Person person("Testo", skills);

    std::string nameSearched = "C++";
    int levelRequired = 6;

    std::optional<Skill> opt = person.skills.find([nameSearched, levelRequired](Skill s) -> bool {
        if (s.name == nameSearched && s.level >= levelRequired) {
            return true;
        }
        return false;
    });

    if(opt.has_value()) {
        std::cout << opt.value().name << std::endl;
    } else {
        std::cout << "not found" << std::endl;
    }

    person.skills.map<std::string>([](Skill s) -> std::string {
        return s.name;
    }).forEach([](std::string s) -> void {
        std::cout << s << std::endl;
    });

    person.skills.remove(*skills[4]);

    person.skills.map<std::string>([](Skill s) -> std::string {
        return s.name;
    }).forEach([](std::string s) -> void {
        std::cout << s << std::endl;
    });

    person.skills.remove(5);

    person.skills.map<std::string>([](Skill s) -> std::string {
        return s.name;
    }).forEach([](std::string s) -> void {
        std::cout << s << std::endl;
    });

    return 0;
}
