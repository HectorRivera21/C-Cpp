#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <ctime>

using namespace std;

const int WIDTH = 40;   // Width of the game screen
const int HEIGHT = 20;  // Height of the game screen
const int MAX_ENEMIES = 5;  // Maximum number of enemies
const char PLAYER = '^';  // Character representing the player
const char ENEMY = '@';   // Character representing the enemy
const char BULLET = '|';  // Character representing the bullet

const int ENEMY_VELOCITY = 1;  // Velocity of the enemies (pixels per frame)
const int BULLET_VELOCITY = 2; // Velocity of the bullets (pixels per frame)

// Function to set the cursor position
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Function to hide the cursor
void hideCursor() {
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

// Function to draw the game screen
void drawScreen(HANDLE hConsole, char screen[HEIGHT][WIDTH]) {
    gotoxy(0, 0);
    for (int i = 0; i < HEIGHT; i++) {
        SetConsoleCursorPosition(hConsole, { 0, static_cast<SHORT>(i) });
        for (int j = 0; j < WIDTH; j++) {
            cout << screen[i][j];
        }
    }
}

// Function to update the game screen
void updateScreen(char screen[HEIGHT][WIDTH], int playerX, int enemyX[], int enemyY[], bool enemyAlive[], vector<pair<int, int>>& bullets) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == HEIGHT - 1)
                screen[i][j] = '_';  // Draw the ground
            else
                screen[i][j] = ' ';  // Clear the screen
        }
    }

    // Draw the player
    screen[HEIGHT - 2][playerX] = PLAYER;

    // Draw the enemies
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemyAlive[i] && enemyY[i] < HEIGHT - 1)
            screen[enemyY[i]][enemyX[i]] = ENEMY;
    }

    // Draw the bullets
    for (const auto& bullet : bullets) {
        int bulletX = bullet.first;
        int bulletY = bullet.second;
        if (bulletY >= 0 && bulletY < HEIGHT)
            screen[bulletY][bulletX] = BULLET;
    }

    drawScreen(GetStdHandle(STD_OUTPUT_HANDLE), screen);
}

int main() {
    char screen[HEIGHT][WIDTH];
    int playerX = WIDTH / 2;  // Starting position of the player
    int enemyX[MAX_ENEMIES] = { 5, 10, 15, 20, 25 };  // Starting positions of enemies
    int enemyY[MAX_ENEMIES] = { 0, 0, 0, 0, 0 };
    bool enemyAlive[MAX_ENEMIES] = { true, true, true, true, true };  // Initially all enemies are alive
    vector<pair<int, int>> bullets;  // Store active bullets' positions

    hideCursor();

    // Create a console window
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, 800, 600, TRUE);

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD bufferSize = { WIDTH, HEIGHT + 1 };
    SetConsoleScreenBufferSize(hConsole, bufferSize);

    // Variables for timing and frame rate control
    const double FRAME_RATE = 30.0;  // Desired frame rate
    const double FRAME_DELAY = 1000.0 / FRAME_RATE;  // Delay between frames in milliseconds
    clock_t startTime = clock();
    clock_t endTime;

    // Game loop
    while (true) {
        // Calculate the elapsed time since the last frame
        endTime = clock();
        double elapsedTime = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC;

        // Check for keyboard input
        if (_kbhit()) {
            char ch = _getch();
            if (ch == 'a' && playerX > 0)  // Move player to the left
                playerX--;
            else if (ch == 'd' && playerX < WIDTH - 1)  // Move player to the right
                playerX++;
            else if (ch == ' ')  // Shoot a bullet
                bullets.push_back({ playerX, HEIGHT - 3 });
        }

        // Move the bullets
        for (auto& bullet : bullets) {
            int& bulletX = bullet.first;
            int& bulletY = bullet.second;
            bulletY -= BULLET_VELOCITY * elapsedTime;
            if (bulletY < 0)
                bulletY = -1;  // Deactivate the bullet
        }

        // Move the enemies
        for (int i = 0; i < MAX_ENEMIES; i++) {
            if (enemyAlive[i]) {
                enemyY[i] += ENEMY_VELOCITY * elapsedTime;
                if (enemyY[i] >= HEIGHT - 1) {
                    enemyAlive[i] = false;  // Enemy reached the ground, mark as dead
                }
            }
        }

        // Update the screen
        updateScreen(screen, playerX, enemyX, enemyY, enemyAlive, bullets);

        // Control the frame rate
        double remainingTime = FRAME_DELAY - elapsedTime * 1000.0;
        if (remainingTime > 0)
            Sleep(static_cast<DWORD>(remainingTime));

        // Update the start time for the next frame
        startTime = clock();
    }

    return 0;
}
