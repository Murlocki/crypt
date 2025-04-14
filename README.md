🔐 crypto_learn
crypto_learn — это модуль на C++ с обёрткой на Python с помощью pybind11, предоставляющий набор криптографических алгоритмов, методов факторизации, генерации простых чисел, тестов на простоту и базовых математических операций.

📦 Возможности
Модуль разбит на тематические подмодули:

🧮 BaseOperations
Базовые математические операции, используемые в криптографии:

Быстрое возведение в степень fast_degree

Функция Эйлера euler_slow, euler_def

Расширенный алгоритм Евклида extended_gcd

Обратный элемент по модулю inverse_element

Решение линейных сравнений solve_linear_congruence

Китайская теорема об остатках solve_chinese_lefts

Диофантовы уравнения solve_diofant_equasion

Первообразные корни find_prime_roots

Квадратичные сравнения solve_quadratic_congruence

Квадратичные вычеты и невычеты find_quadratic_residues_and_non_residues

🔢 Factorize
Алгоритмы факторизации:

Метод Ферма fermat_factorization

Поллард P-1 pollard_p_minus_1_factorization

Поллард Rho pollard_rho_factorization

🔍 PrimeTests
Тесты на простоту:

Тест Ферма fermat_test

Метод пробных делений trial_division_test

Тест Миллера-Рабина miller_rabin_test

🔢 PrimeGenerates
Генерация простых чисел:

Числа Ферма fermat_prime

Числа Мерсенна mersenne_prime

🔐 Encodes
Алгоритмы шифрования:

DES: реализация шифра Data Encryption Standard с методами encrypt и decrypt

🚀 Установка и сборка
Требования
Python ≥ 3.8

C++17 совместимый компилятор

pybind11

CMake

Сборка вручную
bash
Копировать
Редактировать
git clone https://github.com/Murlocki/crypt.git
cd crypt
mkdir build && cd build
cmake ..
make
Или установите как Python-модуль с помощью setup.py (если добавлен).

🧪 Примеры использования
python
Копировать
Редактировать
import crypto_learn

# Факторизация числа
p, q = crypto_learn.Factorize.fermat_factorization(5959)
print(p, q)  # -> 59, 101

# Проверка на простоту
is_prime = crypto_learn.PrimeTests.miller_rabin_test(101)
print(is_prime)  # -> True

# Шифрование строки с помощью DES
cipher = crypto_learn.Encodes.DES()
enc = cipher.encrypt("hello")
dec = cipher.decrypt(enc)
print(enc, dec)  # -> '...' 'hello'

# Поиск первообразных корней
roots = crypto_learn.BaseOperations.find_prime_roots(17)
print(roots)  # -> [3, 5, 6, 7, 10, 11, 12, 14]
