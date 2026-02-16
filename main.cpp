#include <iostream>
#include <string>
#include <ctime>
#include <Windows.h>
#include <conio.h>

using namespace std;

char signs[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};

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
    cout<<"   ";  printSpecChar(signs[0][0]);  cout<<"   |   ";  printSpecChar(signs[0][1]);  cout<<"   |   ";  printSpecChar(signs[0][2]);  cout<<"   \n";
    cout<<"       |       |\n";
    cout<<"-----------------------\n";
/*------------------------------------------------------------*/
    cout<<"       |       |\n";
    cout<<"   ";  printSpecChar(signs[1][0]);  cout<<"   |   ";  printSpecChar(signs[1][1]);  cout<<"   |   ";  printSpecChar(signs[1][2]);  cout<<"   \n";
    cout<<"       |       |\n";
    cout<<"-----------------------\n";
/*------------------------------------------------------------*/
    cout<<"       |       |\n";
    cout<<"   ";  printSpecChar(signs[2][0]);  cout<<"   |   ";  printSpecChar(signs[2][1]);  cout<<"   |   ";  printSpecChar(signs[2][2]);  cout<<"   \n";
    cout<<"       |       |\n";
    cout<<endl<<endl;
}

void resetBoard() {
    for(int y = 0; y<3; y++) {
        for(int i = 0; i<3; i++) {
            signs[y][i] = ' ';
        }
    }
}

bool isThereEmptyCell() {
    for(int i = 0; i<3; i++) {
        for (int j = 0; j<3; j++) {
            if(signs[i][j]==' ')
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
    cout<< "|           -- ma fatto meglio di prima --         |\n";
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
        c1 = signs [sV[i][0][0]] [sV[i][0][1]];
        c2 = signs [sV[i][1][0]] [sV[i][1][1]];
        c3 = signs [sV[i][2][0]] [sV[i][2][1]];
        if (c1!=' ' && c1 == c2  && c2 == c3)
            V = c1;
    }
    return V;
}

class Player {

private:
/*----------------------------------------------------------*/
    char segno;
    int X;
    int Y;

public:
/*----------------------------------------------------------*/
Player(char P) {segno=P;}

bool cordsAreOK() {
    if (X<0||X>2||Y<0||Y>2)
        return false;
    else {return true;}
}

void scegliCella() {
    char comma;
    cout<<"Contrassegna posizione (riga, colonna).\n";
    do {
        cout<<"La tua mossa: ";
        cin>> X >> comma >> Y;
        if (!cordsAreOK())
            cout<<"Mossa non valida. Riprovare\n\n";
    }
    while(!cordsAreOK());
}

void exeTurn() {
    cout<<"Turno di ";
    printSpecChar(segno);
    cout<<".\n";
    do {
        scegliCella();
        if (signs[X][Y] == ' ') {
            signs[X][Y] = segno;
            break;
        }
        else  {cout<<"--Cella occupata--\n";}
    }
    while(signs[X][Y]!=' ');
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
    cout<<"Premere un tasto per giocare: ";
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
            cout<<"\nPareggio! Facit schif!";
        else {
            cout<<"\nIl giocatore ";
            printSpecChar(V);
            cout<<" vince!";
        }
        cout<<"\n\nI lorsignori disiano giocare ancora (1 Si 0 No)? ";
        cin>>playAgain;
    }
    while(playAgain);

    return 0;
}
