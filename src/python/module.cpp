//
// Created by kirill on 29.03.2025.
//
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "library/basic_math/base_operations.h"
#include "library/basic_math/linear_congruence.h"
#include "library/basic_math/diofant_equasion.h"
#include "library/basic_math/quadratic_congruence.h"
#include "library/basic_math/numbers.h"
#include "library/codes/DES.h"
#include<library/basic_math/chinese_lefts.h>
#include<python/convertions.h>
#include<vector>
namespace py = pybind11;

py::int_ py_fast_degree(const py::int_ &number, const py::int_ &degree, const py::int_ &module) {
    return string_to_pyint(fast_degree(
            pyint_to_string(number),
            pyint_to_string(degree),
            pyint_to_string(module)
    ));
}

py::int_ py_euler_slow(const py::int_ &number) {
    return string_to_pyint(euler(
            pyint_to_string(number)
    ));
}

py::int_ py_euler_def(const py::int_ &number) {
    return string_to_pyint(euler_def(
            pyint_to_string(number)
    ));
}


std::vector<py::int_> py_extended_gcd(const py::int_ &first, const py::int_ &second) {
    return strings_to_pyints(extended_gcd(
            pyint_to_string(first),
            pyint_to_string(second)
    ));
}

py::int_ py_inverse_element(const py::int_ &number, const py::int_ &module) {
    return string_to_pyint(inverse_element(
            pyint_to_string(number),
            pyint_to_string(module)
    ));
}

std::vector<py::int_> py_linear_congruence(const py::int_ &a, const py::int_ &b, const py::int_ &module) {
    return strings_to_pyints(solve_linear_congruence(
            pyint_to_string(a),
            pyint_to_string(b),
            pyint_to_string(module)
    ));
}

std::vector<py::int_> py_chinese_lefts(const std::vector<std::vector<py::int_>> &coefs) {
    std::vector<std::vector<std::string>> string_coefs = {};
    string_coefs.reserve(coefs.size());
    std::transform(
            coefs.begin(), coefs.end(),
            std::back_inserter(string_coefs),
            [](const std::vector<py::int_>& coef_vect) {
                return pyints_to_strings(coef_vect); }
            );
    return strings_to_pyints(solve_lefts(string_coefs));
}
std::vector<std::vector<py::int_>> py_diofant_equasion(const py::int_ &a, const py::int_ &b, const py::int_ &d) {

    std::vector<std::vector<std::string>> string_result = solve_diofant_equasion(
                    pyint_to_string(a),
                    pyint_to_string(b),
                    pyint_to_string(d)
            );
    std::vector<std::vector<py::int_>> result;
    std::transform(
            string_result.begin(), string_result.end(),
            std::back_inserter(result),
            [](const std::vector<std::string>& coef_vect) {
                return strings_to_pyints(coef_vect); }
            );
    return result;
}

std::vector<py::int_> py_prime_roots(const py::int_ &module) {
    return strings_to_pyints(find_prime_roots(pyint_to_string(module)));
}
std::vector<py::int_> py_quadratic_congruence(const py::int_ &a, const py::int_ &module) {
    return strings_to_pyints(solve_quadratic_congruence(pyint_to_string(a),pyint_to_string(module)));
}

std::pair<std::vector<py::int_>,std::vector<py::int_>> py_quadratic_res_and_non_res(const py::int_ &module) {
    auto result = find_quadratic_residues_nonresidues(pyint_to_string(module));
    return std::pair(strings_to_pyints(result.first),strings_to_pyints(result.second));
}

py::int_ py_generate_mernsenne_prime(const py::int_& number){
    return string_to_pyint(generate_mersenne_prime(pyint_to_string(number)));
}
py::int_ py_generate_ferma_prime(const py::int_& number){
    return string_to_pyint(generate_fermat_prime(pyint_to_string(number)));
}

py::bool_ py_fermat_test(const py::int_& n, const py::int_& iterations){
    return fermat_test(pyint_to_string(n), pyint_to_string(iterations));
}
py::bool_ py_trial_division_test(const py::int_& n){
    return trial_division_test(pyint_to_string(n));
}
py::bool_ py_miller_rabin_test(const py::int_& n,const py::int_& k){
    return miller_rabin_test(pyint_to_string(n), pyint_to_string(k));
}

std::vector<py::int_> py_fermat_factorization(const py::int_&n){
    return strings_to_pyints(fermat_factorization(pyint_to_string(n)));
}
std::vector<py::int_> py_pollard_p_minus_1_factorization(const py::int_&n,const py::int_&B){
    return strings_to_pyints(pollard_p_minus_1(pyint_to_string(n),pyint_to_string(B)));
}
std::vector<py::int_> py_pollard_rho(const py::int_&n){
    return strings_to_pyints(pollard_rho(pyint_to_string(n)));
}

