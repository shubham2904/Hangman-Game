#include <iostream>
#include <string>
#include<stdio.h>
#include <stdlib.h>
#include <windows.h>
#include<time.h>
#include <conio.h>
using namespace std;
string player1,player2,underscore,guess;
char word[40];
char curr_word[40];
char upd_word[40];
char a;
int wrong=0;
int curr_score=0;
int curr_animalorplace;
char currentkey;
void displayupdated();
void readchar();
void play();
void reset_game();
void quit();
char arrayofalpaha[] ={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
struct node
{
 char data[40];
 node *next;
};
int hash(char *str)
{
 return str[0]-'A';
}
int random1()
{
    return rand()%2;
}
int random2()
{
    return rand()%26;
}
int random3()
{
    return rand()%5;
}
node *placearray[26]={NULL};
node *animalarray[26]={NULL};

void gotoxy(int x,int y)
{
    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
void wait()
{
    for(int i=1;i<=10684;i++)
   {for(int j=1;j<=37684;j++)
{}}
}
char* upstr(char *str)
{
    int len=strlen(str);
    for(int i=0;i<len;i++)
        str[i]=toupper(str[i]);
    return str;
}
//=============================================-----------------FRAME STARTING------------------------------===================================================
void heading()
{
    system("cls");
    gotoxy(38,2);cout<<"**     **      *****     **       **      ****     **     **     *****      **       **"<<endl;
    gotoxy(38,3);cout<<"**     **     **   **    ** *     **     **        ** * * **    **   **     ** *     **"<<endl;
    gotoxy(38,4);cout<<"*********    *********   **   *   **    ** *****   **  *  **   *********    **   *   **"<<endl;
    gotoxy(38,5);cout<<"**     **    **     **   **     * **     ***  **   **     **   **     **    **     * **"<<endl;
    gotoxy(38,6);cout<<"**     **    **     **   **       **      **  **   **     **   **     **    **       **"<<endl;
}


void starting_frame()
{
    heading();
gotoxy(65,20);
fflush(stdin);
cout << "Please type in your name" << endl;
gotoxy(78,22);
getline(cin,player1);
system("cls");
heading();
gotoxy(71,20);
cout << "OK " << player1 << " and " << player2 <<endl;
system("cls");
heading();
gotoxy(70,20);
cout << """Let's start with the game!" <<endl;
wait();
system("cls");
heading();
gotoxy(43,20);
cout << player1 << " please input the word you want(not less than 6 letters) " << player2 << " to guess." << endl;
gotoxy(80,35);
cout << "[Press Backspace key to re-enter the word]"<<endl;
gotoxy(70,22);
 /*for(int i=0;;)
    {   a=getch();
        if(a=='\b')
        {
            i=0;
            system("cls");
            heading();
            gotoxy(43,20);
            cout << player1 << " please input the word you want(not less than 6 letters) " << player2 << " to guess." << endl;
            gotoxy(80,35);
            cout << "[Press Backspace key to re-enter the word]"<<endl;
            gotoxy(70,22);
        }
        else if(a=='\r')
        {
            word[i]='\0';
            break;
        }
        else
        {
        word[i]=a;
        i++;
        cout<<"*";
        }
    }*/
    strcpy(word,"sashakt");

}
void initdisplayword()
{
    int len=strlen(curr_word);
    cout<<len;
    int k=35;
    strcpy(upd_word,"");
    for(int i=0;i<len;i++)
        {
            upd_word[i]='_';
        }
        upd_word[len]='\0';
        gotoxy(35,20);
        cout<<upd_word;
        gotoxy(35,21);
        cout<<curr_word;
        gotoxy(0,47);
}
//=====================================================FRAME END============================================================================================
//==================================================CREATION=====================================================================
void insertanimal(char *str)
{    int pos=hash(str);
    node *tmp = new node;
    strcpy(tmp->data,str);
    tmp->next=NULL;
    if(animalarray[pos]==NULL)
    {
        animalarray[pos]=tmp;
    }
    else
    {
        node *tmp2,*prev;
        node *handler;
        handler=animalarray[pos]->next;
        if(handler==NULL)
        {
            animalarray[pos]->next=tmp;
            //cout<<"inserting first "<<tmp->data<<endl;
        }
        else
        {
            prev=handler;
            while(handler!=NULL&&strcmpi(handler->data,str)>=0)
            {
                prev=handler;
                handler=handler->next;
            }
            if(handler==NULL)
                prev->next=tmp;
            else if(handler==prev)
            {
                tmp->next=handler->next;
                handler->next=tmp;
            }
            else
            {
               tmp2=handler;
               prev->next=tmp;
               tmp->next=tmp2;
            }
        }

    }
}
//=================================PLACE INSERTION=========================================================
void insertplace(char *str)
{
    int pos=hash(str);
    node *tmp = new node;
    strcpy(tmp->data,str);
    tmp->next=NULL;
    if(placearray[pos]==NULL)
    {
        placearray[pos]=tmp;
    }
    else
    {
        node *tmp2,*prev;
        node *handler;
        handler=placearray[pos]->next;
        if(handler==NULL)
        {
            placearray[pos]->next=tmp;
            //cout<<"inserting first "<<tmp->data<<endl;
        }
        else
        {
            prev=handler;
            while(handler!=NULL&&strcmpi(handler->data,str)>=0)
            {
                prev=handler;
                handler=handler->next;
            }
            if(handler==NULL)
                prev->next=tmp;
            else if(handler==prev)
            {
                tmp->next=handler->next;
                handler->next=tmp;
            }
            else
            {
               tmp2=handler;
               prev->next=tmp;
               tmp->next=tmp2;
            }
        }

    }
}
int checkallalpha(char *str)
{
    int len = strlen(str);
    for(int i=0;i<len;i++)
        if(!isalpha(str[i]))
         return 0;
    return 1;
}
void insertelements()
{
 char ch[40];
 int counterforwhile=0;
 char extra;
 FILE *fname,*fplace;
 fname=fopen("place.txt","r");
 fplace=fopen("animal.txt","r");
 cout<<"Opened file"<<endl;
 while(fscanf(fname,"%s",ch)!=EOF)
    {
        while(1)
        {
            counterforwhile++;
            fscanf(fname,"%c",&extra);
            if(extra=='\n'||counterforwhile>=1000)
                break;
        }
        //cout<<"inserting"<<endl;
        if(isalpha(ch[0])&&checkallalpha(ch))
        {
        strcpy(ch,upstr(ch));
       // cout<<ch;
        insertplace(ch);
        }
        //cout<<"inserted successfully"<<endl;
    }
    while(fscanf(fplace,"%s",ch)!=EOF)
    {
        while(1)
        {
            counterforwhile++;
            fscanf(fplace,"%c",&extra);
            if(extra=='\n'||counterforwhile>=1000)
                break;
        }
        //cout<<"inserting"<<endl;
        if(isalpha(ch[0])&&checkallalpha(ch))
        {
        strcpy(ch,upstr(ch));
        //cout<<ch;
        insertanimal(ch);
        }
        //cout<<"inserted successfully"<<endl;
    }
}
//==============================--------------CREATION END-----------------------------==========================================
//====================------------------------MAN START---------------------------------------------------=====================================================
void complete_man()
{
    system("cls");
heading();
gotoxy(0,8);
cout<<"          --------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
for(int c=9;c<=35;c++)
{
gotoxy(10,c);
cout<<"||"<<endl;
gotoxy(85,c);
cout<<"||"<<endl;
gotoxy(160,c);
cout<<"||"<<endl;
}
gotoxy(0,36);
cout<<"          --------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
gotoxy(70,37);
cout<<"Current Score:\t"<<curr_score;
if(wrong==0)
 {
    gotoxy(119,15);cout << "I======" << endl;
    gotoxy(119,16);cout << "II    " << endl;
    gotoxy(119,17);cout << "II   " << endl;
    gotoxy(119,18);cout << "II    " << endl;
    gotoxy(119,19);cout << "II    " << endl;
    gotoxy(119,20);cout << "II  " << endl;
    gotoxy(119,21);cout << "II    " << endl;
    gotoxy(119,22);cout << "II   " << endl;
    gotoxy(119,23);cout << "II " << endl;
    gotoxy(119,24);cout << "II   " << endl;
    gotoxy(119,25);cout << "II  " << endl;
 }
 if(wrong==1)
 {
    gotoxy(119,15);cout << "I======" << endl;
gotoxy(119,16);cout << "II    **" << endl;
gotoxy(119,17);cout << "II   *  *" << endl;
gotoxy(119,18);cout << "II    **" << endl;
gotoxy(119,19);cout << "II  " << endl;
gotoxy(119,20);cout << "II  " << endl;
gotoxy(119,21);cout << "II  " << endl;
gotoxy(119,22);cout << "II  " << endl;
gotoxy(119,23);cout << "II  " << endl;
gotoxy(119,24);cout << "II  " << endl;
gotoxy(119,25);cout << "II  " << endl;
 }if(wrong==2)
 {
    gotoxy(119,15);cout << "I======" << endl;
gotoxy(119,16);cout << "II    **" << endl;
gotoxy(119,17);cout << "II   *  *" << endl;
gotoxy(119,18);cout << "II    **" << endl;
gotoxy(119,19);cout << "II    || " << endl;
gotoxy(119,20);cout << "II    ||  " << endl;
gotoxy(119,21);cout << "II    || " << endl;
gotoxy(119,22);cout << "II   " << endl;
gotoxy(119,23);cout << "II       " << endl;
gotoxy(119,24);cout << "II   " << endl;
gotoxy(119,25);cout << "II " << endl;
 }if(wrong==3)
 {
    gotoxy(119,15);cout << "I======" << endl;
gotoxy(119,16);cout << "II    **" << endl;
gotoxy(119,17);cout << "II   *  *" << endl;
gotoxy(119,18);cout << "II    **" << endl;
gotoxy(119,19);cout << "II    || " << endl;
gotoxy(119,20);cout << "II    ||--" << endl;
gotoxy(119,21);cout << "II    || " << endl;
gotoxy(119,22);cout << "II   " << endl;
gotoxy(119,23);cout << "II    " << endl;
gotoxy(119,24);cout << "II   " << endl;
gotoxy(119,25);cout << "II  " << endl;
 }if(wrong==4)
 {
    gotoxy(119,15);cout << "I======" << endl;
gotoxy(119,16);cout << "II    **" << endl;
gotoxy(119,17);cout << "II   *  *" << endl;
gotoxy(119,18);cout << "II    **" << endl;
gotoxy(119,19);cout << "II    || " << endl;
gotoxy(119,20);cout << "II  --||--" << endl;
gotoxy(119,21);cout << "II    || " << endl;
gotoxy(119,22);cout << "II    " << endl;
gotoxy(119,23);cout << "II     " << endl;
gotoxy(119,24);cout << "II   " << endl;
gotoxy(119,25);cout << "II  " << endl;
 }
 if(wrong==5)
 {
    gotoxy(119,15);cout << "I======" << endl;
gotoxy(119,16);cout << "II    **" << endl;
gotoxy(119,17);cout << "II   *  *" << endl;
gotoxy(119,18);cout << "II    **" << endl;
gotoxy(119,19);cout << "II    || " << endl;
gotoxy(119,20);cout << "II  --||--" << endl;
gotoxy(119,21);cout << "II    || " << endl;
gotoxy(119,22);cout << "II   / " << endl;
gotoxy(119,23);cout << "II  /    " << endl;
gotoxy(119,24);cout << "II   " << endl;
gotoxy(119,25);cout << "II " << endl;
 }
 if(wrong==6)
 {
    gotoxy(119,15);cout << "I======" << endl;
gotoxy(119,16);cout << "II    **" << endl;
gotoxy(119,17);cout << "II   *  *" << endl;
gotoxy(119,18);cout << "II    **" << endl;
gotoxy(119,19);cout << "II    || " << endl;
gotoxy(119,20);cout << "II  --||--" << endl;
gotoxy(119,21);cout << "II    || " << endl;
gotoxy(119,22);cout << "II   /  \\" << endl;
gotoxy(119,23);cout << "II  /    \\ " << endl;
gotoxy(119,24);cout << "II   " << endl;
gotoxy(119,25);cout << "II  YOU ARE DEAD" << endl;
 }
}
//=============================================MAN END================================================================
//============================----------------DISPLAY-----------------================================================
void randomdisplay()
{
    int animalorname=random1();
    int counter=0,countertill;
    countertill=random3();
    if(animalorname==1)
     {
        gotoxy(35,16);
        cout<<"HINT: PLACE";
        node *tmp;
        curr_animalorplace=1;
        tmp = placearray[random2()];
        while(counter<countertill&&tmp->next!=NULL)
        {
            counter++;
            tmp=tmp->next;
        }
        gotoxy(35,20);
        //cout<<tmp->data;
        strcpy(curr_word,tmp->data);
     }
     else
     {
        gotoxy(35,16);
        cout<<"HINT: ANIMAL";
        node *tmp;
        curr_animalorplace=2;
        here: tmp = animalarray[random2()];
        if(tmp==NULL) goto here;
        while(counter<countertill&&tmp->next!=NULL)
        {
            counter++;
            tmp=tmp->next;
        }
        gotoxy(35,20);
        //cout<<tmp->data;
        strcpy(curr_word,tmp->data);
     }
     initdisplayword();
     readchar();
}
//=========================================DISPLAY END================================================================
//===============================================READ==================================================================

   int check(char ch)
   {
       if(ch=='@')
       quit();
       int len=strlen(curr_word);
       int flag=0;
       for(int i=0;i<len;i++)
       {
        if(curr_word[i]==ch)
            {
                flag=-1;
                curr_score+=1;
                upd_word[i]=ch;
            }
       }
       return flag;
   }
   void readchar()
   {
     int poss;
     gotoxy(35,24);
     cin>>a;
     a=toupper(a);
     poss=check(a);
     if(strcmpi(upd_word,curr_word)==0)
        play();
     if(poss==-0)
        wrong++;
      if(wrong==6)
            quit();
        complete_man();
        displayupdated();
        if(strcmpi(upd_word,curr_word)==0)
        { play();}
       readchar();
   }
//==============================================READ END================================================================
void play()
{
    complete_man();
    randomdisplay();
}
void quit()
{
    /*system("cls");
    heading();
    cout<<"          --------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    for(int c=9;c<=35;c++)
        {
            gotoxy(10,c);
            cout<<"||"<<endl;
            gotoxy(85,c);
            cout<<"||"<<endl;
            gotoxy(160,c);
            cout<<"||"<<endl;
        }
    gotoxy(0,36);
    cout<<"          --------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    */
    complete_man();
    gotoxy(40,15);
    cout<<"Player :\t"<<player1;
    gotoxy(40,17);
    cout<<"Score :\t"<<curr_score;
    gotoxy(35,20);
    cout<<"Enter R to Play Again";
    char ch;
    cin>>ch;
    if(ch=='r'||ch=='R')
       reset_game();
    else
      gotoxy(0,38);
      exit(0);
}
void reset_game()
{
    curr_score=0;
    starting_frame();
    wrong=0;
    play();
}
int main()
{
    srand(time(NULL));
    insertelements();
    starting_frame();
    wrong=0;
    play();
    return 0;
}

void displayupdated()
{
    gotoxy(35,20);
    cout<<upd_word;
    gotoxy(35,21);
    cout<<curr_word;
    gotoxy(35,16);
    if(curr_animalorplace==2)
        cout<<"HINT: ANIMAL";
    else
        cout<<"HINT: PLACE";
}
