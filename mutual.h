#pragma once
struct Stone_inf
{
	int color;
	int x;
	int y;
};
struct Stone_color
{
	int x;
	int y;
};
struct Stone_inf Stone_infor[362];//用来保存所有的下棋数据
struct Stone_color Stone_back[182];//用来保存所有的黑棋数据
struct Stone_color Stone_white[181];//用来保存所有的白棋数据
CBitmap bmps[6];//这里存放各个图片