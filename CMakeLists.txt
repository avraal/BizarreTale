cmake_minimum_required(VERSION 3.10)
project(BizarreTale)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER /usr/bin/g++-7)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")

add_executable(BizarreTale src/main.cpp
        src/Engine/Components/CTile.cpp
        src/Engine/MapEditor.cpp
        src/Engine/Components/CPrimitiveQuad.cpp
        src/Engine/ThicknessLine.cpp
        src/Engine/ThicknessLineArray.cpp
        src/Engine/Entity/IEntity.cpp
        src/Engine/Components/IComponent.cpp
        src/Engine/Level.cpp
        src/Engine/Systems/LevelManager.cpp
        src/Engine/Entity/EObject.cpp
        src/Engine/Systems/UIWrapper.cpp
        src/Engine/CustomGUI/EditboxAndLabel.cpp
        src/Engine/Util/IDGenerator.cpp
        src/Game/Game.cpp)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
include_directories(/usr/local/include)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(BizarreTale ${SFML_LIBRARIES} -ltgui pthread)
endif()
