#include "StdAfx.h"
#include "Queue.h"

Queue::Queue(void)
: excu(-2)
{
	for(int i=0;i<6;i++)
	{
		que[i]=0;
	}
	p_head=&que[2];
	p_tail=&que[3];
}

Queue::~Queue(void)
{
}

// 从头入队列
void Queue::push_head(int value)
{
	
	if(p_head>=&que[0])
	{
		*p_head=value;
		p_head--;
	}
	else
	{
		excu--;
		que[5]=que[4];
		que[4]=que[3];
		que[3]=que[2];
		que[2]=que[1];
		que[1]=que[0];
		que[0]=value;
		if(p_tail<=&que[5])
			p_tail++;
	}
}

// 从尾入队列
void Queue::push_tail(int value)
{
	
	if(p_tail<=&que[5])
	{
		*p_tail=value;
		p_tail++;
	}
	else
	{
		excu++;
		que[0]=que[1];
		que[1]=que[2];
		que[2]=que[3];
		que[3]=que[4];
		que[4]=que[5];
		que[5]=value;
		if(p_head>=&que[0])
			p_head--;
	}
}

// 反回队列的值
int Queue::sum_value(void)
{
	if((p_tail==&que[5]+1)&&(p_head==&que[0]-1))
		return (que[0]+que[1]+que[2]+que[3]+que[4]+que[5]);
	return 0;
}

// 把队列里的内容清空
void Queue::Enpty(void)
{
	for(int i=0;i<6;i++)
	{
		que[i]=0;
	}
	excu=-2;
	p_head=&que[2];
	p_tail=&que[3];
}
