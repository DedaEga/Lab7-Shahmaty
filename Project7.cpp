#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <chrono>

using namespace std;
void GetInput(int& x) {
    fstream out;
    string path = "logs.txt";
    auto now = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(now);
    out.open(path, fstream::in | fstream::out | fstream::app);
#pragma warning(suppress : 4996)
    out << std::ctime(&end_time) << "Pol'zovatel' vvel: " << x << endl;
}
void GetOutput(string& outp) {
    fstream out;
    string path = "logs.txt";
    auto now = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(now);
    out.open(path, fstream::in | fstream::out | fstream::app);
#pragma warning(suppress : 4996)
    out << std::ctime(&end_time) << outp << endl;
}

// функция для определения цвета клетки
bool isColor(int x, int y) {
    return (x + y) % 2 == 0;
}

// функция для определения, угрожает ли фигура клетке
bool isThreatened(string figure, int x1, int y1, int x2, int y2) {
    if (figure == "bishop") {
        return abs(x1 - x2) == abs(y1 - y2);
    }
    else if (figure == "rook") {
        return x1 == x2 || y1 == y2;
    }
    else if (figure == "queen") {
        return abs(x1 - x2) == abs(y1 - y2) || x1 == x2 || y1 == y2;
    }
    else if (figure == "knight") {
        return (abs(x1 - x2) == 2 && abs(y1 - y2) == 1) || (abs(x1 - x2) == 1 && abs(y1 - y2) == 2);
    }
    else {
        return false;
    }
}

// функция для определения, может ли фигура достичь клетки за один ход
bool canReachInOneMove(string figure, int x1, int y1, int x2, int y2) {
    if (figure == "bishop") {
        return abs(x1 - x2) == abs(y1 - y2);
    }
    else if (figure == "rook") {
        return x1 == x2 || y1 == y2;
    }
    else if (figure == "queen") {
        return abs(x1 - x2) == abs(y1 - y2) || x1 == x2 || y1 == y2;
    }
    else {
        return false;
    }
}

// функция для определения, может ли фигура достичь клетки за два хода
bool canReachInTwoMoves(string figure, int x1, int y1, int x2, int y2) {
    if (figure == "bishop") {
        if (abs(x1 - x2) == abs(y1 - y2)) {
            // если расстояние между клетками по диагонали равно расстоянию между ферзем и клеткой (m, n) по диагонали,
            // то ферзь может попасть на клетку (m, n) за два хода, перепрыгивая через клетку (x2, y2)
            return true;
        }
        else {
            return false;
        }
    }
    else if (figure == "rook") {
        if (x1 == x2 || y1 == y2) {
            // если ферзь находится на одной вертикали или горизонтали с клеткой (m, n),
            // то он может попасть на клетку (m, n) за два хода, перепрыгивая через клетку (x2, y2)
            return true;
        }
        else {
            return false;
        }
    }
    else if (figure == "queen") {
        if (abs(x1 - x2) == abs(y1 - y2) || x1 == x2 || y1 == y2) {
            // если расстояние между клетками по диагонали равно расстоянию между ферзем и клеткой (m, n) по диагонали, или ферзь находится на одной вертикали или горизонтали с клеткой (m, n),
            // то ферзь может попасть на клетку (m, n) за два хода, перепрыгивая через клетку (x2, y2)
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

int main() {
    int k, l, m, n;
    string figure, outp;
    // вводим координаты клеток и фигуру с консоли
    outp = "Enter coordinates of the first cell (k, l): ";
    cout << outp;
    GetOutput(outp);
    cin >> k >> l;
    GetInput(k);
    GetInput(l);
    outp = "Enter coordinates of the second cell (m, n): ";
    cout << outp;
    GetOutput(outp);
    cin >> m >> n;
    GetInput(m);
    GetInput(n);
    outp = "Enter the name of the figure (bishop, rook, queen, knight): ";
    cout << outp;
    GetOutput(outp);
    cin >> figure;

    // вызываем функцию для определения цвета клеток
    bool isSameColor = isColor(k, l) == isColor(m, n);
    if (isSameColor) {
        outp = "The cells have the same color.";
        cout << outp << endl;
        GetOutput(outp);
    }
    else {
        outp = "The cells have different colors.";
        cout << outp << endl;
        GetOutput(outp);
    }

    // вызываем функцию для определения, угрожает ли фигура клетке
    bool isFigureThreatening = isThreatened(figure, k, l, m, n);
    if (isFigureThreatening) {
        outp = "The figure is threatening the cell.";
        cout << outp << endl;
        GetOutput(outp);
    }
    else {
        outp = "The figure is not threatening the cell.";
        cout << outp << endl;
        GetOutput(outp);
    }

    // вызываем функцию для определения, может ли фигура достиччь клетку за один ход
    bool OneMove = canReachInOneMove(figure, k, l, m, n);
    if (OneMove) {
        outp = "The figure can reach the cell in one move.";
        cout << outp << endl;
        GetOutput(outp);
    }
    else {
        // если фигура не может достичь клетку за один ход, то пытаемся найти клетку, через которую можно перепрыгнуть
        bool TwoMoves = false;
        int x2, y2;
        for (int i = 1; i <= 8; i++) {
            for (int j = 1; j <= 8; j++) {
                if (canReachInTwoMoves(figure, k, l, i, j) && canReachInOneMove(figure, i, j, m, n)) {
                    TwoMoves = true;
                    x2 = i;
                    y2 = j;
                    break;
                }
            }
        }
        if (canReachInTwoMoves) {
            outp = "The figure can reach the cell in two moves by jumping through the cell (";
            cout << outp << x2 << ", " << y2 << ")." << endl;
            GetOutput(outp);
        }
        else {
            outp = "The figure cannot reach the cell in two moves.";
            cout << outp << endl;
            GetOutput(outp);
        }
    }
    // выводим шахматную доску на экран
    for (int j = 8; j >= 1; j--) {
        for (int i = 1; i <= 8; i++) {
            if (i == k && j == l) {
                cout << figure[0] << " ";
            }
            else if (i == m && j == n) {
                cout << "X ";
            }
            else if (isColor(i, j)) {
                cout << "W ";
            }
            else {
                cout << "B ";
            }
        }
        cout << endl;
    }

    return 0;
}