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
	// ����һ����
	POINT m_line[2];
	int color_choce;
	int stone_pen[19][19];
	int stone_pencopy[19][19];//���̵ĸ���
	POINT point_six[2];
	POINT point_four[2];
	POINT point_four1[100][2];
	POINT point_four2[100][2];
public:
	// ����ָ��λ����û���γ�����
	bool is_six(int x, int y, int color);
public:
	// �Ƿ��Ծ���������������һ����
	unsigned long had_six(int color);
public:
	// ������1
	bool computer1;
public:
	// ������2
	bool computer2;
public:
	// ��û����
	int is_four(int x, int y, int color);
public:
	// �Ƿ��Ծ����ĸ�������һ����
	int had_four(int color);
public:
	// �������ĵĸ���
	int num_four1;
public:
	// �������ĵĸ���
	int num_four2;
	int information[1000];//��λ�ķ���ʵ�֣�һ��int����32��λ
	struct Infor informations[1000];//�ýṹ����ʵ��
public:
	void restarinf(void);
	
public:
	void restarinfstructs(void);
public:
	// �������̵ķ���
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
	// ����ǰ�����
	int stone_depth;
public:
	void thenextone_turntow(int &x1, int &y1,int color);
public:
	void All_value_turntwo(int color);
};
