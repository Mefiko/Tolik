#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <limits>
#include <cstdlib>
using namespace std;

/**
 * @brief Считывает значение с клавиатуры с проверкой ввода
 * @return Введенное значение
 */
double getValue();

/**
 * @brief Проверяет корректность введенного угла в радианах
 * @param radians Угол в радианах
 */
void checkAngle(double radians);

/**
 * @brief Переводит радианы в градусы, минуты и секунды
 * @param radians Угол в радианах
 * @param degrees  градусы
 * @param minutes минуты
 * @param seconds секунды
 */
void convertRadToDMS(double radians, int& degrees, int& minutes, double& seconds);

/**
 * @brief Точка входа в программу
 * @return Возвращает 0, если программа выполнена корректно
 */
int main() {
    setlocale(LC_ALL, "RU");
    cout << "Введите угол в радианах: ";
    double radians = getValue();
    checkAngle(radians);

    int degrees, minutes;
    double seconds;
    convertRadToDMS(radians, degrees, minutes, seconds);

    cout << "Результат перевода: ";
    cout << degrees << "° " << minutes << "' " << fixed << "" << seconds << "\"" << endl;

    return 0;
}

double getValue() {
    double value = 0;
    cin >> value;
    if (cin.fail()) {
        cout << "Некорректное значение" << endl;
        abort();
    }
    return value;
}

void checkAngle(double radians) {
    if (isnan(radians)) {
        cout << "Введено нечисловое значение" << endl;
        abort();
    }
}

void convertRadToDMS(double radians, int& degrees, int& minutes, double& seconds) {
    // Переводим радианы в градусы
    double totalDegrees = radians * (180.0 / M_PI);

    // Получаем целую часть градусов
        degrees = (totalDegrees);
    // Вычисляем минуты
    double remaining = (totalDegrees - degrees) * 60.0;
    minutes = remaining;

    // Вычисляем секунды
    seconds = (remaining - minutes) * 60.0;
}