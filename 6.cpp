#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <algorithm>
using namespace std;

enum Array
{
    FArray = 1,
    FRandom = 2
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
 *@brief - Заполнение массива вручную
 *@param arr - указатель на массив
 *@param n - не меняющийся целое число
*/
void fillArray(int* arr, const int n);
/*
 *@brief - Заполнение массива случайными числами
 *@param arr - указатель на массив
 *@param n - не меняющийся целое число
 *@param min_r - минимальное значение диапазона
 *@param max_r - максимальное значение диапазона
*/
void fillArrayRandom(int* arr, const int n, int min_r, int max_r);
/*
 *@brief - Вывод массива на экран
 *@param arr - указатель на массив
 *@param n - не меняющийся целое число
*/
void printArray(int* arr, const int n);

/*
 *@brief - Замена предпоследнего элемента на максимальный по модулю
 *@param copiedArr - указатель на массив
 *@param n - не меняющийся целое число
*/
void replacePenultimateWithMaxAbsolute(int* copiedArr, const int n);
/*
 *@brief - Подсчет элементов, кратных заданному числу N
 *@param arr - указатель на массив
 *@param n - не меняющийся целое число
 *@param N - заданное число для проверки кратности
 *@return Количество элементов, кратных N
*/
int countMultiplesOfN(int* arr, const int n, int N);
/*
 *@brief - Найти номер первой пары соседних элементов с разными знаками
 *@param arr - указатель на массив
 *@param n - не меняющийся целое число
 *@return Номер первой пары или -1, если такой пары нет
*/
int findFirstPairWithDifferentSigns(int* arr, const int n);
/*
 * @brief - Проверка корректности диапазона значений
 * @param min_r - минимальное значение
 * @param max_r - максимальное значение
 */
void checkRange(int min_r, int max_r);
/**
 * @brief Копирует элементы из одного массива в другой
 * @param source - исходный массив
 * @param copySource - массив для копирования
 * @param n - количество элементов для копирования
 */
void copyArray(int* sourse, int* copysourse, const size_t n);
/**
 * @brief Точка входа в программу
 * @return возвращает 0, если программа выполнена верно
*/
int main() {
    setlocale(LC_ALL, "Russian"); // Устанавливаем русскую локаль

    // 1. Получаем и проверяем размер массива
    size_t n = getSize();  // Запрашиваем размер у пользователя
    checkN(n);             // Проверяем корректность размера

    // 2. Создаем динамические массивы
    int* arr = new int[n];        // Основной массив
    int* copiedArr = new int[n];  // Копия для операций

    // 3. Выбор способа заполнения массива
    cout << "Выберите способ заполнения массива:\n";
    cout << FArray << "Вручную\n";
    cout << FRandom << "Случайными числами\n";
    cout << "Ваш выбор: ";
    int choice;
    cin >> choice;
    int min_r = 0, max_r = 0;
    // 4. Обработка выбора пользователя
    switch (choice) {
    case FArray:
        fillArray(arr, n);  // Заполняем вручную
        break;
    case FRandom:
        // Запрашиваем диапазон для случайных чисел
        
        cout << "Введите минимальное значение диапазона: ";
        min_r = getValue();
        cout << "Введите максимальное значение диапазона: ";
        max_r = getValue();
        checkRange(min_r, max_r); // Проверяем корректность диапазона
        fillArrayRandom(arr, n, min_r, max_r); // Заполняем случайными числами
        break;
    default:
        cout << "Неверный выбор!" << endl;
        delete[] arr;       // Освобождаем память
        delete[] copiedArr; // перед выходом
        return 1;           // Выход с ошибкой
    }

    // 5. Копируем массив для операций
    copyArray(arr, copiedArr, n);

    // 6. Выводим исходный массив
    cout << "Исходный массив: " << endl;
    printArray(arr, n);

    // 7. Замена предпоследнего элемента на максимальный по модулю
    replacePenultimateWithMaxAbsolute(copiedArr, n);
    cout << "После замены предпоследнего на максимальный по модулю: " << endl;
    printArray(copiedArr, n);

    // 8. Подсчет элементов, кратных заданному числу N
    cout << "Введите число N для проверки кратности: ";
    int N = getValue();
    int count = countMultiplesOfN(arr, n, N);
    cout << "Количество элементов, кратных " << N << ": " << count << endl;

    // 9. Поиск первой пары соседних элементов с разными знаками
    int pairIndex = findFirstPairWithDifferentSigns(arr, n);
    if (pairIndex != -1) {
        cout << "Первая пара соседних элементов с разными знаками найдена на позиции: " << pairIndex << endl;
    }
    else {
        cout << "В массиве нет пар соседних элементов с разными знаками." << endl;
    }

    // 10. Освобождаем память
    delete[] arr;
    delete[] copiedArr;

    return 0; // !!
}

// Функция для получения целого числа от пользователя
int getValue() {
    int value = 0;
    cin >> value;
    if (cin.fail()) { // Проверка на ошибку ввода
        cout << "Ошибка ввода" << endl;
        abort(); // Аварийное завершение
    }
    return value;
}

// Функция для получения размера массива
size_t getSize() {
    cout << "Введите размер массива:" << endl;
    int n = getValue(); // Получаем число
    checkN(n);          // Проверяем корректность
    return (size_t)n;   // Преобразуем в size_t
}

// Проверка корректности размера массива
void checkN(const int n) {
    if (n <= 0) {
        cout << "Размер массива должен быть положительным" << endl;
        abort();
    }
}

// Проверка корректности диапазона
void checkRange(int min_r, int max_r) {
    if (min_r >= max_r) {
        cout << "Ошибка: минимальное значение должно быть меньше максимального!" << endl;
        abort();
    }
}

// Ручное заполнение массива
void fillArray(int* arr, const int n) {
    for (size_t i = 0; i < n; i++) {
        cout << "Введите элемент " << i + 1 << ": ";
        arr[i] = getValue(); // Получаем каждый элемент
    }
}

// Случайное заполнение массива
void fillArrayRandom(int* arr, const int n, int min_r, int max_r) {
    srand(time(0)); // Инициализация генератора случайных чисел
    for (size_t i = 0; i < n; i++) {
        // Генерация числа в заданном диапазоне
        arr[i] = min_r + rand() % (max_r - min_r + 1);
    }
}

// Вывод массива
void printArray(int* arr, const int n) {
    for (size_t i = 0; i < n; i++) {
        cout << arr[i] << " "; // Выводим элементы через пробел
    }
    cout << endl; // Переход на новую строку
}

// Копирование массива
void copyArray(int* source, int* copysource, const size_t n) {
    for (size_t i = 0; i < n; i++) {
        copysource[i] = source[i]; // Копируем поэлементно
    }
}

// Замена предпоследнего элемента на максимальный по модулю
void replacePenultimateWithMaxAbsolute(int* copiedArr, const int n) {
    if (n < 2) return; // Проверка на минимальный размер массива

    int maxAbsIndex = 0;
    for (size_t i = 1; i < n; i++) {
        if (abs(copiedArr[i]) > abs(copiedArr[maxAbsIndex])) {
            maxAbsIndex = i;
        }
    }

    // Замена предпоследнего элемента
    copiedArr[n - 2] = copiedArr[maxAbsIndex];
}

// Подсчет элементов, кратных заданному числу N
int countMultiplesOfN(int* arr, const int n, int N) {
    if (N == 0) {
        cout << "Ошибка: деление на ноль!" << endl;
        return 0;
    }

    int count = 0;
    for (size_t i = 0; i < n; i++) {
        if (arr[i] % N == 0) {
            count++;
        }
    }
    return count;
}

// Найти номер первой пары соседних элементов с разными знаками
int findFirstPairWithDifferentSigns(int* arr, const int n) {
    for (size_t i = 0; i < n - 1; i++) {
        if ((arr[i] > 0 && arr[i + 1] < 0) || (arr[i] < 0 && arr[i + 1] > 0)) {
            return i; // Возвращаем индекс первого элемента пары
        }
    }
    return -1; // Пара не найдена
}