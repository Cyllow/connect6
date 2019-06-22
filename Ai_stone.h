#pragma once
struct Infor
{
	POINT pos[2];
	int excu[6];
	int value;
	int color;
};

class Ai_stone
{
public:
	Ai_stone(void);
public:
	~Ai_stone(void);
public:
	// 到那一方下
	POINT m_line[2];
	int color_choce;
	int stone_pen[19][19];
	int stone_pencopy[19][19];//棋盘的副本
	POINT point_six[2];
	POINT point_four[2];
	POINT point_four1[100][2];
	POINT point_four2[100][2];
public:
	// 返回指定位置有没有形成六子
	bool is_six(int x, int y, int color);
public:
	// 是否以经有六个子能连在一起了
	unsigned long had_six(int color);
public:
	// 电脑人1
	bool computer1;
public:
	// 电脑人2
	bool computer2;
public:
	// 有没有四
	int is_four(int x, int y, int color);
public:
	// 是否以经有四个活子在一起了
	int had_four(int color);
public:
	// 黑子有四的个数
	int num_four1;
public:
	// 白子有四的个数
	int num_four2;
	int information[1000];//用位的方法实现，一个int形用32个位
	struct Infor informations[1000];//用结构体来实现
public:
	void restarinf(void);
	
public:
	void restarinfstructs(void);
public:
	// 计算棋盘的分数
	void All_value(int color);
public:
	int value_color1;
public:
	int value_color2;
public:
	void thenexttowstone(int &x1, int &y1, int &x2, int &y2,int color);
public:
	void thenextone(int &x1, int &y1,int color);
public:
	// 能向前的深度
	int stone_depth;
public:
	void thenextone_turntow(int &x1, int &y1,int color);
public:
	void All_value_turntwo(int color);
};
