#include <iostream>
#include <Windows.h>
#include <conio.h>
using namespace std;
bool gameOver;
const int width = 30;
const int height = 30;
int x, y, fruitY, fruitX, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
}
void Draw()
{
    system("cls");
    for(int i = 0; i < width+2; i++)
        cout<< "#";
    cout<< endl;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if(j == 0){
                cout<< "#";
            }
            if(i == y && j == x)
                cout << "O";
            else if(i == fruitY && j == fruitX)
                cout<<"F";
            else
            {
                bool prnt = false;
                for(int k = 0; k< nTail;k++)
                {
                    if(tailX[k]==j && tailY[k]==i)
                    {
                        cout<< "o";
                        prnt = true;
                    }
                }
               if(!prnt)cout<<" ";
            }
            if(j == width-1){
                cout<<"#";   
        	}    
        }
        cout<<endl;
    }

    for(int i = 0; i < width+2; i++)
        cout<< "#";
    cout<< endl;
    cout<< "Score:"<< score<<endl;
}   
void Input()
{
    if(_kbhit())
    {
        switch (_getch())
        {
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'x':
                gameOver = true;
                break;
        }
    }   

}
void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0]=x;
    tailY[0]=y;
    for (int i = 1;i < nTail;i++){
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
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
    if(x > width || x < 0 || y > height || y < 0){
        gameOver = true;
        system("cls");
        cout<<"Game Over";
    }
    for(int i = 0; i< nTail; i++)
    {
        if(tailX[i]==x && tailY[i]==y){
            gameOver=true;
            system("cls");
            cout<<"Game Over";
        }
    }
    if(x == fruitX && y == fruitY)
    {
        score+=1;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

int main()
{
    Setup();
    while(!gameOver)
    {
        Draw();
        Sleep(150);
        Input();
        Logic();
    }
}