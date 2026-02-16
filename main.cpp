#include <iostream>
#include <string>
#include <ctime>
#include <Windows.h>
#include <conio.h>

using namespace std;

char marks[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};

void color(int x) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}

void printSpecChar(char C) {
    if (C == 'X')
        color(9);
    else if(C == 'O')
        color(12);
    else
        color(7);
    cout<<C;
    color(7);
}

void showBoard() {
    cout<<"       |       |\n";
    cout<<"   ";  printSpecChar(marks[0][0]);  cout<<"   |   ";  printSpecChar(marks[0][1]);  cout<<"   |   ";  printSpecChar(marks[0][2]);  cout<<"   \n";
    cout<<"       |       |\n";
    cout<<"-----------------------\n";
/*------------------------------------------------------------*/
    cout<<"       |       |\n";
    cout<<"   ";  printSpecChar(marks[1][0]);  cout<<"   |   ";  printSpecChar(marks[1][1]);  cout<<"   |   ";  printSpecChar(marks[1][2]);  cout<<"   \n";
    cout<<"       |       |\n";
    cout<<"-----------------------\n";
/*------------------------------------------------------------*/
    cout<<"       |       |\n";
    cout<<"   ";  printSpecChar(marks[2][0]);  cout<<"   |   ";  printSpecChar(marks[2][1]);  cout<<"   |   ";  printSpecChar(marks[2][2]);  cout<<"   \n";
    cout<<"       |       |\n";
    cout<<endl<<endl;
}

void resetBoard() {
    for(int y = 0; y<3; y++) {
        for(int i = 0; i<3; i++) {
            marks[y][i] = ' ';
        }
    }
}

bool isThereEmptyCell() {
    for(int i = 0; i<3; i++) {
        for (int j = 0; j<3; j++) {
            if(marks[i][j]==' ')
                {return true;}
        }
    }
    return false;
}

void ShowTitle() {
    cout<< "|";
    color(6);  cout<< "=================================================="; color(7);
    cout<< "|\n";
    cout<< "|                                                  |\n";
    cout<< "|                    TIC TAC TOE                   |\n";
    cout<< "|               -- by Tremanuele23 --              |\n";
    cout<< "|                                                  |\n";
    cout<< "|";
    color(6);  cout<< "=================================================="; color(7);
    cout<<"|\n";
    cout<<endl<<endl;
}

char checkWinner () {
    int sV[8][3][2]= {
        /*Orizzontali */ {{0, 0}, {0, 1}, {0, 2}}, /*|*/  {{1, 0}, {1, 1}, {1, 2}}, /*|*/  {{2, 0}, {2, 1}, {2, 2}}, /*|*/
        /*Verticali */   {{0, 0}, {1, 0}, {2, 0}}, /*|*/  {{0, 1}, {1, 1}, {2, 1}}, /*|*/  {{0, 2}, {1, 2}, {2, 2}}, /*|*/
        /*Diagonali*/    {{0, 0}, {1, 1}, {2, 2}},  /*|*/ {{2, 0}, {1, 1}, {0, 2}}
    };
    char V = 'n',c1, c2, c3;
    for(int i = 0; i<8; i++) {
        c1 = marks [sV[i][0][0]] [sV[i][0][1]];
        c2 = marks [sV[i][1][0]] [sV[i][1][1]];
        c3 = marks [sV[i][2][0]] [sV[i][2][1]];
        if (c1!=' ' && c1 == c2  && c2 == c3)
            V = c1;
    }
    return V;
}

class Player {

private:
/*----------------------------------------------------------*/
    char Mark;
    int X;
    int Y;

public:
/*----------------------------------------------------------*/
Player(char P) {Mark=P;}

bool cordsAreOK() {
    if (X<0||X>2||Y<0||Y>2)
        return false;
    else {return true;}
}

void chooseCell() {
    char comma;
    cout<<"Mark your position (row, column).\n";
    do {
        cout<<"Your move: ";
        cin>> X >> comma >> Y;
        if (!cordsAreOK())
            cout<<"Not valid move. Try again\n\n";
    }
    while(!cordsAreOK());
}

void exeTurn() {
    cout<<"Player ";
    printSpecChar(Mark);
    cout<<"'s turn.\n";
    do {
        chooseCell();
        if (marks[X][Y] == ' ') {
            marks[X][Y] = Mark;
            break;
        }
        else  {cout<<"--That cell was already filled--\n";}
    }
    while(marks[X][Y]!=' ');
}
};

int main()
{
/*----Dichiarazione----*/
    srand(time(0));
    int turn = rand()%2;
    char V = 'n';
    bool playAgain;
    Player players[2] = {Player('X'), Player('O')};

/*----Start Page-----*/
    ShowTitle();
    cout<<"Press any key to start playing: ";
    _getch();

/*-------Game-------*/
    do {
        resetBoard();
        do {
            system("CLS");
            showBoard();
            players[turn%2].exeTurn();
            V = checkWinner();
            turn++;
        }
        while(V == 'n' && isThereEmptyCell());
        system("CLS");
        showBoard();
        if(V=='n')
            cout<<"\nTie! What a delusion!";
        else {
            cout<<"\nPlayer ";
            printSpecChar(V);
            cout<<" wins!";
        }
        cout<<"\n\nDo you wish to play another match (1 Yes 0 No)? ";
        cin>>playAgain;
    }
    while(playAgain);

    return 0;
}
