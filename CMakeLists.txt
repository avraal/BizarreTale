cmake_minimum_required(VERSION 3.10)
project(BizarreTale)

set(CMAKE_CXX_STANDARD 17)

add_executable(BizarreTale  src/main.cpp
                            src/TileEntity.cpp
                            src/TileEntity.h
                            src/MapEditor.cpp
                            src/MapEditor.h
                            src/ClassAnalyzer.cpp
                            src/ClassAnalyzer.h
                            src/PrimitiveQuad.cpp
                            src/PrimitiveQuad.hpp
                            src/MapIO.cpp
                            src/MapIO.h
                            src/ThicknessLine.cpp
                            src/ThicknessLine.hpp
                            src/ThicknessLineArray.cpp
                            src/ThicknessLineArray.hpp)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
include_directories(/usr/local/include)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(BizarreTale ${SFML_LIBRARIES} -ltgui pthread)
endif()