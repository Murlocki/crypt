# 🔐 crypto_learn
crypto_learn — это модуль на C++ с обёрткой на Python с помощью pybind11, предоставляющий набор криптографических алгоритмов, методов факторизации, генерации простых чисел, тестов на простоту и базовых математических операций.

## 📦 Возможности
Модуль разбит на тематические подмодули:

### 🧮 BaseOperations
Базовые математические операции, используемые в криптографии:

- Быстрое возведение в степень `fast_degree`

- Функция Эйлера `euler_slow`, `euler_def`

- Расширенный алгоритм Евклида `extended_gcd`

- Обратный элемент по модулю `inverse_element`

- Решение линейных сравнений `solve_linear_congruence`

- Китайская теорема об остатках `solve_chinese_lefts`

- Диофантовы уравнения `solve_diofant_equasion`

- Первообразные корни `find_prime_roots`

- Квадратичные сравнения `solve_quadratic_congruence`

- Квадратичные вычеты и невычеты `find_quadratic_residues_and_non_residues`

### 🔢 Factorize
Алгоритмы факторизации:

- Метод Ферма `fermat_factorization`

- Поллард P-1 `pollard_p_minus_1_factorization`

- Поллард Rho `pollard_rho_factorization`

### 🔍 PrimeTests
Тесты на простоту:

- Тест Ферма `fermat_test`

- Метод пробных делений `trial_division_test`

- Тест Миллера-Рабина `miller_rabin_test`

### 🔢 PrimeGenerates
Генерация простых чисел:

- Числа Ферма `fermat_prime`

- Числа Мерсенна `mersenne_prime`

### 🔐 Encodes
Алгоритмы шифрования:

- DES: реализация шифра Data Encryption Standard с методами `encrypt` и `decrypt`

## 🚀 Установка и сборка
### Требования
- Python ≥ 3.11

- C++17 совместимый компилятор

- pybind11

- CMake

### Сборка вручную
bash
git clone https://github.com/Murlocki/crypt.git
cd crypt
mkdir build && cd build
cmake ..
make

### 🧪 Примеры использования
python
import crypto_learn

### Факторизация числа
```
p, q = crypto_learn.Factorize.fermat_factorization(5959)
print(p, q)  # -> 59, 101
```

### Проверка на простоту
```
is_prime = crypto_learn.PrimeTests.miller_rabin_test(101)
print(is_prime)  # -> True
```

### Шифрование строки с помощью DES
```
cipher = crypto_learn.Encodes.DES()
enc = cipher.encrypt("hello")
dec = cipher.decrypt(enc)
print(enc, dec)  # -> '...' 'hello'
```

### Поиск первообразных корней
```
roots = crypto_learn.BaseOperations.find_prime_roots(17)
print(roots)  # -> [3, 5, 6, 7, 10, 11, 12, 14]
```

## 📘 Документация API
### 📐 BaseOperations
- `fast_degree(a: int, b: int, mod: int) -> int`

Возводит число a в степень b по модулю mod с помощью бинарной экспоненты.

a — основание степени

b — показатель степени

mod — модуль

Возвращает: a^b % mod

- `euler_slow(n: int) -> int`

Медленный способ вычисления функции Эйлера φ(n).

n — натуральное число

Возвращает: φ(n)

- `extended_gcd(a: int, b: int) -> Tuple[int, int, int] `

Расширенный алгоритм Евклида.

a, b — целые числа

Возвращает: (gcd, x, y), такие что a*x + b*y = gcd

- `inverse_element(a: int, mod: int) -> int`

Находит обратный элемент к a по модулю mod, то есть такое x, что a*x ≡ 1 (mod mod).

a — число

mod — модуль

Возвращает: x, или -1, если обратного элемента не существует

- `solve_linear_congruence(a: int, b: int, mod: int) -> List[int]`

Решает линейное сравнение a * x ≡ b (mod mod).

a, b — коэффициенты

mod — модуль

Возвращает: список решений x

- `find_prime_roots(p: int) -> List[int]`

Находит все первообразные корни по модулю p.

p — простое число

Возвращает: список первообразных корней

- `solve_quadratic_congruence(a: int, b: int, c: int, mod: int) -> List[int]`

Решает квадратное сравнение a*x² + b*x + c ≡ 0 (mod mod).

a, b, c — коэффициенты

mod — модуль

Возвращает: список решений x

### 🔍 PrimeTests
- `fermat_test(n: int, k: int = 5) -> bool`

Тест Ферма на простоту.

n — число для проверки

k — число раундов теста

Возвращает: True, если n вероятно простое, иначе False

- `miller_rabin_test(n: int, k: int = 5) -> bool`

Проверка числа на простоту с помощью теста Миллера — Рабина.

n — число для проверки

k — количество раундов

Возвращает: True, если число вероятно простое

### 🔢 Factorize
- `fermat_factorization(n: int) -> Tuple[int, int]`

Факторизация числа методом Ферма.

n — нечётное составное число

Возвращает: кортеж (p, q), где p * q = n

- `pollard_rho_factorization(n: int) -> int`

Факторизация с использованием алгоритма Полларда Rho.

n — составное число

Возвращает: один нетривиальный делитель числа n

### 🔐 Encodes.DES

- `Des(key: str)`

Конструктор класса, реализующего алгоритм DES

- `encrypt(text: str) -> str`

Шифрует строку с помощью DES.

text — строка для шифрования

Возвращает: зашифрованная строка (в hex или base64, зависит от реализации)

- `decrypt(cipher: str) -> str`

Расшифровывает строку, зашифрованную методом encrypt.

cipher — зашифрованная строка

Возвращает: исходный открытый текст
