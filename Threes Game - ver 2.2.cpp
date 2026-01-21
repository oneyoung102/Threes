#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <ctime>
#include <fstream>
#include <vector>
#include <math.h>

#define BLACK 0 
#define BLUE 1 
#define GREEN 2 
#define CYAN 3 
#define RED 4 
#define MAGENTA 5 
#define BROWN 6 
#define LIGHTGRAY 7 
#define DARKGRAY 8 
#define LIGHTBLUE 9 
#define LIGHTGREEN 10 
#define LIGHTCYAN 11 
#define LIGHTRED 12 
#define LIGHTMAGENTA 13 
#define YELLOW 14 
#define WHITE 15 

#define MAPX 8
#define MAPY 6

#define MAXCOUNT12 3  //최대 1,2 허용 갯수 

int i,j,i1,j1,i2,j2,i3,j3;
int imain,jmain;
int mov_x=0,mov_y=0;
int num_rand,moving_true=0;
int max_num=0,next_num;
int random,rand_type_num=100;
int num_tact=0;
int num_back_color=LIGHTGRAY,num_back_color1=LIGHTGRAY,max_num_color=BLACK;
char but;

int have_num[13]={0,0,0,0,0,0,0,0,0,0,0,0,0}; //0,0,0,0,0,0,0,0,0,0,0,0,0    1,1,1,1,1,1,1,1,1,1,1,1,1
int score=0;

int encycle_mode=1,setting_mode=0;//0은 일반 게임 플래이, 1은 숫자 도감 , 2는 튜토리얼  / setting 은 0은 설정 밖, 1은 설정 안, 2는 설정에서 게임 종료  
int height=0,set_type[5]={1,1,1,1,0};

int count1=0,count2=0,count3=0,count6=0,count12=0,count24=0,end_counting=1;

unsigned long long file_int,file_int1,power_int;
char file_char[26];
char name[26];

int tuto_phase=0;

int game_test=0;//0 기본 1 테스트 

int num_pos[17][26]={//멥 위치 고려x 
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};



using namespace std;

std::string Path = "text.txt";
std::ifstream readFile(Path);
std::ofstream writeFile(Path);
ofstream fout;
ifstream fin;

////////////////////////////////////////////////////////////////////////////
void textcolor(int foreground, int background) //글자색 
{ 
int color=foreground+background*16; 
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color); 
}

