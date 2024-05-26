#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include <locale>
#include <io.h>
#include <fcntl.h>

using namespace std;

// Функция для получения суммы элементов матрицы
int getSum(int** matrix, int rows, int cols) {
    int sum = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            sum += matrix[i][j];
        }
    }
    return sum;
}

// Функция для отображения матрицы
void displayMatrix(int** matrix, int rows, int cols, int color) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout, color);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            wcout << matrix[i][j] << L"\t";
        }
        wcout << endl;
    }

    SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Вернуть белый цвет
}

int main() {
    // Установим кодировку UTF-8 для корректного вывода русского текста
    SetConsoleOutputCP(CP_UTF8);
    _setmode(_fileno(stdout), _O_U16TEXT);

    // Сохранение начального состояния цвета консоли
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO start_attribute;
    GetConsoleScreenBufferInfo(hStdOut, &start_attribute);

    int N, M;
    wcout << L"Введите количество строк (N): ";
    cin >> N;
    wcout << L"Введите количество столбцов (M): ";
    cin >> M;

    // Создание матрицы
    int** A = new int* [N];
    for (int i = 0; i < N; ++i) {
        A[i] = new int[M];
    }

    srand(time(0));
    // Заполнение матрицы случайными числами
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            A[i][j] = rand() % 2000; // Случайные числа от 0 до 2000
        }
    }

    // Вывод исходной матрицы
    wcout << L"Исходная матрица:" << endl;
    displayMatrix(A, N, M, FOREGROUND_RED);

    // Вычисление суммы элементов исходной матрицы
    int initialSum = getSum(A, N, M);
    wcout << L"Сумма элементов исходной матрицы: " << initialSum << endl;

    // Преобразование элементов матрицы
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M - 1; ++j) {
            A[i][j] = A[i][j] - A[i][j + 1];
        }
    }

    // Вывод преобразованной матрицы
    wcout << L"Преобразованная матрица:" << endl;
    displayMatrix(A, N, M, FOREGROUND_GREEN);

    // Вычисление суммы элементов преобразованной матрицы
    int transformedSum = getSum(A, N, M);
    wcout << L"Сумма элементов преобразованной матрицы: " << transformedSum << endl;

    // Освобождение памяти
    for (int i = 0; i < N; ++i) {
        delete[] A[i];
    }
    delete[] A;

    // Возврат к исходному цвету консоли
    SetConsoleTextAttribute(hStdOut, start_attribute.wAttributes);

    return 0;
}
