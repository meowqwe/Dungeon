#ifndef _DG_UTILS_H_
#define _DG_UTILS_H_

#include <SDL.h>
#include <cJSON.h>

#include <ctime>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <filesystem>

std::string DG_GetFormattedTime();
cJSON* LoadJSON(std::string str_path);
void SetCursor(SDL_SystemCursor type);
inline int32_t f_toint(double x)
{
    x += 6755399441055744.0;
    return *(int32_t*)&x;
}

#endif // !_DG_UTILS_H_
