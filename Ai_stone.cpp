#include "StdAfx.h"
#include "Ai_stone.h"
#include "Queue.h"
Ai_stone::Ai_stone(void)
: color_choce(1)
, computer1(false)
, computer2(false)
, num_four1(0)
, num_four2(0)
, value_color1(0)
, value_color2(0)
, stone_depth(0)
{
	for(int i=0;i<19;i++)
		for(int j=0;j<19;j++)
		{
			stone_pen[i][j]=0;
		}
		for(int i=0;i<728;i++)
		{
			information[i]=0;
		}
}

Ai_stone::~Ai_stone(void)
{
}

// 返回指定位置有没有形成六子
bool Ai_stone::is_six(int x, int y, int color)
{
	int i=0;
	int j=0;
	int left=0;//<--向左
	int right=0;//-->向右
	int up=0;// /|\向上
	int down=0;// \|/向下
	int left_up=0;//   左上方
	int right_down=0;//右下方
	int up_right=0;//右上方
	int left_down=0;//   左下方
	for(i=x-1;i>=0;i--)//<--向左
	{
		if(stone_pen[i][y]==color)
		{
			left++;
		}
		else
			break;
	}
	for(i=x+1;i<19;i++)//-->向右
	{
		if(stone_pen[i][y]==color)
		{
			right++;
		}
		else
			break;
	}
	for(i=y+1;i<19;i++)// \|/向下
	{
		if(stone_pen[x][i]==color)
		{
			down++;
		}
		else
			break;
	}
	for(i=y-1;i>=0;i--)// /|\向上
	{
		if(stone_pen[x][i]==color)
		{
			up++;
		}
		else
			break;
	}



	for(i=x-1,j=y-1;i>=0&&j>=0;i--,j--)//   左上方
	{
		if(stone_pen[i][j]==color)
		{
			left_up++;
		}
		else
			break;
	}
	for(i=x+1,j=y+1;i<19&&j<19;i++,j++)//右下方
	{
		if(stone_pen[i][j]==color)
		{
			right_down++;
		}
		else
			break;
	}
	for(i=x+1,j=y-1;i<19&&j>=0;i++,j--)//   右上方
	{
		if(stone_pen[i][j]==color)
		{
			up_right++;
		}
		else
			break;
	}
	for(i=x-1,j=y+1;i>=0&&j<19;i--,j++)//左下方
	{
		if(stone_pen[i][j]==color)
		{
			left_down++;
		}
		else
			break;
	}
	if((right+left)>=5)
	{
		point_six[0].y=y;
		point_six[1].y=y;
		point_six[0].x=x-left;
		point_six[1].x=x+right;
		return true;
	}
	else if((up+down)>=5)
	{
		point_six[0].y=y-up;
		point_six[1].y=y+down;
		point_six[0].x=x;
		point_six[1].x=x;
		return true;
	}
	else if((left_up+right_down)>=5)
	{
		point_six[0].y=y-left_up;
		point_six[1].y=y+right_down;
		point_six[0].x=x-left_up;
		point_six[1].x=x+right_down;
		return true;
	}
	else if((up_right+left_down)>=5)
	{
		point_six[0].y=y-up_right;
		point_six[1].y=y+left_down;
		point_six[0].x=x+up_right;
		point_six[1].x=x-left_down;
		return true;
	}

	return false;
}

// 是否以经有六个子能连在一起了
unsigned long Ai_stone::had_six(int color)
{
	if(color==1)
	{
		for(int i=0;i<19;i++)
			for(int j=0;j<19;j++)
			{
				if(stone_pen[i][j]==1)
				{
					if(is_six(i,j,1))
						return 1;
				}
			}
	}
	else if(color==2)
	{
		for(int i=0;i<19;i++)
			for(int j=0;j<19;j++)
			{
				if(stone_pen[i][j]==2)
				{
					if(is_six(i,j,2))
						return 2;
				}
			}
	}
	
	else
		return 0;
}

