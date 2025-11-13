# Документация к классу Triangle

## Описание
Класс `Triangle` реализует фигуру "Треугольник" для лабораторной работы №5Д (Вариант 5).

## Наследование
```cpp
class Triangle : public Shape, public Rotatable, public reflectable
```

Класс использует множественное наследование от трех базовых классов:
- **Shape** - базовый абстрактный класс для всех фигур
- **Rotatable** - интерфейс для фигур с возможностью поворота
- **reflectable** - интерфейс для фигур с возможностью отражения

## Структура класса

### Защищенные поля (protected)
```cpp
Line* _side1;  // Первая сторона треугольника
Line* _side2;  // Вторая сторона треугольника
Line* _side3;  // Третья сторона треугольника
```

### Конструктор
```cpp
Triangle(const Point& p1, const Point& p2, const Point& p3);
```
Принимает три точки - вершины треугольника. Создает три линии, соединяющие эти вершины.

### Методы от базового класса Shape

#### `void draw(Screen* screen) const`
Отрисовывает треугольник на экране, рисуя все три стороны.

#### `void move(Point p)`
Перемещает треугольник на вектор `p`, перемещая все три стороны.

#### `Point getLeftTop() const`
Возвращает левую верхнюю габаритную точку треугольника.
Вычисляется как минимальные значения X и Y среди всех вершин.

#### `Point getRightTop() const`
Возвращает правую верхнюю габаритную точку треугольника.
Вычисляется как максимальный X и минимальный Y.

#### `Point getLeftBottom() const`
Возвращает левую нижнюю габаритную точку треугольника.
Вычисляется как минимальный X и максимальный Y.

#### `Point getRightBottom() const`
Возвращает правую нижнюю габаритную точку треугольника.
Вычисляется как максимальные значения X и Y среди всех вершин.

### Методы от класса Rotatable

#### `void rotateLeft()`
Поворот влево. В данной реализации не используется (заглушка).

#### `void rotateRight()`
Поворот вправо. В данной реализации не используется (заглушка).

### Методы от класса reflectable

#### `void flipHorisontally()`
Горизонтальное отражение. В данной реализации не используется (заглушка).

#### `void flipVertically()`
Вертикальное отражение. В данной реализации не используется (заглушка).

### Деструктор
```cpp
~Triangle()
```
Освобождает память, удаляя все три стороны треугольника.

## Использование в программе

В программе создаются три треугольника:

### 1. Левое ухо (позиция 4)
```cpp
Point earLeftP1(earLeftTop.getX() - 4, earLeftTop.getY() + 2);
Point earLeftP2(earLeftTop.getX(), earLeftTop.getY() + 2);
Point earLeftP3(earLeftTop.getX() - 2, earLeftTop.getY() - 2);
shapes.emplace_back(std::make_shared<Triangle>(earLeftP1, earLeftP2, earLeftP3));
```

### 2. Правое ухо (позиция 5)
```cpp
Point earRightP1(earRightTop.getX(), earRightTop.getY() + 2);
Point earRightP2(earRightTop.getX() + 4, earRightTop.getY() + 2);
Point earRightP3(earRightTop.getX() + 2, earRightTop.getY() - 2);
shapes.emplace_back(std::make_shared<Triangle>(earRightP1, earRightP2, earRightP3));
```

### 3. Кокарда на шляпе (позиция 6)
```cpp
Point kokardaP1(hatCenter.getX() - 2, hatCenter.getY() + 2);
Point kokardaP2(hatCenter.getX() + 2, hatCenter.getY() + 2);
Point kokardaP3(hatCenter.getX(), hatCenter.getY() - 1);
shapes.emplace_back(std::make_shared<Triangle>(kokardaP1, kokardaP2, kokardaP3));
```

## Особенности реализации

1. **Габаритные точки** вычисляются с использованием `std::min` и `std::max` для нахождения крайних координат.

2. **Управление памятью**: 
   - Внутри класса используются сырые указатели (`Line*`)
   - В `main.cpp` объекты Triangle создаются через `std::shared_ptr`
   - Деструктор гарантирует освобождение памяти

3. **Виртуальные функции**: Все методы объявлены как `virtual` с спецификатором `override` для корректной работы полиморфизма.

4. **Заглушки методов**: Методы поворота и отражения оставлены как заглушки (комментарий `/* не реализовано */`), так как в данной задаче они не требуются для позиций 4, 5, 6.

## Файлы проекта

- **src/triangle.h** - заголовочный файл с объявлением и реализацией класса Triangle
- **src/main.cpp** - основная программа, использующая класс Triangle
- **src/point.h** - класс Point
- **src/line.h** - класс Line
- **src/shape.h** - базовый класс Shape
- **src/rotatable.h** - интерфейс Rotatable
- **src/reflectable.h** - интерфейс reflectable

## Компиляция и запуск

```bash
make clean  # Очистка
make        # Компиляция
make run    # Запуск программы
```
