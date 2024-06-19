#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <thread>

using namespace std;
using namespace cv;
using namespace chrono;
using namespace this_thread;

#define BLACK Scalar(0, 0, 0)
#define WHITE Scalar(255, 255, 255)

#define BOARD_SIZE 18   // 보드 크기
#define CELL_SIZE 40    // 한 칸 크기
#define SPACE_SIZE 25   // 여백 크기

Mat board(BOARD_SIZE * CELL_SIZE + SPACE_SIZE * 2, 
    BOARD_SIZE * CELL_SIZE + SPACE_SIZE * 2, CV_8UC3);

bool mouse_is_pressing = false;
int start_x, start_y;

bool OmokPos[BOARD_SIZE + 1][BOARD_SIZE + 1] = {false};
bool blackturn[BOARD_SIZE + 1][BOARD_SIZE + 1] = {false};
bool black_turn = true, GameOver = false;

//bool IsWin(int I, int J)
//{
//    int black_cnt = 0;
//    int white_cnt = 0;
//
//    //세로 승리조건 확인
//    for (int i = 0; i <= BOARD_SIZE + 1; i++)
//    {
//        if (OmokPos[i][J] == true && blackturn[i][J] == true)
//        {
//            black_cnt++;
//        }
//        else
//        {
//            if (black_cnt == 5)
//            {
//                cout << "흑 승리" << endl;
//                return true;
//            }
//            else if (black_cnt > 5)
//            {
//                cout << "5목 이상 둘 수 없습니다." << endl;
//                OmokPos[I][J] = false;
//                return false;
//            }
//            black_cnt = 0;
//        }
//        if (OmokPos[i][J] == true && blackturn[i][J] == false)
//        {
//            white_cnt++;
//        }
//        else
//        {
//            if (white_cnt >= 5)
//            {
//                cout << "백 승리" << endl;
//                return true;
//            }
//            white_cnt = 0;
//        }
//    }
//
//    //가로 승리조건 확인
//    for (int j = 0; j <= BOARD_SIZE + 1; j++)
//    {
//        if (OmokPos[I][j] == true && blackturn[I][j] == true)
//        {
//            black_cnt++;
//        }
//        else
//        {
//            if (black_cnt == 5)
//            {
//                cout << "흑 승리" << endl;
//                return true;
//            }
//            else if (black_cnt > 5)
//            {
//                cout << "5목 이상 둘 수 없습니다." << endl;
//                OmokPos[I][J] = false;
//                return false;
//            }
//            black_cnt = 0;
//        }
//        if (OmokPos[I][j] == true && blackturn[I][j] == false)
//        {
//            white_cnt++;
//        }
//        else
//        {
//            if (white_cnt >= 5)
//            {
//                cout << "백 승리" << endl;
//                return true;
//            }
//            white_cnt = 0;
//        }
//    }
//
//    int min = MIN(I, J);
//    int max = MAX(I, J);
//
//    //좌상방 - 우하방 승리조건 확인
//    for (int k = -min; max + k <= BOARD_SIZE + 1; k++)
//    {
//        if (OmokPos[I + k][J + k] == true && blackturn[I + k][J + k] == true)
//        {
//            black_cnt++;
//        }
//        else
//        {
//            if (black_cnt == 5)
//            {
//                cout << "흑 승리" << endl;
//                return true;
//            }
//            else if (black_cnt > 5)
//            {
//                cout << "5목 이상 둘 수 없습니다." << endl;
//                OmokPos[I][J] = false;
//                return false;
//            }
//            black_cnt = 0;
//        }
//        if (OmokPos[I + k][J + k] == true && blackturn[I + k][J + k] == false)
//        {
//            white_cnt++;
//        }
//        else
//        {
//            if (white_cnt >= 5)
//            {
//                cout << "백 승리" << endl;
//                return true;
//            }
//            white_cnt = 0;
//        }
//    }
//
//    //우상방 - 좌하방 승리조건 확인
//    int sum = I + J;
//    if (sum > BOARD_SIZE)
//    {
//        for (int k = sum - BOARD_SIZE; k <= BOARD_SIZE + 1; k++)
//        {
//            if (OmokPos[k][sum - k] == true && blackturn[k][sum - k] == true)
//            {
//                black_cnt++;
//            }
//            else
//            {
//                if (black_cnt == 5)
//                {
//                    cout << "흑 승리" << endl;
//                    return true;
//                }
//                else if (black_cnt > 5)
//                {
//                    cout << "5목 이상 둘 수 없습니다." << endl;
//                    OmokPos[I][J] = false;
//                    return false;
//                }
//                black_cnt = 0;
//            }
//            if (OmokPos[k][sum - k] == true && blackturn[k][sum - k] == false)
//            {
//                white_cnt++;
//            }
//            else
//            {
//                if (white_cnt >= 5)
//                {
//                    cout << "백 승리" << endl;
//                    return true;
//                }
//                white_cnt = 0;
//            }
//        }
//    }
//    else
//    {
//        for (int k = 0; k <= sum + 1; k++)
//        {
//            if (OmokPos[k][sum - k] == true && blackturn[k][sum - k] == true)
//            {
//                black_cnt++;
//            }
//            else
//            {
//                if (black_cnt == 5)
//                {
//                    cout << "흑 승리" << endl;
//                    return true;
//                }
//                else if (black_cnt > 5)
//                {
//                    cout << "5목 이상 둘 수 없습니다." << endl;
//                    OmokPos[I][J] = false;
//                    return false;
//                }
//                black_cnt = 0;
//            }
//            if (OmokPos[k][sum - k] == true && blackturn[k][sum - k] == false)
//            {
//                white_cnt++;
//            }
//            else
//            {
//                if (white_cnt >= 5)
//                {
//                    cout << "백 승리" << endl;
//                    return true;
//                }
//                white_cnt = 0;
//            }
//        }
//    }
//
//    return true;
//}

