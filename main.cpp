#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameOver;
const int width=20,height=20;
int x,y,fruitX,fruitY,score;
enum eDirection{ STOP=0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
int tailX[100],tailY[100],n;

void SetColor(int value){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  value);
}

void setup()
{
    system("cls");
    gameOver=false;
    dir=STOP;
    x=width/2; y=height/2;
    fruitX=rand()%(width-1)+1;
    fruitY=rand()%(height-1)+1;
    score=0;
}

void draw()
{
    system("cls");
    for(int i=0;i<=width;++i)
    {
        SetColor(7);
        cout<<char(254);
    }
    cout<<endl;


    for(int i=1;i<height;++i)
    {
        for(int j=0;j<=width;++j)
        {
            SetColor(7);
            bool print=false;
            if(j==0||j==width)
            {
                cout<<char(254); print=true;
            }
            if(i==y&&j==x)
            {
                SetColor(2);
                cout<<"O"; print=true;
            }
            if(i==fruitY&&j==fruitX)
            {
                SetColor(4);
                cout<<"F"; print=true;
            }
            for(int k=0;k<n;++k)
                if(tailX[k]==j&&tailY[k]==i)
                {
                    SetColor(2);
                    cout<<"x";
                    print=true;
                }
            if(!print)
                cout<<" ";
        }
        cout<<endl;
    }


    for(int i=0;i<=width;++i)
    {
        SetColor(7);
        cout<<char(254);
    }
    cout<<endl<<"Score: "<<score<<endl;
}

void input()
{
    if(_kbhit())
    {
        switch(_getch())
        {
            case 'a':
                if(dir!=RIGHT)dir=LEFT;
                break;
            case 'd':
                if(dir!=LEFT)dir=RIGHT;
                break;
            case 'w':
                if(dir!=DOWN)dir=UP;
                break;
            case 's':
                if(dir!=UP)dir=DOWN;
                break;
            case 'x':
                gameOver=true;
                break;

        }
    }
}

void logic()
{   int prevX=tailX[0];
    int prevY=tailY[0];
    int prev2X,prev2Y;
    tailX[0]=x;
    tailY[0]=y;
    for(int i=1;i<n;++i)
    {
        prev2X=tailX[i];
        prev2Y=tailY[i];
        tailX[i]=prevX;
        tailY[i]=prevY;
        prevX=prev2X;
        prevY=prev2Y;
    }
    switch(dir)
    {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }
    if( (x==0||x==width) || (y==0||y==height) )
        gameOver=true;
    for(int i=1;i<n;++i)
        if(tailX[i]==x&&tailY[i]==y)
            gameOver=true;
    if( x==fruitX && y==fruitY )
    {
        score+=10;
        ++n;
        fruitX=rand()%(width-1)+1;
        fruitY=rand()%(height-1)+1;
    }
}

int main()
{
    cout<<"SNAKE GAME\n\n";
    cout<<"Controls : WASD = movement , X = quit\n\n\n";
    cout<<"Set tick (ms):\n";
    int t=0;
    cin>>t;
    setup();
    while(!gameOver)
    {
        draw();
        input();
        logic();
        Sleep(t);
    }
    cout<<"Game over\n";
    system("pause");
    return 0;
}
