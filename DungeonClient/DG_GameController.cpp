#include "DG_GameController.h"
#include "DG_Assert.h"
#include "DG_Control.h"
#include "DG_Character.h"


void DG_GameController::Init()
{
	// 加载SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	// 加载日志
	DG_Logger::InitIO();
	LoadResource();
	g_pWindow = SDL_CreateWindow("Dungeon",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		iWidth, iHeight, SDL_WINDOW_SHOWN);
	g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, SDL_RENDERER_ACCELERATED);
	state = DG_GameController::GAME_MENU;
}

void DG_GameController::QuitGame()
{
	DG_Logger::QuitIO();
	SDL_DestroyRenderer(g_pRenderer);
	SDL_DestroyWindow(g_pWindow);
	SDL_Quit();
}

void DG_GameController::LoadResource()
{
	//// 加载游戏资源
	//std::filesystem::directory_iterator itor_skins("assets/skins");
	//for (const std::filesystem::directory_entry& itor : itor_skins)
	//{
	//	// 加载json文件
	//	std::filesystem::path path_skin_folder = itor.path();
	//	cJSON* pjson_config = nullptr;
	//	DG_Assert(pjson_config = LoadJSON((path_skin_folder / "config.json").string()));
	//	// 提取json文件内容
	//	std::map<std::string, SDL_Surface*> map_filename_surface;
	//	cJSON* pjson_item = nullptr;
	//	cJSON* pjson_list_walk = cJSON_GetObjectItem(pjson_config, "walk");
	//	DG_Assert(pjson_list_walk && pjson_list_walk->type == cJSON_Array);
	//	// 加载资源为surface
	//	cJSON_ArrayForEach(pjson_item, pjson_list_walk)
	//	{
	//		if (map_filename_surface.find(pjson_item->valuestring) != map_filename_surface.end())
	//		{
	//			map_filename_surface.insert(std::make_pair(pjson_item->valuestring, IMG_Load((path_skin_folder / pjson_item->valuestring).string().c_str())));
	//		}
	//	}
	//}
}