// 有没有四
int Ai_stone::is_four(int x, int y, int color)
{
	Queue que;
	int i=0;
	int j=0;
	int flat_five=0;
	if(stone_pen[x][y]==0)
		que.push_head(0);
	else if(stone_pen[x][y]==color)
		que.push_head(1);
	else
		return 0;
	for(i=x-1,flat_five=5;i>=0&&flat_five>0;i--,flat_five--)//<--向左
	{
		if(stone_pen[i][y]==0)
		{
			que.push_head(0);
		}
		else if(stone_pen[i][y]==color)
		{
			que.push_head(1);
		}
		else
			break;
		
	}
	if(que.sum_value()==4)
	{
		int flat1,flat2;
		for(i=0;i<5;i++)
		{
			if(que.que[i]==1)
			{
				flat1=i;
				break;
			}
		}
		for(i=5;i>0;i--)
		{
			if(que.que[i]==1)
			{
				flat2=i;
				break;
			}
		}
		point_four[0].y=y;
		point_four[1].y=y;
		point_four[0].x=x-5+flat1;
		point_four[1].x=x-5+flat2;
		return color;
	}
	for(i=x+1,flat_five=5;i<19&&flat_five>0;i++,flat_five--)//-->向右
	{
		if(stone_pen[i][y]==0)
		{
			que.push_tail(0);
			if(que.sum_value()==4)
			{	
				int flat1,flat2;
		for(i=0;i<5;i++)
		{
			if(que.que[i]==1)
			{
				flat1=i;
				break;
			}
		}
		for(i=5;i>0;i--)
		{
			if(que.que[i]==1)
			{
				flat2=i;
				break;
			}
		}
		point_four[0].y=y;
		point_four[1].y=y;
		point_four[0].x=x+que.excu+flat1;
		point_four[1].x=x+que.excu+flat2;
				return color;
			}
		}
		else if(stone_pen[i][y]==color)
		{
			que.push_tail(1);
			if(que.sum_value()==4)
			{	
				int flat1,flat2;
		for(i=0;i<5;i++)
		{
			if(que.que[i]==1)
			{
				flat1=i;
				break;
			}
		}
		for(i=5;i>0;i--)
		{
			if(que.que[i]==1)
			{
				flat2=i;
				break;
			}
		}
		point_four[0].y=y;
		point_four[1].y=y;
		point_four[0].x=x+que.excu+flat1;
		point_four[1].x=x+que.excu+flat2;
				return color;
			}
		}
		else
			break;
		
	}
	que.Enpty();//清空队列

	if(stone_pen[x][y]==color)
		que.push_head(1);
	else
		que.push_head(0);
	for(i=y-1,flat_five=5;i>=0&&flat_five>0;i--,flat_five--)//向上
	{
		if(stone_pen[x][i]==0)
		{
			que.push_head(0);
		}
		else if(stone_pen[x][i]==color)
		{
			que.push_head(1);
		}
		else
			break;
		
	}
	if(que.sum_value()==4)
	{
		int flat1,flat2;
		for(i=0;i<5;i++)
		{
			if(que.que[i]==1)
			{
				flat1=i;
				break;
			}
		}
		for(i=5;i>0;i--)
		{
			if(que.que[i]==1)
			{
				flat2=i;
				break;
			}
		}
		point_four[0].y=y-5+flat1;
		point_four[1].y=y-5+flat2;
		point_four[0].x=x;
		point_four[1].x=x;
		return color;
	}
	for(i=y+1,flat_five=5;i<19&&flat_five>0;i++,flat_five--)//向下
	{
		if(stone_pen[x][i]==0)
		{
			que.push_tail(0);
			if(que.sum_value()==4)
			{	
			int flat1,flat2;
			for(i=0;i<5;i++)
			{
				if(que.que[i]==1)
				{
					flat1=i;
					break;
				}
			}
			for(i=5;i>0;i--)
			{
				if(que.que[i]==1)
				{
					flat2=i;
					break;
				}
			}
				point_four[0].y=y+que.excu+flat1;
				point_four[1].y=y+que.excu+flat2;
				point_four[0].x=x;
				point_four[1].x=x;
				return color;
			}
		}
		else if(stone_pen[x][i]==color)
		{
			que.push_tail(1);
			if(que.sum_value()==4)
			{	
			int flat1,flat2;
			for(i=0;i<5;i++)
			{
				if(que.que[i]==1)
				{
					flat1=i;
					break;
				}
			}
			for(i=5;i>0;i--)
			{
				if(que.que[i]==1)
				{
					flat2=i;
					break;
				}
			}
				point_four[0].y=y+que.excu+flat1;
				point_four[1].y=y+que.excu+flat2;
				point_four[0].x=x;
				point_four[1].x=x;
				return color;
			}
		}
		else
			break;
		
	}
	que.Enpty();//清空队列

	if(stone_pen[x][y]==color)
		que.push_head(1);
	else
		que.push_head(0);
	for(i=x-1,j=y-1,flat_five=5;i>=0&&j>=0&&flat_five>0;i--,j--,flat_five--)//   左上方
	{
		if(stone_pen[i][j]==0)
		{
			que.push_head(0);
		}
		else if(stone_pen[i][j]==color)
		{
			que.push_head(1);
		}
		else
			break;
	}
	if(que.sum_value()==4)
	{
		int flat1,flat2;
		for(i=0;i<5;i++)
		{
			if(que.que[i]==1)
			{
				flat1=i;
				break;
			}
		}
		for(i=5;i>0;i--)
		{
			if(que.que[i]==1)
			{
				flat2=i;
				break;
			}
		}
		point_four[0].y=y-5+flat1;
		point_four[1].y=y-5+flat2;
		point_four[0].x=x-5+flat1;
		point_four[1].x=x-5+flat2;
		return color;
	}
	for(i=x+1,j=y+1,flat_five=5;i<19&&j<19&&flat_five>0;i++,j++,flat_five--)//右下方
	{
		if(stone_pen[i][j]==0)
		{
			que.push_tail(0);
			if(que.sum_value()==4)
			{	
				int flat1,flat2;
		for(i=0;i<5;i++)
		{
			if(que.que[i]==1)
			{
				flat1=i;
				break;
			}
		}
		for(i=5;i>0;i--)
		{
			if(que.que[i]==1)
			{
				flat2=i;
				break;
			}
		}
		point_four[0].y=y+que.excu+flat1;
		point_four[1].y=y+que.excu+flat2;
		point_four[0].x=x+que.excu+flat1;
		point_four[1].x=x+que.excu+flat2;
				return color;
			}
		}
		else if(stone_pen[i][j]==color)
		{
			que.push_tail(1);
			if(que.sum_value()==4)
			{	
				int flat1,flat2;
		for(i=0;i<5;i++)
		{
			if(que.que[i]==1)
			{
				flat1=i;
				break;
			}
		}
		for(i=5;i>0;i--)
		{
			if(que.que[i]==1)
			{
				flat2=i;
				break;
			}
		}
		point_four[0].y=y+que.excu+flat1;
		point_four[1].y=y+que.excu+flat2;
		point_four[0].x=x+que.excu+flat1;
		point_four[1].x=x+que.excu+flat2;
				return color;
			}
		}
		else
			break;
	}


	que.Enpty();//清空队列

	if(stone_pen[x][y]==color)
		que.push_head(1);
	else
		que.push_head(0);
	for(i=x+1,j=y-1,flat_five=5;i<19&&j>=0&&flat_five>0;i++,j--,flat_five--)//   右上方
	{
		if(stone_pen[i][j]==0)
		{
			que.push_head(0);
		}
		else if(stone_pen[i][j]==color)
		{
			que.push_head(1);
		}
		else
			break;
	}
	if(que.sum_value()==4)
	{
		int flat1,flat2;
		for(i=0;i<5;i++)
		{
			if(que.que[i]==1)
			{
				flat1=i;
				break;
			}
		}
		for(i=5;i>0;i--)
		{
			if(que.que[i]==1)
			{
				flat2=i;
				break;
			}
		}
		point_four[0].y=y-5+flat1;
		point_four[1].y=y-5+flat2;
		point_four[0].x=x+5-flat1;
		point_four[1].x=x+5-flat2;
		return color;
	}
	for(i=x-1,j=y+1,flat_five=5;i>=0&&j<19&&flat_five>0;i--,j++,flat_five--)//左下方
	{
		if(stone_pen[i][j]==0)
		{
			que.push_tail(0);
			if(que.sum_value()==4)
			{	
				int flat1,flat2;
		for(i=0;i<5;i++)
		{
			if(que.que[i]==1)
			{
				flat1=i;
				break;
			}
		}
		for(i=5;i>0;i--)
		{
			if(que.que[i]==1)
			{
				flat2=i;
				break;
			}
		}
		point_four[0].y=y+que.excu+flat1;
		point_four[1].y=y+que.excu+flat2;
		point_four[0].x=x-que.excu-flat1;
		point_four[1].x=x-que.excu-flat2;
				return color;
			}
		}
		else if(stone_pen[i][j]==color)
		{
			que.push_tail(1);
			if(que.sum_value()==4)
			{	
				int flat1,flat2;
		for(i=0;i<5;i++)
		{
			if(que.que[i]==1)
			{
				flat1=i;
				break;
			}
		}
		for(i=5;i>0;i--)
		{
			if(que.que[i]==1)
			{
				flat2=i;
				break;
			}
		}
		point_four[0].y=y+que.excu+flat1;
		point_four[1].y=y+que.excu+flat2;
		point_four[0].x=x-que.excu-flat1;
		point_four[1].x=x-que.excu-flat2;
				return color;
			}
		}
		else
			break;
	}
	return 0;
}

