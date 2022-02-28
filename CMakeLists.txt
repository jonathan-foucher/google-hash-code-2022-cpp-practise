cmake_minimum_required(VERSION 3.21)
project(google_hash_code_2022_c__)

set(CMAKE_CXX_STANDARD 23)

add_executable(google_hash_code_2022_c__ src/main.cpp src/models/Person.cpp src/models/Person.h src/models/Skill.cpp src/models/Skill.h src/models/Project.cpp src/models/Project.h src/utils/LinkedList.h src/services/FileService.cpp src/services/FileService.h src/services/ProcessingService.cpp src/services/ProcessingService.h src/utils/StringUtils.h)
