// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by andrew on 12.04.18.
//

#ifndef DEMIURGE_CONST_DEFINITIONS_HPP
#define DEMIURGE_CONST_DEFINITIONS_HPP

#define TILE_SIZE_DEFAULT 64
#define WINDOW_SIZE_FULLHD_WIDTH 1920
#define WINDOW_SIZE_FULLHD_HEIGHT 1080
#define WINDOW_SIZE_HD_WIDTH 1280
#define WINDOW_SIZE_HD_HEIGHT 720
#define INFO_PANEL_TEXT_SIZE 12

using u_int  = unsigned int;                            // 4 (0     /     4 294 967 295)
using us_int = unsigned short int;                      // 2 (0     /     65 535       )
using ul_int = unsigned long  int;                      
/*
ul_int
linux: 8 (0     /     18 446 744 073 709 551 615)
windows: // 4 (0     /     4 294 967 295)
*/
#endif //DEMIURGE_CONST_DEFINITIONS_HPP