// 是否以经有四个活子在一起了
int Ai_stone::had_four(int color)
{
	
	
	if(color==1)
	{
		num_four1=0;
		for(int i=0;i<19;i++)
			for(int j=0;j<19;j++)
			{
				if(stone_pen[i][j]!=2)
				{
					if(is_four(i,j,1))
					{
						point_four1[num_four1][0]=point_four[0];
						point_four1[num_four1][1]=point_four[1];
						num_four1++;
					}
				}
			}
	}
	else if(color==2)
	{
		num_four2=0;
		for(int i=0;i<19;i++)
			for(int j=0;j<19;j++)
			{
				if(stone_pen[i][j]!=1)
				{
					if(is_four(i,j,2))
					{
						point_four2[num_four2][0]=point_four[0];
						point_four2[num_four2][1]=point_four[1];
						num_four2++;
					}
				}
			}
	}
	else
		return 0;
}

void Ai_stone::restarinf(void)
{
	int number=0;
	int value=0;
	int color=0;
	for(int i=0;i<19;i++)
	{
		for(int j=0;j<14;j++)
		{
			for(int num=0;num<6;num++)
			{
				if(stone_pen[i][j+num]==0)
				{
					;
				}
				else if(stone_pen[i][j+num]==1)
				{
					if(color==2)
					{
						break;
					}
					color=1;
					information[number]+=1<<num;
					value++;
				}
				else
				{
					if(color==1)
					{
						break;
					}
					color=2;
					information[number]+=1<<num;
					value++;
				}
			}//低6位是6个子的排列
			information[number]+=i<<21;//用20位来保存始未点座标7~26位
			information[number]+=j<<16;
			information[number]+=i<<11;
			information[number]+=(j+5)<<6;
			information[number]+=value<<26;
			information[number]+=color<<29;
			number++;
		}
	}

	for(int j=0;j<19;j++)
	{
		for(int i=0;i<14;i++)
		{
			for(int num=0;num<6;num++)
			{
				if(stone_pen[i][j+num]==0)
				{
					;
				}
				else if(stone_pen[i][j+num]==1)
				{
					if(color==2)
					{
						break;
					}
					color=1;
					information[number]+=1<<num;
					value++;
				}
				else
				{
					if(color==1)
					{
						break;
					}
					color=2;
					information[number]+=1<<num;
					value++;
				}
			}//低6位是6个子的排列
			information[number]+=i<<21;//用20位来保存始未点座标7~26位
			information[number]+=j<<16;
			information[number]+=i<<11;
			information[number]+=(j+5)<<6;
			information[number]+=value<<26;
			information[number]+=color<<29;
			number++;
		}
	}
}


