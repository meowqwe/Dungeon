#ifndef _GAME_CONTROLLER_H_
#define _GAME_CONTROLLER_H_

#include <SDL.h>
#include <SDL_image.h>
#include <cJSON.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <filesystem>

#include "DG_Sprite.h"
#include "DG_Logger.h"

class DG_GameController
{
public:
	enum GameState {
		GAME_INIT = 0, GAME_MENU, GAME_STARTING, GAME_RUNNING, GAME_EXIT
	}state;
	void Init();			// ��ʼ��
	void Menu();			// �˵�����
	void SetupForRun();		// ��ʼ����Ϸ��Դ
	void Run();				// ��Ϸ����
	void Wait();			// ����֡��
	void QuitGame();		// �ͷ���Ϸ��Դ���˳�
	void LoadResource();
private:
	std::map<std::string, DG_Sprite> Sprite;
	std::map<std::string, SDL_Surface*> GameResource;
	Uint32 start = 0;
	Uint32 end = 0;
	int iWidth = 1000;
	int iHeight = 740;
};

#endif // !_GAME_CONTROLLER_H_