PYBIND11_MODULE(crypto_learn, m) {
    m.doc() = R"doc(
        Модуль crypto_learn - набор криптографических алгоритмов и математических операций
        для работы с простыми числами, факторизации, шифрования и базовых арифметических операций.
    )doc";

    // Модуль факторизации
    auto factorize_ops = m.def_submodule("Factorize", R"doc(
        Алгоритмы факторизации чисел.

        Содержит реализации:
        - Метод факторизации Ферма
        - Алгоритм Полларда P-1
        - Алгоритм Полларда Rho
    )doc");

    factorize_ops.def("fermat_factorization", &py_fermat_factorization,
                      py::arg("number"),
                      R"doc(
            Факторизация числа методом Ферма.

            Parameters:
                number (int): Число для факторизации (должно быть нечётным составным)

            Returns:
                tuple: (p, q) такие что p*q = number

            Raises:
                ValueError: Если входное число чётное или простое
        )doc");

    factorize_ops.def("pollard_p_minus_1_factorization", &py_pollard_p_minus_1_factorization,
                      py::arg("number"),
                      py::arg("B")=py::int_(5),
                      R"doc(
            Факторизация числа алгоритмом Полларда P-1.

            Parameters:
                number (int): Число для факторизации
                B (int, optional): Граница гладкости (по умолчанию 5)

            Returns:
                int: Нетривиальный делитель числа или 1 если не найден
        )doc");

    factorize_ops.def("pollard_rho_factorization", &py_pollard_rho,
                      py::arg("number"),
                      R"doc(
            Факторизация числа алгоритмом Полларда Rho.

            Parameters:
                number (int): Число для факторизации

            Returns:
                int: Нетривиальный делитель числа
        )doc");

    // Модуль проверки на простоту
    auto prime_tests_ops = m.def_submodule("PrimeTests", R"doc(
        Тесты проверки чисел на простоту.

        Содержит:
        - Тест Ферма
        - Метод пробных делений
        - Тест Миллера-Рабина
    )doc");

    prime_tests_ops.def("fermat_test", &py_fermat_test,
                        py::arg("number"),
                        py::arg("iter_count")=py::int_(5),
                        R"doc(
            Тест Ферма на простоту числа.

            Parameters:
                number (int): Проверяемое число
                iter_count (int, optional): Количество итераций (по умолчанию 5)

            Returns:
                bool: Вероятно простое (True) или составное (False)
        )doc");

    prime_tests_ops.def("trial_division_test", &py_trial_division_test,
                        py::arg("number"),
                        R"doc(
            Проверка простоты методом пробных делений.

            Parameters:
                number (int): Проверяемое число

            Returns:
                bool: Простое (True) или составное (False)
        )doc");

    prime_tests_ops.def("miller_rabin_test", &py_miller_rabin_test,
                        py::arg("number"),
                        py::arg("k")=py::int_(5),
                        R"doc(
            Тест Миллера-Рабина на простоту числа.

            Parameters:
                number (int): Проверяемое число
                k (int, optional): Количество раундов (по умолчанию 5)

            Returns:
                bool: Вероятно простое (True) или составное (False)
        )doc");

    // Модуль генерации простых чисел
    auto prime_generates = m.def_submodule("PrimeGenerates", R"doc(
        Генерация специальных простых чисел.

        Содержит:
        - Простые числа Ферма
        - Простые числа Мерсенна
    )doc");

    prime_generates.def("fermat_prime", &py_generate_ferma_prime,
                        py::arg("n"),
                        R"doc(
            Генерация простого числа Ферма вида 2^(2^n) + 1.

            Parameters:
                n (int): Параметр генерации (0 <= n <= 4)

            Returns:
                int: Простое число Ферма

            Raises:
                ValueError: Если n не в допустимом диапазоне
        )doc");

    prime_generates.def("mersenne_prime", &py_generate_mernsenne_prime,
                        py::arg("p"),
                        R"doc(
            Генерация простого числа Мерсенна вида 2^p - 1.

            Parameters:
                p (int): Показатель степени (должен быть простым)

            Returns:
                int: Простое число Мерсенна или 0 если не простое
        )doc");

    // Модуль шифрования
    auto encodes = m.def_submodule("Encodes", R"doc(
        Алгоритмы шифрования.

        Содержит реализацию:
        - Алгоритма DES (Data Encryption Standard)
    )doc");

    py::class_<DES>(encodes, "DES", R"doc(
        Класс для шифрования/дешифрования по алгоритму DES.

        Args:
            key (str, optional): 64-битный ключ в двоичном виде (по умолчанию стандартный ключ)
    )doc")
            .def(py::init<string>(),
                 py::arg("key")="1010101010111011000010010001100000100111001101101100110011011101")
            .def("encrypt", &DES::encrypt,
                 py::arg("string_to_encode"),
                 R"doc(
                Шифрование строки.

                Parameters:
                    string_to_encode (str): Строка для шифрования

                Returns:
                    str: Зашифрованная строка
            )doc")
            .def("decrypt", &DES::decrypt,
                 py::arg("string_to_decode"),
                 R"doc(
                Дешифрование строки.

                Parameters:
                    string_to_decode (str): Строка для дешифрования

                Returns:
                    str: Расшифрованная строка
            )doc");

    // Базовые операции
    auto base_operations = m.def_submodule("BaseOperations", R"doc(
        Базовые математические операции для криптографии.

        Содержит:
        - Быстрое возведение в степень
        - Функция Эйлера
        - Расширенный алгоритм Евклида
        - Обратный элемент
        - Решение линейных и квадратичных сравнений
        - Китайская теорема об остатках
        - Решение диофантовых уравнений
        - Поиск первообразных корней
    )doc");

    base_operations.def("fast_degree", &py_fast_degree,
                        py::arg("number"),
                        py::arg("degree"),
                        py::arg("module") = py::int_(1),
                        R"doc(
            Быстрое возведение в степень по модулю.

            Parameters:
                number (int): Основание
                degree (int): Показатель степени
                module (int, optional): Модуль (по умолчанию 1)

            Returns:
                int: (number^degree) mod module
        )doc");

    base_operations.def("euler_slow", &py_euler_slow,
                        py::arg("number"),
                        R"doc(
            Вычисление функции Эйлера (медленный алгоритм).

            Parameters:
                number (int): Входное число

            Returns:
                int: Значение функции Эйлера φ(n)
        )doc");

    base_operations.def("euler_def", &py_euler_def,
                        py::arg("number"),
                        R"doc(
            Вычисление функции Эйлера через факторизацию.

            Parameters:
                number (int): Входное число

            Returns:
                int: Значение функции Эйлера φ(n)
        )doc");

    base_operations.def("extended_gcd", &py_extended_gcd,
                        py::arg("first"),
                        py::arg("second"),
                        R"doc(
            Расширенный алгоритм Евклида.

            Parameters:
                first (int): Первое число
                second (int): Второе число

            Returns:
                tuple: (НОД, x, y) такие что a*x + b*y = НОД(a,b)
        )doc");

    base_operations.def("inverse_element", &py_inverse_element,
                        py::arg("number"),
                        py::arg("module")=py::int_(1),
                        R"doc(
            Нахождение обратного элемента по модулю.

            Parameters:
                number (int): Число
                module (int, optional): Модуль (по умолчанию 1)

            Returns:
                int: Обратный элемент или 0 если не существует
        )doc");

    base_operations.def("solve_linear_congruence", &py_linear_congruence,
                        py::arg("a"),
                        py::arg("b"),
                        py::arg("module"),
                        R"doc(
            Решение линейного сравнения a*x ≡ b (mod m).

            Parameters:
                a (int): Коэффициент
                b (int): Свободный член
                module (int): Модуль

            Returns:
                list: Список решений или пустой список если нет решений
        )doc");

    base_operations.def("solve_chinese_lefts", &py_chinese_lefts,
                        py::arg("coefs"),
                        R"doc(
            Решение системы сравнений (Китайская теорема об остатках).

            Parameters:
                coefs (list): Список кортежей [(a1, m1), (a2, m2), ...]

            Returns:
                int: Решение системы или 0 если нет решения
        )doc");

    base_operations.def("solve_diofant_equasion", &py_diofant_equasion,
                        py::arg("a"),
                        py::arg("b"),
                        py::arg("d"),
                        R"doc(
            Решение диофантова уравнения a*x + b*y = d.

            Parameters:
                a (int): Коэффициент при x
                b (int): Коэффициент при y
                d (int): Свободный член

            Returns:
                tuple: (x0, y0) - частное решение или (0,0) если нет решения
        )doc");

    base_operations.def("find_prime_roots", &py_prime_roots,
                        py::arg("module"),
                        R"doc(
            Поиск первообразных корней по модулю.

            Parameters:
                module (int): Модуль (простое число)

            Returns:
                list: Список первообразных корней
        )doc");

    base_operations.def("solve_quadratic_congruence", &py_quadratic_congruence,
                        py::arg("a"),
                        py::arg("module"),
                        R"doc(
            Решение квадратичного сравнения x^2 ≡ a (mod p).

            Parameters:
                a (int): Число
                module (int): Простой модуль

            Returns:
                list: Список решений или пустой список если нет решений
        )doc");

    base_operations.def("find_quadratic_residues_and_non_residues", &py_quadratic_res_and_non_res,
                        py::arg("module"),
                        R"doc(
            Поиск квадратичных вычетов и невычетов по модулю.

            Parameters:
                module (int): Модуль

            Returns:
                tuple: (residues, non_residues) - списки вычетов и невычетов
        )doc");
}