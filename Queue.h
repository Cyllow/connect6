#pragma once

class Queue//����һ����ͷ���Խ����ݵĶ���
{
public:
	Queue(void);
public:
	~Queue(void);
private:
	
	int *p_head;
	int *p_tail;
	int *pp;
public:
	int que[6];
	// ��ͷ�����
	void push_head(int value);
	// ��β��������
	void push_tail(int value);
	// ���ض��е�ֵ
	int sum_value(void);
public:
	// �Ѷ�������������
	void Enpty(void);
public:
	// x,y��que�е�ƫ����
	int excu;
};
