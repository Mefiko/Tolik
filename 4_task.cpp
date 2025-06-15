#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>

using namespace std;
// y = ln(1 / (1 + 2x + x²))
/**
 * @brief Функция для вычисления y
 * @param x - входное значение
 * @return возвращает значение y или NAN при недопустимых значениях
 */
double getY(const double x);

/**
 * @brief Считывает значение с клавиатуры с проверкой ввода
 * @return введенное значение
 */
double getValue();

/**
 * @brief Проверяет корректность шага
 * @param step - шаг
 */
void checkStep(const double step);

/**
 * @brief Проверяет допустимость аргумента для функции
 * @param x - значение аргумента
 * @return true если функция не определена, false если определена
 */
bool isUndefined(const double x);
/**
 * @brief Точка входа в программу
 * @return возвращает 0, если программа выполнена верно
*/
int main() {
    setlocale(LC_ALL, "RU");

    // Ввод данных
    cout << "Введите начало интервала (xstart): ";
    double xstart = getValue();

    cout << "Введите конец интервала (xend): ";
    double xend = getValue();

    cout << "Введите шаг (step): ";
    double step = getValue();
    checkStep(step);

    cout << fixed << setprecision(6);
    cout << "x\t\ty(x)" << endl;
    cout << "---------------------" << endl;

    for (double x = xstart; x <= xend + numeric_limits<double>::epsilon(); x += step) {
        if (isUndefined(x)) {
            cout << x << "\t\t" << "Неопределенность: функция не существует" << endl;
        }
        else {
            double y = getY(x);
            if (isnan(y)) {
                cout << x << "\t\t" << "Неопределенность: результат не существует" << endl;
            }
            else {
                cout << x << "\t\t" << y << endl;
            }
        }
    }

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

void checkStep(const double step) {
    if (step <= 0) {
        cout << "Ошибка: шаг должен быть положительным" << endl;
        abort();
    }
}

bool isUndefined(const double x) {
    // Проверка знаменателя на ноль
    double denominator = 1.0 + 2.0 * x + x * x;
    return (fabs(denominator) < numeric_limits<double>::epsilon()) || denominator <= 0;
}

double getY(const double x) {
    double denominator = 1.0 + 2.0 * x + x * x;
    if (denominator <= 0) {
        return NAN;
    }
    return log(1.0 / denominator);
}