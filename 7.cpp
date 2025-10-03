#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <algorithm>
#include <vector>
using namespace std;

enum Array
{
    FArray = 1,
    FRandom = 2,
};

/*
 *@brief - Получение целого числа от пользователя
 *@return - возвращает рассчитанное значение
*/
int getValue();
/*
 *@brief - Получение размера массива
*/
size_t getSize();
/*
 *@brief -  Проверка корректности размера массива
 *@param n - не меняющийся целое число
*/
void checkN(const int n);
/*
 *@brief - Создание двумерного массива
 *@param rows - количество строк
 *@param cols - количество столбцов
 *@return указатель на созданный массив
*/
int** create2DArray(const size_t rows, const size_t cols);
/*
 *@brief - Удаление двумерного массива
 *@param arr - указатель на массив
 *@param rows - количество строк
*/
void delete2DArray(int** arr, const size_t rows);
/*
 *@brief - Заполнение массива вручную
 *@param arr - указатель на массив
 *@param rows - количество строк
 *@param cols - количество столбцов
*/
void fill2DArray(int** arr, const size_t rows, const size_t cols);
/*
 *@brief - Заполнение массива случайными числами
 *@param arr - указатель на массив
 *@param rows - количество строк
 *@param cols - количество столбцов
 *@param min_r - минимальное значение диапазона
 *@param max_r - максимальное значение диапазона
*/
void fill2DArrayRandom(int** arr, const size_t rows, const size_t cols, int min_r, int max_r);
/*
 *@brief - Вывод массива на экран
 *@param arr - указатель на массив
 *@param rows - количество строк
 *@param cols - количество столбцов
*/
void print2DArray(int** arr, const size_t rows, const size_t cols);
/*
 *@brief - Копирование двумерного массива
 *@param source - исходный массив
 *@param rows - количество строк
 *@param cols - количество столбцов
 *@return указатель на новый массив
*/
int** copy2DArray(int** source, const size_t rows, const size_t cols);

// Функции для варианта 16
/*
 *@brief - Замена четных элементов каждой строки нулями
 *@param arr - указатель на массив
 *@param rows - количество строк
 *@param cols - количество столбцов
*/
void replaceEvenWithZero(int** arr, const size_t rows, const size_t cols);
/*
 *@brief - Вставка строк после строк с минимальным значением
 *@param arr - указатель на массив
 *@param rows - количество строк (изменяемый параметр)
 *@param cols - количество столбцов
 *@return указатель на новый массив
*/
int** insertRowsAfterMin(int** arr, size_t& rows, const size_t cols);

int main() {
    setlocale(LC_ALL, "Russian");

    // 1. Получаем размеры массива
    cout << "Введите количество строк: ";
    size_t rows = getSize();
    cout << "Введите количество столбцов: ";
    size_t cols = getSize();

    // 2. Создаем массив
    int** arr = create2DArray(rows, cols);

    // 3. Выбор способа заполнения
    cout << "Выберите способ заполнения массива:\n";
    cout << FArray << " Вручную\n";
    cout << FRandom << " Случайными числами\n";
    cout << "Ваш выбор: ";

    int choice;
    cin >> choice;
    int min_r = 0, max_r = 0;
    // 4. Заполнение массива
    switch (choice) {
    case FArray:
        fill2DArray(arr, rows, cols);
        break;
    case FRandom:
        cout << "Введите минимальное значение диапазона: ";
        min_r = getValue();
        cout << "Введите максимальное значение диапазона: ";
        max_r = getValue();
        fill2DArrayRandom(arr, rows, cols, min_r, max_r);
        break;
    default:
        cout << "Неверный выбор!" << endl;
        delete2DArray(arr, rows);
        return 1;
    }

    // Вывод исходного массива
    cout << "\nИсходный массив:" << endl;
    print2DArray(arr, rows, cols);

    // 1. Замена четных элементов нулями
    int** arrCopy1 = copy2DArray(arr, rows, cols);
    replaceEvenWithZero(arrCopy1, rows, cols);
    cout << "\nПосле замены четных элементов нулями:" << endl;
    print2DArray(arrCopy1, rows, cols);

    // 2. Вставка строк после строк с минимальным значением
    size_t newRows = rows;
    int** arrCopy2 = insertRowsAfterMin(arr, newRows, cols);
    cout << "\nПосле вставки строк:" << endl;
    print2DArray(arrCopy2, newRows, cols);

    // Освобождение памяти
    delete2DArray(arr, rows);
    delete2DArray(arrCopy1, rows);
    delete2DArray(arrCopy2, newRows);

    return 0;
}

// Реализация функций для работы с двумерным массивом

int** create2DArray(const size_t rows, const size_t cols) {
    int** arr = new int* [rows];
    for (size_t i = 0; i < rows; i++) {
        arr[i] = new int[cols];
    }
    return arr;
}

void delete2DArray(int** arr, const size_t rows) {
    for (size_t i = 0; i < rows; i++) {
        delete[] arr[i];
    }
    delete[] arr;
}

void fill2DArray(int** arr, const size_t rows, const size_t cols) {
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            cout << "Введите элемент [" << i << "][" << j << "]: ";
            arr[i][j] = getValue();
        }
    }
}

void fill2DArrayRandom(int** arr, const size_t rows, const size_t cols, int min_r, int max_r) {
    srand(time(0));
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            arr[i][j] = min_r + rand() % (max_r - min_r + 1);
        }
    }
}

void print2DArray(int** arr, const size_t rows, const size_t cols) {
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            cout << arr[i][j] << "\t";
        }
        cout << endl;
    }
}

int** copy2DArray(int** source, const size_t rows, const size_t cols) {
    int** copy = create2DArray(rows, cols);
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            copy[i][j] = source[i][j];
        }
    }
    return copy;
}

// Реализация функций для варианта 16

void replaceEvenWithZero(int** arr, const size_t rows, const size_t cols) {
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (arr[i][j] % 2 == 0) {
                arr[i][j] = 0;
            }
        }
    }
}

int** insertRowsAfterMin(int** arr, size_t& rows, const size_t cols) {
    // Находим минимальное значение в массиве
    int minVal = arr[0][0];
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (arr[i][j] < minVal) {
                minVal = arr[i][j];
            }
        }
    }

    // Находим строки с минимальным значением
    vector<size_t> rowsWithMin;
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (arr[i][j] == minVal) {
                rowsWithMin.push_back(i);
                break;
            }
        }
    }

    // Создаем новый массив с дополнительными строками
    size_t newRows = rows + rowsWithMin.size();
    int** newArr = create2DArray(newRows, cols);

    size_t newRow = 0;
    for (size_t i = 0; i < rows; i++) {
        // Копируем текущую строку
        for (size_t j = 0; j < cols; j++) {
            newArr[newRow][j] = arr[i][j];
        }
        newRow++;

        // Проверяем, нужно ли вставить новую строку после этой
        for (size_t k = 0; k < rowsWithMin.size(); k++) {
            if (i == rowsWithMin[k]) {
                // Вставляем строку 1, 2, 3, ...
                for (size_t j = 0; j < cols; j++) {
                    newArr[newRow][j] = j + 1;
                }
                newRow++;
                break;
            }
        }
    }

    rows = newRows;
    return newArr;
}

int getValue() {
    int value = 0;
    cin >> value;
    if (cin.fail()) {
        cout << "Ошибка ввода" << endl;
        abort();
    }
    return value;
}

size_t getSize() {
    int n = getValue();
    checkN(n);
    return (size_t)n;
}

void checkN(const int n) {
    if (n <= 0) {
        cout << "Размер массива должен быть положительным" << endl;
        abort();
    }
}