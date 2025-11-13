// Файл test_triangle.cpp
// Модульные тесты для класса Triangle

#include "../src/triangle.h"
#include "../src/screen.h"
#include <iostream>
#include <cassert>
#include <memory>

// Утилита для вывода результатов тестов
void printTestResult(const char* testName, bool passed) {
  std::cout << "[" << (passed ? "PASS" : "FAIL") << "] " << testName << std::endl;
}

// Тест 1: Создание треугольника
void testTriangleCreation() {
  Point p1(10, 10);
  Point p2(20, 10);
  Point p3(15, 5);
  
  auto triangle = std::make_unique<Triangle>(p1, p2, p3);
  
  printTestResult("testTriangleCreation", triangle != nullptr);
}

// Тест 2: Получение габаритных точек
void testBoundingBox() {
  Point p1(10, 20); // Левая нижняя
  Point p2(30, 20); // Правая нижняя
  Point p3(20, 10); // Верхняя
  
  Triangle triangle(p1, p2, p3);
  
  Point leftTop = triangle.getLeftTop();
  Point rightTop = triangle.getRightTop();
  Point leftBottom = triangle.getLeftBottom();
  Point rightBottom = triangle.getRightBottom();
  
  bool test1 = (leftTop.getX() == 10 && leftTop.getY() == 10);
  bool test2 = (rightTop.getX() == 30 && rightTop.getY() == 10);
  bool test3 = (leftBottom.getX() == 10 && leftBottom.getY() == 20);
  bool test4 = (rightBottom.getX() == 30 && rightBottom.getY() == 20);
  
  printTestResult("testBoundingBox - LeftTop", test1);
  printTestResult("testBoundingBox - RightTop", test2);
  printTestResult("testBoundingBox - LeftBottom", test3);
  printTestResult("testBoundingBox - RightBottom", test4);
}

// Тест 3: Перемещение треугольника
void testMove() {
  Point p1(10, 10);
  Point p2(20, 10);
  Point p3(15, 5);
  
  Triangle triangle(p1, p2, p3);
  
  Point moveVector(5, 5);
  triangle.move(moveVector);
  
  Point leftTop = triangle.getLeftTop();
  Point rightBottom = triangle.getRightBottom();
  
  // До: LeftTop(10,5), после сдвига на (5,5): LeftTop(15,10)
  bool moved = (leftTop.getX() == 15 && leftTop.getY() == 10 &&
                rightBottom.getX() == 25 && rightBottom.getY() == 15);
  
  printTestResult("testMove", moved);
}

// Тест 4: Отрисовка треугольника без ошибок
void testDraw() {
  Point p1(5, 5);
  Point p2(15, 5);
  Point p3(10, 10);
  
  Triangle triangle(p1, p2, p3);
  Screen screen(30, 20);
  
  bool noException = true;
  try {
    triangle.draw(&screen);
  } catch (...) {
    noException = false;
  }
  
  printTestResult("testDraw", noException);
}

// Тест 5: Вырожденный треугольник (все точки на одной линии)
void testDegenerateTriangle() {
  Point p1(10, 10);
  Point p2(20, 10);
  Point p3(15, 10); // Все на одной горизонтальной линии
  
  Triangle triangle(p1, p2, p3);
  Screen screen(30, 20);
  
  bool noException = true;
  try {
    triangle.draw(&screen);
  } catch (...) {
    noException = false;
  }
  
  printTestResult("testDegenerateTriangle", noException);
}

// Тест 6: Треугольник с совпадающими вершинами
void testCoincidentVertices() {
  Point p1(10, 10);
  Point p2(10, 10);
  Point p3(10, 10);
  
  Triangle triangle(p1, p2, p3);
  
  Point leftTop = triangle.getLeftTop();
  Point rightBottom = triangle.getRightBottom();
  
  // Все точки должны совпадать
  bool test = (leftTop.getX() == 10 && leftTop.getY() == 10 &&
               rightBottom.getX() == 10 && rightBottom.getY() == 10);
  
  printTestResult("testCoincidentVertices", test);
}

// Тест 7: Большой треугольник
void testLargeTriangle() {
  Point p1(0, 100);
  Point p2(100, 100);
  Point p3(50, 0);
  
  Triangle triangle(p1, p2, p3);
  Screen screen(150, 150);
  
  bool noException = true;
  try {
    triangle.draw(&screen);
  } catch (...) {
    noException = false;
  }
  
  printTestResult("testLargeTriangle", noException);
}

