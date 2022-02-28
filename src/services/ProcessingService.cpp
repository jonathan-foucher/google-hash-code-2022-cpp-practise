#include "ProcessingService.h"
#include "../utils/StringUtils.h"

LinkedList<std::string> ProcessingService::process(LinkedList<std::string> inputContent) {
    fileContentToObjects(inputContent);
    simulate();
    std::cout << "score : ";
    std::cout << score << std::endl;
    return formatResults();
}

void ProcessingService::fileContentToObjects(LinkedList<std::string> content) {
    node<std::string> *curr = content.head;

    std::vector<std::string> firstLine = split(curr->data, ' ');
    int numberOfContributors = stoi(firstLine[0]);
    int numberOfProjects = stoi(firstLine[1]);

    int actualRow = 0;
    for (int contributor = 0; contributor < numberOfContributors; contributor++) {
        actualRow++;
        curr = curr->next;
        std::vector<std::string> personLine = split(curr->data, ' ');
        int personNbOfSkills = stoi(personLine[1]);
        LinkedList<Skill> personSkills;

        for (int skill = 0; skill < personNbOfSkills; skill++) {
            actualRow++;
            curr = curr->next;
            std::vector<std::string> skillLine = split(curr->data, ' ');
            Skill newSkill(skillLine[0], stoi(skillLine[1]));
            personSkills.add(newSkill);
        }

        Person newPerson(personLine[0], personSkills);
        persons.add(newPerson);
    }

    for (int project = 0; project < numberOfProjects; project++) {
        actualRow++;
        curr = curr->next;
        std::vector<std::string> projectLine = split(curr->data, ' ');
        LinkedList<Skill> roles;
        int projectNbOfRole = stoi(projectLine[4]);

        for (int role = 0; role < projectNbOfRole; role++) {
            actualRow++;
            curr = curr->next;
            std::vector<std::string> roleLine = split(curr->data, ' ');
            Skill newRole(roleLine[0], stoi(roleLine[1]));
            roles.add(newRole);
        }

        Project newProject(projectLine[0], stoi(projectLine[1]), stoi(projectLine[2]), stoi(projectLine[3]), roles);
        projects.add(newProject);
    }
}

void ProcessingService::simulate() {
    LinkedList<Project> availableProjects;
    do {
        projects.forEachAddr([this](Project *project) -> void {
            if (project->isInProgress) {
                project->progression++;

                if (project->isFinished()) {
                    project->isInProgress = false;
                    int contributorIndex = 0;
                    project->contributors.forEach([&project, &contributorIndex](Person contributor) -> void {
                        contributor.isAvailable = true;
                        Skill *role = project->roles[contributorIndex];
                        Skill *skill = contributor.skills.find([&role](Skill skill) -> bool { return skill.name == role->name; }).value();
                        if (role->level >= skill->level) {
                            skill->level++;
                        }
                        contributorIndex++;
                    });
                    score += project->getCompletedScore(actualDay);
                }
            }
        });

        LinkedList<Person> availablePersons = persons.filter([](Person person) -> bool {
            return person.isAvailable;
        });

        projects.forEachAddr([this, &availablePersons](Project *project) -> void {
            if (project->contributors.size == 0 && project->calculateActualScore(actualDay) > 0) {
                LinkedList<Person> availablePersonsCopy = availablePersons.makeCopy();
                bool isDoable = project->roles.every([&availablePersonsCopy](Skill role) -> bool {
                    std::optional<Person*> contributorFound = availablePersonsCopy.find([role](Person person) -> bool {
                        return person.hasSkill(role.name, role.level);
                    });

                    if (contributorFound.has_value()) {
                        availablePersonsCopy.remove(contributorFound.value());
                        return true;
                    }
                    return false;
                });

                if (isDoable) {
                    project->roles.forEach([&project, &availablePersons](Skill role) -> void {
                        Person *contributor = availablePersons.find([&role](Person person) -> bool {
                            return person.hasSkill(role.name, role.level);
                        }).value();
                        availablePersons.remove(contributor);
                        contributor->isAvailable = false;
                        project->contributors.add(*contributor);
                    });
                    project->isInProgress = true;
                    project->orderId = this->projectOrderId++;
                }
            }
        });

        actualDay++;
        availableProjects = projects.filter([this](Project project) -> bool {
            return (project.contributors.size == 0 && project.calculateActualScore(actualDay) > 0) || project.isInProgress;
        });
    } while (availableProjects.size > 0);
}

LinkedList<std::string> ProcessingService::formatResults() {
    LinkedList<Project> plannedProjects = projects.filter([](Project project) -> bool {
                return project.contributors.size > 0;
            })
            .sort([](Project projectA, Project projectB) -> bool {
                return projectA.orderId < projectB.orderId;
            });

    LinkedList<std::string> results;
    results.add(std::to_string(plannedProjects.size));
    plannedProjects.forEach([&results](Project project) -> void {
        results.add(project.name);

        std::string contributorsStr;
        project.contributors.forEach([&contributorsStr](Person contributor) -> void {
            contributorsStr.append(contributor.name);
            contributorsStr.append(" ");
        });
        results.add(contributorsStr);
    });
    return results;
}
