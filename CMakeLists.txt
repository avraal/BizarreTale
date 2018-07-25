cmake_minimum_required(VERSION 3.10)
project(BizarreTale)

set(CMAKE_CXX_STANDARD 17)

add_executable(BizarreTale  src/main.cpp
                            src/CTile.cpp
                            src/CTile.h
                            src/MapEditor.cpp
                            src/MapEditor.h
                            src/CPrimitiveQuad.cpp
                            src/CPrimitiveQuad.hpp
                            src/MapIO.cpp
                            src/MapIO.h
                            src/ThicknessLine.cpp
                            src/ThicknessLine.hpp
                            src/ThicknessLineArray.cpp
                            src/ThicknessLineArray.hpp
                            src/Abstract/IEntity.cpp
                            src/Abstract/IEntity.hpp
                            src/Abstract/IComponent.cpp
                            src/Abstract/IComponent.hpp
                            src/Systems/SRender.cpp
                            src/Systems/SRender.hpp
                            src/Abstract/ISystem.cpp
                            src/Abstract/ISystem.hpp
                            src/Level.cpp src/Level.hpp
                            src/Systems/LevelManager.cpp
                            src/Systems/LevelManager.hpp
                            src/Entity/EObject.cpp
                            src/Entity/EObject.hpp)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
include_directories(/usr/local/include)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(BizarreTale ${SFML_LIBRARIES} -ltgui pthread)
endif()