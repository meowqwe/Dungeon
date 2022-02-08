#include <SDL.h>
#include <SDL_image.h>
#include <cJSON.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <filesystem>

#include "DG_Assert.h" 
#include "DG_Sprite.h"
#include "DG_Utils.h"
#include "DG_GameController.h"

SDL_Window*		g_pWindow;
SDL_Renderer*	g_pRenderer;
DG_GameController g_Game;

#undef main
int main(int argc, char** argv)
{
	while (g_Game.state != DG_GameController::GAME_EXIT)
	{
		switch (g_Game.state)
		{
		case DG_GameController::GAME_INIT:
			g_Game.Init();
			break;
		case DG_GameController::GAME_MENU:
			g_Game.Menu();
			break;
		case DG_GameController::GAME_STARTING:
			break;
		case DG_GameController::GAME_RUNNING:
			break;
		case DG_GameController::GAME_EXIT:
			g_Game.QuitGame();
			break;
		default:
			break;
		}
	}
	return 0;
}