bool VictoryReading(int I, int J)
{
    int black_cnt = 0;
    int white_cnt = 0;

    // 세로 승리조건 확인
    for (int i = I - 5; i <= I + 5; i++) 
    {
        if (i < 0 || i > BOARD_SIZE + 1) continue;

        if (OmokPos[i][J] && blackturn[i][J]) 
            black_cnt++;
        else 
        {
            if (black_cnt == 5) 
            {
                cout << "흑 승리" << endl;
                GameOver = true;
                return true;
            }
            else if (black_cnt > 5) 
            {
                cout << "흑은 5개 이상 둘 수 없습니다." << endl;
                OmokPos[I][J] = false;
                return false;
            }
            black_cnt = 0;
        }

        if (OmokPos[i][J] && !blackturn[i][J]) 
            white_cnt++;
        else 
        {
            if (white_cnt >= 5) 
            {
                cout << "백 승리" << endl;
                GameOver = true;
                return true;
            }
            white_cnt = 0;
        }
    }

    // 가로 승리조건 확인
    for (int j = J - 5; j <= J + 5; j++) 
    {
        if (j < 0 || j > BOARD_SIZE + 1) continue;

        if (OmokPos[I][j] && blackturn[I][j]) 
        {
            black_cnt++;
        }
        else 
        {
            if (black_cnt == 5) 
            {
                cout << "흑 승리" << endl;
                GameOver = true;
                return true;
            }
            else if (black_cnt > 5) 
            {
                cout << "흑은 5개 이상 둘 수 없습니다." << endl;
                OmokPos[I][J] = false;
                return false;
            }
            black_cnt = 0;
        }

        if (OmokPos[I][j] && !blackturn[I][j]) 
        {
            white_cnt++;
        }
        else 
        {
            if (white_cnt >= 5) 
            {
                cout << "백 승리" << endl;
                GameOver = true;
                return true;
            }
            white_cnt = 0;
        }
    }

    // 좌상방 - 우하방 승리조건 확인
    for (int k = -5; k <= 5; k++) 
    {
        int x = I + k;
        int y = J + k;
        if (x < 0 || y < 0 || x > BOARD_SIZE + 1 || y > BOARD_SIZE + 1) continue;

        if (OmokPos[x][y] && blackturn[x][y]) 
            black_cnt++;
        else 
        {
            if (black_cnt == 5) 
            {
                cout << "흑 승리" << endl;
                GameOver = true;
                return true;
            }
            else if (black_cnt > 5) 
            {
                cout << "흑은 5개 이상 둘 수 없습니다." << endl;
                OmokPos[I][J] = false;
                return false;
            }
            black_cnt = 0;
        }

        if (OmokPos[x][y] && !blackturn[x][y]) 
            white_cnt++;
        else 
        {
            if (white_cnt >= 5) 
            {
                cout << "백 승리" << endl;
                GameOver = true;
                return true;
            }
            white_cnt = 0;
        }
    }

    // 우상방 - 좌하방 승리조건 확인
    for (int k = -5; k <= 5; k++) 
    {
        int x = I + k;
        int y = J - k;
        if (x < 0 || y < - 1 || x > BOARD_SIZE + 1 || y > BOARD_SIZE + 1) continue;

        if (OmokPos[x][y] && blackturn[x][y]) 
            black_cnt++;
        else 
        {
            if (black_cnt == 5) 
            {
                cout << "흑 승리" << endl;
                GameOver = true;
                return true;
            }
            else if (black_cnt > 5) 
            {
                cout << "흑은 5개 이상 둘 수 없습니다." << endl;
                OmokPos[I][J] = false;
                return false;
            }
            black_cnt = 0;
        }

        if (OmokPos[x][y] && !blackturn[x][y]) 
            white_cnt++;
        else 
        {
            if (white_cnt >= 5) 
            {
                cout << "백 승리" << endl;
                GameOver = true;
                return true;
            }
            white_cnt = 0;
        }
    }

    cout << I << ", " << J << ", " << (blackturn[I][J] ? "black" : "white") << endl;
    return true;
}

