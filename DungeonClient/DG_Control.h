#ifndef _DG_CONTROL_H_
#define _DG_CONTROL_H_
#include "DG_Sprite.h"
class DG_Control :
	public DG_Sprite
{
public:
	DG_Control(std::string file_path, bool lean = false);
	bool IsInControl(SDL_Rect rect, int x, int y);
};

class DG_Button :
	public DG_Control
{
public:
	DG_Button(std::string file_path1,std::string file_path2 = nullptr, bool lean = false);
	~DG_Button();
	bool SwitchHighlight();
	void Render(const SDL_Rect* src, const SDL_Rect* dst);
	int CheckMouseType(SDL_Rect rect, SDL_Event e);
	int CheckHighlight(SDL_Rect rect, SDL_Event e);
	bool IfClicked(SDL_Rect rect, SDL_Event e);

private:
	bool highlight = false;	// trueΪ����״̬
	bool cursor = false;	// trueΪ����
	SDL_Surface* __m_pSurfaceH = nullptr;
	SDL_Texture* __m_pTextureH = nullptr;
};


#endif // !_DG_CONTROL_H_

