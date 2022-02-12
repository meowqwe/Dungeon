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
	bool IsStop();			// ��ɫ�Ƿ���ֹͣ״̬
	bool InAnimation();		// ��ɫ�����Ƿ񲥷�
	void Animine();			// ���Ž�ɫ����
private:
	std::vector<SDL_Surface*> s_walks;
	std::vector<SDL_Surface*> s_idles;
	std::vector<SDL_Texture*> walks;
	std::vector<SDL_Texture*> idles;
	double xspeed = 0;
	double yspeed = 0;
	bool animation = true;	// true Ϊ����������
	int keydown = 0;		// ���������µ�����
	int count = 0;			// �������ż���
	int dir = 0;			// ����Ϊ0
	int state = 0;			// ��ɫ״̬��0Ϊ��ʼ��1Ϊ�߶�
	int time = 0;			// ���ƶ��������ٶ�
	double addspeed = 0.1;	// ���ٶ�
	double maxspeed = 2;
	bool lockw = false;
	bool locka = false;
	bool locks = false;
	bool lockd = false;
};

#endif // !_DG_CHARACTER_H_