#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#define levelWidth 3840
#define levelHeight 2176

#define FREESPACE 'x'
#define BOUNDARY 'y'
#define WALL 'W'
#define PLAYER 'p'
#define TEMP 'z'

#define TEXTURESIZE 64
#define GRANULARITY 64