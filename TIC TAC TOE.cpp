#include <iostream>
#include <iomanip>
using namespace std;

char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};

int choice;
int row, column;
char turn = 'X';
bool draw = false;

void display_board() {
    system("clear"); 
    cout << setw(40) << "PLAYER - 1 [X] vs PLAYER - 2 [O]" << endl;
    cout << setw(33) << " |     |     " << endl;
    cout << setw(33) << " |  " << board[0][0] << "  |  " << board[0][1] << "  |  " << board[0][2] << "  " << endl;
    cout << setw(33) << " |_____|_____|_____" << endl;
    cout << setw(33) << " |     |     " << endl;
    cout << setw(33) << " |  " << board[1][0] << "  |  " << board[1][1] << "  |  " << board[1][2] << "  " << endl;
    cout << setw(33) << " |_____|_____|_____" << endl;
    cout << setw(33) << " |     |     " << endl;
    cout << setw(33) << " |  " << board[2][0] << "  |  " << board[2][1] << "  |  " << board[2][2] << "  " << endl;
    cout << setw(33) << " |     |     " << endl;
}

void player_turn() {
    if (turn == 'X') {
        cout << "Player - 1 [X] turn : ";
    } else if (turn == 'O') {
        cout << "Player - 2 [O] turn : ";
    }
    
    cin >> choice;

    while (choice < 1 || choice > 9 || board[(choice - 1) / 3][(choice - 1) % 3] == 'X' || board[(choice - 1) / 3][(choice - 1) % 3] == 'O') {
        cout << "Invalid Move. Please choose another: ";
        cin >> choice;
    }

    row = (choice - 1) / 3;
    column = (choice - 1) % 3;

    if (turn == 'X') {
        board[row][column] = 'X';
        turn = 'O';
    } else if (turn == 'O') {
        board[row][column] = 'O';
        turn = 'X';
    }
}

bool gameover() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2] ||
            board[0][i] == board[1][i] && board[0][i] == board[2][i]) {
            return false;
        }
    }

    if (board[0][0] == board[1][1] && board[0][0] == board[2][2] ||
        board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
        return false;
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                return true;
            }
        }
    }

    draw = true;
    return false;
}

int main() {
    cout << "T I C K -- T A C -- T O E -- G A M E\n";
    cout << "FOR 2 PLAYERS\n";
    
    while (gameover()) {
        display_board();
        player_turn();
    }

    display_board(); 
    if (turn == 'X' && !draw) {
        cout << "\nCongratulations! Player with 'X' has won the game\n";
    } else if (turn == 'O' && !draw) {
        cout << "\nCongratulations! Player with 'O' has won the game\n";
    } else {
        cout << "\nGAME DRAW!!!\n";
    }

    return 0;
}

