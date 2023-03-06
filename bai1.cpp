#include<bits/stdc++.h>

using namespace std;

const int MAX_SIZE = 100; // kích thước tối đa của bảng đồ
const int MAX_MINES = 100; // số lượng mìn tối đa trên bảng đồ

int board[MAX_SIZE][MAX_SIZE]; // ma trận lưu bản đồ
bool revealed[MAX_SIZE][MAX_SIZE]; // ma trận lưu trạng thái các ô đã mở
int m, n, K; // kích thước bảng đồ và số lượng mìn

// Sinh ngẫu nhiên các vị trí của các quả mìn trên bản đồ
void generateMines() {
    int count = 0;
    while (count < K) {
        int x = rand() % m;
        int y = rand() % n;
        if (board[x][y] != -1) {
            board[x][y] = -1;
            count++;
        }
    }
}

// In ra bản đồ hiện tại, với các ô đã mở thì in số lượng mìn trong 8 ô xung quanh
void printBoard(int rows, int cols) {
    // In bản đồ ra màn hình
    cout << "  ";
    for (int i = 0; i < n; i++) cout << i << " ";
    cout << endl;
    for (int i = 0; i < m; i++) {
        cout << i << " ";
        for (int j = 0; j < n; j++) {
            if (revealed[i][j]) {
                if (board[i][j] == -1) {
                    cout << "* ";
                }
                else {
                    cout << board[i][j] << " ";
                }
            }
            else {
                cout << ". ";
            }
        }
        cout << endl;
    }
}

// Tính số lượng mìn trong 8 ô xung quanh ô (x, y)
int countMines(int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) {
                continue;
            }
            int row = x + i;
            int col = y + j;
            if (row >= 0 && row < m && col >= 0 && col < n && board[row][col] == -1) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    srand(time(NULL)); // khởi tạo seed cho hàm sinh số ngẫu nhiên

    // Nhập kích thước bảng đồ và số lượng mìn
    cout << "Nhap kich thuoc bang(m, n) va so luong min: ";
    cin >> m >> n >> K;

    // Khởi tạo bản đồ và ma trận trạng thái
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            board[i][j] = 0;
            revealed[i][j] = false;
        }
    }

    // Sinh ngẫu nhiên các vị trí của các quả mìn trên bản đồ
    generateMines();

    // Bắt đầu trò chơi
    bool gameOver = false;
    while (!gameOver) {
        printBoard(m, n);

        // Nhập tọa độ ô cần mở
        int x, y;
        cout << "Nhap toa do de mo, cach nhau boi dau cach(bat dau tu toa do 0): ";
        cin >> x >> y;

        // Kiểm tra tọa độ có hợp lệ không
        if (x < 0 || x >= m || y < 0 || y >= n) {
            cout << "Toa do khong hop le, vui long thu lai!" << endl;
            continue;
        }

        // Kiểm tra ô đã được mở chưa
        if (revealed[x][y]) {
            cout << "O da duoc mo, vui long thu lai!" << endl;
            continue;
        }

        // Mở ô và kiểm tra có trúng mìn hay không
        revealed[x][y] = true;
        if (board[x][y] == -1) {
            cout << "YOU'RE DEAD!" << endl;
            printBoard(m, n);
            gameOver = true;
        }
        else {
            // Tính số lượng mìn trong 8 ô xung quanh và gán vào ô vừa mở
            int count = countMines(x, y);
            board[x][y] = count;

            // Kiểm tra thắng cuộc
            int countUnrevealed = 0;
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (!revealed[i][j]) {
                        countUnrevealed++;
                    }
                }
            }
            if (countUnrevealed == K) {
                cout << "Chuc mung, ban da thang!!!" << endl;
                printBoard(m, n);
                gameOver = true;
            }
        }
    }

    return 0;
}
