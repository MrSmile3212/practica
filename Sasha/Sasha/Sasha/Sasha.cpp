// Sasha.cpp: главный файл проекта.

// Sasha.cpp: ������� ���� �������.

#include "stdafx.h" 
#include <stdio.h>  
#include <conio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <malloc.h> 
#include <clocale>  
#include <windows.h> 
 
using namespace System; 
using namespace std;
using namespace System::IO;

#define ENTER 13 
#define ESC 27 
#define UP 72 
#define DOWN 80 
#define HOME 71 
#define END 79 
 
 
struct z { 
 char name[17]; 
 int power; 
 char mark[25];
 int data;
 int cost;
 int mileage;
 };

 
struct sp { 
 char name[17]; 
 int power; 
 struct sp* sled; 
 struct sp* pred; 
 
 } *spisok;

struct dg { 
 char mark[25]; 
 int power; 
 struct dg* sled; 
 } *strocky;

int menu(int, char **);
void costdata(int, struct z*);
void minpower(int, struct z*);
void maxmark(int, struct z*);
void alfavit(int, struct z*, struct sp**);
void vstavka(int, struct z*, char*, struct sp**);
void vyvod(int, struct z*,  struct sp**);
void diagramma(int, struct z*,  struct sp**); 
void dgvstavka(int, struct z*,  struct sp**);

void vyvod(int NC, struct z* cars, struct sp** spisok)
{
int i;
Console::Clear();
Console::CursorVisible::set(false); 
Console::WindowWidth = 125;  
Console::WindowHeight = 25;  
Console::BufferHeight=Console::WindowHeight; 
Console::BufferWidth = Console::WindowWidth; 
Console::BackgroundColor=ConsoleColor::Blue;  
Console::ForegroundColor=ConsoleColor::Yellow;  
printf("#################################################################################################"); 
printf("\n   НАЗВАНИЕ    |    МОЩНОСТЬ(Л.С.)   |   МАРКА   |   ГОД ВЫПУСКА   |    ЦЕНА     |    ПРОБЕГ     \n"); 
printf("#################################################################################################"); 
if(!(*spisok))
 for(i=0;i<NC;i++)
	printf("\n %-17s %8d %19s %13d %15d %14d     ", 
	cars[i].name, cars[i].power, 
	cars[i].mark,cars[i].data, 
	cars[i].cost,cars[i].mileage);
_getch();
}

void vstavka(int NC, struct z* cars, char* name, struct sp** spisok)
{
int i;
struct sp *New,*nt,*z=0;
for(nt=*spisok; nt!=0 && strcmp(nt->name,name)<0; z=nt, nt=nt->sled);
if(nt && strcmp(nt->name,name)==0) return;

New=(struct sp *) malloc(sizeof(struct sp));
strcpy(New->name,name);

New->pred=z;
New->sled=nt;
New->power=0;
for(i=0;i<NC;i++)
	if(strcmp(cars[i].name,name)==0)
		New->power+=cars[i].power;
if (!z) *spisok=New;
if (nt) nt->pred=New;
if (z) z->sled=New;
return;
}

void dgvstavka(int NC, struct z* cars,char* mark, struct sp** spisok)
{
	int i;
	struct dg *nov,*nt,*z=0;
	for(nt=strocky; nt!=0 && strcmp(nt->mark,mark)<0; z=nt, nt=nt->sled);
	if(nt && strcmp(nt->mark,mark)==0) return;
	nov=(struct dg *) malloc(sizeof(struct dg));
	strcpy(nov->mark,mark);
	nov->sled=nt;

	nov->power=0;
	for(i=0;i<NC;i++)
	if(strcmp(cars[i].mark,mark)==0)
	nov->power+=cars[i].power;
	if(!z) strocky=nov;
	else z->sled=nov;
	return;
}

