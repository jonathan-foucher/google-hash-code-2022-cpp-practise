#include <iostream>
#include <utility>
#include "ProcessingService.h"
#include "../utils/StringUtils.h"

using namespace std;

vector<string> ProcessingService::process(vector<string> inputContent) {
    fileContentToObjects(move(inputContent));
    simulate();
    cout << "score : ";
    cout << score << endl;
    return formatResults();
}

void ProcessingService::fileContentToObjects(vector<string> content) {
    int actualRow = 0;
    vector<string> firstLine = split(content[actualRow], ' ');
    int numberOfContributors = stoi(firstLine[0]);
    int numberOfProjects = stoi(firstLine[1]);

    for (int contributor = 0; contributor < numberOfContributors; contributor++) {
        actualRow++;
        vector<string> personLine = split(content[actualRow], ' ');
        int personNbOfSkills = stoi(personLine[1]);
        vector<Skill> personSkills;

        for (int skill = 0; skill < personNbOfSkills; skill++) {
            actualRow++;
            vector<string> skillLine = split(content[actualRow], ' ');
            Skill newSkill(skillLine[0], stoi(skillLine[1]));
            personSkills.push_back(newSkill);
        }

        Person newPerson(personLine[0], personSkills);
        persons.push_back(newPerson);
    }

    for (int project = 0; project < numberOfProjects; project++) {
        actualRow++;
        vector<string> projectLine = split(content[actualRow], ' ');
        vector<Skill> roles;
        int projectNbOfRole = stoi(projectLine[4]);

        for (int role = 0; role < projectNbOfRole; role++) {
            actualRow++;
            vector<string> roleLine = split(content[actualRow], ' ');
            Skill newRole(roleLine[0], stoi(roleLine[1]));
            roles.push_back(newRole);
        }

        Project newProject(projectLine[0], stoi(projectLine[1]), stoi(projectLine[2]), stoi(projectLine[3]), roles);
        projects.push_back(newProject);
    }
}

void ProcessingService::simulate() {
    do {
        for (Project &project: projects) {
            if (project.isInProgress) {
                project.progression++;

                if (project.isFinished()) {
                    project.isInProgress = false;
                    int contributorIndex = 0;
                    for_each(project.contributors.begin(), project.contributors.end(), [&project, &contributorIndex](Person *contributor) -> void {
                        contributor->isAvailable = true;
                        Skill role = project.roles[contributorIndex];
                        for (Skill &skill: contributor->skills) {
                            if (skill.name == role.name) {
                                if (role.level >= skill.level) {
                                    skill.level++;
                                }
                                break;
                            }
                        }
                        contributorIndex++;
                    });
                    score += project.getCompletedScore(actualDay);
                }
            }
        }

        vector<Person *> availablePersons;
        for (Person &person: persons) {
            if (person.isAvailable) {
                availablePersons.push_back(&person);
            }
        }

        for (Project &project: projects) {
            if (project.contributors.empty() && project.calculateActualScore(actualDay) > 0) {
                vector<Person *> availablePersonsCopy;
                copy(availablePersons.begin(), availablePersons.end(), back_inserter(availablePersonsCopy));
                if (all_of(project.roles.begin(), project.roles.end(), [&availablePersonsCopy](const Skill &role) -> bool {
                    unsigned long contributorFound = erase_if(availablePersonsCopy, [role](Person *person) -> bool { return person->hasSkill(role.name, role.level); });
                    if (contributorFound > 0) {
                        return true;
                    }
                    return false;
                })) {
                    for_each(project.roles.begin(), project.roles.end(), [&project, &availablePersons](Skill role) -> void {

                        auto contributorFound = find_if(availablePersons.begin(),
                                                        availablePersons.end(),
                                                        [&role](Person *person) -> bool { return person->hasSkill(role.name, role.level); });
                        if (contributorFound != availablePersons.end()) {
                            Person *contributor = *contributorFound;
                            erase_if(availablePersons, [&contributor](const Person *person) -> bool { return contributor->name == person->name; });
                            contributor->isAvailable = false;
                            project.contributors.push_back(contributor);
                        }
                    });
                    project.isInProgress = true;
                    project.orderId = this->projectOrderId++;
                }
            }
        }

        actualDay++;
        if (!any_of(projects.begin(), projects.end(), [this](const Project &project) -> bool {
            return (project.contributors.empty() && project.calculateActualScore(actualDay) > 0) || project.isInProgress;
        })) {
            break;
        }
    } while (true);
}

vector<string> ProcessingService::formatResults() {
    vector<Project> plannedProjects;
    copy_if(projects.begin(), projects.end(), back_inserter(plannedProjects), [](const Project &project) -> bool {
        return !project.contributors.empty();
    });

    sort(plannedProjects.begin(), plannedProjects.end(), [](const Project &projectA, const Project &projectB) -> bool {
        return projectA.orderId < projectB.orderId;
    });

    vector<string> results;
    results.push_back(to_string(plannedProjects.size()));
    for_each(plannedProjects.begin(), plannedProjects.end(), [&results](Project project) -> void {
        results.push_back(project.name);

        string contributorsStr;
        for_each(project.contributors.begin(), project.contributors.end(), [&contributorsStr](const Person *contributor) -> void {
            contributorsStr.append(contributor->name);
            contributorsStr.append(" ");
        });
        results.push_back(contributorsStr);
    });
    return results;
}