void Ai_stone::restarinfstructs(void)
{
	int number=0;
	int value=0;
	int color=0;
	for(int i=0;i<19;i++)//向右
	{
		for(int j=0;j<14;j++)
		{
			value=0;
			color=0;
			for(int num=0;num<6;num++)
			{
				if(stone_pen[i][j+num]==0)
				{
					informations[number].excu[num]=0;;
				}
				else if(stone_pen[i][j+num]==1)
				{
					if(color==2)
					{
						color=-1;
						break;
					}
					color=1;
					informations[number].excu[num]=1;
					value++;
				}
				else
				{
					if(color==1)
					{
						color=-1;
						break;
					}
					color=2;
					informations[number].excu[num]=2;
					value++;
				}
			}
			informations[number].pos[0].x=i;
			informations[number].pos[0].y=j;
			informations[number].pos[1].x=i;
			informations[number].pos[1].y=j+5;
			if(color==-1)
				value=-1;
			informations[number].value=value;
			informations[number].color=color;
			number++;
		}
	}

	for(int j=0;j<19;j++)//向下
	{
		for(int i=0;i<14;i++)
		{
			color=0;
			value=0;
			for(int num=0;num<6;num++)
			{
				if(stone_pen[i+num][j]==0)
				{
					;
				}
				else if(stone_pen[i+num][j]==1)
				{
					if(color==2)
					{
						color=-1;
						break;
					}
					color=1;
					informations[number].excu[num]=1;
					value++;
				}
				else
				{
					if(color==1)
					{
						color=-1;
						break;
					}
					color=2;
					informations[number].excu[num]=2;
					value++;
				}
			}
			informations[number].pos[0].x=i;
			informations[number].pos[0].y=j;
			informations[number].pos[1].x=i+5;
			informations[number].pos[1].y=j;
			if(color==-1)
				value=-1;
			informations[number].value=value;
			informations[number].color=color;
			number++;
		}
	}
	for(int i=5;i<19;i++)//左上方向右下方
	{
		for(int j=0;j<=i-5;j++)
		{
			color=0;
			value=0;
			for(int num=0;num<6;num++)
			{
				if(stone_pen[i-j-num][j+num]==0)
				{
					;
				}
				else if(stone_pen[i-j-num][j+num]==1)
				{
					if(color==2)
					{
						color=-1;
						break;
					}
					color=1;
					informations[number].excu[num]=1;
					value++;
				}
				else
				{
					if(color==1)
					{
						color=-1;
						break;
					}
					color=2;
					informations[number].excu[num]=2;
					value++;
				}
			}
			informations[number].pos[0].x=i-j;
			informations[number].pos[0].y=j;
			informations[number].pos[1].x=i-j-5;
			informations[number].pos[1].y=j+5;
			if(color==-1)
				value=-1;
			informations[number].value=value;
			informations[number].color=color;
			number++;
		}
	}
	for(int i=1;i<14;i++)
	{
		for(int j=i;j<=18-5;j++)
		{
			color=0;
			value=0;
			for(int num=0;num<6;num++)
			{
				if(stone_pen[18-j+i-num][j+num]==0)
				{
					;
				}
				else if(stone_pen[18-j+i-num][j+num]==1)
				{
					if(color==2)
					{
						color=-1;
						break;
					}
					color=1;
					informations[number].excu[num]=1;
					value++;
				}
				else
				{
					if(color==1)
					{
						color=-1;
						break;
					}
					color=2;
					informations[number].excu[num]=2;
					value++;
				}
			}
			informations[number].pos[0].x=18-j+i;
			informations[number].pos[0].y=j;
			informations[number].pos[1].x=18-j+i-5;
			informations[number].pos[1].y=j+5;
			if(color==-1)
				value=-1;
			informations[number].value=value;
			informations[number].color=color;
			number++;
		}
	}
	for(int i=5;i<19;i++)//左下方向右上方
	{
		for(int j=18-i;j<=13;j++)
		{
			color=0;
			value=0;
			for(int num=0;num<6;num++)
			{
				if(stone_pen[j-(18-i)+num][j+num]==0)
				{
					;
				}
				else if(stone_pen[j-(18-i)+num][j+num]==1)
				{
					if(color==2)
					{
						color=-1;
						break;
					}
					color=1;
					informations[number].excu[num]=1;
					value++;
				}
				else
				{
					if(color==1)
					{
						color=-1;
						break;
					}
					color=2;
					informations[number].excu[num]=2;
					value++;
				}
			}
			informations[number].pos[0].x=j-(18-i);
			informations[number].pos[0].y=j;
			informations[number].pos[1].x=j-(18-i)+5;
			informations[number].pos[1].y=j+5;
			if(color==-1)
				value=-1;
			informations[number].value=value;
			informations[number].color=color;
			number++;
		}
	}
	for(int i=1;i<14;i++)
	{
		for(int j=0;j<=18-i-5;j++)
		{
			color=0;
			value=0;
			for(int num=0;num<6;num++)
			{
				if(stone_pen[i+j+num][j+num]==0)
				{
					;
				}
				else if(stone_pen[i+j+num][j+num]==1)
				{
					if(color==2)
					{
						color=-1;
						break;
					}
					color=1;
					informations[number].excu[num]=1;
					value++;
				}
				else
				{
					if(color==1)
					{
						color=-1;
						break;
					}
					color=2;
					informations[number].excu[num]=2;
					value++;
				}
			}
			informations[number].pos[0].x=j+i;
			informations[number].pos[0].y=j;
			informations[number].pos[1].x=j+i+5;
			informations[number].pos[1].y=j+5;
			if(color==-1)
				value=-1;
			informations[number].value=value;
			informations[number].color=color;
			number++;
		}
	}
}

