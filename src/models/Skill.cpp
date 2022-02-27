#include "Skill.h"
#include <utility>

Skill::Skill() = default;

Skill::Skill(std::string name, int level) : name(std::move(name)), level(level) {}