void minpower(int NC, struct z* cars)
{
	int i=0; struct z best;
	strcpy(best.name,cars[0].name);
	best.power=cars[0].power;
	for(i=0;i<NC;i++)
		if (cars[i].power<best.power)
		{
		strcpy(best.name,cars[i].name);
		best.power=cars[i].power;
		}
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::White;
	Console::CursorLeft=10;
	Console::CursorTop=15;
	printf("Минимальную мощность имеет автомобиль %s",best.name);
	Console::CursorLeft=10;
	Console::CursorTop=16;
	printf("Его мощность составляет %d л.с.",best.power);
	getch();
}

void alfavit(int NC, struct z* cars, struct sp** spisok)
{
	int i;
	struct sp *nt, *p;
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::White;
	Console::Clear();
	if(!(*spisok))
		for(i=0;i<NC;i++)
			vstavka(NC, cars,cars[i].name, spisok);
	Console::Clear();
	printf("\n Название            |          Мощность(л.c.)");
	printf("\n ################################################\n");
	for(nt=*spisok; nt!=0; nt=nt->sled){
		printf("\n %-35s %d",nt->name,nt->power);
		p = nt;
	}
	Console::CursorLeft = 50;
	Console::CursorTop = 1;
	printf("Название               |          Мощность(л.c.)");
	Console::CursorLeft = 50;
	Console::CursorTop = 2;
	printf("###################################################");
	for(nt = p, i = 4; nt != 0, i < NC + 4; nt = nt -> pred, i++){
		Console::CursorLeft=50;
		Console::CursorTop= i;
		printf("%-38s %ld",nt -> name, nt -> power);
	}
	getch();
}

void maxmark(int NC, struct z* cars) 
{ 
	int i=0; struct z best; 
	strcpy(best.mark,cars[0].mark); 
	for(i=1;i<NC;i++){ 
	if (strlen(cars[i].mark)>strlen(best.mark)) 
	{ 
		strcpy(best.mark,cars[i].mark);
		strcpy(best.name,cars[i].name);
	}
	}
	Console::ForegroundColor=ConsoleColor::Black; 
	Console::BackgroundColor=ConsoleColor::White; 
	Console::CursorLeft=10; 
	Console::CursorTop=15; 
	printf("Самое длинное название марки %s ",best.mark); 
	Console::CursorLeft=10; 
	Console::CursorTop=16; 
	printf("имеет автомобиль %s ",best.name); 
	getch(); 
}

void costdata(int NC, struct z* cars) 
{
	int i,j,k=0;
	Console::BackgroundColor=ConsoleColor::Yellow;
	Console::ForegroundColor=ConsoleColor::Black;
	Console::Clear();
	printf("\n\rОдинаковая цена, но разный год выпуска");
	printf("\n\r##############################################################\n\r");
	for(i=1;i<NC;i++)
	{
		for(j=0;j<i;j++)
			if((cars[i].cost == cars[j].cost) && (cars[i].data != cars[j].data))
				{printf("%-10s   %d      %d\n",cars[i].name,cars[i].cost,cars[i].data);
				 printf("%-10s   %d      %d\n",cars[j].name,cars[j].cost,cars[j].data);
				 k++;
				 break;
				}
	}
	if(k==0) printf("Совпадений нет!");
	getch();
}

void diagramma(int NC, struct z *cars,  struct sp** spisok) 
{
	struct dg *nt;
	int len,i,NColor, sum, j;
	System::ConsoleColor Color;
	Console::ForegroundColor=ConsoleColor::Green;
	Console::BackgroundColor=ConsoleColor::Yellow;
	Console::Clear();

	if(!strocky)
	for(i=0;i<NC;i++)
	dgvstavka(NC,cars,cars[i].mark,spisok);
	Color=ConsoleColor::Black; NColor=0;

	Console::CursorLeft=5;
	printf("Марка       Общая мошность(л.с.)\n");
	printf("####################################################################################################");
	for(nt=strocky,i=0; nt!=0; nt=nt->sled,i++)
	{	
		sum = 0;
		for(j = 0; j<NC; j++){
			if(strcmp(cars[j].mark,nt->mark) == 0){
				sum  = sum + cars[j].power;
			}
		}
		
		Console::ForegroundColor=ConsoleColor::Green;
		Console::BackgroundColor= ConsoleColor::Yellow;
		Console::CursorLeft=5; Console::CursorTop=i+2;
		printf("%s", nt->mark);
		Console::CursorLeft=25;
		printf("%d", sum);
		Console::BackgroundColor=++Color; NColor++;
		Console::CursorLeft=47;
		for(len=0; len<sum/40; len++) printf(" ");
		if(NColor==14)
		{ Color=ConsoleColor::Black; NColor=0; }
	}
	getch();
	return ; 
}


