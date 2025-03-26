#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <ctime>

using namespace std;

const int width = 12;
const int height = 22;
vector<vector<int>> board(height, vector<int>(width, 0));

vector<vector<vector<int>>> tetrominoes = {
    {{1, 1, 1}, {0, 1, 0}}, 
    {{1, 1}, {1, 1}},       
    {{1, 1, 0}, {0, 1, 1}}, 
    {{0, 1, 1}, {1, 1, 0}}, 
    {{1, 1, 1, 1}},         
    {{1, 0, 0}, {1, 1, 1}}, 
    {{0, 0, 1}, {1, 1, 1}}  
};

vector<string> colors = {"🟪", "🟨", "🟩", "🟥", "🟦", "🟧", "🟫"};

int posX, posY, currentPiece;
bool gameOver = false;
int fallSpeed = 15; 
int moveSpeed = 2; 
int score = 0; 

void setCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void newPiece() {
    posX = width / 2 - 2;
    posY = 0;
    currentPiece = rand() % tetrominoes.size();
    
    vector<vector<int>> piece = tetrominoes[currentPiece];
    for (int i = 0; i < piece.size(); i++) {
        for (int j = 0; j < piece[i].size(); j++) {
            if (piece[i][j] == 1 && board[posY + i][posX + j] != 0) {
                gameOver = true;
                return;
            }
        }
    }
}

void drawBoard() {
    setCursorPosition(0, 0);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (board[i][j] == 0)
                cout << "⬜";
            else
                cout << colors[board[i][j] - 1];
        }
        cout << endl;
    }
    cout << "Score: " << score << endl;
    if (gameOver) cout << "GAME OVER! Press R to Restart" << endl;
}

void clearPiece() {
    vector<vector<int>> piece = tetrominoes[currentPiece];
    for (int i = 0; i < piece.size(); i++) {
        for (int j = 0; j < piece[i].size(); j++) {
            if (piece[i][j] == 1 && posY + i < height && posX + j < width) {
                board[posY + i][posX + j] = 0;
            }
        }
    }
}

void placePiece() {
    vector<vector<int>> piece = tetrominoes[currentPiece];
    for (int i = 0; i < piece.size(); i++) {
        for (int j = 0; j < piece[i].size(); j++) {
            if (piece[i][j] == 1 && posY + i < height && posX + j < width) {
                board[posY + i][posX + j] = currentPiece + 1;
            }
        }
    }
}

void clearLines() {
    for (int i = height - 1; i >= 0; i--) {
        bool fullLine = true;
        for (int j = 0; j < width; j++) {
            if (board[i][j] == 0) {
                fullLine = false;
                break;
            }
        }
        if (fullLine) {  
            score += 10;  
            for (int k = i; k > 0; k--) {
                board[k] = board[k - 1];  
            }
            board[0] = vector<int>(width, 0);  
            i++;  
        }
    }
}

int findDropPosition() {
    int dropY = posY;
    while (true) {
        vector<vector<int>> piece = tetrominoes[currentPiece];
        bool canMove = true;
        for (int i = 0; i < piece.size(); i++) {
            for (int j = 0; j < piece[i].size(); j++) {
                if (piece[i][j] == 1 && (dropY + i + 1 >= height || board[dropY + i + 1][posX + j] != 0)) {
                    canMove = false;
                    break;
                }
            }
            if (!canMove) break;
        }
        if (canMove) dropY++;
        else break;
    }
    return dropY;
}

void handleInput() {
    static int moveCounter = 0;

    if (_kbhit()) {
        char key = _getch();
        
        if (key == 'a') { 
            if (++moveCounter % moveSpeed == 0) { 
                bool canMove = true;
                vector<vector<int>> piece = tetrominoes[currentPiece];
                for (int i = 0; i < piece.size(); i++) {
                    for (int j = 0; j < piece[i].size(); j++) {
                        if (piece[i][j] == 1) {
                            if (posX + j - 1 < 0 || board[posY + i][posX + j - 1] != 0) {
                                canMove = false;
                                break;
                            }
                        }
                    }
                }
                if (canMove) posX--; 
            }
        }

        if (key == 'd') { 
            if (++moveCounter % moveSpeed == 0) { 
                bool canMove = true;
                vector<vector<int>> piece = tetrominoes[currentPiece];
                for (int i = 0; i < piece.size(); i++) {
                    for (int j = 0; j < piece[i].size(); j++) {
                        if (piece[i][j] == 1) {
                            if (posX + j + 1 >= width || board[posY + i][posX + j + 1] != 0) {
                                canMove = false;
                                break;
                            }
                        }
                    }
                }
                if (canMove) posX++; 
            }
        }

        if (key == 's') posY++; 
        if (key == ' ') {  
            clearPiece();
            posY = findDropPosition();
            placePiece();
            drawBoard();
            Sleep(500);
            clearLines();  
            newPiece();
            return;
        }
        if (key == 'w') {  
            vector<vector<int>> rotated;
            vector<vector<int>> piece = tetrominoes[currentPiece];
            int rows = piece.size(), cols = piece[0].size();
            rotated.resize(cols, vector<int>(rows, 0));
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    rotated[j][rows - 1 - i] = piece[i][j];
                }
            }

            bool canRotate = true;
            for (int i = 0; i < rotated.size(); i++) {
                for (int j = 0; j < rotated[i].size(); j++) {
                    if (rotated[i][j] == 1) {
                        if (posX + j < 0 || posX + j >= width || posY + i >= height || board[posY + i][posX + j] != 0) {
                            canRotate = false;
                            break;
                        }
                    }
                }
            }

            if (canRotate) tetrominoes[currentPiece] = rotated;
        }
        if (key == 'r' && gameOver) {  
            board = vector<vector<int>>(height, vector<int>(width, 0));
            gameOver = false;
            score = 0;
            newPiece();
        }
    }
}


void gameLoop() {
    int fallCounter = 0;
    while (!gameOver) {
        clearPiece();
        handleInput();
        
        if (++fallCounter % fallSpeed == 0) { 
            posY++;
            fallCounter = 0;
        }

        if (posY >= findDropPosition()) { 
            clearPiece();  
            placePiece();
            drawBoard();
            Sleep(500);
            clearLines();  
            newPiece();  
            continue;
        }
        placePiece();
        drawBoard();
        Sleep(50);
    }
}

int main() {
    system("chcp 65001 > nul"); 
    srand(time(0));

    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    newPiece();
    gameLoop();
    return 0;
}