void DG_GameController::Menu()
{
	// 加载背景
	DG_Sprite background("./assets/background/menu.png");
	SDL_Rect back = { 0, 0, iWidth, iHeight};
	// 加载按钮图片
	std::map<std::string, DG_Button*> buttons;
	DG_Button btn_LoadGame("./assets/button/btn_LoadGame_idle.png", 
		"./assets/button/btn_LoadGame_hover.png");
	buttons.insert(std::pair<std::string, DG_Button*>("btn_LoadGame", &btn_LoadGame));
	DG_Button btn_NewGame("./assets/button/btn_NewGame_idle.png", 
		"./assets/button/btn_NewGame_hover.png");
	buttons.insert(std::pair<std::string, DG_Button*>("btn_NewGame", &btn_NewGame));
	DG_Button btn_Setting("./assets/button/btn_Setting_idle.png", 
		"./assets/button/btn_Setting_hover.png");
	buttons.insert(std::pair<std::string, DG_Button*>("btn_Setting", &btn_Setting));
	DG_Button btn_Quit("./assets/button/btn_Quit_idle.png", 
		"./assets/button/btn_Quit_hover.png");
	buttons.insert(std::pair<std::string,DG_Button*>("btn_Quit",&btn_Quit));
	// 设置按钮方块大小位置
	std::map<std::string, SDL_Rect> rects;
	SDL_Rect rectLoadGame = { 
		iWidth / 2 - buttons.find("btn_LoadGame")->second->m_nWidth / 2, 
		iHeight / 3 * 2 + 0 * 60 , 
		buttons.find("btn_LoadGame")->second->m_nWidth, 
		buttons.find("btn_LoadGame")->second->m_nHeight };
	rects.insert(std::make_pair("btn_LoadGame",rectLoadGame));
	SDL_Rect rectNewGame = { 
		iWidth / 2 - buttons.find("btn_NewGame")->second->m_nWidth / 2, 
		iHeight / 3 * 2 + 1 * 60 , 
		buttons.find("btn_NewGame")->second->m_nWidth, 
		buttons.find("btn_NewGame")->second->m_nHeight };
	rects.insert(std::make_pair("btn_NewGame",rectNewGame));
	SDL_Rect rectSetting = { 
		iWidth / 2 - buttons.find("btn_Setting")->second->m_nWidth / 2, 
		iHeight / 3 * 2 + 2 * 60 , 
		buttons.find("btn_Setting")->second->m_nWidth, 
		buttons.find("btn_Setting")->second->m_nHeight };
	rects.insert(std::make_pair("btn_Setting",rectSetting));
	SDL_Rect rectQuit = { 
		iWidth / 2 - buttons.find("btn_Quit")->second->m_nWidth / 2, 
		iHeight / 3 * 2 + 3 * 60 , 
		buttons.find("btn_Quit")->second->m_nWidth, 
		buttons.find("btn_Quit")->second->m_nHeight };
	rects.insert(std::make_pair("btn_Quit",rectQuit));
	// 主循环
	SDL_Event event;
	while (g_Game.state == GAME_MENU)
	{
		start = SDL_GetPerformanceCounter();
		SDL_RenderClear(g_pRenderer);
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				g_Game.state = GAME_EXIT;
				break;
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
				// 按钮点击检测
				if (buttons.find("btn_Quit")->second->IfClicked(rects.find("btn_Quit")->second, event))
				{
					g_Game.state = GAME_EXIT;
				}
				else if (buttons.find("btn_NewGame")->second->IfClicked(rects.find("btn_NewGame")->second, event))
				{
					SetCursor(SDL_SYSTEM_CURSOR_ARROW);
					g_Game.state = GAME_RUNNING;
				}
				break;
			case SDL_MOUSEMOTION:
				// 按钮选中时的高光与光标切换
				for (auto it = buttons.begin(); it != buttons.end(); it++)
				{
					it->second->CheckHighlight(rects.find(it->first)->second, event);
					it->second->CheckMouseType(rects.find(it->first)->second, event);
				}
				break;
			default:
				break;
			}
			// 背景与按钮渲染
			background.Render(&back, &back);
			for (auto it = buttons.begin(); it != buttons.end(); it++)
			{
				it->second->Render(nullptr, &rects.find(it->first)->second);
			}
			SDL_RenderPresent(g_pRenderer);
			end = SDL_GetPerformanceCounter();
			Wait();
		}
		end = SDL_GetPerformanceCounter();
		Wait();
	}
}

void DG_GameController::SetupForRun()
{
}
void DG_GameController::Run()
{
	// 加载背景图片
	DG_Sprite background1("./assets/background/Lobby1.png");
	DG_Sprite background2("./assets/background/Lobby2.png");
	SDL_Rect back = { 0, 0, iWidth, iHeight };
	// 加载人物
	DG_Character Steve("./assets/skins/Steve/idle_1.png");
	SDL_Rect rectSteve = { iWidth / 2, iHeight / 2, Steve.m_nWidth, Steve.m_nHeight };

	SDL_Event event;
	while (g_Game.state == GAME_RUNNING)
	{
		start = SDL_GetPerformanceCounter();
		SDL_RenderClear(g_pRenderer);
		while (SDL_PollEvent(&event)) {
			switch (event.type)
			{
			case SDL_QUIT:
				g_Game.state = GAME_EXIT;
				break;
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				Steve.DoLogic(event);
				break;
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
				break;
			case SDL_MOUSEMOTION:
				break;
			default:
				break;
			}
		}
		Steve.Animine();
		background1.Render(&back, &back);
		background2.Render(&back, &back);
		Steve.UpdatePos(&rectSteve);
		Steve.Render(nullptr, &rectSteve);
		SDL_RenderPresent(g_pRenderer);
		end = SDL_GetPerformanceCounter();
		Wait();
	}
	end = SDL_GetPerformanceCounter();
	Wait();
}
void DG_GameController::Wait()
{
	float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
	if (elapsedMS < 16.666f) SDL_Delay(16.666f - elapsedMS);
}
