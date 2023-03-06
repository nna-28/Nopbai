#include<bits/stdc++.h>
using namespace std;

const int MAX_ROWS = 100;
const int MAX_COLS = 100;
const int MAX_MINES = 100;
const char MINE = '*';
const char COVERED = '.';
const char UNCOVERED = ' ';
const int DX[] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int DY[] = {-1, 0, 1, -1, 1, -1, 0, 1};

void initialize_board(char board[MAX_ROWS][MAX_COLS], int rows, int cols) {
    // Tạo bản đồ mìn
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            board[i][j] = COVERED;
        }
    }
}
bool is_valid_coordinate(int row, int col, int rows, int cols) {
    return row >= 0 && row < rows && col >= 0 && col < cols;
}
void place_mines(char board[MAX_ROWS][MAX_COLS], int rows, int cols, int num_mines) {
    // Đặt các quả mìn ngẫu nhiên trên bản đồ
    int mines_placed = 0;
    while (mines_placed < num_mines) {
        int x = rand() % rows;
        int y = rand() % cols;
        if (board[x][y] != MINE) {
            board[x][y] = MINE;
            mines_placed++;
        }
    }
}

void print_board(char board[MAX_ROWS][MAX_COLS], int rows, int cols) {
    // In bản đồ ra màn hình
    cout << "   ";
    for (int j = 0; j < cols; j++) {
        cout << j << " ";
    }

    cout << "   ";
    for (int j = 0; j < cols; j++) {
        cout << "  ";
    }
    cout << endl;
    for (int i = 0; i < rows; i++) {
        cout << i << "  ";
        for (int j = 0; j < cols; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << "   ";
    for (int j = 0; j < cols; j++) {
        cout << "  ";
    }
    cout << endl;
}

int count_adjacent_mines(char board[MAX_ROWS][MAX_COLS], int x, int y, int rows, int cols) {
    // Đếm số lượng quả mìn xung quanh một ô
    int count = 0;
    for (int i = 0; i < 8; i++) {
        int nx = x + DX[i];
        int ny = y + DY[i];
        if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && board[nx][ny] == MINE) {
            count++;
        }
    }
    return count;
}

void uncover_board(char board[MAX_ROWS][MAX_COLS], char visible_board[MAX_ROWS][MAX_COLS], int x, int y, int rows, int cols) {
// Mở các ô xung quanh một ô đã mở, đệ quy nếu ô mới mở không có quả mìn và chưa được mở
if (board[x][y] == MINE) {
return;
}
int count = count_adjacent_mines(board, x, y, rows, cols);
visible_board[x][y] = count + '0';
if (count > 0) {
return;
}
for (int i = 0; i < 8; i++) {
int nx = x + DX[i];
int ny = y + DY[i];
if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && visible_board[nx][ny] == COVERED) {
uncover_board(board, visible_board, nx, ny, rows, cols);
}
}
}

bool is_game_over(char board[MAX_ROWS][MAX_COLS], char visible_board[MAX_ROWS][MAX_COLS], int rows, int cols) {
// Kiểm tra xem trò chơi đã kết thúc chưa
for (int i = 0; i < rows; i++) {
for (int j = 0; j < cols; j++) {
if (board[i][j] == MINE && visible_board[i][j] == UNCOVERED) {
return true;
}
}
}
return false;
}

bool is_game_won(char board[MAX_ROWS][MAX_COLS], char visible_board[MAX_ROWS][MAX_COLS], int rows, int cols, int num_mines) {
    int num_covered = 0;
    int num_correct_board = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (board[i][j] == MINE) {
                num_correct_board++;
            }
            if (visible_board[i][j] == COVERED ) {
                num_covered++;
            }
        }
    }
    return num_correct_board == num_mines && num_covered == num_mines;
}

int main() {
int rows, cols, num_mines;
cout << "Nhap so hang, cot, bom cach nhau boi dau cach: ";
cin >> rows >> cols >> num_mines;
char board[MAX_ROWS][MAX_COLS];
char visible_board[MAX_ROWS][MAX_COLS];
srand(time(0));
initialize_board(visible_board, rows, cols);
initialize_board(board, rows, cols);
place_mines(board, rows, cols, num_mines);
print_board(visible_board, rows, cols);

while (!is_game_over(board, visible_board, rows, cols)) {
    int x, y;
    cout << "Nhap toa do (x,y) de choi: ";
    cin >> x >> y;
    if (is_valid_coordinate(x, y, rows, cols) == false) {
    cout << "Toa do sai, xin vui long nhap lai: " << endl;

} else {

        if(visible_board[x][y] != '.')
        {
            cout << "O nay da duoc nhap, vui long thu lai!" << endl;
            continue;

        }

    if (board[x][y] == MINE) {
        visible_board[x][y] = MINE;
        cout << "YOU'RE DEAD!" << endl;
        print_board(visible_board, rows, cols);

        break;
    } else {
        uncover_board(board, visible_board, x, y, rows, cols);
        print_board(visible_board, rows, cols);
    }
     if (is_game_won(board, visible_board, rows, cols, num_mines)) {
        cout << "Chuc mung, ban da thang!!!" << endl;
        print_board(visible_board, rows, cols);

        break;
     }
    }
}

return 0;
}