// 计算棋盘的分数
void Ai_stone::All_value(int color)
{
	value_color1=0;
	value_color2=0;
	for(int i=0;i<924;i++)
	{
		switch(informations[i].value)
		{
		case 6:
			if(informations[i].color==1)
				value_color1+=1000000;
			else
				value_color2+=1000000;
			break;
		case 5:
			if(informations[i].color==1)
			{
				if(color==1)
					value_color1+=10000;
				else
					value_color1+=3000;
			}
			else
			{
				if(color==2)
					value_color2+=10000;
				else
					value_color2+=3000;
			}
			break;
		case 4:
			if(informations[i].color==1)
			{
				if(color==1)
					value_color1+=200;
				else
					value_color1+=2000;
			}
			else
			{
				if(color==2)
					value_color2+=200;
				else
					value_color2+=2000;
			}
			break;
		case 3:
			if(informations[i].color==1)
			{
				if(color==1)
					value_color1+=100;
				else
					value_color1+=40;
			}
			else
			{
				if(color==2)
					value_color2+=100;
				else
					value_color2+=40;
			}
			break;
		case 2:
			if(informations[i].color==1)
			{
				if(color==1)
					value_color1+=20;
				else
					value_color1+=25;
			}
			else
			{
				if(color==2)
					value_color2+=20;
				else
					value_color2+=25;
			}
			break;
		case 1:
			if(informations[i].color==1)
				value_color1+=1;
			else
				value_color2+=1;
		}
	}
}

