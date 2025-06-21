#include <iostream>
#include <cmath>

using namespace std;
/**
 * @brief считывает целое число с клавиатуры с проверкой ввода
 * @return считанное значение
*/
int getValue();

/**
 * @brief считывает вещественное число с клавиатуры с проверкой ввода
 * @return считанное значение
*/
double getDouble();

/**
 * @brief проверяет, что введенное значение удовлетваряет условию n>=1
 * @param n считанное значение
*/
void checkN(const int n);

/**
 * @brief Рассчитывает сумму n первых членов ряда
 * @param n заданное число членов
 * @return сумму n первых членов ряда
*/
double sumN(const int n);

/**
 * @brief Рассчитывает следующий член ряда через рекуррентное выражение
 * @param curent текущий член ряда
 * @param i текущий индекс
 * @return следующий член ряда
*/
double getNext(const double current, const int k);

/**
 * @brief проверяет, что введенное значение удовлетваряет условию e>0
 * @param e считанное значение
*/
void checkE(const double e);

/**
 * @brief Рассчитывает сумму первых членов ряда, не превышающих по модулю e
 * @param e заданная точность
 * @return сумму первых членов ряда, не превышающих по модулю e
*/
double sumE(const double e);

/**
 * @brief Точка входа в программу
 * @return возвращает 0, если программа выполнена верно
*/
int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Введите число членов ряда для рассчета последовательности: ";
    int n = getValue();
    checkN(n);
    cout << "Сумма " << n << " членов ряда равна " << sumN(n) << endl;
    cout << "Введите погрешность для рассчета последовательности: ";
    double e = getDouble();
    checkE(e);
    cout << "Сумма членов ряда с точностью е равна " << sumE(e) << endl;;
    return 0;
}

int getValue()
{
    int value = 0;
    cin >> value;
    if (cin.fail())
    {
        cout << "Ошибка ввода" << endl;
        abort();
    }
    return value;
}

double getDouble()
{
    double value = 0.0;
    cin >> value;
    if (cin.fail())
    {
        cout << "Ошибка ввода" << endl;
        abort();
    }
    return value;
}

void checkN(const int n)
{
    if (n < 0)
    {
        cout << "Ошибка ввода" << endl;
        abort();
    }
}

double sumN(const int n)
{

    const double first = 1.0;
    double curent = first;
    double result = first;
    for (int k = 0; k <= n; k++)
    {
        curent = getNext(curent, k);
        result += curent;
    }
    return result;
}

double getNext(const double curent, const int k)
{
    double numerator = (k % 2 == 0) ? k : -k;

    // Вычисляем k! и (k+1)!
    double factorial_k = 1;
    for (int i = 2; i <= k; ++i) {
        factorial_k *= i;
    }

    double factorial_k_plus_1 = factorial_k * (k + 1);

    double denominator = factorial_k * factorial_k + factorial_k_plus_1;

    return numerator / denominator;
   ;
}

void checkE(const double e)
{
    if (e <= 0)
    {
        cout << "Ошибка ввода" << endl;
        abort();
    }
}

double sumE(const double e)
{
    const double first = 1.0;
    double curent = first;
    double result = 0.0;
    for (int k = 0; abs(curent) > e; k++) // Индекс текущего члена(a_k)   k++ // Увеличиваем после вычисления
    {
        result += curent;
        curent = getNext(curent, k); // Теперь передаем k вместо k-1

    }
    return result;
}