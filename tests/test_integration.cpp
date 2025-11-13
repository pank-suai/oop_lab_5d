// Интеграционный тест - проверка всей программы
#include "../src/triangle.h"
#include "../src/square.h"
#include "../src/line.h"
#include "../src/screen.h"
#include <iostream>
#include <vector>
#include <memory>

int main() {
  std::cout << "========================================" << std::endl;
  std::cout << "  Интеграционный тест" << std::endl;
  std::cout << "========================================" << std::endl << std::endl;
  
  bool allTestsPassed = true;
  
  // Тест 1: Создание экрана
  std::cout << "[TEST] Создание экрана 50x35... ";
  auto screen = std::make_unique<Screen>(50, 35);
  std::cout << "OK" << std::endl;
  
  // Тест 2: Создание коллекции фигур
  std::cout << "[TEST] Создание вектора фигур... ";
  std::vector<std::shared_ptr<Shape>> shapes;
  std::cout << "OK" << std::endl;
  
  // Тест 3: Добавление квадрата (шляпа)
  std::cout << "[TEST] Добавление квадрата (шляпа)... ";
  shapes.emplace_back(std::make_shared<Square>(Point(15, 3), Point(32, 12)));
  std::cout << "OK" << std::endl;
  
  // Тест 4: Добавление линии
  std::cout << "[TEST] Добавление линии под шляпой... ";
  Point p1 = shapes[shapes.size() - 1]->getLeftBottom();
  p1.setX(p1.getX() - 2);
  p1.setY(p1.getY() + 1);
  Point p2 = shapes[shapes.size() - 1]->getRightBottom();
  p2.setX(p2.getX() + 2);
  p2.setY(p2.getY() + 1);
  shapes.emplace_back(std::make_shared<Line>(p1, p2));
  std::cout << "OK" << std::endl;
  
  // Тест 5: Добавление квадрата (голова)
  std::cout << "[TEST] Добавление квадрата (голова)... ";
  p1 = shapes[shapes.size() - 1]->getLeftBottom();
  p1.setX(p1.getX() + 1);
  p1.setY(p1.getY() + 1);
  p2 = shapes[shapes.size() - 1]->getRightBottom();
  p2.setX(p2.getX() - 1);
  p2.setY(p2.getY() + 10);
  shapes.emplace_back(std::make_shared<Square>(p1, p2));
  std::shared_ptr<Shape> head = shapes[shapes.size() - 1];
  std::cout << "OK" << std::endl;
  
  // Тест 6: Добавление треугольника (левое ухо)
  std::cout << "[TEST] Добавление треугольника (левое ухо)... ";
  Point earLeftTop = head->getLeftTop();
  Point earLeftP1(earLeftTop.getX() - 4, earLeftTop.getY() + 2);
  Point earLeftP2(earLeftTop.getX(), earLeftTop.getY() + 2);
  Point earLeftP3(earLeftTop.getX() - 2, earLeftTop.getY() - 2);
  shapes.emplace_back(std::make_shared<Triangle>(earLeftP1, earLeftP2, earLeftP3));
  std::cout << "OK" << std::endl;
  
  // Тест 7: Добавление треугольника (правое ухо)
  std::cout << "[TEST] Добавление треугольника (правое ухо)... ";
  Point earRightTop = head->getRightTop();
  Point earRightP1(earRightTop.getX(), earRightTop.getY() + 2);
  Point earRightP2(earRightTop.getX() + 4, earRightTop.getY() + 2);
  Point earRightP3(earRightTop.getX() + 2, earRightTop.getY() - 2);
  shapes.emplace_back(std::make_shared<Triangle>(earRightP1, earRightP2, earRightP3));
  std::cout << "OK" << std::endl;
  
  // Тест 8: Добавление треугольника (кокарда)
  std::cout << "[TEST] Добавление треугольника (кокарда)... ";
  std::shared_ptr<Shape> hat = shapes[0];
  Point hatCenter = hat->getLeftTop();
  hatCenter.setX((hat->getLeftTop().getX() + hat->getRightTop().getX()) / 2);
  hatCenter.setY(hat->getLeftTop().getY() + 3);
  Point kokardaP1(hatCenter.getX() - 2, hatCenter.getY() + 2);
  Point kokardaP2(hatCenter.getX() + 2, hatCenter.getY() + 2);
  Point kokardaP3(hatCenter.getX(), hatCenter.getY() - 1);
  shapes.emplace_back(std::make_shared<Triangle>(kokardaP1, kokardaP2, kokardaP3));
  std::cout << "OK" << std::endl;
  
  // Тест 9: Проверка количества фигур
  std::cout << "[TEST] Проверка количества треугольников... ";
  int triangleCount = 0;
  for (auto& shape : shapes) {
    if (dynamic_cast<Triangle*>(shape.get())) {
      triangleCount++;
    }
  }
  if (triangleCount == 3) {
    std::cout << "OK (найдено: " << triangleCount << ")" << std::endl;
  } else {
    std::cout << "FAIL (ожидалось 3, найдено: " << triangleCount << ")" << std::endl;
    allTestsPassed = false;
  }
  
  // Тест 10: Отрисовка всех фигур
  std::cout << "[TEST] Отрисовка всех фигур на экране... ";
  try {
    for (auto shape : shapes) {
      shape->draw(screen.get());
    }
    std::cout << "OK" << std::endl;
  } catch (...) {
    std::cout << "FAIL (исключение при отрисовке)" << std::endl;
    allTestsPassed = false;
  }
  
  // Тест 11: Вывод экрана
  std::cout << "[TEST] Вывод экрана... ";
  try {
    screen->draw();
    std::cout << "OK" << std::endl;
  } catch (...) {
    std::cout << "FAIL (исключение при выводе)" << std::endl;
    allTestsPassed = false;
  }
  
  std::cout << std::endl << "========================================" << std::endl;
  if (allTestsPassed) {
    std::cout << "  РЕЗУЛЬТАТ: ВСЕ ТЕСТЫ ПРОЙДЕНЫ" << std::endl;
  } else {
    std::cout << "  РЕЗУЛЬТАТ: ЕСТЬ ОШИБКИ" << std::endl;
  }
  std::cout << "========================================" << std::endl;
  
  return allTestsPassed ? 0 : 1;
}
