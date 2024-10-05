#include "raylib.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "math.h"
#include "string.h"
#include <stddef.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define SCREENWIDTH 800
#define SCREENHEIGHT 600
#define TILES 4
#define BOARDWIDTH 400
#define BOARDHEIGHT 400
#define BACKGROUND (Color){250, 248, 239, 255}
#define FOREGROUND (Color){119, 110, 101, 255}
#define COLOR_2 (Color){235, 225, 215, 255}
#define COLOR_4 (Color){232, 220, 196, 255}
#define COLOR_8 (Color){243, 178, 122, 255}
#define COLOR_16 (Color){246, 150, 100, 255}
#define COLOR_32 (Color){247, 124, 95, 255}
#define COLOR_64 (Color){245, 94, 59, 255}
#define COLOR_128 (Color){237, 207, 115, 255}
#define COLOR_256 (Color){231, 199, 95, 255}
#define COLOR_512 (Color){219, 185, 74, 255}
#define COLOR_1024 (Color){232, 193, 62, 255}
#define COLOR_2048 (Color){237, 194, 45, 255}

void initialize(int board[4][4]);
void display(int board[TILES][TILES]);

typedef enum GameScreen
{
    LOGO = 0,
    TITLE,
    GAMEPLAY,
    ENDING
} GameScreen;

void initialize(int board[TILES][TILES])
{
    for (size_t i = 0; i < TILES; i++)
    {
        for (size_t j = 0; j < TILES; j++)
        {
            board[i][j] = 0;
        }
    }
}

void randomizePositions(int board[TILES][TILES])
{
    srand(time(NULL));
    int x1 = rand() % TILES,
        y1 = rand() % TILES,
        x2 = rand() % TILES,
        y2 = rand() % TILES;

    board[x1][y1] = 2;
    board[x2][y2] = 2;
}

void randomizeNewPositions(int board[TILES][TILES])
{
    srand(time(NULL));
    bool done = false;
    do
    {
        int x1 = rand() % TILES,
            y1 = rand() % TILES;

        if (board[x1][y1] == 0)
        {
            board[x1][y1] = 2;
            done = true;
        }
    } while (!done);
}

