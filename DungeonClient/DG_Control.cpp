#include "DG_Control.h"

DG_Control::DG_Control(std::string file_path, bool lean) :DG_Sprite(file_path, lean) {
}


bool DG_Control::IsInControl(SDL_Rect rect, int x, int y)
{
    if (x > rect.x && x < rect.x + rect.w) {
        if (y > rect.y && y < rect.y + rect.h) {
            return true;
        }
    }
	return false;
}

DG_Button::DG_Button(std::string file_path1, 
	std::string file_path2, 
	bool lean) :DG_Control(file_path1, lean) {
	if (__m_pSurfaceH = IMG_Load(file_path2.c_str()))
	{
		m_nWidth = __m_pSurfaceH->w, m_nHeight = __m_pSurfaceH->h;
		if (!lean) __m_pTextureH = SDL_CreateTextureFromSurface(g_pRenderer, __m_pSurfaceH);
	}
}

DG_Button::~DG_Button()
{
	if (__m_pSurface)
	{
		SDL_FreeSurface(__m_pSurface);
		__m_pSurface = nullptr;
	}

	if (__m_pTexture)
	{
		SDL_DestroyTexture(__m_pTexture);
		__m_pTexture = nullptr;
	}
	if (__m_pSurfaceH)
	{
		SDL_FreeSurface(__m_pSurfaceH);
		__m_pSurfaceH = nullptr;
	}

	if (__m_pTextureH)
	{
		SDL_DestroyTexture(__m_pTextureH);
		__m_pTextureH = nullptr;
	}
}


bool DG_Button::SwitchHighlight()
{
	if (highlight) { // ÅÐ¶Ï²¢ÐÞ¸Ä¸ßÁÁ×´Ì¬
		highlight = false;
		return false;
	}
	else
	{
		highlight = true;
		return true;
	}
}

void DG_Button::Render(const SDL_Rect* src, const SDL_Rect* dst)
{
	if (!__m_pTexture && !__m_pSurface) return;

	if (!__m_pTextureH && !__m_pSurfaceH) return;
	if (!__m_pTexture)
		__m_pTexture = SDL_CreateTextureFromSurface(g_pRenderer, __m_pSurface);

	if (!__m_pTextureH)
		__m_pTextureH = SDL_CreateTextureFromSurface(g_pRenderer, __m_pSurfaceH);

	if (highlight) {
		SDL_RenderCopy(g_pRenderer, __m_pTextureH, src, dst);
	}
	else {
		SDL_RenderCopy(g_pRenderer, __m_pTexture, src, dst);
	}

	
}

int DG_Button::CheckMouseType(SDL_Rect rect, SDL_Event e)
{
	if (e.type == SDL_MOUSEMOTION) {
		if (IsInControl(rect, e.motion.x, e.motion.y)) {
			if(!cursor)SetCursor(SDL_SYSTEM_CURSOR_HAND);
			cursor = true;
		}
		else
		{
			if(cursor)SetCursor(SDL_SYSTEM_CURSOR_ARROW);
			cursor = false;
		}
	}
	return 0;
}

int DG_Button::CheckHighlight(SDL_Rect rect, SDL_Event e)
{
	if (e.type == SDL_MOUSEMOTION) {
		if (IsInControl(rect, e.motion.x, e.motion.y)) {
			if (!highlight) SwitchHighlight();
		}
		else
		{
			if (highlight) SwitchHighlight();
		}
	}
	return -1;
}

bool DG_Button::IfClicked(SDL_Rect rect, SDL_Event e)
{
	if (e.type == SDL_MOUSEBUTTONDOWN) {
		if (e.button.button == SDL_BUTTON_LEFT) {
			if (IsInControl(rect, e.motion.x, e.motion.y)) {
				return true;
			}
		}
	}
	return false;
}
