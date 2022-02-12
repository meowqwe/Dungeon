#ifndef _DG_CHARACTER_H_
#define _DG_CHARACTER_H_

#include "DG_Sprite.h"
#include <vector>
class DG_Character :
	public DG_Sprite
{
public:
	DG_Character(std::string file_path, 
		bool lean = false);
	~DG_Character();
	void Render(const SDL_Rect* src, const SDL_Rect* dst);
	void DoLogic(SDL_Event event);
	void UpdatePos(SDL_Rect* rect);
	void Turn(int d);
	bool IsStop();			// 角色是否处于停止状态
	bool InAnimation();		// 角色动画是否播放
	void Animine();			// 播放角色动画
private:
	std::vector<SDL_Surface*> s_walks;
	std::vector<SDL_Surface*> s_idles;
	std::vector<SDL_Texture*> walks;
	std::vector<SDL_Texture*> idles;
	double xspeed = 0;
	double yspeed = 0;
	bool animation = true;	// true 为动画播放中
	int keydown = 0;		// 按键正按下的数量
	int count = 0;			// 动画播放计数
	int dir = 0;			// 向右为0
	int state = 0;			// 角色状态，0为初始，1为走动
	int time = 0;			// 控制动画播放速度
	double addspeed = 0.1;	// 加速度
	double maxspeed = 2;
	bool lockw = false;
	bool locka = false;
	bool locks = false;
	bool lockd = false;
};

#endif // !_DG_CHARACTER_H_