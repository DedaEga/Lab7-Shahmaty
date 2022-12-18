#include <iostream>
#include <string>

using namespace std;

// функция для определения цвета клетки
bool isWhite(int x, int y) {
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
    string figure;
    // вводим координаты клеток и фигуру с консоли
    cout << "Enter coordinates of the first cell (k, l): ";
    cin >> k >> l;
    cout << "Enter coordinates of the second cell (m, n): ";
    cin >> m >> n;
    cout << "Enter the name of the figure (bishop, rook, queen, knight): ";
    cin >> figure;

    // вызываем функцию для определения цвета клеток
    bool isSameColor = isWhite(k, l) == isWhite(m, n);
    if (isSameColor) {
        cout << "The cells have the same color." << endl;
    }
    else {
        cout << "The cells have different colors." << endl;
    }

    // вызываем функцию для определения, угрожает ли фигура клетке
    bool isFigureThreatening = isThreatened(figure, k, l, m, n);
    if (isFigureThreatening) {
        cout << "The figure is threatening the cell." << endl;
    }
    else {
        cout << "The figure is not threatening the cell." << endl;
    }

    // вызываем функцию для определения, может ли фигура достиччь клетку за один ход
    bool OneMove = canReachInOneMove(figure, k, l, m, n);
    if (OneMove) {
        cout << "The figure can reach the cell in one move." << endl;
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
            cout << "The figure can reach the cell in two moves by jumping through the cell (" << x2 << ", " << y2 << ")." << endl;
        }
        else {
            cout << "The figure cannot reach the cell in two moves." << endl;
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
            else if (isWhite(i, j)) {
                cout << "# ";
            }
            else {
                cout << "# ";
            }
        }
        cout << endl;
    }

    return 0;
}