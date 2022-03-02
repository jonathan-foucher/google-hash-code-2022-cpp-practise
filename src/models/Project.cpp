#include "Project.h"

#include <utility>

Project::Project() = default;

Project::Project(std::string name, int duration, int score, int bestBefore, std::vector<Skill> roles) : name(std::move(name)), duration(duration), score(score), bestBefore(bestBefore), roles(std::move(roles)) {}

bool Project::isFinished() const {
    return progression == duration;
}

int Project::calculateActualScore(int actualDay) const {
    int scorePenalty = actualDay + duration - bestBefore;
    int actualScore = scorePenalty > 0 ? score - scorePenalty : score;
    return actualScore > 0 ? actualScore : 0;
}

int Project::getCompletedScore(int actualDay) const {
    int scorePenalty = actualDay - bestBefore;
    int actualScore = scorePenalty > 0 ? score - scorePenalty : score;
    return actualScore > 0 ? actualScore : 0;
}
