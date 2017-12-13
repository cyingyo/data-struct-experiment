//
// Created by samson on 17-11-29.
//
#include "iostream"
#include "map"
#include "../stack/arrayStack.h"
#include "../queue/array_queue.h"

using namespace std;

map<char, int> symp;

int getNumber(char a) {
    switch(a) {
        case '1' :
            return 1;
        case '2' :
            return 2;
        case '3' :
            return 3;
        case '4' :
            return 4;
        case '5' :
            return 5;
        case '6' :
            return 6;
        case '7' :
            return 7;
        case '8' :
            return 8;
        case '9' :
            return 9;
        case '0' :
            return 0;
        default:
            return -1;
    }
}

int doCal(int one, char mid, int two) {
    switch (mid) {
        case '+' :
            return one + two;
        case '-' :
            return one - two;
        case '*' :
            return one * two;
        case '/' :
            return one / two;
        default:
            return 0;
    }
}

void caculate(const char* inputs, int len) {
    cout << "��Ҫ����ı��ʽΪ:" << inputs << endl;
    symp['('] = 0;
    symp[')'] = 0;
    symp['+'] = 1;
    symp['-'] = 1;
    symp['*'] = 2;
    symp['/'] = 2;

    ArrayStack<int> nums(len);
    ArrayStack<char> sy(len);
    for (int i = 0; i < len; ++i) {
        char ele = inputs[i];
        if (getNumber(ele) != -1) nums.push(getNumber(ele)); //��������֣�ѹ������ջ
        else {
            if (sy.isEmpty()) sy.push(ele); //����ջΪ�գ�ֱ��ѹ��
            else if (ele == '(') sy.push(ele); //����������ʱ�����ж������ȼ���ֱ��ѹ��
            else { //�ж����ȼ�
                if (symp[ele] > symp[sy.top()]) sy.push(ele); //���ȼ�����ջ��Ԫ��

                else { //���ȼ����ڻ�С��ջ��Ԫ�أ��������з��ţ���������
                    while (! sy.isEmpty()) {
                        char mid = sy.pop();
                        if (mid == '(') break; //������������ţ�ֹͣ��ջ

                        int two = nums.pop();
                        int one = nums.pop();
                        int ans = doCal(one, mid, two);
                        nums.push(ans);
                    }

                    if (ele != ')') sy.push(ele);
                }
            }
        }
    }

    while (! sy.isEmpty()) {
        char mid = sy.pop();
        int two = nums.pop();
        int one = nums.pop();
        int ans = doCal(one, mid, two);
        nums.push(ans);
    }
    cout << "�������㣬���Ϊ:" << nums.top() << endl;
}


struct Position {

    Position() {}
    Position(int r, int c) {
        row = r;
        col = c;
    }

    int row;
    int col;
};

bool findMazePath(int **maze, int rowSize, int colSize) {
    int row = rowSize - 2;
    int col = colSize - 2;

    auto path = new ArrayStack<Position>();

    Position offset[4];
    offset[0].row = 0; offset[0].col = 1;   //right
    offset[1].row = 1; offset[1].col = 0;   //down
    offset[2].row = 0; offset[2].col = -1;  //left
    offset[3].row = -1; offset[3].col = 0;  //up

    Position here(1, 1);
    *((int*)maze + rowSize*1 + 1) = 2;//    maze[1][1] = 1;
    int option = 0;
    int lastOption = 3;

    while (here.row != row || here.col != col) {
        int r, c;
        while (option <= lastOption) {
            r = here.row + offset[option].row;
            c = here.col + offset[option].col;
            if (*((int*)maze + rowSize*r + c) == 0) break;
            option++;
        }

        if (option <= lastOption) {
            path->push(here);
            here.row = r;
            here.col = c;
            *((int*)maze + rowSize*r + c) = 2;
            option = 0;
        } else {
            *((int*)maze + rowSize*here.row + here.col) = 9;
            if (path->isEmpty()) {
                cout << "û����ȷ·���߳����Թ�!" << endl;
                return false;
            }
            Position next = path->pop();
            if (next.row == here.row) option = next.col - here.col + 2; //�ж�here ��������λ��
            else option = next.row - here.row + 3;
            here = next;
        }
    }

    cout << "�ɹ��߳��Թ���" << endl;
    for (int i = 1; i <= row; ++i) {
        for (int j = 1; j <= col; ++j) {
            cout << *((int*)maze + rowSize*i + j) << " ";
        }
        cout << endl;
    }

//    cout << endl << "�Թ�·��Ϊ��" << endl;
//    cout << "(" << row << ", " << col << ")" << endl;
//    while (!path->isEmpty()) {
//        Position o = path->pop();
//        cout << "(" << o.row << ", " << o.col << ")" << endl;
//    }
    return true;
}

void inputMazePath() {
    int rowSize;
    int colSize;
    cout << "�������Թ���������";
    cin >> rowSize;
    cout << "�������Թ���������";
    cin >> colSize;

    int row = rowSize;
    int col = colSize;
    rowSize += 2;
    colSize += 2;
    int maze[rowSize][colSize];

    for (int i = 0; i < rowSize; ++i) {
        maze[i][0] = 1;
        maze[i][colSize-1] = 1;
    }
    for (int j = 0; j < colSize; ++j) {
        maze[0][j] = 1;
        maze[rowSize-1][j] = 1;
    }

    for (int k = 1; k <= row; ++k) {
        for (int i = 1; i <= col; ++i) {
            cin >> maze[k][i];
        }
    }

    findMazePath((int**)maze, rowSize, colSize);
}

bool findMinPath(int **grid, Position start, Position end, int rowSize, int colSize) {

    int row = rowSize - 2;
    int col = colSize - 2;

    Position offset[4];
    offset[0].row = 0; offset[0].col = 1;   //right
    offset[1].row = 1; offset[1].col = 0;   //down
    offset[2].row = 0; offset[2].col = -1;  //left
    offset[3].row = -1; offset[3].col = 0;  //up

    Position here = start;
    *((int*)grid + rowSize*here.row + here.col) = 2;
    int neibor = 4;
    ArrayQueue<Position> wait(row * col);
    while (here.row != end.row && here.col != end.col) {
        for (int i = 0; i < neibor; ++i) {
            int r = here.row + offset[i].row;
            int c = here.col + offset[i].col;

            if (*((int *) grid + rowSize * r + c) == 0 ||
                (*((int *) grid + rowSize * here.row + here.col) + 1 < *((int *) grid + rowSize * r + c)))
                *((int *) grid + rowSize * r + c) = *((int *) grid + rowSize * here.row + here.col) + 1;

            Position in(r, c);
            wait.push(in);
        }

        if (wait.isEmpty()) {
            cout << "����㵽�յ�û��·��" << endl;
            return false;
        }
        here = wait.pop();
    }

    cout << "�ҵ����·��" << endl;
    for (int j = 0; j < row; ++j) {
        for (int i = 0; i < col; ++i) {
            cout << *((int *) grid + rowSize * i + j) << " ";
        }
        cout << endl;
    }
}