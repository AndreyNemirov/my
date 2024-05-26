#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include <locale>
#include <io.h>
#include <fcntl.h>

using namespace std;

// ������� ��� ��������� ����� ��������� �������
int getSum(int** matrix, int rows, int cols) {
    int sum = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            sum += matrix[i][j];
        }
    }
    return sum;
}

// ������� ��� ����������� �������
void displayMatrix(int** matrix, int rows, int cols, int color) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout, color);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            wcout << matrix[i][j] << L"\t";
        }
        wcout << endl;
    }

    SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // ������� ����� ����
}

int main() {
    // ��������� ��������� UTF-8 ��� ����������� ������ �������� ������
    SetConsoleOutputCP(CP_UTF8);
    _setmode(_fileno(stdout), _O_U16TEXT);

    // ���������� ���������� ��������� ����� �������
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO start_attribute;
    GetConsoleScreenBufferInfo(hStdOut, &start_attribute);

    int N, M;
    wcout << L"������� ���������� ����� (N): ";
    cin >> N;
    wcout << L"������� ���������� �������� (M): ";
    cin >> M;

    // �������� �������
    int** A = new int* [N];
    for (int i = 0; i < N; ++i) {
        A[i] = new int[M];
    }

    srand(time(0));
    // ���������� ������� ���������� �������
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            A[i][j] = rand() % 2000; // ��������� ����� �� 0 �� 2000
        }
    }

    // ����� �������� �������
    wcout << L"�������� �������:" << endl;
    displayMatrix(A, N, M, FOREGROUND_RED);

    // ���������� ����� ��������� �������� �������
    int initialSum = getSum(A, N, M);
    wcout << L"����� ��������� �������� �������: " << initialSum << endl;

    // �������������� ��������� �������
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M - 1; ++j) {
            A[i][j] = A[i][j] - A[i][j + 1];
        }
    }

    // ����� ��������������� �������
    wcout << L"��������������� �������:" << endl;
    displayMatrix(A, N, M, FOREGROUND_GREEN);

    // ���������� ����� ��������� ��������������� �������
    int transformedSum = getSum(A, N, M);
    wcout << L"����� ��������� ��������������� �������: " << transformedSum << endl;

    // ������������ ������
    for (int i = 0; i < N; ++i) {
        delete[] A[i];
    }
    delete[] A;

    // ������� � ��������� ����� �������
    SetConsoleTextAttribute(hStdOut, start_attribute.wAttributes);

    return 0;
}