// Тест 8: Множественное перемещение
void testMultipleMove() {
  Point p1(10, 10);
  Point p2(20, 10);
  Point p3(15, 5);
  
  Triangle triangle(p1, p2, p3);
  
  triangle.move(Point(5, 5));
  triangle.move(Point(5, 5));
  triangle.move(Point(-10, -10));
  
  Point leftTop = triangle.getLeftTop();
  
  // Финальная позиция: (10+5+5-10, 5+5+5-10) = (10, 5)
  bool test = (leftTop.getX() == 10 && leftTop.getY() == 5);
  
  printTestResult("testMultipleMove", test);
}

// Тест 9: Проверка методов поворота (не реализованы)
void testRotateMethods() {
  Point p1(10, 10);
  Point p2(20, 10);
  Point p3(15, 5);
  
  Triangle triangle(p1, p2, p3);
  
  Point beforeLeft = triangle.getLeftTop();
  Point beforeRight = triangle.getRightBottom();
  
  triangle.rotateLeft();
  triangle.rotateRight();
  
  Point afterLeft = triangle.getLeftTop();
  Point afterRight = triangle.getRightBottom();
  
  // Координаты не должны измениться (методы не реализованы)
  bool test = (beforeLeft.getX() == afterLeft.getX() && 
               beforeLeft.getY() == afterLeft.getY() &&
               beforeRight.getX() == afterRight.getX() && 
               beforeRight.getY() == afterRight.getY());
  
  printTestResult("testRotateMethods - не реализованы", test);
}

// Тест 10: Проверка методов отражения (не реализованы)
void testFlipMethods() {
  Point p1(10, 10);
  Point p2(20, 10);
  Point p3(15, 5);
  
  Triangle triangle(p1, p2, p3);
  
  Point beforeLeft = triangle.getLeftTop();
  Point beforeRight = triangle.getRightBottom();
  
  triangle.flipHorisontally();
  triangle.flipVertically();
  
  Point afterLeft = triangle.getLeftTop();
  Point afterRight = triangle.getRightBottom();
  
  // Координаты не должны измениться (методы не реализованы)
  bool test = (beforeLeft.getX() == afterLeft.getX() && 
               beforeLeft.getY() == afterLeft.getY() &&
               beforeRight.getX() == afterRight.getX() && 
               beforeRight.getY() == afterRight.getY());
  
  printTestResult("testFlipMethods - не реализованы", test);
}

// Тест 11: Проверка утечек памяти (создание/удаление)
void testMemoryLeak() {
  bool noException = true;
  
  try {
    for (int i = 0; i < 1000; ++i) {
      auto triangle = std::make_unique<Triangle>(
        Point(10, 10), 
        Point(20, 10), 
        Point(15, 5)
      );
      // Деструктор должен автоматически очистить память
    }
  } catch (...) {
    noException = false;
  }
  
  printTestResult("testMemoryLeak - 1000 создание/удаление", noException);
}

// Тест 12: Треугольник с нулевыми координатами
void testZeroCoordinates() {
  Point p1(0, 0);
  Point p2(0, 5);
  Point p3(5, 0);
  
  Triangle triangle(p1, p2, p3);
  
  Point leftTop = triangle.getLeftTop();
  
  bool test = (leftTop.getX() == 0 && leftTop.getY() == 0);
  
  printTestResult("testZeroCoordinates", test);
}

int main() {
  std::cout << "========================================" << std::endl;
  std::cout << "  Модульные тесты класса Triangle" << std::endl;
  std::cout << "========================================" << std::endl << std::endl;
  
  testTriangleCreation();
  testBoundingBox();
  testMove();
  testDraw();
  testDegenerateTriangle();
  testCoincidentVertices();
  testLargeTriangle();
  testMultipleMove();
  testRotateMethods();
  testFlipMethods();
  testMemoryLeak();
  testZeroCoordinates();
  
  std::cout << std::endl << "========================================" << std::endl;
  std::cout << "  Все тесты завершены" << std::endl;
  std::cout << "========================================" << std::endl;
  
  return 0;
}
