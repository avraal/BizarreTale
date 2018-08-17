cmake_minimum_required(VERSION 3.10)
project(BizarreTale)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER /usr/bin/g++-7)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")

add_executable(BizarreTale  src/main.cpp
        src/Components/CTile.cpp
                            src/MapEditor.cpp
        src/Components/CPrimitiveQuad.cpp
                            src/MapIO.cpp
                            src/ThicknessLine.cpp
                            src/ThicknessLineArray.cpp
        src/Entity/IEntity.cpp
        src/Components/IComponent.cpp
                            src/Systems/SRender.cpp
        src/Systems/ISystem.cpp
                            src/Level.cpp
                            src/Systems/SLevelManager.cpp
                            src/Entity/EObject.cpp
                            src/Systems/SUi.cpp
                            src/CustomGUI/EditboxAndLabel.cpp
                            src/Util/IDGenerator.cpp)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
include_directories(/usr/local/include)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(BizarreTale ${SFML_LIBRARIES} -ltgui pthread)
endif()