///////////////////////////////////////////////////////////////////////////////
void Gotoxy(int x, int y)          //gotxy
{
	COORD Pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Pos);	
	
}
//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
void Write(int x, int y, int foreground, int background, char text[10000]){
	if(y-height>=0&&y-height<=29){
	Gotoxy(x, y-height);
	textcolor(foreground, background);
	cout<<text;	
	}
	
}
//////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////
void Num_write(int init_num_x, int init_num_y,float num){//멥 위치 고려x 
	
	max_num_color=BLACK;
	if(num_pos[init_num_y][init_num_x]==max_num)
	max_num_color=LIGHTRED;
	
	if(init_num_x==1||init_num_x==6||init_num_x==7||init_num_x==12||init_num_x==13||init_num_x==18||init_num_x==19)
	num_back_color=LIGHTGRAY;
	else
	num_back_color=DARKGRAY;
	
	if(init_num_x+5==6||init_num_x+5==7||init_num_x+5==12||init_num_x+5==13||init_num_x+5==18||init_num_x+5==19||init_num_x+5==24)
	num_back_color1=LIGHTGRAY;
	else
	num_back_color1=DARKGRAY;
	
	//////////////////////////////////////////////////////////////컬러카드 
	if((encycle_mode!=1&&init_num_y<=16)||(encycle_mode==1&&init_num_y<=12))
	if(num==1){
	Write(init_num_x+MAPX,init_num_y+MAPY,BLACK  ,num_back_color," ");
	Write(init_num_x+1+MAPX,init_num_y+MAPY,BLACK  ,CYAN,"    ");
	Write(init_num_x+5+MAPX,init_num_y+MAPY,BLACK  ,num_back_color1," ");
	
	Write(init_num_x+MAPX,init_num_y+1+MAPY,BLACK  ,num_back_color," ");
	Write(init_num_x+1+MAPX,init_num_y+1+MAPY,WHITE,CYAN," １ ");
	Write(init_num_x+5+MAPX,init_num_y+1+MAPY,BLACK  ,num_back_color1," ");
	
	Write(init_num_x+MAPX,init_num_y+2+MAPY,BLACK  ,num_back_color," ");
	Write(init_num_x+1+MAPX,init_num_y+2+MAPY,BLACK,CYAN,"    ");
	Write(init_num_x+5+MAPX,init_num_y+2+MAPY,BLACK  ,num_back_color1," ");
	}
	else if(num==2){
	Write(init_num_x+MAPX,init_num_y+MAPY,BLACK  ,num_back_color," ");
	Write(init_num_x+1+MAPX,init_num_y+MAPY,BLACK,LIGHTRED  ,"    ");
	Write(init_num_x+5+MAPX,init_num_y+MAPY,BLACK  ,num_back_color1," ");
	
	Write(init_num_x+MAPX,init_num_y+1+MAPY,BLACK  ,num_back_color," ");
	Write(init_num_x+1+MAPX,init_num_y+1+MAPY,WHITE,LIGHTRED," ２ ");
	Write(init_num_x+5+MAPX,init_num_y+1+MAPY,BLACK  ,num_back_color1," ");
	
	Write(init_num_x+MAPX,init_num_y+2+MAPY,BLACK  ,num_back_color," ");
	Write(init_num_x+1+MAPX,init_num_y+2+MAPY,BLACK,LIGHTRED,"    ");
	Write(init_num_x+5+MAPX,init_num_y+2+MAPY,BLACK  ,num_back_color1," ");
	}
	else if(num==3){
	Write(init_num_x+MAPX,init_num_y+MAPY,BLACK  ,num_back_color," ");	
	Write(init_num_x+1+MAPX,init_num_y+MAPY,BLACK ,WHITE,"    ");
	Write(init_num_x+5+MAPX,init_num_y+MAPY,BLACK  ,num_back_color1," ");
	
	Write(init_num_x+MAPX,init_num_y+1+MAPY,BLACK  ,num_back_color," ");
	Write(init_num_x+1+MAPX,init_num_y+1+MAPY,BLACK,WHITE," ３ ");
	Write(init_num_x+5+MAPX,init_num_y+1+MAPY,BLACK  ,num_back_color1," ");
	
	Write(init_num_x+MAPX,init_num_y+2+MAPY,BLACK  ,num_back_color," ");
	Write(init_num_x+1+MAPX,init_num_y+2+MAPY,BLACK ,BROWN,"._. ");
	Write(init_num_x+5+MAPX,init_num_y+2+MAPY,BLACK  ,num_back_color1," ");
	}
	else if(num==6){
	Write(init_num_x+MAPX,init_num_y+MAPY,BLACK  ,num_back_color," ");	
	Write(init_num_x+1+MAPX,init_num_y+MAPY,BLACK ,WHITE,"    ");
	Write(init_num_x+5+MAPX,init_num_y+MAPY,BLACK  ,num_back_color1," ");
	
	Write(init_num_x+MAPX,init_num_y+1+MAPY,BLACK  ,num_back_color," ");
	Write(init_num_x+1+MAPX,init_num_y+1+MAPY,max_num_color,WHITE," ６ ");
	Write(init_num_x+5+MAPX,init_num_y+1+MAPY,BLACK  ,num_back_color1," ");
	
	Write(init_num_x+MAPX,init_num_y+2+MAPY,BLACK  ,num_back_color," ");
	Write(init_num_x+1+MAPX,init_num_y+2+MAPY,BLACK ,BROWN,".__.");
	Write(init_num_x+5+MAPX,init_num_y+2+MAPY,BLACK  ,num_back_color1," ");
	}	
	else if(num==12){
	Write(init_num_x+MAPX,init_num_y+MAPY,BLACK  ,num_back_color," ");	
	Write(init_num_x+1+MAPX,init_num_y+MAPY,BLACK ,WHITE,"    ");
	Write(init_num_x+5+MAPX,init_num_y+MAPY,BLACK  ,num_back_color1," ");
	
	Write(init_num_x+MAPX,init_num_y+1+MAPY,BLACK  ,num_back_color," ");
	Write(init_num_x+1+MAPX,init_num_y+1+MAPY,max_num_color,WHITE," 12 ");
	Write(init_num_x+5+MAPX,init_num_y+1+MAPY,BLACK  ,num_back_color1," ");
	
	Write(init_num_x+MAPX,init_num_y+2+MAPY,BLACK  ,num_back_color," ");
	Write(init_num_x+1+MAPX,init_num_y+2+MAPY,BLACK ,BROWN,",__,");
	Write(init_num_x+5+MAPX,init_num_y+2+MAPY,BLACK  ,num_back_color1," ");
	}
	else if(num==24){
	Write(init_num_x+MAPX,init_num_y+MAPY,BLACK  ,num_back_color," ");	
	Write(init_num_x+1+MAPX,init_num_y+MAPY,BLACK ,WHITE,"    ");
	Write(init_num_x+5+MAPX,init_num_y+MAPY,BLACK  ,num_back_color1," ");
	
	Write(init_num_x+MAPX,init_num_y+1+MAPY,BLACK  ,num_back_color," ");
	Write(init_num_x+1+MAPX,init_num_y+1+MAPY,max_num_color,WHITE," 24 ");
	Write(init_num_x+5+MAPX,init_num_y+1+MAPY,BLACK  ,num_back_color1," ");
	
	Write(init_num_x+MAPX,init_num_y+2+MAPY,BLACK  ,num_back_color," ");
	Write(init_num_x+1+MAPX,init_num_y+2+MAPY,BLACK ,BROWN,"-o- ");
	Write(init_num_x+5+MAPX,init_num_y+2+MAPY,BLACK  ,num_back_color1," ");
	}
	else if(num==48){
	Write(init_num_x+MAPX,init_num_y+MAPY,BLACK  ,num_back_color," ");	
	Write(init_num_x+1+MAPX,init_num_y+MAPY,BLACK ,WHITE,"    ");
	Write(init_num_x+5+MAPX,init_num_y+MAPY,BLACK  ,num_back_color1," ");
	
	Write(init_num_x+MAPX,init_num_y+1+MAPY,BLACK  ,num_back_color," ");
	Write(init_num_x+1+MAPX,init_num_y+1+MAPY,max_num_color,WHITE," 48 ");
	Write(init_num_x+5+MAPX,init_num_y+1+MAPY,BLACK  ,num_back_color1," ");
	
	Write(init_num_x+MAPX,init_num_y+2+MAPY,BLACK  ,num_back_color," ");
	Write(init_num_x+MAPX+1,init_num_y+2+MAPY,BLACK ,BROWN,".");
	Write(init_num_x+MAPX+2,init_num_y+2+MAPY,WHITE ,BROWN,",");
	Write(init_num_x+MAPX+3,init_num_y+2+MAPY,BLACK ,BROWN,"_.");
	Write(init_num_x+5+MAPX,init_num_y+2+MAPY,BLACK  ,num_back_color1," ");
	}
	else if(num==96){
	Write(init_num_x+MAPX,init_num_y+MAPY,BLACK  ,num_back_color," ");	
	Write(init_num_x+1+MAPX,init_num_y+MAPY,BLACK ,WHITE,"    ");
	Write(init_num_x+5+MAPX,init_num_y+MAPY,BLACK  ,num_back_color1," ");
	
	Write(init_num_x+MAPX,init_num_y+1+MAPY,BLACK  ,num_back_color," ");
	Write(init_num_x+1+MAPX,init_num_y+1+MAPY,max_num_color,WHITE," 96 ");
	Write(init_num_x+5+MAPX,init_num_y+1+MAPY,BLACK  ,num_back_color1," ");
	
	Write(init_num_x+MAPX,init_num_y+2+MAPY,BLACK  ,num_back_color," ");
	Write(init_num_x+MAPX+1,init_num_y+2+MAPY,BLACK ,BROWN,".");
	Write(init_num_x+MAPX+2,init_num_y+2+MAPY,WHITE ,BROWN,",");
	Write(init_num_x+MAPX+3,init_num_y+2+MAPY,WHITE ,BROWN,",");
	Write(init_num_x+MAPX+4,init_num_y+2+MAPY,BLACK ,BROWN,".");
	Write(init_num_x+5+MAPX,init_num_y+2+MAPY,BLACK  ,num_back_color1," ");
	}
	else if(num==192){
	Write(init_num_x+MAPX,init_num_y+MAPY,BLACK  ,num_back_color," ");	
	Write(init_num_x+1+MAPX,init_num_y+MAPY,BLACK ,BROWN,"    ");
	Write(init_num_x+5+MAPX,init_num_y+MAPY,BLACK  ,num_back_color1," ");
	
	Write(init_num_x+MAPX,init_num_y+1+MAPY,BROWN  ,num_back_color,"|");
	Write(init_num_x+1+MAPX,init_num_y+1+MAPY,max_num_color,WHITE,"192 ");
	Write(init_num_x+5+MAPX,init_num_y+1+MAPY,BROWN  ,num_back_color1,"|");
	
	Write(init_num_x+MAPX,init_num_y+2+MAPY,BLACK  ,num_back_color,"[");
	Write(init_num_x+1+MAPX,init_num_y+2+MAPY,BLACK ,BROWN,".");
	Write(init_num_x+2+MAPX,init_num_y+2+MAPY,WHITE ,BROWN,"~~");
	Write(init_num_x+4+MAPX,init_num_y+2+MAPY,BLACK ,BROWN,".");
	Write(init_num_x+5+MAPX,init_num_y+2+MAPY,BLACK  ,num_back_color1,"]");
	}
	else if(num==384){
	Write(init_num_x+MAPX,init_num_y+MAPY,BROWN  ,num_back_color,"{");	
	Write(init_num_x+1+MAPX,init_num_y+MAPY,BLACK ,BROWN,"    ");
	Write(init_num_x+5+MAPX,init_num_y+MAPY,BLACK  ,num_back_color1," ");
	
	Write(init_num_x+MAPX,init_num_y+1+MAPY,BLACK  ,num_back_color," ");
	Write(init_num_x+1+MAPX,init_num_y+1+MAPY,max_num_color,WHITE,"384_");
	Write(init_num_x+5+MAPX,init_num_y+1+MAPY,BLACK  ,num_back_color1," ");
	
	Write(init_num_x+MAPX,init_num_y+2+MAPY,BLACK  ,num_back_color,"'");
	Write(init_num_x+1+MAPX,init_num_y+2+MAPY,BLACK ,BROWN,".");
	Write(init_num_x+MAPX+2,init_num_y+2+MAPY,WHITE ,BROWN,",");
	Write(init_num_x+MAPX+3,init_num_y+2+MAPY,BLACK ,BROWN,"_o");
	Write(init_num_x+5+MAPX,init_num_y+2+MAPY,BLACK  ,num_back_color1,"'");
	}
	else if(num==768){
	Write(init_num_x+MAPX,init_num_y+MAPY,BROWN  ,num_back_color,"_");	
	Write(init_num_x+1+MAPX,init_num_y+MAPY,BROWN ,WHITE,"^  ^");
	Write(init_num_x+5+MAPX,init_num_y+MAPY,BROWN  ,num_back_color1,"_");
	
	Write(init_num_x+MAPX,init_num_y+1+MAPY,BROWN  ,BROWN," ");
	Write(init_num_x+1+MAPX,init_num_y+1+MAPY,max_num_color,WHITE,"768 ");
	Write(init_num_x+5+MAPX,init_num_y+1+MAPY,BROWN  ,BROWN," ");
	
	Write(init_num_x+MAPX,init_num_y+2+MAPY,BROWN  ,num_back_color,"V");
	Write(init_num_x+1+MAPX,init_num_y+2+MAPY,BLACK ,BROWN,":");
	Write(init_num_x+MAPX+2,init_num_y+2+MAPY,YELLOW ,BROWN,"-");
	Write(init_num_x+MAPX+3,init_num_y+2+MAPY,LIGHTRED ,BROWN,"-");
	Write(init_num_x+MAPX+4,init_num_y+2+MAPY,BLACK ,BROWN,":");
	Write(init_num_x+5+MAPX,init_num_y+2+MAPY,BROWN  ,num_back_color1,"V");
	}
	else if(num==1536){
	Write(init_num_x+MAPX,init_num_y+MAPY,WHITE  ,num_back_color,":");	
	Write(init_num_x+1+MAPX,init_num_y+MAPY,BLACK ,WHITE,"    ");
	Write(init_num_x+5+MAPX,init_num_y+MAPY,WHITE  ,num_back_color1,":");
	
	Write(init_num_x+MAPX,init_num_y+1+MAPY,WHITE  ,num_back_color,":");
	Write(init_num_x+1+MAPX,init_num_y+1+MAPY,max_num_color,WHITE,"1536");
	Write(init_num_x+5+MAPX,init_num_y+1+MAPY,WHITE  ,num_back_color1,":");
	
	Write(init_num_x+MAPX,init_num_y+2+MAPY,WHITE  ,num_back_color,";");
	Write(init_num_x+1+MAPX,init_num_y+2+MAPY,BLACK ,BROWN,"^");
	Write(init_num_x+MAPX+2,init_num_y+2+MAPY,WHITE ,BROWN,"V");
	Write(init_num_x+MAPX+3,init_num_y+2+MAPY,WHITE ,BROWN,"V");
	Write(init_num_x+MAPX+4,init_num_y+2+MAPY,BLACK ,BROWN,"^");
	Write(init_num_x+5+MAPX,init_num_y+2+MAPY,WHITE  ,num_back_color1,";");
	}
	else if(num==3072){
	Write(init_num_x+MAPX,init_num_y+MAPY,WHITE  ,num_back_color," ");	
	Write(init_num_x+1+MAPX,init_num_y+MAPY,BLACK ,WHITE,"    ");
	Write(init_num_x+5+MAPX,init_num_y+MAPY,WHITE  ,num_back_color1," ");
	
	Write(init_num_x+MAPX,init_num_y+1+MAPY,WHITE  ,num_back_color,"+");
	Write(init_num_x+1+MAPX,init_num_y+1+MAPY,max_num_color,WHITE,"3072");
	Write(init_num_x+5+MAPX,init_num_y+1+MAPY,WHITE  ,num_back_color1,"+");
	
	Write(init_num_x+MAPX,init_num_y+2+MAPY,BROWN  ,num_back_color,"[");
	Write(init_num_x+1+MAPX,init_num_y+2+MAPY,BLACK ,BROWN,"\"");
	Write(init_num_x+MAPX+2,init_num_y+2+MAPY,BLACK ,BROWN,"==");
	Write(init_num_x+MAPX+4,init_num_y+2+MAPY,BLACK ,BROWN,"\"");
	Write(init_num_x+5+MAPX,init_num_y+2+MAPY,BROWN  ,num_back_color1,"]");
	}
	else if(num==6144){
	Write(init_num_x+MAPX,init_num_y+MAPY,BROWN  ,num_back_color,"{");	
	Write(init_num_x+1+MAPX,init_num_y+MAPY,BLACK ,BROWN,"    ");
	Write(init_num_x+5+MAPX,init_num_y+MAPY,BROWN  ,num_back_color1,"}");
	
	Write(init_num_x+MAPX,init_num_y+1+MAPY,BROWN  ,BROWN," ");
	Write(init_num_x+1+MAPX,init_num_y+1+MAPY,max_num_color,WHITE,"6144");
	Write(init_num_x+5+MAPX,init_num_y+1+MAPY,BROWN  ,BROWN," ");
	
	Write(init_num_x+MAPX,init_num_y+2+MAPY,BROWN  ,num_back_color,"'");
	Write(init_num_x+1+MAPX,init_num_y+2+MAPY,WHITE ,BLACK,"^^^^");
	Write(init_num_x+5+MAPX,init_num_y+2+MAPY,BROWN  ,num_back_color1,"'");
	}
	else if(num==12288){
	Write(init_num_x+MAPX,init_num_y+MAPY,WHITE  ,num_back_color,"[");	
	Write(init_num_x+1+MAPX,init_num_y+MAPY,LIGHTRED ,WHITE,"^");
	Write(init_num_x+2+MAPX,init_num_y+MAPY,BLACK ,WHITE,"  ");
	Write(init_num_x+4+MAPX,init_num_y+MAPY,CYAN ,WHITE,"^");
	Write(init_num_x+5+MAPX,init_num_y+MAPY,WHITE  ,num_back_color1,"]");
	
	Write(init_num_x+MAPX,init_num_y+1+MAPY,WHITE  ,WHITE," ");
	Write(init_num_x+1+MAPX,init_num_y+1+MAPY,BLACK,BROWN,"o");
	Write(init_num_x+2+MAPX,init_num_y+1+MAPY,WHITE,BROWN,"▼");
	Write(init_num_x+4+MAPX,init_num_y+1+MAPY,BLACK,BROWN,"o");
	Write(init_num_x+5+MAPX,init_num_y+1+MAPY,WHITE  ,WHITE," ");
	
	Write(init_num_x+MAPX,init_num_y+2+MAPY,WHITE  ,num_back_color,"'");
	Write(init_num_x+1+MAPX,init_num_y+2+MAPY,BLACK ,BROWN," ∇ ");
	Write(init_num_x+5+MAPX,init_num_y+2+MAPY,WHITE  ,num_back_color1,"'");
	}
/////////////////////////////////////////////////////////////////////흑백카드	
		if(num==1+10000){
	Write(init_num_x+MAPX,init_num_y+MAPY,BLACK  ,num_back_color," ");
	Write(init_num_x+1+MAPX,init_num_y+MAPY,BLACK  ,DARKGRAY,"    ");
	Write(init_num_x+5+MAPX,init_num_y+MAPY,BLACK  ,num_back_color1," ");
	
	Write(init_num_x+MAPX,init_num_y+1+MAPY,BLACK  ,num_back_color," ");
	Write(init_num_x+1+MAPX,init_num_y+1+MAPY,WHITE,DARKGRAY," １ ");
	Write(init_num_x+5+MAPX,init_num_y+1+MAPY,BLACK  ,num_back_color1," ");
	
	Write(init_num_x+MAPX,init_num_y+2+MAPY,BLACK  ,num_back_color," ");
	Write(init_num_x+1+MAPX,init_num_y+2+MAPY,BLACK,DARKGRAY,"    ");
	Write(init_num_x+5+MAPX,init_num_y+2+MAPY,BLACK  ,num_back_color1," ");
	}
	else if(num==2+10000){
	Write(init_num_x+MAPX,init_num_y+MAPY,BLACK  ,num_back_color," ");
	Write(init_num_x+1+MAPX,init_num_y+MAPY,BLACK,DARKGRAY  ,"    ");
	Write(init_num_x+5+MAPX,init_num_y+MAPY,BLACK  ,num_back_color1," ");
	
	Write(init_num_x+MAPX,init_num_y+1+MAPY,BLACK  ,num_back_color," ");
	Write(init_num_x+1+MAPX,init_num_y+1+MAPY,WHITE,DARKGRAY," ２ ");
	Write(init_num_x+5+MAPX,init_num_y+1+MAPY,BLACK  ,num_back_color1," ");
	
	Write(init_num_x+MAPX,init_num_y+2+MAPY,BLACK  ,num_back_color," ");
	Write(init_num_x+1+MAPX,init_num_y+2+MAPY,BLACK,DARKGRAY,"    ");
	Write(init_num_x+5+MAPX,init_num_y+2+MAPY,BLACK  ,num_back_color1," ");
	}
	else if(num==3+10000){
	Write(init_num_x+MAPX,init_num_y+MAPY,BLACK  ,num_back_color," ");	
	Write(init_num_x+1+MAPX,init_num_y+MAPY,BLACK ,WHITE,"    ");
	Write(init_num_x+5+MAPX,init_num_y+MAPY,BLACK  ,num_back_color1," ");
	
	Write(init_num_x+MAPX,init_num_y+1+MAPY,BLACK  ,num_back_color," ");
	Write(init_num_x+1+MAPX,init_num_y+1+MAPY,BLACK,WHITE," ３ ");
	Write(init_num_x+5+MAPX,init_num_y+1+MAPY,BLACK  ,num_back_color1," ");
	
	Write(init_num_x+MAPX,init_num_y+2+MAPY,BLACK  ,num_back_color," ");
	Write(init_num_x+1+MAPX,init_num_y+2+MAPY,BLACK ,DARKGRAY,",_, ");
	Write(init_num_x+5+MAPX,init_num_y+2+MAPY,BLACK  ,num_back_color1," ");
	}
	else if(num==6+10000){
	Write(init_num_x+MAPX,init_num_y+MAPY,BLACK  ,num_back_color," ");	
	Write(init_num_x+1+MAPX,init_num_y+MAPY,BLACK ,WHITE,"    ");
	Write(init_num_x+5+MAPX,init_num_y+MAPY,BLACK  ,num_back_color1," ");
	
	Write(init_num_x+MAPX,init_num_y+1+MAPY,BLACK  ,num_back_color," ");
	Write(init_num_x+1+MAPX,init_num_y+1+MAPY,BLACK,WHITE," ６ ");
	Write(init_num_x+5+MAPX,init_num_y+1+MAPY,BLACK  ,num_back_color1," ");
	
	Write(init_num_x+MAPX,init_num_y+2+MAPY,BLACK  ,num_back_color," ");
	Write(init_num_x+1+MAPX,init_num_y+2+MAPY,BLACK ,DARKGRAY,",__,");
	Write(init_num_x+5+MAPX,init_num_y+2+MAPY,BLACK  ,num_back_color1," ");
	}	
	else if(num==12+10000){
	Write(init_num_x+MAPX,init_num_y+MAPY,BLACK  ,num_back_color," ");	
	Write(init_num_x+1+MAPX,init_num_y+MAPY,BLACK ,WHITE,"    ");
	Write(init_num_x+5+MAPX,init_num_y+MAPY,BLACK  ,num_back_color1," ");
	
	Write(init_num_x+MAPX,init_num_y+1+MAPY,BLACK  ,num_back_color," ");
	Write(init_num_x+1+MAPX,init_num_y+1+MAPY,BLACK,WHITE," 12 ");
	Write(init_num_x+5+MAPX,init_num_y+1+MAPY,BLACK  ,num_back_color1," ");
	
	Write(init_num_x+MAPX,init_num_y+2+MAPY,BLACK  ,num_back_color," ");
	Write(init_num_x+1+MAPX,init_num_y+2+MAPY,BLACK ,DARKGRAY,"x__x");
	Write(init_num_x+5+MAPX,init_num_y+2+MAPY,BLACK  ,num_back_color1," ");
	}
	else if(num==24+10000){
	Write(init_num_x+MAPX,init_num_y+MAPY,BLACK  ,num_back_color," ");	
	Write(init_num_x+1+MAPX,init_num_y+MAPY,BLACK ,WHITE,"    ");
	Write(init_num_x+5+MAPX,init_num_y+MAPY,BLACK  ,num_back_color1," ");
	
	Write(init_num_x+MAPX,init_num_y+1+MAPY,BLACK  ,num_back_color," ");
	Write(init_num_x+1+MAPX,init_num_y+1+MAPY,BLACK,WHITE," 24 ");
	Write(init_num_x+5+MAPX,init_num_y+1+MAPY,BLACK  ,num_back_color1," ");
	
	Write(init_num_x+MAPX,init_num_y+2+MAPY,BLACK  ,num_back_color," ");
	Write(init_num_x+1+MAPX,init_num_y+2+MAPY,BLACK ,DARKGRAY,"-x- ");
	Write(init_num_x+5+MAPX,init_num_y+2+MAPY,BLACK  ,num_back_color1," ");
	}
	else if(num==48+10000){
	Write(init_num_x+MAPX,init_num_y+MAPY,BLACK  ,num_back_color," ");	
	Write(init_num_x+1+MAPX,init_num_y+MAPY,BLACK ,WHITE,"    ");
	Write(init_num_x+5+MAPX,init_num_y+MAPY,BLACK  ,num_back_color1," ");
	
	Write(init_num_x+MAPX,init_num_y+1+MAPY,BLACK  ,num_back_color," ");
	Write(init_num_x+1+MAPX,init_num_y+1+MAPY,BLACK,WHITE," 48 ");
	Write(init_num_x+5+MAPX,init_num_y+1+MAPY,BLACK  ,num_back_color1," ");
	
	Write(init_num_x+MAPX,init_num_y+2+MAPY,BLACK  ,num_back_color," ");
	Write(init_num_x+MAPX+1,init_num_y+2+MAPY,BLACK ,DARKGRAY,"x");
	Write(init_num_x+MAPX+2,init_num_y+2+MAPY,WHITE ,DARKGRAY,",");
	Write(init_num_x+MAPX+3,init_num_y+2+MAPY,BLACK ,DARKGRAY,"_x");
	Write(init_num_x+5+MAPX,init_num_y+2+MAPY,BLACK  ,num_back_color1," ");
	}
	else if(num==96+10000){
	Write(init_num_x+MAPX,init_num_y+MAPY,BLACK  ,num_back_color," ");	
	Write(init_num_x+1+MAPX,init_num_y+MAPY,BLACK ,WHITE,"    ");
	Write(init_num_x+5+MAPX,init_num_y+MAPY,BLACK  ,num_back_color1," ");
	
	Write(init_num_x+MAPX,init_num_y+1+MAPY,BLACK  ,num_back_color," ");
	Write(init_num_x+1+MAPX,init_num_y+1+MAPY,BLACK,WHITE," 96 ");
	Write(init_num_x+5+MAPX,init_num_y+1+MAPY,BLACK  ,num_back_color1," ");
	
	Write(init_num_x+MAPX,init_num_y+2+MAPY,BLACK  ,num_back_color," ");
	Write(init_num_x+MAPX+1,init_num_y+2+MAPY,BLACK ,DARKGRAY,"x");
	Write(init_num_x+MAPX+2,init_num_y+2+MAPY,WHITE ,DARKGRAY,",");
	Write(init_num_x+MAPX+3,init_num_y+2+MAPY,WHITE ,DARKGRAY,",");
	Write(init_num_x+MAPX+4,init_num_y+2+MAPY,BLACK ,DARKGRAY,"x");
	Write(init_num_x+5+MAPX,init_num_y+2+MAPY,BLACK  ,num_back_color1," ");
	}
	else if(num==192+10000){
	Write(init_num_x+MAPX,init_num_y+MAPY,BLACK  ,num_back_color," ");	
	Write(init_num_x+1+MAPX,init_num_y+MAPY,BLACK ,DARKGRAY,"    ");
	Write(init_num_x+5+MAPX,init_num_y+MAPY,BLACK  ,num_back_color1," ");
	
	Write(init_num_x+MAPX,init_num_y+1+MAPY,DARKGRAY  ,num_back_color,"|");
	Write(init_num_x+1+MAPX,init_num_y+1+MAPY,max_num_color,WHITE,"192 ");
	Write(init_num_x+5+MAPX,init_num_y+1+MAPY,DARKGRAY  ,num_back_color1,"|");
	
	Write(init_num_x+MAPX,init_num_y+2+MAPY,BLACK  ,num_back_color,"[");
	Write(init_num_x+1+MAPX,init_num_y+2+MAPY,BLACK ,DARKGRAY,"x");
	Write(init_num_x+2+MAPX,init_num_y+2+MAPY,WHITE ,DARKGRAY,"~~");
	Write(init_num_x+4+MAPX,init_num_y+2+MAPY,BLACK ,DARKGRAY,"x");
	Write(init_num_x+5+MAPX,init_num_y+2+MAPY,BLACK  ,num_back_color1,"]");
	}
	else if(num==384+10000){
	Write(init_num_x+MAPX,init_num_y+MAPY,DARKGRAY  ,num_back_color,"{");	
	Write(init_num_x+1+MAPX,init_num_y+MAPY,BLACK ,DARKGRAY,"    ");
	Write(init_num_x+5+MAPX,init_num_y+MAPY,BLACK  ,num_back_color1," ");
	
	Write(init_num_x+MAPX,init_num_y+1+MAPY,BLACK  ,num_back_color," ");
	Write(init_num_x+1+MAPX,init_num_y+1+MAPY,BLACK,WHITE,"384_");
	Write(init_num_x+5+MAPX,init_num_y+1+MAPY,BLACK  ,num_back_color1," ");
	
	Write(init_num_x+MAPX,init_num_y+2+MAPY,BLACK  ,num_back_color,"'");
	Write(init_num_x+1+MAPX,init_num_y+2+MAPY,BLACK ,DARKGRAY,".");
	Write(init_num_x+MAPX+2,init_num_y+2+MAPY,WHITE ,DARKGRAY,",");
	Write(init_num_x+MAPX+3,init_num_y+2+MAPY,BLACK ,DARKGRAY,"_x");
	Write(init_num_x+5+MAPX,init_num_y+2+MAPY,BLACK  ,num_back_color1,"'");
	}
	else if(num==768+10000){
	Write(init_num_x+MAPX,init_num_y+MAPY,DARKGRAY  ,num_back_color,"_");	
	Write(init_num_x+1+MAPX,init_num_y+MAPY,DARKGRAY ,WHITE,"^  ^");
	Write(init_num_x+5+MAPX,init_num_y+MAPY,DARKGRAY  ,num_back_color1,"_");
	
	Write(init_num_x+MAPX,init_num_y+1+MAPY,DARKGRAY  ,DARKGRAY," ");
	Write(init_num_x+1+MAPX,init_num_y+1+MAPY,BLACK,WHITE,"768 ");
	Write(init_num_x+5+MAPX,init_num_y+1+MAPY,DARKGRAY  ,DARKGRAY," ");
	
	Write(init_num_x+MAPX,init_num_y+2+MAPY,DARKGRAY  ,num_back_color,"V");
	Write(init_num_x+1+MAPX,init_num_y+2+MAPY,BLACK ,DARKGRAY,"x");
	Write(init_num_x+MAPX+2,init_num_y+2+MAPY,LIGHTGRAY ,DARKGRAY,"-");
	Write(init_num_x+MAPX+3,init_num_y+2+MAPY,LIGHTGRAY ,DARKGRAY,"-");
	Write(init_num_x+MAPX+4,init_num_y+2+MAPY,BLACK ,DARKGRAY,"x");
	Write(init_num_x+5+MAPX,init_num_y+2+MAPY,DARKGRAY  ,num_back_color1,"V");
	}
	else if(num==1536+10000){
	Write(init_num_x+MAPX,init_num_y+MAPY,WHITE  ,num_back_color,":");	
	Write(init_num_x+1+MAPX,init_num_y+MAPY,BLACK ,WHITE,"    ");
	Write(init_num_x+5+MAPX,init_num_y+MAPY,WHITE  ,num_back_color1,":");
	
	Write(init_num_x+MAPX,init_num_y+1+MAPY,WHITE  ,num_back_color,":");
	Write(init_num_x+1+MAPX,init_num_y+1+MAPY,BLACK,WHITE,"1536");
	Write(init_num_x+5+MAPX,init_num_y+1+MAPY,WHITE  ,num_back_color1,":");
	
	Write(init_num_x+MAPX,init_num_y+2+MAPY,WHITE  ,num_back_color,";");
	Write(init_num_x+1+MAPX,init_num_y+2+MAPY,BLACK ,DARKGRAY,"x");
	Write(init_num_x+MAPX+2,init_num_y+2+MAPY,WHITE ,DARKGRAY,"V");
	Write(init_num_x+MAPX+3,init_num_y+2+MAPY,WHITE ,DARKGRAY,"V");
	Write(init_num_x+MAPX+4,init_num_y+2+MAPY,BLACK ,DARKGRAY,"xw");
	Write(init_num_x+5+MAPX,init_num_y+2+MAPY,WHITE  ,num_back_color1,";");
	}
	else if(num==3072+10000){
	Write(init_num_x+MAPX,init_num_y+MAPY,WHITE  ,num_back_color," ");	
	Write(init_num_x+1+MAPX,init_num_y+MAPY,BLACK ,WHITE,"    ");
	Write(init_num_x+5+MAPX,init_num_y+MAPY,WHITE  ,num_back_color1," ");
	
	Write(init_num_x+MAPX,init_num_y+1+MAPY,DARKGRAY  ,num_back_color,"+");
	Write(init_num_x+1+MAPX,init_num_y+1+MAPY,BLACK,WHITE,"3072");
	Write(init_num_x+5+MAPX,init_num_y+1+MAPY,DARKGRAY  ,num_back_color1,"+");
	
	Write(init_num_x+MAPX,init_num_y+2+MAPY,DARKGRAY  ,num_back_color,"[");
	Write(init_num_x+1+MAPX,init_num_y+2+MAPY,BLACK ,DARKGRAY,"x");
	Write(init_num_x+MAPX+2,init_num_y+2+MAPY,BLACK ,DARKGRAY,"==");
	Write(init_num_x+MAPX+4,init_num_y+2+MAPY,BLACK ,DARKGRAY,"x");
	Write(init_num_x+5+MAPX,init_num_y+2+MAPY,DARKGRAY  ,num_back_color1,"]");
	}
	else if(num==6144+10000){
	Write(init_num_x+MAPX,init_num_y+MAPY,DARKGRAY  ,num_back_color,"{");	
	Write(init_num_x+1+MAPX,init_num_y+MAPY,BLACK ,DARKGRAY,"    ");
	Write(init_num_x+5+MAPX,init_num_y+MAPY,DARKGRAY  ,num_back_color1,"}");
	
	Write(init_num_x+MAPX,init_num_y+1+MAPY,DARKGRAY  ,DARKGRAY," ");
	Write(init_num_x+1+MAPX,init_num_y+1+MAPY,BLACK,WHITE,"6144");
	Write(init_num_x+5+MAPX,init_num_y+1+MAPY,DARKGRAY  ,DARKGRAY," ");
	
	Write(init_num_x+MAPX,init_num_y+2+MAPY,DARKGRAY  ,num_back_color,"'");
	Write(init_num_x+1+MAPX,init_num_y+2+MAPY,WHITE ,BLACK,"`^^^");
	Write(init_num_x+5+MAPX,init_num_y+2+MAPY,DARKGRAY  ,num_back_color1,"'");
	}
	else if(num==12288+10000){
	Write(init_num_x+MAPX,init_num_y+MAPY,WHITE  ,num_back_color,"[");	
	Write(init_num_x+1+MAPX,init_num_y+MAPY,LIGHTGRAY ,WHITE,"^");
	Write(init_num_x+2+MAPX,init_num_y+MAPY,BLACK ,WHITE,"  ");
	Write(init_num_x+4+MAPX,init_num_y+MAPY,LIGHTGRAY ,WHITE,"^");
	Write(init_num_x+5+MAPX,init_num_y+MAPY,WHITE  ,num_back_color1,"]");
	
	Write(init_num_x+MAPX,init_num_y+1+MAPY,WHITE  ,WHITE," ");
	Write(init_num_x+1+MAPX,init_num_y+1+MAPY,BLACK,DARKGRAY,"o");
	Write(init_num_x+2+MAPX,init_num_y+1+MAPY,WHITE,DARKGRAY,"▼");
	Write(init_num_x+4+MAPX,init_num_y+1+MAPY,BLACK,DARKGRAY,"o");
	Write(init_num_x+5+MAPX,init_num_y+1+MAPY,WHITE  ,WHITE," ");
	
	Write(init_num_x+MAPX,init_num_y+2+MAPY,WHITE  ,num_back_color,"'");
	Write(init_num_x+1+MAPX,init_num_y+2+MAPY,BLACK ,DARKGRAY," ∇ ");
	Write(init_num_x+5+MAPX,init_num_y+2+MAPY,WHITE  ,num_back_color1,"'");
	}
	/////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////
void Map(){
	i=0;
	j=0;
	while(i<=25){//가로줄, 새로줄
		while((j<=15&&encycle_mode!=1)||(j<=11&&encycle_mode==1)){
			Write(MAPX+i,MAPY+j,BLACK,LIGHTGRAY," ");	
			j+=1;
		}
		j=0;
		i+=25;
	}
	if(encycle_mode!=1)
	Write(MAPX,MAPY+16,BLACK,LIGHTGRAY,"                          ");
	else if(encycle_mode==1)
	Write(MAPX,MAPY+12,BLACK,LIGHTGRAY,"                          ");	
	
	i=0;
	j=0;
	while(i<=3){//가로줄, 새로줄
		while((j<=3&&encycle_mode!=1)||(j<=2&&encycle_mode==1)){
			j1=0;
			i1=0;
			while(i1<=5){
				while(j1<=3){
					num_tact=0;
					i2=-5;
					j2=-3;
					while(i2<=5){
						while(j2<=3){					
							if(j*4+j2>=0&&j*4+j2<=16&&i*6+i2+1>=0&&i*6+i2+1<=25){
							if(num_pos[j*4+j2][i*6+i2+1]!=0){
								i3=i2;
								j3=j2;
								num_tact+=1;
							}	
						}
							j2+=1;
						}
						j2=-3;
						i2+=1;
					}
					
					if(i1==0||i1==5||j1==0){
						if(num_tact>=1){
							if(i1<i3||i1>5+i3||j1<j3||j1>2+j3)
							Write(MAPX+i*6+i1+1,MAPY+j*4+j1,BLACK,LIGHTGRAY," ");	
						}
						else{
							Write(MAPX+i*6+i1+1,MAPY+j*4+j1,BLACK,LIGHTGRAY," ");	
						}
					}
					
						
						
					j1+=1;
			}
			j1=0;
			i1+=1;
			}			
			j+=1;
		}
		i+=1;
		j=0;
	}
	
	i=0;
	j=0;
	while(i<=3){//가로줄, 새로줄 재외한, 카드가 위치한 부분 
		while((j<=3&&encycle_mode!=1)||(j<=2&&encycle_mode==1)){
			j1=0;
			i1=0;
			while(i1<=3){
				while(j1<=2){
					num_tact=0;
					i2=-3;
					j2=-2;
					while(i2<=3){
						while(j2<=2){					
							if(1+j*4+j2>=0&&1+j*4+j2<=16&&2+i*6+i2>=0&&2+i*6+i2<=25){
							if(num_pos[1+j*4+j2][2+i*6+i2]!=0){
								i3=i2;
								j3=j2;
								num_tact+=1;
							}	
						}
							j2+=1;
						}
						j2=-2;
						i2+=1;
					}
					if(num_tact>=1){
						if(i1<i3||i1>5+i3||j1<j3||j1>2+j3)
						Write(MAPX+2+i*6+i1,MAPY+1+j*4+j1,BLACK,DARKGRAY," ");	
					}
					else{
						Write(MAPX+2+i*6+i1,MAPY+1+j*4+j1,BLACK,DARKGRAY," ");	
					}
						
						
					j1+=1;
			}
			j1=0;
			i1+=1;
			}			
			j+=1;
		}
		i+=1;
		j=0;
	}
}
/////////////////////////////////////////////////////////////
void Background(){
	i=0;
	j=0;
	while(i<=41){
		while(j<=29){
			if((i<MAPX||j<MAPY||i>MAPX+25||(j>MAPY+16&&encycle_mode!=1)||(j>MAPY+12&&encycle_mode==1))&&(i<MAPX+11||j>MAPY-1||i>MAPY+16)&&(i<MAPX||i>MAPX+4||j<2||j>4)&&(i<MAPX+21||i>MAPX+25||j<2||j>4)&&(i<MAPX||i>MAPX+25||j<21||j>23)&&(i<MAPX+8||i>MAPX+18||j!=3))
			Write(i,j,BLACK,WHITE," ");
			else if(i>=MAPX+11&&j<=MAPY-2&&i<=MAPY+16&&(i<MAPX+12||i>MAPY+15||j>MAPY-3||j<2)){
			if(encycle_mode==0&&end_counting!=0)
				Write(i,j,BLACK,LIGHTGRAY," ");
			else if(encycle_mode==1||encycle_mode==2||end_counting==0)
				Write(i,j,BLACK,WHITE," ");	
			}			
			else if(j==MAPY-1&&i==MAPX+11){
			if(encycle_mode==0&&end_counting!=0)
				Write(i,j,DARKGRAY,WHITE,"next");
			else if(encycle_mode==1||encycle_mode==2||end_counting==0)	
				Write(i,j,BLACK,WHITE,"    ");		
			}
			
			j+=1;
		}
		j=0;
		i+=1;
	}
	
	if(encycle_mode!=2&&end_counting!=0){
	Write(MAPX,2,DARKGRAY,WHITE,"_____"); 
	Write(MAPX,3,WHITE,DARKGRAY," :== ");
	if(set_type[2]==1)//visible key 	
	Write(MAPX,4,LIGHTGRAY,WHITE,">>'r'");
	else if(set_type[2]==0)//visible key
	Write(MAPX,4,LIGHTGRAY,WHITE,"     ");	
	}
	else if(encycle_mode==2||end_counting==0){
	Write(MAPX,2,WHITE,WHITE,"     "); 
	Write(MAPX,3,WHITE,WHITE,"     "); 
	Write(MAPX,4,WHITE,WHITE,"     ");		
	}
	if(encycle_mode==1){
	Write(MAPX+21,2,DARKGRAY,WHITE,"_____"); 
	Write(MAPX+21,3,WHITE,DARKGRAY,"1+2=3"); 	
	if(set_type[2]==1)//visible key
	Write(MAPX+21,4,LIGHTGRAY,WHITE,">>'t'");
	else if(set_type[2]==0)//visible key
	Write(MAPX+21,4,LIGHTGRAY,WHITE,"     ");
	}
	else{
	Write(MAPX+21,2,WHITE,WHITE,"     "); 
	Write(MAPX+21,3,WHITE,WHITE,"     "); 	
	Write(MAPX+21,4,WHITE,WHITE,"     ");	
	}
	if(encycle_mode!=1){
	Write(MAPX+8,3,WHITE,WHITE,"   ");
	Write(MAPX+15,3,WHITE,WHITE,"    ");	
	}
	
	
		
	if(encycle_mode==0&&end_counting!=0){
	if(next_num==0){
		Write(MAPX+12,2,BLACK,LIGHTGRAY,"  ");
		Write(MAPX+12,3,BLACK,LIGHTGRAY,"  ");
	}
	else if(next_num==1){
		Write(MAPX+12,2,BLACK,CYAN,"  ");
		Write(MAPX+12,3,BLACK,CYAN,"  ");
	}
	else if(next_num==2){
		Write(MAPX+12,2,BLACK,LIGHTRED,"  ");
		Write(MAPX+12,3,BLACK,LIGHTRED,"  ");
	}
	else if(next_num==3){
		Write(MAPX+12,2,BLACK,WHITE,"３");
		Write(MAPX+12,3,BROWN,WHITE,"__");
	}
	else if(next_num==6){
		Write(MAPX+12,2,BLACK,WHITE,"６");
		Write(MAPX+12,3,BROWN,WHITE,"__");
	}
	else if(next_num==12&&max_num>48){
		Write(MAPX+12,2,BLACK,WHITE,"12");
		Write(MAPX+12,3,BROWN,WHITE,"__");
	}
	else if(next_num==24&&max_num>192){
		Write(MAPX+12,2,BLACK,WHITE,"24");
		Write(MAPX+12,3,BROWN,WHITE,"__");
	}
	else if(next_num==48&&max_num>768){
		Write(MAPX+12,2,BLACK,WHITE,"48");
		Write(MAPX+12,3,BROWN,WHITE,"__");
	}
	else if(next_num==96&&max_num>3072){
		Write(MAPX+12,2,BLACK,WHITE,"96");
		Write(MAPX+12,3,BROWN,WHITE,"__");
	}
	else if((next_num>6&&max_num<=48)||(next_num>=24&&max_num<=192)||(next_num>=48&&max_num<=768)||(next_num>=96&&max_num<=3072)||(next_num>192&&max_num>3072)){
		Write(MAPX+12,2,BLACK,WHITE,"＋");
		Write(MAPX+12,3,BROWN,WHITE,"__");
	}	
	}
	else if(encycle_mode!=0||end_counting==0){
		Write(MAPX+12,2,BLACK,WHITE,"  ");
		Write(MAPX+12,3,BLACK,WHITE,"  ");
	}
	
}
//////////////////////////////////////////////////////////////////////////
void Counting(){
	count1=0;
	count2=0;
	count3=0;
	count6=0;
	count12=0;
	count24=0;
	i=0;
	j=0;
	while(i<=25){
		while(j<=16){
			if(num_pos[j][i]==1)
			count1+=1;
			else if(num_pos[j][i]==2)
			count2+=1;
			else if(num_pos[j][i]==3)
			count3+=1;
			else if(num_pos[j][i]==6)
			count6+=1;
			else if(num_pos[j][i]==12)
			count12+=1;
			else if(num_pos[j][i]==24)
			count24+=1;
			j+=1;
		}
		j=0;
		i+=1;
	}
}

void Max_num_detect(){
	i=0;                   //맥스 넘버 감지 
	j=0;
	while(i<=25){
		while(j<=16){
			if(num_pos[j][i]>=max_num&&num_pos[j][i]!=0)
			max_num=num_pos[j][i];	
			
			j+=1;
		}
		j=0;
		i+=1;
	}
} 

void Next_num_random(){
	
	if(max_num<=24)
	rand_type_num=89;
	else if(max_num>=24&&max_num<48)
	rand_type_num=96;
	else if(max_num>48&&max_num<=192)
	rand_type_num=100;
	else if(max_num>192&&max_num<=384)
	rand_type_num=102;
	else if(max_num>384&&max_num<=768)
	rand_type_num=106;
	else if(max_num>768&&max_num<=1536)
	rand_type_num=109;
	else if(max_num>1536&&max_num<=3072)
	rand_type_num=113;
	else if(max_num>3072)
	rand_type_num=117;
	
	
	random=rand()%rand_type_num;	
	if(random<=15){
		next_num=1;
		if(count1>=MAXCOUNT12)
		next_num=2;
	}		
	else if(random>15&&random<=30){
		next_num=2;
		if(count2>=MAXCOUNT12)
		next_num=1;
	}
	else if(random>30&&random<=60)
		next_num=3;
	else if(random>60&&random<=85)
		next_num=6;
	else if(random>85&&random<=92)
		next_num=12;
	else if(random>92&&random<=102)
		next_num=24;
	else if(random>102&&random<=108)
		next_num=48;
	else if(random>108&&random<=111)
		next_num=96;
	else if(random>111&&random<=113)
		next_num=192;
	else if(random>113&&random<=115)
		next_num=384;
	else if(random>115&&random<=117)
		next_num=768;	
		
		if(game_test==1){
		if(next_num%3==0)//테스트 
		next_num*=16;
		else
		next_num=192;
		} 
		 
}
//////////////////////////////////////////////////////////////////////////
void Num_display(){
	i=0;
	j=0;
	while(i<=25){
		while(j<=16){
				
				if(num_pos[j][i]!=0)
				Num_write(i,j,num_pos[j][i]);
				
				
			j+=1;
		}
		j=0;
		i+=1;
	}
}
/////////////////////////////////////////////////////////////////////////
void CursorView()             //커서 삭제 
{
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
    cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
void Setting(){
	Write(MAPX+17,3+29,DARKGRAY,WHITE,"            ");				 
	Write(MAPX+17,4+29,DARKGRAY,WHITE,"ＯＰＴＩＯＮ");
	Write(MAPX+17,5+29,DARKGRAY,WHITE,"            ");
					
	Write(MAPX,1+29,DARKGRAY,WHITE,"                               ");
	Write(MAPX,2+29,DARKGRAY,WHITE,"_____"); 
	Write(MAPX,3+29,WHITE,DARKGRAY," <-- ");
	if(set_type[2]==1)//visible key 
	Write(MAPX,4+29,LIGHTGRAY,WHITE,">>'r'");
	else if(set_type[2]==0)//visible key 
	Write(MAPX,4+29,LIGHTGRAY,WHITE,"     ");
	Write(MAPX-1,5+29,DARKGRAY,WHITE,"                                ");
	
	Write(MAPX-3,8+29,LIGHTGRAY,WHITE,"                                   ");
	Write(MAPX-3,9+29,LIGHTGRAY,WHITE,"================================   ");
	Write(MAPX-3,10+29,LIGHTGRAY,WHITE,"                                   ");
	Write(MAPX-3,11+29,DARKGRAY,WHITE,"  option                           ");
	Write(MAPX-1,12+29,DARKGRAY,WHITE,"                                   ");
	if(set_type[0]==1){
	Write(MAPX-1,13+29,LIGHTRED,LIGHTGRAY,"●");
	Write(MAPX+1,13+29,DARKGRAY,LIGHTGRAY," music                   ");
	Write(MAPX+23,13+29,WHITE,LIGHTRED," ♪ ");	
	}	
	else if(set_type[0]==0){
	Write(MAPX-1,13+29,DARKGRAY,LIGHTGRAY,"●");
	Write(MAPX+1,13+29,DARKGRAY,LIGHTGRAY," music                   ");
	Write(MAPX+23,13+29,WHITE,DARKGRAY," ♪ ");	
	}
	if(set_type[2]==1)//visible key 
	Write(MAPX-1,14+29,LIGHTGRAY,WHITE,">>'1'                              ");
	else if(set_type[2]==0)//visible key
	Write(MAPX-1,14+29,LIGHTGRAY,WHITE,"                                   ");
	if(set_type[1]==1){
	Write(MAPX-1,15+29,LIGHTRED,LIGHTGRAY,"●");
	Write(MAPX+1,15+29,DARKGRAY,LIGHTGRAY," sound effect            ");
	Write(MAPX+23,15+29,WHITE,LIGHTRED," ★ ");
	}
	else if(set_type[1]==0){
	Write(MAPX-1,15+29,DARKGRAY,LIGHTGRAY,"●");
	Write(MAPX+1,15+29,DARKGRAY,LIGHTGRAY," sound effect            ");
	Write(MAPX+23,15+29,WHITE,DARKGRAY," ★ ");
	}
	if(set_type[2]==1)//visible key
	Write(MAPX-1,16+29,LIGHTGRAY,WHITE,">>'2'                              ");
	else if(set_type[2]==0)//visible key
	Write(MAPX-1,16+29,LIGHTGRAY,WHITE,"                                   ");
	if(set_type[2]==1){
	Write(MAPX-1,17+29,LIGHTRED,LIGHTGRAY,"●");
	Write(MAPX+1,17+29,DARKGRAY,LIGHTGRAY," visible key             ");
	Write(MAPX+23,17+29,WHITE,LIGHTRED," § ");
	}
	else if(set_type[2]==0){
	Write(MAPX-1,17+29,DARKGRAY,LIGHTGRAY,"●");
	Write(MAPX+1,17+29,DARKGRAY,LIGHTGRAY," visible key             ");
	Write(MAPX+23,17+29,WHITE,DARKGRAY," § ");
	}
	if(set_type[2]==1)//visible key
	Write(MAPX-1,18+29,LIGHTGRAY,WHITE,"<<'3'                              ");
	else if(set_type[2]==0)//visible key
	Write(MAPX-1,18+29,LIGHTGRAY,WHITE,"                                   ");
	if(set_type[3]==1){
	Write(MAPX-1,19+29,LIGHTRED,LIGHTGRAY,"●");
	Write(MAPX+1,19+29,DARKGRAY,LIGHTGRAY," record save            ");
	Write(MAPX+23,19+29,WHITE,LIGHTRED," √ ");
	}
	else if(set_type[3]==0){
	Write(MAPX-1,19+29,DARKGRAY,LIGHTGRAY,"●");
	Write(MAPX+1,19+29,DARKGRAY,LIGHTGRAY," record save            ");
	Write(MAPX+23,19+29,WHITE,DARKGRAY," √ ");
	}
	if(set_type[2]==1)//visible key
	Write(MAPX-1,20+29,LIGHTGRAY,WHITE,">>'4'                              ");
	else if(set_type[2]==0)//visible key
	Write(MAPX-1,20+29,LIGHTGRAY,WHITE,"                                   ");
	if(encycle_mode==1){
		if(set_type[4]==1){
		Write(MAPX-1,21+29,LIGHTRED,LIGHTGRAY,"●");
		Write(MAPX+1,21+29,DARKGRAY,LIGHTGRAY," start boost            ");
		Write(MAPX+23,21+29,WHITE,LIGHTRED," ↙ ");
		}
		else if(set_type[4]==0){
		Write(MAPX-1,21+29,DARKGRAY,LIGHTGRAY,"●");
		Write(MAPX+1,21+29,DARKGRAY,LIGHTGRAY," start boost            ");
		Write(MAPX+23,21+29,WHITE,DARKGRAY," ↙ ");
		}
		else if(set_type[4]==2){
		Write(MAPX-1,21+29,CYAN,LIGHTGRAY,"●");
		Write(MAPX+1,21+29,CYAN,LIGHTGRAY," mega boost             ");
		Write(MAPX+23,21+29,WHITE,CYAN," ↙ ");
		}
		if(set_type[2]==1)//visible key
		Write(MAPX-1,22+29,LIGHTGRAY,WHITE,">>'5'                              ");
		else if(set_type[2]==0)//visible key
		Write(MAPX-1,22+29,LIGHTGRAY,WHITE,"                                   ");
		Write(MAPX-1,23+29,LIGHTGRAY,WHITE,"                                   ");	
	}	
	else{
		Write(MAPX-1,21+29,LIGHTGRAY,WHITE,"                                   ");
	}
	if(encycle_mode==0){
		Write(MAPX-1,22+29,WHITE,WHITE,"                            ");
		Write(MAPX-1,23+29,WHITE,LIGHTRED,"                            ");
		Write(MAPX-1,24+29,WHITE,LIGHTRED,"  Press 'q' to go to Manu!  ");
		Write(MAPX-1,25+29,WHITE,LIGHTRED,"                            ");
		Write(MAPX-1,26+29,WHITE,WHITE,"                            ");
	}
	
}
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void Mov_detect(){
	if(kbhit()){
			but=_getch();
			if(but=='w'){
			moving_true=0;
			mov_y=0;
			while(mov_y<=3){	
				
				mov_y+=1;
				imain=0;
				jmain=0;
				while(imain<=25){
					while((jmain<=13&&encycle_mode!=1)||(jmain<=9&&encycle_mode==1)){
						if(encycle_mode!=1){
						if((num_pos[jmain][imain]+num_pos[jmain-5+mov_y][imain])%3==0&&((num_pos[jmain][imain]+num_pos[jmain-5+mov_y][imain]==3)||num_pos[jmain][imain]==num_pos[jmain-5+mov_y][imain])&&num_pos[jmain][imain]!=0&&num_pos[jmain-5+mov_y][imain]!=0&&jmain!=1&&jmain-5+mov_y>=0){
						    moving_true+=1;
							if(num_pos[jmain-1][imain]!=0){
								num_pos[jmain-1][imain]+=num_pos[jmain][imain];
								num_pos[jmain][imain]=0;	
							}
							else{
							num_pos[jmain-1][imain]=num_pos[jmain][imain];
							num_pos[jmain][imain]=0;	
							}	
						}	
						}					
						if(jmain-4>=0){				
							if(num_pos[jmain][imain]!=0&&num_pos[jmain-4][imain]==0&&jmain!=1){
								moving_true+=1;
								num_pos[jmain-1][imain]=num_pos[jmain][imain];
								num_pos[jmain][imain]=0;							
							}
						}
						else{
							if(num_pos[jmain][imain]!=0&&jmain!=1){
								moving_true+=1;
								num_pos[jmain-1][imain]=num_pos[jmain][imain];
								num_pos[jmain][imain]=0;							
							}
						}
						 
						jmain+=1;
					}
					jmain=0;
					imain+=1;
				}
				Map();
				Num_display();
				Sleep(10);	
				
				if(encycle_mode==0||(encycle_mode==2&&tuto_phase>=4)){
				if(mov_y==2){
					if(moving_true>0){   //숫자 랜덤 소환 
					do{
						num_rand=(rand()%4)*6+1;				
					}while(num_pos[13][num_rand]!=0||num_pos[12][num_rand]!=0);
				
					if(num_pos[13][num_rand]==0&&num_pos[12][num_rand]==0){
							num_pos[14][num_rand]=next_num;
						}
						
					if(encycle_mode==0)
					Next_num_random();
					else if(encycle_mode==2){
						if(tuto_phase<=5){
						if(count3<=3)
						next_num=3;
						else
						next_num=0;
						}	
						else if(tuto_phase>=6){
							if(count1<3)
							next_num=1;
							else if(count2<3)
							next_num=2;
							else
							next_num=0;
						}						
					}
				}
				}				
				else if(mov_y==4){
					i=0;
					while(i<=3){
						if(num_pos[14][i*6+1]!=0){
							num_pos[13][i*6+1]=num_pos[14][i*6+1];
							num_pos[14][i*6+1]=0;
						}
						i+=1;
						}
					}	
				}	
				}
									
			}
			else if(but=='s'){
			moving_true=0;
			mov_y=0;
			while(mov_y<=3){
				mov_y+=1;
				imain=0;
				if(encycle_mode!=1)
				jmain=16;
				else if(encycle_mode==1)
				jmain=12;
				
				while(imain<=25){
					while(jmain>=1){
						if(encycle_mode!=1){
						if((num_pos[jmain][imain]+num_pos[jmain+5-mov_y][imain])%3==0&&((num_pos[jmain][imain]+num_pos[jmain+5-mov_y][imain]==3)||num_pos[jmain][imain]==num_pos[jmain+5-mov_y][imain])&&num_pos[jmain][imain]!=0&&num_pos[jmain+5-mov_y][imain]!=0&&jmain!=13&&jmain+4<=16){
						    moving_true+=1;
							if(num_pos[jmain+1][imain]!=0){
								num_pos[jmain+1][imain]+=num_pos[jmain][imain];
								num_pos[jmain][imain]=0;	
							}
							else{
							num_pos[jmain+1][imain]=num_pos[jmain][imain];
							num_pos[jmain][imain]=0;	
							}	
						}	
						}
						
						if(jmain+4<=16){	
							if(num_pos[jmain][imain]!=0&&num_pos[jmain+4][imain]==0&&((jmain!=13&&encycle_mode!=1)||(jmain!=9&&encycle_mode==1))){
								moving_true+=1;
								num_pos[jmain+1][imain]=num_pos[jmain][imain];
								num_pos[jmain][imain]=0;
							}
						}
						else{
							if(num_pos[jmain][imain]!=0&&num_pos[jmain+4][imain]==0&&((jmain!=13&&encycle_mode!=1)||(jmain!=9&&encycle_mode==1))){
								moving_true+=1;
								num_pos[jmain+1][imain]=num_pos[jmain][imain];
								num_pos[jmain][imain]=0;
							}
						}
						jmain-=1;
					}
					if(encycle_mode!=1)
					jmain=16;
					else if(encycle_mode==1)
					jmain=12;
					
					imain+=1;
				}
				Map();
				Num_display();
				Sleep(10);
				
				if(encycle_mode==0||(encycle_mode==2&&tuto_phase>=4)){
				if(mov_y==2){
					if(moving_true>0){   //숫자 랜덤 소환 
					do{
						num_rand=(rand()%4)*6+1;				
					}while(num_pos[0][num_rand]!=0||num_pos[1][num_rand]!=0);
				
					if(num_pos[0][num_rand]==0&&num_pos[1][num_rand]==0){
							num_pos[0][num_rand]=next_num;
						}
					
					if(encycle_mode==0)
					Next_num_random();
					else if(encycle_mode==2){
						if(tuto_phase<=5){
						if(count3<=3)
						next_num=3;
						else
						next_num=0;
						}
						else if(tuto_phase>=6){
							if(count1<3)
							next_num=1;
							else if(count2<3)
							next_num=2;
							else
							next_num=0;
						}
					}	
					}	
				}
				else if(mov_y==4){
					i=0;
					while(i<=3){
						if(num_pos[0][i*6+1]!=0){
							num_pos[1][i*6+1]=num_pos[0][i*6+1];
							num_pos[0][i*6+1]=0;
						}
						i+=1;
					}
				}		
				}
									
				}
			}	
			else if(but=='a'){
			mov_x=0;
			while(mov_x<=5){
				moving_true=0;
				mov_x+=1;
				imain=0;
				jmain=0;
				while(imain<=19){
					while((jmain<=13&&encycle_mode!=1)||(jmain<=9&&encycle_mode==1)){
						if(encycle_mode!=1){
						if((num_pos[jmain][imain]+num_pos[jmain][imain-7+mov_x])%3==0&&((num_pos[jmain][imain]+num_pos[jmain][imain-7+mov_x]==3)||num_pos[jmain][imain]==num_pos[jmain][imain-7+mov_x])&&num_pos[jmain][imain]!=0&&num_pos[jmain][imain-7+mov_x]!=0&&imain!=1&&imain-7+mov_x>=0){
						    moving_true+=1;
							if(num_pos[jmain][imain-1]!=0){
								num_pos[jmain][imain-1]+=num_pos[jmain][imain];
								num_pos[jmain][imain]=0;	
							}
							else{
							num_pos[jmain][imain-1]=num_pos[jmain][imain];
							num_pos[jmain][imain]=0;	
							}	
						}	
						}
						
						if(imain-6>=0){
							if(num_pos[jmain][imain]!=0&&num_pos[jmain][imain-6]==0&&imain!=1){
								moving_true+=1;
								num_pos[jmain][imain-1]=num_pos[jmain][imain];
								num_pos[jmain][imain]=0;							
							}
						}
						else{
							if(num_pos[jmain][imain]!=0&&imain!=1){
								moving_true+=1;
								num_pos[jmain][imain-1]=num_pos[jmain][imain];
								num_pos[jmain][imain]=0;							
							}
						}
						jmain+=1;
					}
					jmain=0;
					imain+=1;
				}
				Map();
				Num_display();
				Sleep(5);
				
				if(encycle_mode==0||(encycle_mode==2&&tuto_phase>=4)){
				if(mov_x==5){
					if(moving_true>0){   //숫자 랜덤 소환 
					do{
						num_rand=(rand()%4)*4+1;				
					}while(num_pos[num_rand][20]!=0||num_pos[num_rand][19]!=0);
				
					if(num_pos[num_rand][20]==0&&num_pos[num_rand][19]==0){
							num_pos[num_rand][20]=next_num;
						}
					
					if(encycle_mode==0)
					Next_num_random();
					else if(encycle_mode==2){
						if(tuto_phase<=5){
						if(count3<=3)
						next_num=3;
						else
						next_num=0;
						}						
						else if(tuto_phase>=6){
							if(count1<3)
							next_num=1;
							else if(count2<3)
							next_num=2;
							else
							next_num=0;
						}
					}	
				}
				}
				else if(mov_x==6){
					j=0;
					while(j<=3){
						if(num_pos[j*4+1][20]!=0){
							num_pos[j*4+1][19]=num_pos[j*4+1][20];
							num_pos[j*4+1][20]=0;
						}
						j+=1;
					}
				}	
				}
						
				}				
			}
			else if(but=='d'){	
			mov_x=0;
			while(mov_x<=5){
				moving_true=0;
				mov_x+=1;
				imain=25;
				jmain=0;
				while(imain>=1){
					while((jmain<=13&&encycle_mode!=1)||(jmain<=9&&encycle_mode==1)){
						if(encycle_mode!=1){
						if((num_pos[jmain][imain]+num_pos[jmain][imain+7-mov_x])%3==0&&((num_pos[jmain][imain]+num_pos[jmain][imain+7-mov_x]==3)||num_pos[jmain][imain]==num_pos[jmain][imain+7-mov_x])&&num_pos[jmain][imain]!=0&&num_pos[jmain][imain+7-mov_x]!=0&&imain!=19&&imain+6<=25){
						    moving_true+=1;
							if(num_pos[jmain][imain+1]!=0){
								num_pos[jmain][imain+1]+=num_pos[jmain][imain];
								num_pos[jmain][imain]=0;	
							}
							else{
							num_pos[jmain][imain+1]=num_pos[jmain][imain];
							num_pos[jmain][imain]=0;	
							}	
						}	
						}
						
						if(num_pos[jmain][imain]!=0&&num_pos[jmain][imain+6]==0&&imain!=19&&imain+6<=25){
							moving_true+=1;
							num_pos[jmain][imain+1]=num_pos[jmain][imain];
							num_pos[jmain][imain]=0;																			
						}
						else if(num_pos[jmain][imain]!=0&&imain!=19&&imain+6>25){
								moving_true+=1;
								num_pos[jmain][imain+1]=num_pos[jmain][imain];
								num_pos[jmain][imain]=0;							
							} 
						jmain+=1;
					}
					jmain=0;
					imain-=1;
				}
				Map();
				Num_display();
				Sleep(5);
				
				if(encycle_mode==0||(encycle_mode==2&&tuto_phase>=4)){
				if(mov_x==5){
					if(moving_true>0){   //숫자 랜덤 소환 
					do{
						num_rand=(rand()%4)*4+1;				
					}while(num_pos[num_rand][0]!=0||num_pos[num_rand][1]!=0);
				
					if(num_pos[num_rand][0]==0&&num_pos[num_rand][1]==0){
							num_pos[num_rand][0]=next_num;
						}
					if(encycle_mode==0)
					Next_num_random();
					else if(encycle_mode==2){
						if(tuto_phase<=5){
						if(count3<=3)
						next_num=3;
						else
						next_num=0;
						}				
						else if(tuto_phase>=6){
							if(count1<3)
							next_num=1;
							else if(count2<3)
							next_num=2;
							else
							next_num=0;
						}
					}
				}
				}
				else if(mov_x==6){
					j=0;
					while(j<=3){
						if(num_pos[j*4+1][0]!=0){
							num_pos[j*4+1][1]=num_pos[j*4+1][0];
							num_pos[j*4+1][0]=0;
						}
						j+=1;
					}
				}		
				}
						
				}
			}
			else if(but=='r'&&encycle_mode!=2){
				
				if(setting_mode==1){
				fout.open("Num_set.txt");//숫자 종류 
				i=0;
				file_int=0;
				while(i<=4){
					power_int=pow(10,4-i);
					file_int+=set_type[i]*power_int;
					i+=1;
				}
				fout<<file_int;
				fout.close();	
				}
				
				fin.open("Max_num_score.txt");
				file_int1=0;
				fin>>file_int1;
				fin.close();
				fin.open("Num_name.txt");
				fin>>file_char;
				fin.close();
				
				if(setting_mode==0)
				height=0;
				else if(setting_mode==1)
				height=29;
				while((height<=29)&&(setting_mode==0)||(height>=0)&&(setting_mode==1)){					
					Sleep(1);
					Background();
					Map();
					Num_display();
					if(encycle_mode==1){
					Write(MAPX,21,WHITE,DARKGRAY,"                          "); 
					Write(MAPX,22,WHITE,DARKGRAY," Press 'q' to Play THREES "); 
					Write(MAPX,23,WHITE,DARKGRAY,"                          "); 
					Write(MAPX+7,3,CYAN,WHITE,"Ｔ"); 
					Write(MAPX+9,3,LIGHTRED,WHITE,"Ｈ"); 
					Write(MAPX+11,3,DARKGRAY,WHITE,"ＲＥＥＳ");
					}
//////////////////////////////////////////	
									
					Setting();
						
					if(6+29-height>=0&&6+29-height<=29){
					Write(MAPX-1,6+29,WHITE,WHITE,"                            ");
					Gotoxy(MAPX-1,6+29-height);//max점수 디스플래이 
					textcolor(BROWN,WHITE);
					cout<<file_char;
					textcolor(DARKGRAY,WHITE);
					cout<<"'s ";	
					}	
					if(7+29-height>=0&&7+29-height<=29){
					Write(MAPX-1,7+29,LIGHTGRAY,LIGHTGRAY,"                            ");
					Gotoxy(MAPX,7+29-height);//max점수 디스플래이 
					textcolor(DARKGRAY,LIGHTGRAY);
					cout<<"MAX SCORE | "<<file_int1;
					}					
////////////////////////////////////////					
					if(setting_mode==0)
					height+=1;
					else if(setting_mode==1)
					height-=1;		
				}
				if(height==30)
				height=29;
				else if(height==-1)
				height=0;
				
				if(setting_mode==0)
				setting_mode=1;
				else if(setting_mode==1)
				setting_mode=0;	
			}
//////////////////////////////////////////			
			else if(but=='q'&&encycle_mode==1&&setting_mode==0){
				encycle_mode=0;
				max_num=0; 
				i=0;
				j=0;
				while(i<=3){
					while(j<=2){
						num_pos[j*4+1][i*6+1]=0;							
						j+=1;
					}
					j=0;
					i+=1;
				} 
				Num_display();
				
				j=0;
				while(j<=6){
					Write(MAPX,20+j,WHITE,WHITE,"                          "); 
					Write(MAPX,21+j,WHITE,DARKGRAY,"                          "); 
					Write(MAPX,22+j,WHITE,DARKGRAY," Press 'q' to Play THREES "); 
					Write(MAPX,23+j,WHITE,DARKGRAY,"                          "); 
					
					if(j*3-3>=0){
					Write(j*3-3,0,WHITE,WHITE,"   "); 
					Write(j*3-3,1,WHITE,WHITE,"   "); 
					Write(j*3-3,2,WHITE,WHITE,"   ");
					Write(j*3-3,3,WHITE,WHITE,"   "); 
					Write(j*3-3,4,WHITE,WHITE,"   "); 
					Write(j*3-3,5,WHITE,WHITE,"   ");	
					}
					
					Write(j*1.4,2,DARKGRAY,WHITE," "); 
					Write(j*1.4,3,DARKGRAY,WHITE," "); 
					Write(j*1.4,4,DARKGRAY,WHITE," ");
					Write(j*1.4,2,DARKGRAY,WHITE,"_____"); 
					Write(j*1.4,3,WHITE,DARKGRAY," :== "); 
					if(set_type[2]==1)//visible key 
					Write(j*1.4,4,LIGHTGRAY,WHITE,">>'r'"); 
					else if(set_type[2]==0)//visible key 
					Write(j*1.4,4,LIGHTGRAY,WHITE,"     ");
					
					Write(j*3,0,WHITE,LIGHTGRAY,"    "); 
					Write(j*3,1,WHITE,LIGHTGRAY,"    "); 
					Write(j*3,2,WHITE,LIGHTGRAY,"    ");
					Write(j*3,3,WHITE,LIGHTGRAY,"    "); 
					Write(j*3,4,WHITE,LIGHTGRAY,"    "); 
					Write(j*3,5,DARKGRAY,WHITE,"next");					
					
					Write(MAPX-5+j*4.9,2,DARKGRAY,WHITE,"     "); 
					Write(MAPX-5+j*4.9,3,DARKGRAY,WHITE,"     "); 
					Write(MAPX-5+j*4.9,4,DARKGRAY,WHITE,"     ");
					Write(MAPX+j*4.9,4,DARKGRAY,WHITE,"_____"); 
					Write(MAPX+j*4.9,3,WHITE,DARKGRAY," :== ");
					if(set_type[2]==1)//visible key 
					Write(j*4.9,4,LIGHTGRAY,WHITE,">>'r'"); 
					else if(set_type[2]==0)//visible key
					Write(j*4.9,4,LIGHTGRAY,WHITE,"     ");  
					
					Write(MAPX+21-1+j*1.4,2,DARKGRAY,WHITE," "); 
					Write(MAPX+21-1+j*1.4,3,DARKGRAY,WHITE," "); 
					Write(MAPX+21-1+j*1.4,4,DARKGRAY,WHITE," "); 
					Write(MAPX+21+j*1.4,2,DARKGRAY,WHITE,"_____"); 
					Write(MAPX+21+j*1.4,3,WHITE,DARKGRAY,"1+2=3"); 
					if(set_type[2]==1)//visible key 
					Write(MAPX+21+j*1.4,4,LIGHTGRAY,WHITE,">>'t'"); 
					else if(set_type[2]==0)//visible key 
					Write(MAPX+21+j*1.4,4,LIGHTGRAY,WHITE,"     "); 
					
					
					Write(MAPX+5+j*3,3,CYAN,WHITE,"  "); 
					if(MAPX+7+j*3<41)
					Write(MAPX+7+j*3,3,CYAN,WHITE,"Ｔ"); 
					if(MAPX+9+j*3<41)
					Write(MAPX+9+j*3,3,LIGHTRED,WHITE,"Ｈ"); 
					if(MAPX+11+j*3<41)
					Write(MAPX+11+j*3,3,DARKGRAY,WHITE,"Ｒ"); 
					if(MAPX+13+j*3<41)
					Write(MAPX+13+j*3,3,DARKGRAY,WHITE,"Ｅ"); 
					if(MAPX+15+j*3<41)
					Write(MAPX+15+j*3,3,DARKGRAY,WHITE,"Ｅ"); 
					if(MAPX+17+j*3<41)
					Write(MAPX+17+j*3,3,DARKGRAY,WHITE,"Ｓ"); 
					
					
					Sleep(5);
					j+=1;
				}
			}
			else if(but=='t'&&encycle_mode==1&&setting_mode==0){
			encycle_mode=2;
				max_num=0; 
				next_num=3;
				tuto_phase=0;
				i=0;
				j=0;
				while(i<=3){
					while(j<=2){
						num_pos[j*4+1][i*6+1]=0;							
						j+=1;
					}
					j=0;
					i+=1;
				} 
				Num_display();
				
				j=0;
				while(j<=6){
					Write(MAPX,20+j,WHITE,WHITE,"                          "); 
					Write(MAPX,21+j,WHITE,DARKGRAY,"                          "); 
					Write(MAPX,22+j,WHITE,DARKGRAY," Press 'q' to Play THREES "); 
					Write(MAPX,23+j,WHITE,DARKGRAY,"                          "); 
					
					Write(MAPX-5+j*4.9,2,DARKGRAY,WHITE,"     "); 
					Write(MAPX-5+j*4.9,3,DARKGRAY,WHITE,"     "); 
					Write(MAPX-5+j*4.9,4,DARKGRAY,WHITE,"     ");
					Write(MAPX+j*4.9,2,DARKGRAY,WHITE,"_____"); 
					Write(MAPX+j*4.9,3,WHITE,DARKGRAY," :== ");
					if(set_type[2]==1)//visible key 
					Write(MAPX+j*4.9,4,LIGHTGRAY,WHITE,">>'r'"); 
					else if(set_type[2]==0)//visible key  
					Write(MAPX+j*4.9,4,LIGHTGRAY,WHITE,"     "); 
					
					Write(MAPX+21-1+j*1.4,2,DARKGRAY,WHITE," "); 
					Write(MAPX+21-1+j*1.4,3,DARKGRAY,WHITE," "); 
					Write(MAPX+21-1+j*1.4,4,DARKGRAY,WHITE," "); 
					Write(MAPX+21+j*1.4,2,DARKGRAY,WHITE,"_____"); 
					Write(MAPX+21+j*1.4,3,WHITE,DARKGRAY,"1+2=3"); 
					if(set_type[2]==1)//visible key 
					Write(MAPX+21+j*1.4,4,LIGHTGRAY,WHITE,">>'t'"); 
					else if(set_type[2]==0)//visible key 
					Write(MAPX+21+j*1.4,4,LIGHTGRAY,WHITE,"     "); 
					
					
					Write(MAPX+6+j*3,3,CYAN,WHITE,"  "); 
					if(MAPX+7+j*3<41)
					Write(MAPX+7+j*3,3,CYAN,WHITE,"Ｔ"); 
					if(MAPX+9+j*3<41)
					Write(MAPX+9+j*3,3,LIGHTRED,WHITE,"Ｈ"); 
					if(MAPX+11+j*3<41)
					Write(MAPX+11+j*3,3,DARKGRAY,WHITE,"Ｒ"); 
					if(MAPX+13+j*3<41)
					Write(MAPX+13+j*3,3,DARKGRAY,WHITE,"Ｅ"); 
					if(MAPX+15+j*3<41)
					Write(MAPX+15+j*3,3,DARKGRAY,WHITE,"Ｅ"); 
					if(MAPX+17+j*3<41)
					Write(MAPX+17+j*3,3,DARKGRAY,WHITE,"Ｓ"); 
					
					
					Sleep(5);
					j+=1;
				}	
			}
			else if(but=='1'&&setting_mode==1){
				if(set_type[0]==1)
				set_type[0]=0;
				else if(set_type[0]==0)
				set_type[0]=1;
				Setting();
			}
			else if(but=='2'&&setting_mode==1){
				if(set_type[1]==1)
				set_type[1]=0;
				else if(set_type[1]==0)
				set_type[1]=1;
				Setting();
			}
			else if(but=='3'&&setting_mode==1){
				if(set_type[2]==1)
				set_type[2]=0;
				else if(set_type[2]==0)
				set_type[2]=1;
				Setting();
			}
			else if(but=='4'&&setting_mode==1){
				if(set_type[3]==1)
				set_type[3]=0;
				else if(set_type[3]==0)
				set_type[3]=1;
				Setting();			
			}
			else if(but=='5'&&setting_mode==1&&encycle_mode==1){
				if(set_type[4]==1)
				set_type[4]=2;
				else if(set_type[4]==0)
				set_type[4]=1;
				else if(set_type[4]==2)
				set_type[4]=0;
				Setting();			
			}	
			else if(but=='q'&&encycle_mode==0&&end_counting!=0&&setting_mode==1){
				
				fout.open("Num_set.txt");//숫자 종류 
				i=0;
				file_int=0;
				while(i<=4){
					power_int=pow(10,4-i);
					file_int+=set_type[i]*power_int;
					i+=1;
				}
				fout<<file_int;
				fout.close();	
				
				fin.open("Max_num_score.txt");
				file_int1=0;
				fin>>file_int1;		
				fin.close();	
				encycle_mode=1;	
					score=0;
					i=0;
					j=0;
					while(i<=3){
						while(j<=3){
							num_pos[j*4+1][i*6+1]=0;							
							j+=1;
						}
						j=0;
						i+=1;
					}
					end_counting=1;	
					max_num=0;
					
				height=29;
				while(height>=0){				
					Sleep(1);
					Background();
					Map();
					Num_display();
					Write(MAPX,21,WHITE,DARKGRAY,"                          "); 
					Write(MAPX,22,WHITE,DARKGRAY," Press 'q' to Play THREES "); 
					Write(MAPX,23,WHITE,DARKGRAY,"                          "); 
					Write(MAPX+7,3,CYAN,WHITE,"Ｔ"); 
					Write(MAPX+9,3,LIGHTRED,WHITE,"Ｈ"); 
					Write(MAPX+11,3,DARKGRAY,WHITE,"ＲＥＥＳ");
//////////////////////////////////////////	
					Write(MAPX+17,3+29,DARKGRAY,WHITE,"            ");				 
					Write(MAPX+17,4+29,DARKGRAY,WHITE,"ＯＰＴＩＯＮ");
					Write(MAPX+17,5+29,DARKGRAY,WHITE,"            ");
					
					Write(MAPX,1+29,DARKGRAY,WHITE,"                               ");
					Write(MAPX,2+29,DARKGRAY,WHITE,"_____"); 
					Write(MAPX,3+29,WHITE,DARKGRAY," <-- ");
					if(set_type[2]==1)//visible key
					Write(MAPX,4+29,LIGHTGRAY,WHITE,">>'r'");
					else if(set_type[2]==0)//visible key
					Write(MAPX,4+29,LIGHTGRAY,WHITE,"     ");
					Write(MAPX-1,5+29,DARKGRAY,WHITE,"                                ");
					
					Setting();
						
					if(6+29-height>=0&&6+29-height<=29){
					Write(MAPX-1,6+29,WHITE,WHITE,"                            ");
					Gotoxy(MAPX-1,6+29-height);//max점수 디스플래이 
					textcolor(BROWN,WHITE);
					cout<<file_char;
					textcolor(DARKGRAY,WHITE);
					cout<<"'s ";	
					}	
					if(7+29-height>=0&&7+29-height<=29){
					Write(MAPX-1,7+29,LIGHTGRAY,LIGHTGRAY,"                            ");
					Gotoxy(MAPX,7+29-height);//max점수 디스플래이 
					textcolor(DARKGRAY,LIGHTGRAY);
					cout<<"MAX SCORE | "<<file_int1;
					}					
////////////////////////////////////////					
					height-=1;		
				}
				height=0;
				setting_mode=2;
			}
	}
}
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
int main(){
	Manu :
////////////////////////////
	fin.open("Num_set.txt");//설정   
	file_int=0;
	fin>>file_int;
	i=0;
	while(i<=4){
		power_int=pow(10,4-i);			
		set_type[i]=(file_int%(power_int*10)-file_int%power_int)/power_int;
		i+=1;
	}
	fin.close();
//////////////////////////
	next_num=0;
	tuto_phase=0;
	encycle_mode=1;
	score=0;
	i=0;
	j=0;
	while(i<=3){
		while(j<=3){
			num_pos[j*4+1][i*6+1]=0;							
			j+=1;
		}
		j=0;
		i+=1;
	}
	end_counting=1;
	Num_display();
	CursorView();
		
	Background();
	Map();
	
	Write(MAPX+7,3,CYAN,WHITE,"Ｔ"); 
	Write(MAPX+9,3,LIGHTRED,WHITE,"Ｈ"); 
	Write(MAPX+11,3,DARKGRAY,WHITE,"ＲＥＥＳ"); 
	
	Write(MAPX,2,DARKGRAY,WHITE,"_____"); 
	Write(MAPX,3,WHITE,DARKGRAY," :== "); 
	if(set_type[2]==1)//visible key
	Write(MAPX,4,LIGHTGRAY,WHITE,">>'r'"); 
	else if(set_type[2]==0)//visible key
	Write(MAPX,4,LIGHTGRAY,WHITE,"     "); 
	
	Write(MAPX+21,2,DARKGRAY,WHITE,"_____"); 
	Write(MAPX+21,3,WHITE,DARKGRAY,"1+2=3"); 
	if(set_type[2]==1)//visible key
	Write(MAPX+21,4,LIGHTGRAY,WHITE,">>'t'"); 
	else if(set_type[2]==0)//visible key
	Write(MAPX,4,LIGHTGRAY,WHITE,"     "); 
	
	Write(MAPX,21,WHITE,DARKGRAY,"                          "); 
	Write(MAPX,22,WHITE,DARKGRAY," Press 'q' to Play THREES "); 
	Write(MAPX,23,WHITE,DARKGRAY,"                          "); 
	
////////////////////////////////
fin.open("have_num.txt");//숫자 종류  
file_int=0;
fin>>file_int;
i=0;
while(i<=12){
	power_int=pow(10,12-i);
	have_num[i]=(file_int%(power_int*10)-file_int%power_int)/power_int;
	i+=1;
}
fin.close();
//////////////////////////////////////

	Sleep(150);
	i2=0;//number 디스플래이  
	j2=0;
	i1=0;		
	while(j2<=2){
		while(i2<=3){
			power_int=pow(2,i1);
			if(have_num[i1]!=0){
			num_pos[j2*4+1][i2*6+1]=3*power_int;	
			Sleep(30);
			Num_display();
			}			
			i1+=1;
			i2+=1;
		}
		i2=0;
		j2+=1;
	}
	Max_num_detect();
	Num_display();
	
	
	while(encycle_mode==1){   //시작할 때 시작버튼 퇴장, 넥스트 넘버  디스플래이 등장 
	    Mov_detect();
			
	}
////////////////////////////////////////////// 시작 창	
////////////////////////////////////////////
	
if(encycle_mode==2&&tuto_phase==0){
Map();
Background();
Sleep(500);	
Write(MAPX+7,3,CYAN,WHITE,"Ｔ"); 
Write(MAPX+9,3,LIGHTRED,WHITE,"Ｈ"); 
Write(MAPX+11,3,DARKGRAY,WHITE,"ＲＥＥＳ"); 
Write(12,24,DARKGRAY,WHITE,"Press 'q' to start"); 
tuto_phase+=1;

while(tuto_phase==1){
if(kbhit()){
	but=_getch();
	if(but=='q'){
Sleep(300);		
Write(MAPX-1,3,DARKGRAY,WHITE,"   Introducing"); 
Write(MAPX+13,3,CYAN,WHITE," １ "); 
Write(MAPX+17,3,DARKGRAY,WHITE,"and"); 
Write(MAPX+20,3,LIGHTRED,WHITE," ２"); 
Write(MAPX+22,3,DARKGRAY,WHITE,"!  "); 
Write(8,24,DARKGRAY,WHITE,"Using w/a/s/d to move them");
Sleep(100);	
num_pos[1+4][1+6]=1;
Num_display();
Sleep(100);	
num_pos[1+8][1+12]=2;
Num_display();
tuto_phase+=1;
	}
}	
}
while(tuto_phase==2){
Mov_detect();	
if(num_pos[1+4][1+6]!=1){
Write(MAPX-1,3,DARKGRAY,WHITE,"       Using the wall       ");
Write(MAPX+4,4,DARKGRAY,WHITE,"Combine"); 
Write(MAPX+11,4,CYAN,WHITE," １ "); 
Write(MAPX+15,4,DARKGRAY,WHITE,"and"); 
Write(MAPX+19,4,LIGHTRED,WHITE," ２"); 
Write(8,24,DARKGRAY,WHITE,"                           "); 
tuto_phase+=1;
}
}

while(tuto_phase==3){
	/////////////////////////////벽 
	i=0;
	while(i<=25){
		if(i<=10||i>=15){
		Write(MAPX+i,MAPY-1,LIGHTRED,WHITE,"=");
		Write(MAPX+i,MAPY+17,LIGHTRED,WHITE,"=");	
		}		
		i+=1;
	}
	j=0;
	while(j<=16){
		Write(MAPX-2,MAPY+j,LIGHTRED,WHITE,"∥");
		Write(MAPX+25+1,MAPY+j,LIGHTRED,WHITE,"∥");
		j+=1;
	}
	Write(MAPX-2,MAPY-1,LIGHTRED,WHITE,"■");
	Write(MAPX-2,MAPY+17,LIGHTRED,WHITE,"■");
	Write(MAPX+26,MAPY-1,LIGHTRED,WHITE,"■");
	Write(MAPX+26,MAPY+17,LIGHTRED,WHITE,"■");
	Write(MAPX+11,MAPY-1,LIGHTRED,WHITE,"WALL");
	Write(MAPX+11,MAPY+17,LIGHTRED,WHITE,"WALL");
	//////////////////////////
Mov_detect();
Max_num_detect();
Counting();
if(count3==1){//3 감지 상수
	/////////////////////////////벽 
	i=0;
	while(i<=29){
		Write(MAPX-2+i,MAPY-1,LIGHTRED,WHITE," ");
		Write(MAPX-2+i,MAPY+17,LIGHTRED,WHITE," ");			
		i+=1;
	}
	j=0;
	while(j<=16){
		Write(MAPX-2,MAPY+j,LIGHTRED,WHITE,"  ");
		Write(MAPX+25+1,MAPY+j,LIGHTRED,WHITE,"  ");
		j+=1;
	}
	//////////////////////////

	Write(MAPX-1,3,DARKGRAY,WHITE,"      Moving the card,      ");
	Write(MAPX+4,4,DARKGRAY,WHITE,"Get the next number!");
	Write(9,24,DARKGRAY,WHITE,"Using w/a/s/d to move it");	
	tuto_phase+=1;
}	
}
while(tuto_phase==4){
Map();
Num_display();
Mov_detect();
Counting();
Max_num_detect();
if(count3>=2){//3 감지 상수
	Write(MAPX-1,3,DARKGRAY,WHITE,"         3 + 3 = 6         ");
	Write(MAPX+4,4,DARKGRAY,WHITE,"                      ");
	Write(9,24,DARKGRAY,WHITE,"                              ");	
	tuto_phase+=1;
}	
}	
while(tuto_phase==5){
Map();
Num_display();
Mov_detect();
Counting();
Max_num_detect();
if(count6>=1){//3 감지 상수
	Write(MAPX-3,3,DARKGRAY,WHITE,"If numbers above 3 are combined");
	Write(MAPX+3,4,LIGHTRED,WHITE,"they must be the same!");
	Write(5,24,DARKGRAY,WHITE,"Only numbers above 3 are doubled");	
	tuto_phase+=1;
}	
}
while(tuto_phase==6){
Map();
Num_display();
Mov_detect();
Counting();
Max_num_detect();
if(count12>=1){//3 감지 상수
	Write(MAPX-3,3,DARKGRAY,WHITE,"            Make 24!           ");
	Write(MAPX+3,4,LIGHTRED,WHITE,"                            ");
	Write(5,24,DARKGRAY,WHITE,"                                     ");	
	tuto_phase+=1;
}	
}
while(tuto_phase==7){
Map();
Num_display();
Counting();
Mov_detect();
Max_num_detect();
if(count24>=1){//3 감지 상수
	Write(MAPX+2,3,DARKGRAY,WHITE," This is ");
	Write(MAPX+11,3,CYAN,WHITE,"Ｔ"); 
	Write(MAPX+13,3,LIGHTRED,WHITE,"Ｈ"); 
	Write(MAPX+15,3,DARKGRAY,WHITE,"ＲＥＥＳ"); 
	Write(12,24,DARKGRAY,WHITE,"Press 'q' to skip!"); 
while(tuto_phase==7){
if(kbhit()){
	but=_getch();
	if(but=='q'){
	tuto_phase+=1;	
			}	
		}
	}
	}
}
while(tuto_phase==8){
Map();
Num_display();
Counting();
Mov_detect();
Max_num_detect();
	Write(MAPX,3,DARKGRAY,WHITE,"    Make a max number!     ");
	Write(12,24,DARKGRAY,WHITE," That is the goal "); 
if(count24>=2){
tuto_phase+=1;
}
}
if(tuto_phase==9){
	encycle_mode=0;
					j=0;
				while(j<=6){					
					if(j*3-3>=0){
					Write(j*3-3,0,WHITE,WHITE,"   "); 
					Write(j*3-3,1,WHITE,WHITE,"   "); 
					Write(j*3-3,2,WHITE,WHITE,"   ");
					Write(j*3-3,3,WHITE,WHITE,"   "); 
					Write(j*3-3,4,WHITE,WHITE,"   "); 
					Write(j*3-3,5,WHITE,WHITE,"   ");	
					}					
					Write(j*1.4-1,2,DARKGRAY,WHITE,"  "); 
					Write(j*1.4-1,3,DARKGRAY,WHITE,"  ");
					Write(j*1.4-1,4,DARKGRAY,WHITE,"  "); 
					Write(j*1.4,2,DARKGRAY,WHITE,"_____"); 
					Write(j*1.4,3,WHITE,DARKGRAY," :== "); 
					Write(j*1.4,4,LIGHTGRAY,WHITE," :== "); 
					
					Write(j*3,0,WHITE,LIGHTGRAY,"    "); 
					Write(j*3,1,WHITE,LIGHTGRAY,"    "); 
					Write(j*3,2,WHITE,LIGHTGRAY,"    ");
					Write(j*3,3,WHITE,LIGHTGRAY,"    "); 
					Write(j*3,4,WHITE,LIGHTGRAY,"    "); 
					Write(j*3,5,DARKGRAY,WHITE,"next");					
					Sleep(5);
					j+=1;
				}
next_num=3;
Background();
tuto_phase=10;
}
}

//////////////////////////////////////////////////////////////////////////////////////////////튜토리얼
//////////////////////////////////////////////////////////////////////////////////////////////
if(encycle_mode==0&&tuto_phase!=10){
	Counting();
random=rand()%100;	
if(random<=30){//넥스트 넘버  
	next_num=1;
	if(count1>=MAXCOUNT12)
	next_num=2;
}	
else if(random>30&&random<=60){
	next_num=2;
	if(count2>=MAXCOUNT12)
	next_num=1;
}	
else if(random>60&&random<=99)
	next_num=3;
	
if(game_test==1)//테스트  
next_num=1536;
////////////////////////////////////////	

	Background();
	Map();
	Num_display();
	Sleep(150);	

////////////////////////////////////////////////////	
	
	srand((unsigned int) time(NULL));  //처음 시작 카드 랜덤배치  
	if(game_test==0){//테스트  
	i1=0;
	j1=0;//num_display 때문에 i,j에 1 붙임 
	while(i1<=3){
		while(j1<=3){
			if(rand()%100<=55)
			num_pos[j1*4+1][i1*6+1]=0;
			else if(rand()%100>55&&rand()%100<=60)
			num_pos[j1*4+1][i1*6+1]=1;			
			else if(rand()%100>60&&rand()%100<=65)
			num_pos[j1*4+1][i1*6+1]=2;
			else if(rand()%100>65&&rand()%100<=85)
			num_pos[j1*4+1][i1*6+1]=3;
			else if(rand()%100>85&&rand()%100<=90)
			num_pos[j1*4+1][i1*6+1]=6;
			else if(rand()%100>90&&rand()%100<=95)
			num_pos[j1*4+1][i1*6+1]=12;
			else if(rand()%100>90&&rand()%100<=99)
			num_pos[j1*4+1][i1*6+1]=24;
			
			if(num_pos[j1*4+1][i1*6+1]!=0){
			Num_display();
			Sleep(95);	
			}
			
			j1+=1;
			
		}
		i1+=1;
		j1=0;
	}	
	}
	
	if(set_type[4]==1){//카드 부스트 
	do{
	j=(rand()%4)*4+1;
	i=(rand()%4)*6+1;
	}while(num_pos[j][i]!=0);	
	num_pos[j][i]=48;
	}
	else if(set_type[4]==2){//카드 부스트 
	i=1;
	while(i<=12){
		if(have_num[i-1]==1&&have_num[i]==0&&i!=12)
		j1=i-1;
		if(have_num[11]==1)
		j1=11;
		
		i+=1;
	}	
	do{
	j=(rand()%4)*4+1;
	i=(rand()%4)*6+1;
	}while(num_pos[j][i]!=0);	
	power_int=pow(2,j1);
	num_pos[j][i]=3*power_int;
	}

}

///////////////////////////////////////////////////////////	게임 진행  
//////////////////////////////////////////////////////////

	while(end_counting!=0&&encycle_mode==0){

i=0;
j=0;
while(i<=3){
	while(j<=3){
		if(num_pos[1+j*4][1+i*6]==3){
		have_num[0]=1;	
		}		
		else if(num_pos[1+j*4][1+i*6]==6){
		have_num[0]=1;
		have_num[1]=1;	
		}		
		else if(num_pos[1+j*4][1+i*6]==12){
		have_num[0]=1;
		have_num[1]=1;	
		have_num[2]=1;	
		}		
		else if(num_pos[1+j*4][1+i*6]==24){
		have_num[0]=1;
		have_num[1]=1;	
		have_num[2]=1;
		have_num[3]=1;	
		}		
		else if(num_pos[1+j*4][1+i*6]==48){
		have_num[0]=1;
		have_num[1]=1;	
		have_num[2]=1;
		have_num[3]=1;
		have_num[4]=1;	
		}		
		else if(num_pos[1+j*4][1+i*6]==96)
		have_num[5]=1;
		else if(num_pos[1+j*4][1+i*6]==192)
		have_num[6]=1;
		else if(num_pos[1+j*4][1+i*6]==384)
		have_num[7]=1;
		else if(num_pos[1+j*4][1+i*6]==768)
		have_num[8]=1;
		else if(num_pos[1+j*4][1+i*6]==1536)
		have_num[9]=1;
		else if(num_pos[1+j*4][1+i*6]==3072)
		have_num[10]=1;
		else if(num_pos[1+j*4][1+i*6]==6144)
		have_num[11]=1;
		else if(num_pos[1+j*4][1+i*6]==12288)
		have_num[12]=1;
		j+=1;
	}
	j=0;
	i+=1;
}
		
	Background();
	Map();
	Counting();	
	Num_display();
	
////////////////////////////////////////////////////////////////	  
	
	Mov_detect();
	Max_num_detect();
	
	if(setting_mode==2){// 설정에서 게임 종료  
	setting_mode=0;
	goto Manu;
}	
////////////////////////////////////////////////////////////////////////////////	

if(set_type[3]==1){	//점수 저장 	
fout.open("have_num.txt");//숫자 종류 
i=0;
file_int=0;
while(i<=12){
	power_int=pow(10,12-i);
	file_int+=have_num[i]*power_int;
	i+=1;
}
fout<<file_int;
fout.close();	
}
/////////////////////////////////////////////////

if(encycle_mode==0){
end_counting=0;
i=0;
j=0;
while(i<=3){
	while(j<=3){
		if(num_pos[j*4+1][i*6+1]!=0){
			if((num_pos[j*4+1][i*6+1]!=1&&num_pos[j*4+1][i*6+1]!=2)&&((num_pos[j*4+1][i*6+1]==num_pos[j*4+1][i*6+6+1]&&i*6+1+6<25)||(num_pos[j*4+1][i*6+1]==num_pos[j*4+1][i*6+1-6]&&i*6+1-6>0)||(num_pos[j*4+1][i*6+1]==num_pos[j*4+1+4][i*6+1]&&j*4+1+4<16)||(num_pos[j*4+1][i*6+1]==num_pos[j*4+1-4][i*6+1]&&j*4+1-4>0)))
			end_counting+=1;
			else if((num_pos[j*4+1][i*6+1]==1||num_pos[j*4+1][i*6+1]==2)&&((num_pos[j*4+1][i*6+1]+num_pos[j*4+1][i*6+1+6]==3&&i*6+1+6<25)||(num_pos[j*4+1][i*6+1]+num_pos[j*4+1][i*6+1-6]==3&&i*6+1-6>0)||(num_pos[j*4+1][i*6+1]+num_pos[j*4+1+4][i*6+1]==3&&j*4+1+4<16)||(num_pos[j*4+1][i*6+1]+num_pos[j*4+1-4][i*6+1]==3&&j*4+1-4>0)))
			end_counting+=1;
		}	
		else if (num_pos[j*4+1][i*6+1]==0)
		end_counting+=1;
							
		j+=1;
	}
	j=0;
	i+=1;
}
if(max_num==12288)  
end_counting=0;  
    }
		
}
   
    ///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////    
	next_num=0;
	tuto_phase=0;
	
	Background();
	Map();   
	Num_display();

j=5;//넥스트 넘버 퇴장 
while(j>=0){
	Write(19,j,DARKGRAY,WHITE,"next"); 
	if(j!=5)
	Write(19,j+1,WHITE,WHITE,"    "); 
	
	Write(MAPX+5-(5-j)*1.4,2,DARKGRAY,WHITE,"  "); 
	Write(MAPX+5-(5-j)*1.4,3,DARKGRAY,WHITE,"  "); 
	Write(MAPX-(5-j)*1.4,2,DARKGRAY,WHITE,"_____"); 
	Write(MAPX-(5-j)*1.4,3,WHITE,DARKGRAY," :== "); 
	Sleep(15);
	j-=1;
}
Write(MAPX-7,2,WHITE,WHITE,"     "); 
Write(MAPX-7,3,WHITE,WHITE,"     "); 
Write(19,0,WHITE,WHITE,"    "); 

	Write(7,24,DARKGRAY,WHITE,"Press 'q' to see your score!"); 	
    while(1){
    	if(kbhit()){
			but=_getch();
			if(but=='q'){
				
	Gotoxy(MAPX,MAPY-1);//점수 디스플래이  
	textcolor(BLACK,WHITE);
	cout<<"SCORE | "<<score;	
			
	Sleep(200);
	Write(7,24,DARKGRAY,WHITE,"                                "); 			
	i1=0;//Num_display에 있는 i,j 때문에 1붙임   
	j1=0;
	while(i1<=3){
		while(j1<=3){
			if(num_pos[j1*4+1][i1*6+1]!=max_num&&num_pos[j1*4+1][i1*6+1]==1){
			num_pos[j1*4+1][i1*6+1]+=10000;		
			j3+=1;//흑백화 상수				
			}			
			j1+=1;
		}
		j1=0;
		i1+=1;
	}
	if(j3>=1) 
	Sleep(100);
	j3=0;
	Num_display();
	//////////1
	 i1=0;//Num_display에 있는 i,j 때문에 1붙임   
	j1=0;
	while(i1<=3){
		while(j1<=3){
			if(num_pos[j1*4+1][i1*6+1]!=max_num&&num_pos[j1*4+1][i1*6+1]==2){
			num_pos[j1*4+1][i1*6+1]+=10000;			
			j3+=1;//흑백화 상수	
			}			
			j1+=1;
		}
		j1=0;
		i1+=1;
	}
	if(j3>=1) 
	Sleep(100);
	j3=0;
	//////////2
	Num_display();	
	j2=0;
    while(j2<=12){
    i2=pow(2,j2);
	i1=0;//Num_display에 있는 i,j 때문에 1붙임   
	j1=0;
	while(i1<=3){
		while(j1<=3){
			if(num_pos[j1*4+1][i1*6+1]!=max_num&&num_pos[j1*4+1][i1*6+1]==3*i2){
			num_pos[j1*4+1][i1*6+1]+=10000;			
			j3+=1;//흑백화 상수	
			}			
			j1+=1;
		}
		j1=0;
		i1+=1;
	}
	if(j3>=1) 
	Sleep(100);
	j3=0;
	//////////1,2제외 
	Num_display();	
	j2+=1;	
	}	
//////////	점수 
	j2=0;
    while(j2<=12){
    i2=pow(2,j2);
	i1=0;//Num_display에 있는 i,j 때문에 1붙임   
	j1=0;
	while(i1<=3){
		while(j1<=3){
			if(num_pos[j1*4+1][i1*6+1]-10000!=max_num&&num_pos[j1*4+1][i1*6+1]-10000==3*i2){		
			Gotoxy(i1*6+1+MAPX,j1*4+1+MAPY);
			textcolor(BROWN,BLACK);
			power_int=pow(3,j2+1);
			cout<<"+"<<power_int;	
			score+=power_int;	
			j3+=1;//점수 디스플래이 상수
			}
			else if(num_pos[j1*4+1][i1*6+1]==max_num&&num_pos[j1*4+1][i1*6+1]==3*i2){		
			Gotoxy(i1*6+1+MAPX,j1*4+1+MAPY);
			textcolor(LIGHTRED,BLACK);
			power_int=pow(3,j2+1);
			cout<<"+"<<power_int;
			score+=power_int;
			j3+=1;//점수 디스플래이 상수
			}
			
			Gotoxy(MAPX,MAPY-1);//점수 디스플래이 
			textcolor(BLACK,WHITE);
			cout<<"SCORE | "<<score;
						
			j1+=1;
		}
		j1=0;
		i1+=1;
	}
	if(j3>=1) 
	Sleep(100);
	j3=0;
	j2+=1;	
	}
	///////////////////////////////////////////점수 저장 
if(set_type[3]==1){	
fin.open("Max_num_score.txt");
file_int=0;
fin>>file_int;
fin.close();	
if(score>file_int){
	fout.open("Max_num_score.txt");
	fout<<score;
	fout.close();
	Gotoxy(MAPX,MAPY-1);//점수 디스플래이 
	textcolor(LIGHTRED,WHITE);
	cout<<"SCORE | "<<score;
}
}
else if(set_type[3]==0){
	file_int=10000000000;
}
//////////////////////////////////////////// 
	while(1){		
		////////////////////////////////////////////////////
		if(score>file_int)
		Write(7,24,DARKGRAY,WHITE,"   Press 'q' to record it"); 
		else if(score<=file_int)
		Write(7,24,DARKGRAY,WHITE,"  Press 'q' to go to manu!"); 
		
		j2=0;//기록 완료 상수 
    	if(kbhit()){
			but=_getch();
			if(but=='q'){
				if(score>file_int){
			j=0;
			while(j<=15){	
			Write(MAPX-2,29-j,BROWN,WHITE,"■");
			Write(MAPX,29-j,WHITE,BROWN,"                          ");
			Write(MAPX+25+1,29-j,BROWN,WHITE,"■");
			if(j>=1)
				Write(MAPX-2,30-j,WHITE,DARKGRAY,"                              ");
			if(j>=2)
				Write(MAPX-2,31-j,WHITE,DARKGRAY,"  name                        ");
			if(j>=3){
			Write(MAPX-2,32-j,WHITE,DARKGRAY,"  ");
			Write(MAPX,32-j,DARKGRAY,WHITE,"                          ");
			Write(MAPX+25+1,32-j,WHITE,DARKGRAY,"  ");	
			}
			if(j>=4){
			Write(MAPX-2,33-j,WHITE,DARKGRAY,"  ");
			Write(MAPX,33-j,DARKGRAY,WHITE,"                          ");
			Write(MAPX+25+1,33-j,WHITE,DARKGRAY,"  ");	
			}
			if(j>=5){
			Write(MAPX-2,34-j,WHITE,DARKGRAY,"  ");
			Write(MAPX,34-j,DARKGRAY,WHITE,"                          ");
			Write(MAPX+25+1,34-j,WHITE,DARKGRAY,"  ");	  
			}			
			if(j>=6)
				Write(MAPX-2,35-j,WHITE,DARKGRAY,"                             ");
			if(j>=7)
				Write(MAPX-2,36-j,LIGHTGRAY,DARKGRAY,"  Use English or numbers     ");
			if(j>=8)
				Write(MAPX-2,37-j,WHITE,DARKGRAY,"                             ");
			Sleep(10);
			j+=1;	
			}
			/////////////////////////////////////
			i=0;
			while(i<=24){
				name[i]=' ';
				i+=1;
			}
			i1=0;
			while(j2==0){//기록 완료 상수 
				if(kbhit()){  
					but=_getch();
					if(but!=0x08&&but!=0x0D&&but!=' '&&i1<=25){
						textcolor(DARKGRAY,WHITE);
						Gotoxy(MAPX+i1,19);
						cout<<but;       
						name[i1]=but;	
						i1+=1;
					}
					else if(but==0x08){    //backspace 감지 
						if(i1<=25)
						Write(MAPX+i1,19,DARKGRAY,WHITE," ");
						if(i1>0)
						i1-=1;
						Write(MAPX+i1,19,DARKGRAY,WHITE," ");
						name[i1]=' ';	
					}	
					else if(but==' '){
						Write(MAPX+i1,19,DARKGRAY,WHITE,"_");       
						name[i1]='_';	
						i1+=1;
					}
					else if(but==0x0D){
						fout.open("Num_name.txt");//숫자 종류 			
						fout<<name;
						fout.close();
						Map();
						Background();
						Num_display();
						Sleep(400);
						j2=1;//기록 완료 상수 
				}
			}
			if(i1<=25&&i>=30&&i<50){//단위시간상수 i 
			Write(MAPX+i1,19,DARKGRAY,WHITE,"|");
			}
			else if(i1<=25&&i>=60){//단위시간상수 i 
			Write(MAPX+i1,19,DARKGRAY,WHITE," ");
			i=0;	//단위시간상수 i 
			}
			Sleep(5);
			i+=1;//단위시간상수 i 
			
		}
	}			
				j=6;
				while(j>=0){ 
					Write(MAPX,21+j,WHITE,DARKGRAY,"                          "); 
					Write(MAPX,22+j,WHITE,DARKGRAY," Press 'q' to Play THREES "); 
					Write(MAPX,23+j,WHITE,DARKGRAY,"                          "); 
					if(j<=5)
					Write(MAPX,24+j,WHITE,WHITE,"                          ");
					
					if(MAPX+5+j*4.9<=36){
					Write(MAPX+5+j*4.9,2,DARKGRAY,WHITE,"     "); 
					Write(MAPX+5+j*4.9,3,DARKGRAY,WHITE,"     "); 
					Write(MAPX+5+j*4.9,4,DARKGRAY,WHITE,"     "); 	
					}				
					Write(MAPX+j*4.9,2,DARKGRAY,WHITE,"_____"); 
					Write(MAPX+j*4.9,3,WHITE,DARKGRAY," :== "); 
					if(set_type[2]==1)//visible key
					Write(MAPX+j*4.9,4,LIGHTGRAY,WHITE,">>'r'");
					else if(set_type[2]==0)//visible key
					Write(MAPX+j*4.9,4,LIGHTGRAY,WHITE,"     ");
					
					
					Write(MAPX+21+j*1.4,2,DARKGRAY,WHITE,"_____"); 
					Write(MAPX+21+j*1.4,3,WHITE,DARKGRAY,"1+2=3"); 
					if(set_type[2]==1)//visible key
					Write(MAPX+21+j*1.4,4,LIGHTGRAY,WHITE,">>'t'"); 
					else if(set_type[2]==0)//visible key
					Write(MAPX+21+j*1.4,4,LIGHTGRAY,WHITE,"     "); 
					if(MAPX+21+5+j*1.4<=40){
					Write(MAPX+21+5+j*1.4,2,DARKGRAY,WHITE," "); 
					Write(MAPX+21+5+j*1.4,3,DARKGRAY,WHITE," "); 
					Write(MAPX+21+5+j*1.4,4,WHITE,DARKGRAY," ");	
					} 
					
					if(MAPX+19+j*3<=39)					
					Write(MAPX+19+j*3,3,CYAN,WHITE,"  "); 
					if(MAPX+7+j*3<41)
					Write(MAPX+7+j*3,3,CYAN,WHITE,"Ｔ"); 
					if(MAPX+9+j*3<41)
					Write(MAPX+9+j*3,3,LIGHTRED,WHITE,"Ｈ"); 
					if(MAPX+11+j*3<41)
					Write(MAPX+11+j*3,3,DARKGRAY,WHITE,"Ｒ"); 
					if(MAPX+13+j*3<41)
					Write(MAPX+13+j*3,3,DARKGRAY,WHITE,"Ｅ"); 
					if(MAPX+15+j*3<41)
					Write(MAPX+15+j*3,3,DARKGRAY,WHITE,"Ｅ"); 
					if(MAPX+17+j*3<41)
					Write(MAPX+17+j*3,3,DARKGRAY,WHITE,"Ｓ"); 					
					Sleep(5);
					j-=1;
				}
			goto Manu;			
			}
		}
	}
			}
		}
	} 

Write(0,27,WHITE,WHITE," "); 
	
}
