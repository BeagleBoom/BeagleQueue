cmake_minimum_required(VERSION 3.6)

project(EventQueue)

set(CMAKE_CXX_STANDARD 11)

# Find source files
file(GLOB SOURCES src/*.cpp)

# Include header files
include_directories(include)

# Create shared library
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# Install library
install(TARGETS ${PROJECT_NAME} DESTINATION lib)

# Install library headers
file(GLOB HEADERS include/*.h)
install(FILES ${HEADERS} DESTINATION include/${PROJECT_NAME})

set(CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(Poco REQUIRED JSON)

target_link_libraries(${PROJECT_NAME} PUBLIC ${Poco_Foundation_LIBRARY})
target_link_libraries(${PROJECT_NAME} PUBLIC ${Poco_Util_LIBRARY})
target_link_libraries(${PROJECT_NAME} PUBLIC ${Poco_JSON_LIBRARY})
