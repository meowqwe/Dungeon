#include "DG_GameController.h"
#include "DG_Assert.h"
#include "DG_Control.h"


void DG_GameController::Init()
{
	// 加载SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	// 加载日志
	DG_Logger::InitIO();
	//// 加载人物皮肤
	//std::filesystem::directory_iterator itor_skins("assets/skins");
	//for (const std::filesystem::directory_entry& itor : itor_skins)
	//{
	//	// 加载json文件
	//	std::filesystem::path path_skin_folder = itor.path();
	//	cJSON* pjson_config = nullptr;
	//	DG_Assert(pjson_config = LoadJSON((path_skin_folder / "config.json").string()));
	//	// 提取json文件内容：walk
	//	std::map<std::string, SDL_Surface*> map_filename_surface;
	//	cJSON* pjson_item = nullptr;
	//	cJSON* pjson_list_walk = cJSON_GetObjectItem(pjson_config, "walk");
	//	DG_Assert(pjson_list_walk && pjson_list_walk->type == cJSON_Array);
	//	// 加载皮肤资源为surface
	//	cJSON_ArrayForEach(pjson_item, pjson_list_walk)
	//	{
	//		if (map_filename_surface.find(pjson_item->valuestring) != map_filename_surface.end())
	//		{
	//			map_filename_surface.insert(std::make_pair(pjson_item->valuestring, IMG_Load((path_skin_folder / pjson_item->valuestring).string().c_str())));
	//		}
	//	}
	//}
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
	//std::filesystem::directory_iterator itor_resource(path);
	//std::map<std::string, SDL_Surface*> map_filename_surface;
	//for (const std::filesystem::directory_entry& itor : itor_resource)
	//{
	//	// 加载json文件
	//	std::filesystem::path path_skin_folder = itor.path();
	//	cJSON* pjson_config = nullptr;
	//	DG_Assert(pjson_config = LoadJSON((path_skin_folder / json).string()));
	//	// 提取json文件内容
	//	cJSON* pjson_item = nullptr;
	//	cJSON* pjson_list_key = cJSON_GetObjectItem(pjson_config, "walk");
	//	DG_Assert(pjson_list_key && pjson_list_key->type == cJSON_Array);
	//	// 加载资源为surface
	//	cJSON_ArrayForEach(pjson_item, pjson_list_key)
	//	{
	//		if (map_filename_surface.find(pjson_item->valuestring) != map_filename_surface.end())
	//		{
	//			map_filename_surface.insert(std::make_pair(pjson_item->valuestring, IMG_Load((path_skin_folder / pjson_item->valuestring).string().c_str())));
	//		}
	//	}
	//}
	//return map_filename_surface;
}

void DG_GameController::Menu()
{
	DG_Sprite background("./assets/background/menu.png");
	SDL_Rect back = { 0, 0, iWidth, iHeight};
	std::vector<DG_Button*> buttons;
	DG_Button btn_LoadGame("./assets/button/btn_LoadGame_idle.png", "./assets/button/btn_LoadGame_hover.png");
	buttons.emplace_back(&btn_LoadGame);
	DG_Button btn_NewGame("./assets/button/btn_NewGame_idle.png", "./assets/button/btn_NewGame_hover.png");
	buttons.emplace_back(&btn_NewGame);
	DG_Button btn_Setting("./assets/button/btn_Setting_idle.png", "./assets/button/btn_Setting_hover.png");
	buttons.emplace_back(&btn_Setting);
	DG_Button btn_Quit("./assets/button/btn_Quit_idle.png", "./assets/button/btn_Quit_hover.png");
	buttons.emplace_back(&btn_Quit);

	std::vector<SDL_Rect> rects;
	for (int i = 0; i < buttons.size(); i++)
	{
		SDL_Rect rect = {iWidth/2 - buttons[i]->m_nWidth/2, iHeight/3 * 2 + i * 60 , buttons[i]->m_nWidth, buttons[i]->m_nHeight};
		rects.emplace_back(rect);
	}

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
				break;
			case SDL_MOUSEMOTION:
				for (int i = 0; i < buttons.size(); i++)
				{
					buttons[i]->CheckHighlight(rects[i], event);
				}
				break;
			default:
				break;
			}
			background.Render(&back, &back);
			for (int i = 0; i < buttons.size(); i++)
			{
				buttons[i]->Render(nullptr, &rects[i]);
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

void DG_GameController::Render_Frame()
{
}

void DG_GameController::Wait()
{
	float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
	if (elapsedMS < 16.666f) SDL_Delay(16.666f - elapsedMS);
}