int menu(int n, char **dan)
	{
	int y1=0,y2=n-1;
	char c=1;
	while (c!=ESC)
	{
		switch(c) {
		case DOWN: y2=y1; y1++; break;
		case UP: y2=y1; y1--; break;
		case HOME: y2=y1; y1=0; break; 
		case END: y2=y1; y1=6; break;
		case ENTER: return y1+1;
	}

	if(y1>n-1){y2=n-1;y1=0;}
	if(y1<0) {y2=0;y1=n-1;}

	Console::ForegroundColor=ConsoleColor::Yellow;
	Console::BackgroundColor=ConsoleColor::Blue;
	Console::CursorLeft=11;
	Console::CursorTop=y1+5;
	printf("%s",dan[y1]);
	Console::ForegroundColor=ConsoleColor::DarkMagenta; 
	Console::BackgroundColor=ConsoleColor::Cyan;
	Console::CursorLeft=11;
	Console::CursorTop=y2+5;
	printf("%s",dan[y2]);
	c=(char) getch();
	} 
	exit(0);
	}
 
 
 
int main(array<System::String ^> ^args) 
{ 
char *(dan[7]) = {
	"Вывод таблицы                                                                        ",
	"Автомобиль с минимальной мощностью?                                                  ", 
	"Алфавитный порядок(прямой и обратный)                                                ", 
	"Самое длинное название марки автомобилей?                                            ", 
	"Если одинаковая стоимость у автомобилей разного года выпуска?                        ", 
	"Диаграмма                                                                            ", 
	"Выход                                                                                ",
}; 
int NC;

setlocale(LC_CTYPE,"Russian"); 
int i,n; 
FILE *in; 
struct z *cars; 
Console::CursorVisible::set(false);

 ConsoleColor bgColor = Console::BackgroundColor;
 ConsoleColor fgColor = Console::ForegroundColor;
 Console::WindowWidth = 125;  
 Console::WindowHeight = 25;  
 Console::BufferHeight=Console::WindowHeight;  
 Console::BufferWidth = Console::WindowWidth;
 
 if ((in=fopen("bd52.dat","r"))==NULL) 
  { 
  printf("Файл базы данных не открыт!");  
  getch(); 
  exit(1); 
  } 
 
fscanf(in,"%d",&NC); 
cars=(struct z*)malloc(NC*sizeof(struct z));

for (i=0; i<NC; i++)  
 fscanf(in,"%s%d%s%d%d%d", 
 cars[i].name,
 &cars[i].power,
 cars[i].mark,
 &cars[i].data,
 &cars[i].cost,
 &cars[i].mileage);
 
while(1) 
 {
 Console::BackgroundColor=ConsoleColor::Yellow;
 Console::Clear();
 Console::CursorLeft=10;  
 Console::CursorTop=4; 
 Console::ForegroundColor=ConsoleColor::DarkMagenta; 
 Console::BackgroundColor=ConsoleColor::Cyan;
 
 for (i=0;i<7;i++)  
  { 
  Console::CursorLeft=10; 
  Console::CursorTop=i+5; 
  printf(" %s ",dan[i]); 
  } 
 Console::CursorLeft=10; 
 Console::CursorTop=12; 
 n=menu(7,dan); 
 switch(n) {
  case 1: vyvod(NC, cars, &spisok);break;
  case 2: minpower(NC, cars);break; 
  case 3: alfavit(NC, cars, &spisok);break; 
  case 4: maxmark(NC, cars);break; 
  case 5: costdata(NC, cars);break;
  case 6: diagramma(NC, cars, &spisok);break;
  case 7: exit(0); 
  }
 }
return 0; 
} 


