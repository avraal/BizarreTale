cmake_minimum_required(VERSION 3.10)
project(Demiurge)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_COMPILER /usr/bin/g++-7)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")

add_executable(Demiurge src/main.cpp
#        src/Engine/MapEditor.cpp
        src/Engine/ThicknessLine.cpp
        src/Engine/ThicknessLineArray.cpp
        src/Engine/Entity/IEntity.cpp
        src/Engine/Components/IComponent.cpp
        src/Engine/Level.cpp
        src/Engine/Systems/LevelManager.cpp
        src/Engine/Entity/EObject.cpp
        src/Engine/Systems/UIWrapper.cpp
        src/Engine/CustomGUI/EditboxAndLabel.cpp
        src/Game/Game.cpp
        src/Game/Labyrinth/Labyrinth.cpp
        src/Engine/Systems/Managers/EntityManager.cpp
        src/Engine/Systems/Managers/ComponentManager.cpp
        src/Engine/Components/CDrawable.cpp
        src/Engine/Components/CTransform.cpp
        src/Game/TestNewECS/TestECS.cpp
        src/Engine/Util/GetClassName.hpp)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)

if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Demiurge ${SFML_LIBRARIES} -ltgui pthread)
endif()