void Ai_stone::thenexttowstone(int &x1, int &y1, int &x2, int &y2,int color)
{
	int x3,y3,x4,y4,x5,y5,x6,y6,x10,y10,x11,y11;
	int value_depth=0;

	restarinfstructs();
	thenextone(x1,y1,color);
	stone_pen[x1][y1]=color;

	restarinfstructs();
	thenextone_turntow(x2,y2,color);
	stone_pen[x2][y2]=color;
	restarinfstructs();
	All_value(color);
	int color2=1;
	if(color==1)
		color2=2;

	if(color==1&&(value_color1-value_color2)>100000)
		return;
	else
		(color==2&&(value_color2-value_color1)>100000);
	
	thenextone(x3,y3,color2);
	stone_pen[x3][y3]=color2;

	restarinfstructs();
	thenextone_turntow(x4,y4,color2);
	stone_pen[x4][y4]=color2;

	restarinfstructs();
	thenextone(x10,y10,color);
	stone_pen[x10][y10]=color;

	restarinfstructs();
	int value_dif1=0;
	All_value(color);
	if(color==1)
		value_dif1=value_color1-value_color2;
	else
		value_dif1=value_color2-value_color1;




	stone_pen[x1][y1]=0;
	stone_pen[x2][y2]=0;
	stone_pen[x3][y3]=0;
	stone_pen[x4][y4]=0;
	stone_pen[x10][y10]=0;



		
	restarinfstructs();
	thenextone(x5,y5,color2);
	stone_pen[x5][y5]=color;

	restarinfstructs();
	thenextone_turntow(x6,y6,color2);
	stone_pen[x6][y6]=color;


	restarinfstructs();
	thenextone(x3,y3,color2);
	stone_pen[x3][y3]=color2;

	restarinfstructs();
	thenextone_turntow(x4,y4,color2);
	stone_pen[x4][y4]=color2;

	restarinfstructs();
	thenextone(x11,y11,color);
	stone_pen[x11][y11]=color;

	restarinfstructs();
	int value_dif2=0;
	All_value(color);
	if(color==1)
		value_dif2=value_color1-value_color2;
	else
		value_dif2=value_color2-value_color1;

	stone_pen[x5][y5]=0;
	stone_pen[x6][y6]=0;
	stone_pen[x3][y3]=0;
	stone_pen[x4][y4]=0;
	stone_pen[x11][y11]=0;

	if(value_dif2>value_dif1)
	{
		x1=x5;
		y1=y5;
		x2=x6;
		y2=y6;
	}
	//::Sleep(3000);
}
/*void Ai_stone::restarinfstructs(int **stone_pencopy )
{
	int number=0;
	int value=0;
	int color=0;
	for(int i=0;i<19;i++)//向右
	{
		for(int j=0;j<14;j++)
		{
			value=0;
			color=0;
			for(int num=0;num<6;num++)
			{
				if(stone_pencopy[i][j+num]==0)
				{
					;
				}
				else if(stone_pencopy[i][j+num]==1)
				{
					if(color==2)
					{
						color=-1;
						break;
					}
					color=1;
					informations[number].excu[num]=1;
					value++;
				}
				else
				{
					if(color==1)
					{
						color=-1;
						break;
					}
					color=2;
					informations[number].excu[num]=2;
					value++;
				}
			}
			informations[number].pos[0].x=i;
			informations[number].pos[0].y=j;
			informations[number].pos[1].x=i;
			informations[number].pos[1].y=j+5;
			if(color==-1)
				value=-1;
			informations[number].value=value;
			informations[number].color=color;
			number++;
		}
	}

	for(int j=0;j<19;j++)//向下
	{
		for(int i=0;i<14;i++)
		{
			color=0;
			value=0;
			for(int num=0;num<6;num++)
			{
				if(stone_pencopy[i+num][j]==0)
				{
					;
				}
				else if(stone_pencopy[i+num][j]==1)
				{
					if(color==2)
					{
						color=-1;
						break;
					}
					color=1;
					informations[number].excu[num]=1;
					value++;
				}
				else
				{
					if(color==1)
					{
						color=-1;
						break;
					}
					color=2;
					informations[number].excu[num]=2;
					value++;
				}
			}
			informations[number].pos[0].x=i;
			informations[number].pos[0].y=j;
			informations[number].pos[1].x=i+5;
			informations[number].pos[1].y=j;
			if(color==-1)
				value=-1;
			informations[number].value=value;
			informations[number].color=color;
			number++;
		}
	}
	for(int i=5;i<19;i++)//左上方向右下方
	{
		for(int j=0;j<=i-5;j++)
		{
			color=0;
			value=0;
			for(int num=0;num<6;num++)
			{
				if(stone_pencopy[i-j-num][j+num]==0)
				{
					;
				}
				else if(stone_pencopy[i-j-num][j+num]==1)
				{
					if(color==2)
					{
						color=-1;
						break;
					}
					color=1;
					informations[number].excu[num]=1;
					value++;
				}
				else
				{
					if(color==1)
					{
						color=-1;
						break;
					}
					color=2;
					informations[number].excu[num]=2;
					value++;
				}
			}
			informations[number].pos[0].x=i-j;
			informations[number].pos[0].y=j;
			informations[number].pos[1].x=i-j-5;
			informations[number].pos[1].y=j+5;
			if(color==-1)
				value=-1;
			informations[number].value=value;
			informations[number].color=color;
			number++;
		}
	}
	for(int i=0;i<14;i++)
	{
		for(int j=i;j<=18-5;j++)
		{
			color=0;
			value=0;
			for(int num=0;num<6;num++)
			{
				if(stone_pencopy[18-j+i-num][j+num]==0)
				{
					;
				}
				else if(stone_pencopy[18-j+i-num][j+num]==1)
				{
					if(color==2)
					{
						color=-1;
						break;
					}
					color=1;
					informations[number].excu[num]=1;
					value++;
				}
				else
				{
					if(color==1)
					{
						color=-1;
						break;
					}
					color=2;
					informations[number].excu[num]=2;
					value++;
				}
			}
			informations[number].pos[0].x=18-j+i;
			informations[number].pos[0].y=j;
			informations[number].pos[1].x=18-j+i-5;
			informations[number].pos[1].y=j+5;
			if(color==-1)
				value=-1;
			informations[number].value=value;
			informations[number].color=color;
			number++;
		}
	}
	for(int i=5;i<19;i++)//左下方向右上方
	{
		for(int j=18-i;j<=13;j++)
		{
			color=0;
			value=0;
			for(int num=0;num<6;num++)
			{
				if(stone_pencopy[j-(18-i)+num][j+num]==0)
				{
					;
				}
				else if(stone_pencopy[j-(18-i)+num][j+num]==1)
				{
					if(color==2)
					{
						color=-1;
						break;
					}
					color=1;
					informations[number].excu[num]=1;
					value++;
				}
				else
				{
					if(color==1)
					{
						color=-1;
						break;
					}
					color=2;
					informations[number].excu[num]=2;
					value++;
				}
			}
			informations[number].pos[0].x=j-(18-i);
			informations[number].pos[0].y=j;
			informations[number].pos[1].x=j-(18-i)+5;
			informations[number].pos[1].y=j+5;
			if(color==-1)
				value=-1;
			informations[number].value=value;
			informations[number].color=color;
			number++;
		}
	}
	for(int i=1;i<14;i++)
	{
		for(int j=0;j<=18-i-5;j++)
		{
			color=0;
			value=0;
			for(int num=0;num<6;num++)
			{
				if(stone_pencopy[i+j+num][j+num]==0)
				{
					;
				}
				else if(stone_pencopy[i+j+num][j+num]==1)
				{
					if(color==2)
					{
						color=-1;
						break;
					}
					color=1;
					informations[number].excu[num]=1;
					value++;
				}
				else
				{
					if(color==1)
					{
						color=-1;
						break;
					}
					color=2;
					informations[number].excu[num]=2;
					value++;
				}
			}
			informations[number].pos[0].x=j+i;
			informations[number].pos[0].y=j;
			informations[number].pos[1].x=j+i+5;
			informations[number].pos[1].y=j+5;
			if(color==-1)
				value=-1;
			informations[number].value=value;
			informations[number].color=color;
			number++;
		}
	}
}
*/
void Ai_stone::thenextone(int &x1, int &y1,int color)   
{
	POINT thesame_value[10];
	for(int number=0;number<10;number++)
	{
		thesame_value[number].x=-1;
		thesame_value[number].y=-1;
	}
	int value_dif=0;
	All_value(color);
	if(color==1)
		value_dif=value_color1-value_color2;
	else
		value_dif=value_color2-value_color1;

	for(int i=0;i<19;i++)
		for(int j=0;j<19;j++)
		{
			if(stone_pen[i][j]==0)
			{
				stone_pen[i][j]=color;
				restarinfstructs();
				All_value(color);
				int value_difs=0;
				if(color==1)
					value_difs=value_color1-value_color2;
				else
					value_difs=value_color2-value_color1;
				if(value_difs>value_dif)
				{
					stone_pen[i][j]=0;
					x1=i;
					y1=j;
					value_dif=value_difs;
				}
				else if(value_difs==value_dif)
				{
					for(int number=9;number>0;number--)
					{
						thesame_value[number]=thesame_value[number-1];
					}
					thesame_value[0].x=i;
					thesame_value[0].y=j;
					stone_pen[i][j]=0;
				}
				else
				{
					stone_pen[i][j]=0;
				}
			}
		}
		if(thesame_value[0].x>x1||(thesame_value[0].x==x1&&thesame_value[0].y>y1))
		{
			int i=1;
			while(thesame_value[i].x>=x1&&i<10)
				i++;
			//i--;
			if(i<10)
			{
				thesame_value[i].x=x1;
				thesame_value[i].y=y1;
				i++;
			}
			srand(LOWORD(GetCurrentTime()));
			int swicth=rand()%i;
			x1=thesame_value[swicth].x;
			y1=thesame_value[swicth].y;
		}
}

