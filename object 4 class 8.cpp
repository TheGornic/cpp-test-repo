// object 4 class 8.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <cmath>

int main() {
    // Число калькулятора.
    double number, cur_number;
    std::string sign;

    if (!(std::cin >> number)) {
        std::cerr << "Error: Numeric operand expected" << std::endl;
    }
    else {
        cur_number = number;
        while (std::cin >> sign) {
            if (sign == "*") {
                if (std::cin >> number) {
                    cur_number *= number;
                }
                else {
                    std::cerr << "Error: Numeric operand expected" << std::endl;
                    break;
                }
            }
            else if (sign == "+") {
                if (std::cin >> number) {
                    cur_number += number;
                }
                else {
                    std::cerr << "Error: Numeric operand expected" << std::endl;
                    break;
                }
            }
            else if (sign == "-") {
                if (std::cin >> number) {
                    cur_number -= number;
                }
                else {
                    std::cerr << "Error: Numeric operand expected" << std::endl;
                    break;
                }
            }
            else if (sign == "/") {
                if (std::cin >> number) {
                    cur_number /= number;
                }
                else {
                    std::cerr << "Error: Numeric operand expected" << std::endl;
                    break;
                }
            }
            else if (sign == "**") {
                if (std::cin >> number) {
                    cur_number = std::pow(cur_number, number);
                }
                else {
                    std::cerr << "Error: Numeric operand expected" << std::endl;
                    break;
                }
            }
            else if (sign == ":") {
                if (std::cin >> number) {
                    cur_number = number;
                }
                else {
                    std::cerr << "Error: Numeric operand expected" << std::endl;
                    break;
                }
            }
            else if (sign == "=") {
                std::cout << cur_number << std::endl;
            }
            else if (sign == "q") {
                break;
            }
            else if (sign == "c") {
                cur_number = 0;
            }
            else {
                std::cerr << "Error: Unknown token " << sign << std::endl;
                break;
            }
        }
    }
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
