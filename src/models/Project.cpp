#include "Project.h"

Project::Project() {}

Project::Project(const std::string &name, int duration, int score, int bestBefore, const LinkedList<Skill> &roles) : name(name), duration(duration), score(score), bestBefore(bestBefore), roles(roles) {}

bool Project::isFinished() {
    return progression == duration;
}

int Project::calculateActualScore(int actualDay) {
    int scorePenalty = actualDay + duration - bestBefore;
    int actualScore = scorePenalty > 0 ? score - scorePenalty : score;
    return actualScore > 0 ? actualScore : 0;
}

int Project::getCompletedScore(int actualDay) {
    int scorePenalty = actualDay - bestBefore;
    int actualScore = scorePenalty > 0 ? score - scorePenalty : score;
    return actualScore > 0 ? actualScore : 0;
}
