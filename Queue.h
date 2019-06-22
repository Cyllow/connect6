#pragma once

class Queue//这是一个两头可以进数据的队列
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
	// 从头入队列
	void push_head(int value);
	// 从尾加入数据
	void push_tail(int value);
	// 反回队列的值
	int sum_value(void);
public:
	// 把队列里的内容清空
	void Enpty(void);
public:
	// x,y在que中的偏移量
	int excu;
};