void PutDown(int x, int y)
{
    for (int i = 0; i <= BOARD_SIZE; i++)
        for (int j = 0; j <= BOARD_SIZE; j++)
            if (y > SPACE_SIZE + (i * CELL_SIZE) - CELL_SIZE / 2 && y < SPACE_SIZE + (i * CELL_SIZE) + CELL_SIZE / 2 && 
                x > SPACE_SIZE + (j * CELL_SIZE) - CELL_SIZE / 2 && x < SPACE_SIZE + (j * CELL_SIZE) + CELL_SIZE / 2)
            {
                if (OmokPos[i][j] == false) //빈 자리라면
                {
                    blackturn[i][j] = black_turn;
                    OmokPos[i][j] = true;
                    if (VictoryReading(i, j))   //착수 가능한 자리라면
                    {
                        circle(board, Point(SPACE_SIZE + (j * CELL_SIZE), SPACE_SIZE + (i * CELL_SIZE)), 
                            CELL_SIZE / 2 - 3, black_turn == true ? BLACK : WHITE, -1);
                        imshow("Omok Game", board);
                        black_turn = !black_turn;   //턴 교대
                    }
                }
                else //빈 자리가 아니라면
                    cout << "둘 수 없음" << endl;
                return;
            }
}

void mouse_callback(int event, int x, int y, int flags, void* userdata)
{
    if(!GameOver)
    {
        if (event == EVENT_LBUTTONDOWN)
        {
            mouse_is_pressing = true;
            start_x = x;
            start_y = y;
        }
        if (event == EVENT_LBUTTONUP && mouse_is_pressing == true && start_x == x && start_y == y)
        {
            mouse_is_pressing = false;
            PutDown(x, y);
        }
    }
}

void drawBoard(Mat& board) 
{
    // 배경 색
    board = Scalar(95, 180, 240);

    // 세로 선
    for (int i = 0; i <= BOARD_SIZE; ++i)
        line(board, Point(SPACE_SIZE, i * CELL_SIZE + SPACE_SIZE), 
            Point(BOARD_SIZE * CELL_SIZE + SPACE_SIZE, i * CELL_SIZE + SPACE_SIZE), 
            BLACK, 2);

    // 가로 선
    for (int j = 0; j <= BOARD_SIZE; ++j)
        line(board, Point(j * CELL_SIZE + SPACE_SIZE, SPACE_SIZE), 
            Point(j * CELL_SIZE + SPACE_SIZE, BOARD_SIZE * CELL_SIZE + SPACE_SIZE), 
            BLACK, 2);
}

int main() 
{
    namedWindow("Omok Game");
    setMouseCallback("Omok Game", mouse_callback);

    drawBoard(board);
    while (1)
    {
        imshow("Omok Game", board);
        if (waitKey(1) == 27)
            break;
    }
    return 0;
}