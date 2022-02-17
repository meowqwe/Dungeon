#include "DG_Character.h"

DG_Character::DG_Character(std::string file_path, 
	bool lean): DG_Sprite(file_path, lean)
{
	SDL_Surface* t = IMG_Load("./assets/skins/Steve/idle_1.png");
	s_idles.emplace_back(t);
	t = IMG_Load("./assets/skins/Steve/idle_2.png");
	s_idles.emplace_back(t);
	t = IMG_Load("./assets/skins/Steve/walk_1.png");
	s_walks.emplace_back(t);
	t = IMG_Load("./assets/skins/Steve/walk_2.png");
	s_walks.emplace_back(t);
	t = IMG_Load("./assets/skins/Steve/walk_3.png");
	s_walks.emplace_back(t);
	for (int i = 0; i < s_idles.size(); i++) {
		idles.emplace_back(SDL_CreateTextureFromSurface(g_pRenderer, s_idles[i]));
	}
	for (int i = 0; i < s_walks.size(); i++) {
		walks.emplace_back(SDL_CreateTextureFromSurface(g_pRenderer, s_walks[i]));
	}
}

DG_Character::~DG_Character()
{
	for (int i = 0; i < s_idles.size(); i++) {
		SDL_FreeSurface(s_idles[i]);
	}
	for (int i = 0; i < s_walks.size(); i++) {
		SDL_FreeSurface(s_walks[i]);
	}
	for (int i = 0; i < s_idles.size(); i++) {
		SDL_DestroyTexture(idles[i]);
	}
	for (int i = 0; i < s_walks.size(); i++) {
		SDL_DestroyTexture(walks[i]);
	}
}

void DG_Character::Render(const SDL_Rect* src, const SDL_Rect* dst)
{
	if (s_idles.empty() || s_walks.empty()) return;
	if (idles.empty() || walks.empty()) return;
	switch (state)
	{
	case 0:
		SDL_RenderCopy(g_pRenderer, idles[count], src, dst);
		break;
	case 1:
		switch (dir)
		{
		case 0:
			SDL_RenderCopy(g_pRenderer, walks[count], src, dst);
			break;
		case 1:
			SDL_RenderCopyEx(g_pRenderer, walks[count], src, dst, 0, nullptr, SDL_FLIP_HORIZONTAL);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void DG_Character::DoLogic(SDL_Event event)
{
	if (event.type == SDL_KEYDOWN) 
	{
		if (event.key.keysym.sym == SDLK_w) {
			if (!lockw)
			{
				lockw = true;
				keydown++;
			}
			state = 1;
		}
		else if (event.key.keysym.sym == SDLK_a) {
			if (!locka)
			{
				locka = true;
				keydown++;
			}
			state = 1;
		}
		else if (event.key.keysym.sym == SDLK_s) {
			if (!locks)
			{
				locks = true;
				keydown++;
			}
			state = 1;
		}
		else if (event.key.keysym.sym == SDLK_d) {
			if (!lockd)
			{
				lockd = true;
				keydown++;
			}
			state = 1;
		}
	}
	else if (event.type == SDL_KEYUP)
	{
		if (event.key.keysym.sym == SDLK_w) {
			keydown--;
			lockw = false;
			if (!locks) yspeed = 0;
			if (state == 1) count = 0;
		}
		else if (event.key.keysym.sym == SDLK_a) {
			keydown--;
			locka = false;
			if (!lockd) xspeed = 0;
			if (state == 1) count = 0;
		}
		else if (event.key.keysym.sym == SDLK_s) {
			keydown--;
			locks = false;
			if (!lockw) yspeed = 0;
			if (state == 1) count = 0;
		}
		else if (event.key.keysym.sym == SDLK_d) {
			keydown--;
			lockd = false;
			if (!locka) xspeed = 0;
			if (state == 1) count = 0;
		}
		if (keydown == 0) {
			xspeed = 0;
			yspeed = 0;
			state = 0;
		}
	}
}

void DG_Character::UpdatePos(SDL_Rect* rect)
{
	if (lockw && yspeed > -maxspeed)
	{
		yspeed -= addspeed;
	}
	if (locka && xspeed > -maxspeed)
	{
		xspeed -= addspeed;
		Turn(1);
	}
	if (locks && yspeed < maxspeed)
	{
		yspeed += addspeed;
	}
	if (lockd && xspeed < maxspeed)
	{
		xspeed += addspeed;
		Turn(0);
	}
	speed = std::max(abs(xspeed), abs(yspeed));
	angle = atan2(yspeed, xspeed);
	rect->x = rect->x + f_toint(speed * SDL_cos(angle));
	rect->y = rect->y + f_toint(speed * SDL_sin(angle));
}

void DG_Character::Turn(int dir)
{
	this->dir = dir;
}

bool DG_Character::IsStop()
{
	if (xspeed == 0 && yspeed == 0)return true;
	return false;
}

bool DG_Character::InAnimation()
{
	return animation;
}

void DG_Character::Animine()
{
	time = (time + 1) % 15;
	if (time == 0)
	{
		switch (state)
		{
		case 0:
			count = (count + 1) % 2;
			break;
		case 1:
			count = (count + 1) % 3;
			break;
		default:
			break;
		}
	}
}
