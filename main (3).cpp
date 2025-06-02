#include <iostream>
#include <cmath>
using namespace std;

/**
 *@brief - Функция для вычисления a по заданной формуле
 *@param x - значение переменной x
 *@param y - значение переменной y
 *@param z - значение переменной z
 *@return - возвращает рассчитанное значение a
 */
double getA(const double x, const double y, const double z);

/**
 *@brief - Функция для вычисления b по заданной формуле
 *@param x - значение переменной x
 *@param y - значение переменной y
 *@param z - значение переменной z
 *@return - возвращает рассчитанное значение b
 */
double getB(const double x, const double y, const double z);

/**
 *@brief - Функция для вычисления C по заданному уравнению 
 *@param a - значение переменной a
 *@param b - значение переменной b 
 *@return - возвращает рассчитанное значение C
 */
double getC(const double a, const double b);

/**
 *@brief - Функция для вычисления D по заданному уравнению 
 *@param a - значение переменной a
 *@param b - значение переменной b 
 *@return - возвращает рассчитанное значение D
 */
double getD(const double a, const double b);

int main()
{
    // Заданные значения
    const double x = 0.29;
    const double y = 3.7;
    const double z = -1;

    // Вычисляем a и b по формулам с исправленной экспонентой
    double a = getA(x, y, z);
    double b = getB(x, y, z);

    // Выводим результаты функций C и D
    cout << "C = " << getC(a, b) << endl;
    cout << "D = " << getD(a, b) << endl;

    return 0;
}

double getA(const double x, const double y, const double z)
{
    // Исправленная формула: a = 3 * x * ln(y) + e^{z * x}
    return 3 * x * log(y) + exp(z * x);
}

double getB(const double x, const double y, const double z)
{
    // b = (|2 * y * z| / sin^2(x)) - (x^2 / 3)
    return (fabs(2 * y * z) / pow(sin(x), 2)) - (x * x / 3);
}

double getC(const double a, const double b)
{
    // Используем те же формулы из исходного кода:
    return a * a + cos(a + b) - exp(a / b);
}

double getD(const double a, const double b)
{
    return a / (b + tan(a + b)) + 25 * log(a);
}