void Ai_stone::thenextone_turntow(int &x1, int &y1,int color)
{
	int value_dif=0;
	bool flat=false;//是不是下过测试棋
	All_value_turntwo(color);
	if(color==1)
		value_dif=value_color1-value_color2;
	else
		value_dif=value_color2-value_color1;

	for(int i=0;i<19;i++)
		for(int j=0;j<19;j++)
		{
			if(stone_pen[i][j]==0)
			{
				stone_pen[i][j]=color;
				if(flat)
				stone_pen[x1][y1]=0;//把上次的测试棋取消
				restarinfstructs();
				All_value_turntwo(color);
				int value_difs=0;
				if(color==1)
					value_difs=value_color1-value_color2;
				else
					value_difs=value_color2-value_color1;
				if(value_difs>value_dif)
				{
					if(flat)
						stone_pen[x1][y1]=0;
					x1=i;
					y1=j;
					flat=true;
					value_dif=value_difs;
				}
				else
				{
					if(flat)
						stone_pen[x1][y1]=color;
					stone_pen[i][j]=0;
				}
			}
		}
}

void Ai_stone::All_value_turntwo(int color)
{
	value_color1=0;
	value_color2=0;
	for(int i=0;i<938;i++)
	{
		switch(informations[i].value)
		{
		case 6:
			if(informations[i].color==1)
				value_color1+=1000000;
			else
				value_color2+=1000000;
			break;
		case 5:
			if(informations[i].color==1)
			{
				if(color==1)
					value_color1+=200;
				else
					value_color1+=2000;
			}
			else
			{
				if(color==2)
					value_color2+=200;
				else
					value_color2+=2000;
			}
			break;
		case 4:
			if(informations[i].color==1)
			{
				if(color==1)
					value_color1+=200;
				else
					value_color1+=2000;
			}
			else
			{
				if(color==2)
					value_color2+=200;
				else
					value_color2+=2000;
			}
			break;
		case 3:
			if(informations[i].color==1)
			{
				if(color==1)
					value_color1+=40;
				else
					value_color1+=50;
			}
			else
			{
				if(color==2)
					value_color2+=40;
				else
					value_color2+=50;
			}
			break;
		case 2:
			if(informations[i].color==1)
			{
				if(color==1)
					value_color1+=20;
				else
					value_color1+=25;
			}
			else
			{
				if(color==2)
					value_color2+=20;
				else
					value_color2+=25;
			}
			break;
		case 1:
			if(informations[i].color==1)
				value_color1+=1;
			else
				value_color2+=1;
		}
	}
}