void display(int board[TILES][TILES])
{
    for (size_t i = 0; i < TILES; i++)
    {
        for (size_t j = 0; j < TILES; j++)
        {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/* 0 2 0 2     2 2 0 0
   0 0 2 0     2 0 0 0
   0 2 0 2  -> 2 2 0 0
   2 TILES 0 0     2 TILES 0 0

   0 0 2 2     2 0 2 0    2 2 0 0
   0 0 0 2     2 0 0 0    2 0 0 0
   0 0 2 2  -> 2 0 2 0 -> 2 2 0 0
   0 0 2 TILES     2 0 TILES 0    2 TILES 0 0
*/
void left(int board[TILES][TILES])
{
    bool changeMade = false;
    // Mezclar los números
    for (size_t i = 0; i < TILES; i++)
    {
        bool zeroFound = false;
        int zeroFoundPos = 0;
        for (size_t j = 0; j < TILES; j++)
        {
            if (board[i][j] != 0)
            {
                for (size_t k = j + 1; k < TILES; k++)
                {
                    if (board[i][k] != 0 && board[i][j] != board[i][k]) 
                    {
                        break;
                    } 
                    else if (board[i][j] == board[i][k])
                    {
                        board[i][j] = board[i][j] + board[i][j];
                        board[i][k] = 0;
                        j = k;
                        changeMade = true;
                        break;
                    }
                }
            }
        }
    }

    // Mover los números
    for (size_t i = 0; i < TILES; i++)
    {
        bool zeroFound = false;
        int zeroFoundPos = 0;
        for (size_t j = 0; j < TILES; j++)
        {
            if (zeroFound && board[i][j] != 0)
            {
                board[i][zeroFoundPos] = board[i][j];
                board[i][j] = 0;
                j = zeroFoundPos;
                zeroFound = false;
                changeMade = true;
            }
            else if (!zeroFound && board[i][j] == 0)
            {
                zeroFound = true;
                zeroFoundPos = j;
            }
        }
    }
    if (changeMade) 
        randomizeNewPositions(board);
    // display(board);
}

/* 0 2 0 2     0 0 2 2
   0 0 2 0     0 0 0 2
   0 2 0 2  -> 0 0 2 2
   2 TILES 0 0     0 0 2 TILES
*/
void right(int board[TILES][TILES])
{
    bool changeMade = false;
    for (size_t i = 0; i < TILES; i++)
    {
        bool zeroFound = false;
        int zeroFoundPos = 0;
        for (ssize_t j = 3; j >= 0; j--)
        {
            if (board[i][j] != 0)
            {
                for (ssize_t k = j - 1; k >= 0; k--)
                {
                    if (board[i][k] != 0 && board[i][j] != board[i][k]) 
                    {
                        break;
                    } 
                    else if (board[i][j] == board[i][k])
                    {
                        board[i][j] = board[i][j] + board[i][j];
                        board[i][k] = 0;
                        j = k;
                        changeMade = true;
                        break;
                    }
                }
            }
        }
    }

    for (size_t i = 0; i < TILES; i++)
    {
        bool zeroFound = false;
        int zeroFoundPos = 0;
        for (ssize_t j = 3; j >= 0; j--)
        {
            if (zeroFound && board[i][j] != 0)
            {
                board[i][zeroFoundPos] = board[i][j];
                board[i][j] = 0;
                j = zeroFoundPos;
                zeroFound = false;
                changeMade = true;
            }
            else if (!zeroFound && board[i][j] == 0)
            {
                zeroFound = true;
                zeroFoundPos = j;
            }
        }
    }
    if (changeMade)
        randomizeNewPositions(board);
    // display(board);
}

void up(int board[TILES][TILES])
{
    bool changeMade = false;
    for (size_t i = 0; i < TILES; i++)
    {
        bool zeroFound = false;
        int zeroFoundPos = 0;
        for (size_t j = 0; j < TILES; j++)
        {
            if (board[j][i] != 0)
            {
                for (size_t k = j + 1; k < TILES; k++)
                {
                    if (board[k][i] != 0 && board[j][i] != board[k][i]) 
                    {
                        break;
                    } 
                    else if (board[j][i] == board[k][i])
                    {
                        board[j][i] = board[j][i] + board[j][i];
                        board[k][i] = 0;
                        j = k;
                        changeMade = true;
                        break;
                    }
                }
            }
        }
    }

    for (size_t i = 0; i < TILES; i++)
    {
        bool zeroFound = false;
        int zeroFoundPos = 0;
        for (size_t j = 0; j < TILES; j++)
        {
            if (zeroFound && board[j][i] != 0)
            {
                board[zeroFoundPos][i] = board[j][i];
                board[j][i] = 0;
                j = zeroFoundPos;
                zeroFound = false;
                changeMade = true;
            }
            else if (!zeroFound && board[j][i] == 0)
            {
                zeroFound = true;
                zeroFoundPos = j;
            }
        }
    }
    if (changeMade)
        randomizeNewPositions(board);
    // display(board);
}

void down(int board[TILES][TILES])
{
    bool changeMade = false;
    for (size_t i = 0; i < TILES; i++)
    {
        bool zeroFound = false;
        int zeroFoundPos = 0;
        for (ssize_t j = 3; j >= 0; j--)
        {
            if (board[j][i] != 0)
            {
                for (ssize_t k = j - 1; k >= 0; k--)
                {
                    if (board[k][i] != 0 && board[j][i] != board[k][i]) 
                    {
                        break;
                    } 
                    else if (board[j][i] == board[k][i])
                    {
                        board[j][i] = board[j][i] + board[j][i];
                        board[k][i] = 0;
                        j = k;
                        changeMade = true;
                        break;
                    }
                }
            }
        }
    }

    for (size_t i = 0; i < TILES; i++)
    {
        bool zeroFound = false;
        int zeroFoundPos = 0;
        for (ssize_t j = 3; j >= 0; j--)
        {
            if (zeroFound && board[j][i] != 0)
            {
                board[zeroFoundPos][i] = board[j][i];
                board[j][i] = 0;
                j = zeroFoundPos;
                zeroFound = false;
                changeMade = true;
            }
            else if (!zeroFound && board[j][i] == 0)
            {
                zeroFound = true;
                zeroFoundPos = j;
            }
        }
    }
    if (changeMade)
        randomizeNewPositions(board);
    // display(board);
}

int lerp(int start, int end, double t)
{
    return start + (end - start) * t;
}

float animate2048(float t)
{
    return t - floor(t);
}

float animate(float t)
{
    return 1 - (( 1 - t ) * ( 1 - t ));
}

void ribbon(char* text, int quantity, float timeElapsed)
{
    for (int i = 0; i < quantity + 1; i++)
    {
        int textWidth = strlen(text) * 40;
        int offset = -1 * textWidth - (SCREENWIDTH - textWidth * quantity) / quantity;
        DrawText(text,
                 lerp(offset  + offset * -i,
                      offset  + offset * -(i + 1),
                      animate2048(timeElapsed / 7.0)),
                 20,
                 40,
                 FOREGROUND);
    }
}

int main(void)
{
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "MY 2048 BABY!!!");

    GameScreen currentScreen = LOGO;

    // TODO: Initialize all required variables and load all required data here!

    int framesCounter = 0; // Useful to count frames

    SetTargetFPS(60); // Set desired framerate (frames-per-second)

    int board[TILES][TILES];
    initialize(board);
    randomizePositions(board);
    display(board);

    Vector2 clickPosition = (Vector2){0, 0};
    float timeElapsed = 0;
    enum Movement
    {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
    enum Movement m;

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        switch (currentScreen)
        {
        case LOGO:
        {
            framesCounter++; // Count frames

            if (framesCounter > 0)
            {
                currentScreen = TITLE;
            }
        }
        break;
        case TITLE:
        {
            // Press enter to change to GAMEPLAY screen
            if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
            {
                currentScreen = GAMEPLAY;
            }
        }
        break;
        case GAMEPLAY:
        {
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            {
                int x = 0, y = 0;
                clickPosition.x = GetMouseX();
                clickPosition.y = GetMouseY();

                x = MAX(0, MIN(550, clickPosition.x - 250));
                y = MAX(0, MIN(425, clickPosition.y - 125));
                printf("%f %f\n", clickPosition.x, clickPosition.y);
                printf("%d %d\n", x, y);
            }

            if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))
            {
                up(board);
                m = UP;
            }
            if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT))
            {
                left(board);
                m = LEFT;
            }
            if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN))
            {
                down(board);
                m = DOWN;
            }
            if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT))
            {
                right(board);
                m = RIGHT;
            }
            if (IsKeyPressed(KEY_ENTER))
            {
                currentScreen = ENDING;
            }
        }
        break;
        case ENDING:
        {
            // Press enter to return to TITLE screen
            if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
            {
                currentScreen = TITLE;
            }
        }
        break;
        default:
            break;
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        switch (currentScreen)
        {
        case LOGO:
        {
            // TODO: Draw LOGO screen here!
            DrawText("TIC TAC TOE", 20, 20, 40, LIGHTGRAY);
            DrawText("Cargando juego...", 290, 220, 20, GRAY);
        }
        break;
        case TITLE:
        {
            // TODO: Draw TITLE screen here!
            DrawRectangle(0, 0, SCREENWIDTH, SCREENHEIGHT, LIGHTGRAY);
            DrawText("TIC TAC TOE", 20, 20, 40, BLACK);
            DrawText("PRESS ENTER TO GO TO START", 120, 220, 20, BLACK);
        }
        break;
        case GAMEPLAY:
        {
            timeElapsed += GetFrameTime();
            // TODO: Draw GAMEPLAY screen here!
            DrawRectangle(0, 0, SCREENWIDTH, SCREENHEIGHT, BACKGROUND);
            // Cada celda es de 100 x 100
            for (size_t i = 0; i < TILES + 1; i++) // VERTICAL
            {
                DrawLine((SCREENWIDTH - BOARDWIDTH) / 2 + (BOARDWIDTH / TILES) * i,
                         100,
                         (SCREENWIDTH - BOARDWIDTH) / 2 + (BOARDWIDTH / TILES) * i,
                         BOARDWIDTH + 100,
                         FOREGROUND);
            }
            for (size_t i = 0; i < TILES + 1; i++) // HORIZONTAL
            {
                DrawLine((SCREENWIDTH - BOARDWIDTH) / 2,
                         100 + (BOARDHEIGHT / TILES) * i,
                         (SCREENWIDTH - BOARDWIDTH) / 2 + BOARDWIDTH,
                         100 + (BOARDHEIGHT / TILES) * i,
                         FOREGROUND);
            }
            for (size_t i = 0; i < TILES; i++)
            {
                for (size_t j = 0; j < TILES; j++)
                {
                    if (board[i][j] != 0)
                    {
                        char text[5];
                        Color background_squares;
                        Color foreground_squares = BACKGROUND;
                        switch (board[i][j])
                        {
                        case 2:
                            background_squares = COLOR_2;
                            foreground_squares = FOREGROUND;
                            break;
                        case 4:
                            background_squares = COLOR_4;
                            foreground_squares = FOREGROUND;
                            break;
                        case 8:
                            background_squares = COLOR_8;
                            break;
                        case 16:
                            background_squares = COLOR_16;
                            break;
                        case 32:
                            background_squares = COLOR_32;
                            break;
                        case 64:
                            background_squares = COLOR_64;
                            break;
                        case 128:
                            background_squares = COLOR_128;
                            break;
                        case 256:
                            background_squares = COLOR_256;
                            break;
                        case 512:
                            background_squares = COLOR_512;
                            break;
                        case 1024:
                            background_squares = COLOR_1024;
                            break;
                        case 2048:
                            background_squares = COLOR_2048;
                            break;
                        
                        default:
                            background_squares = (Color){0,0,0,255};
                            break;
                        }
                        switch (m)
                        {
                        case UP:
                            DrawRectangle((SCREENWIDTH - BOARDWIDTH) / 2 + (BOARDWIDTH / TILES) * j + 1,
                                      100 + (BOARDHEIGHT / TILES) * i + 1,
                                      BOARDWIDTH / TILES - 3,
                                      BOARDHEIGHT / TILES - 3,
                                      background_squares);
                            break;
                        case DOWN:
                            break;
                        case LEFT:
                            break;
                        case RIGHT:
                            break;
                        
                        default:
                            break;
                        }
                        DrawRectangle((SCREENWIDTH - BOARDWIDTH) / 2 + (BOARDWIDTH / TILES) * j + 1,
                                      100 + (BOARDHEIGHT / TILES) * i + 1,
                                      BOARDWIDTH / TILES - 3,
                                      BOARDHEIGHT / TILES - 3,
                                      background_squares);
                        sprintf(text, "%d", board[i][j]); // Convert integer to string
                        DrawText(text,
                                 (SCREENWIDTH - BOARDWIDTH) / 2 + (BOARDWIDTH / TILES) * j + (BOARDWIDTH / TILES) / 2,
                                 100 + (BOARDHEIGHT / TILES) * i + (BOARDHEIGHT / TILES) / 2 - 20,
                                 40,
                                 foreground_squares);
                    }
                }
            }
            // printf("%d\n", lerp((double) -1 * strlen("2048") * 20.0, 800, animate2048(timeElapsed / 10.0)));
            ribbon("2048", 4, timeElapsed);
            
            DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 20, 550, 30, FOREGROUND);
        }
        break;
        case ENDING:
        {
            // TODO: Draw ENDING screen here!
            DrawRectangle(0, 0, 400, 400, BLUE);
            DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);
            DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);
        }
        break;
        default:
            break;
        }

        EndDrawing();
    }

    // De-Initialization

    // TODO: Unload all loaded data (textures, fonts, audio) here!

    CloseWindow(); // Close window and OpenGL context
    return 0;
}