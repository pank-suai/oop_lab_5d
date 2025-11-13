
#include <iostream>
#include "screen.h"
#include "line.h"
#include "square.h"
#include "triangle.h"  // Подключаем новый класс Triangle
#include <vector>
#include <memory>

int main()
{
  system("color F1");
  auto screen = std::make_unique<Screen>(50, 35);
  std::vector<std::shared_ptr<Shape>> shapes;
  
  // Создаём шляпу
  shapes.emplace_back(std::make_shared<Square>(Point(15, 3), Point(32, 12)));
  
  // Линия под шляпой
  Point p1 = shapes[shapes.size() - 1]->getLeftBottom();
  p1.setX(p1.getX() - 2);
  p1.setY(p1.getY() + 1);
  Point p2 = shapes[shapes.size() - 1]->getRightBottom();
  p2.setX(p2.getX() + 2);
  p2.setY(p2.getY() + 1);
  shapes.emplace_back(std::make_shared<Line>(p1, p2));
  
  // Создаём голову
  p1 = shapes[shapes.size() - 1]->getLeftBottom();
  p1.setX(p1.getX() + 1);
  p1.setY(p1.getY() + 1);
  p2 = shapes[shapes.size() - 1]->getRightBottom();
  p2.setX(p2.getX() - 1);
  p2.setY(p2.getY() + 10);
  shapes.emplace_back(std::make_shared<Square>(p1, p2));
  std::shared_ptr<Shape> head = shapes[shapes.size() - 1];
  
  // ====== ПОЗИЦИЯ 4: ЛЕВОЕ УХО (ТРЕУГОЛЬНИК) ======
  // Создаём треугольник слева от головы
  Point earLeftTop = head->getLeftTop();
  Point earLeftP1(earLeftTop.getX() - 4, earLeftTop.getY() + 2);  // Левая вершина
  Point earLeftP2(earLeftTop.getX(), earLeftTop.getY() + 2);       // Правая вершина (у головы)
  Point earLeftP3(earLeftTop.getX() - 2, earLeftTop.getY() - 2);  // Верхняя вершина
  shapes.emplace_back(std::make_shared<Triangle>(earLeftP1, earLeftP2, earLeftP3));
  
  // ====== ПОЗИЦИЯ 5: ПРАВОЕ УХО (ТРЕУГОЛЬНИК) ======
  // Создаём треугольник справа от головы
  Point earRightTop = head->getRightTop();
  Point earRightP1(earRightTop.getX(), earRightTop.getY() + 2);      // Левая вершина (у головы)
  Point earRightP2(earRightTop.getX() + 4, earRightTop.getY() + 2);  // Правая вершина
  Point earRightP3(earRightTop.getX() + 2, earRightTop.getY() - 2);  // Верхняя вершина
  shapes.emplace_back(std::make_shared<Triangle>(earRightP1, earRightP2, earRightP3));
  
  // ====== ПОЗИЦИЯ 6: КОКАРДА НА ШЛЯПЕ (ТРЕУГОЛЬНИК) ======
  // Маленький треугольник на шляпе, вершиной вверх
  std::shared_ptr<Shape> hat = shapes[0];
  Point hatCenter = hat->getLeftTop();
  hatCenter.setX((hat->getLeftTop().getX() + hat->getRightTop().getX()) / 2);
  hatCenter.setY(hat->getLeftTop().getY() + 3);
  
  Point kokardaP1(hatCenter.getX() - 2, hatCenter.getY() + 2);  // Левая нижняя вершина
  Point kokardaP2(hatCenter.getX() + 2, hatCenter.getY() + 2);  // Правая нижняя вершина
  Point kokardaP3(hatCenter.getX(), hatCenter.getY() - 1);       // Верхняя вершина
  shapes.emplace_back(std::make_shared<Triangle>(kokardaP1, kokardaP2, kokardaP3));
  
  // Левый глаз
  Point eyeLeft = head->getLeftTop();
  eyeLeft.setX(eyeLeft.getX() + 2);
  eyeLeft.setY(eyeLeft.getY() + 2);
  Point eyeRight = Point(eyeLeft.getX() + 2, eyeLeft.getY());
  shapes.emplace_back(std::make_shared<Line>(eyeLeft, eyeRight));
  
  // Правый глаз
  eyeRight = head->getRightTop();
  eyeRight.setX(eyeRight.getX() - 2);
  eyeRight.setY(eyeRight.getY() + 2);
  eyeLeft = Point(eyeRight.getX() - 2, eyeRight.getY());
  shapes.emplace_back(std::make_shared<Line>(eyeLeft, eyeRight));
  
  std::shared_ptr<Shape> leftEye = shapes[shapes.size() - 2];
  std::shared_ptr<Shape> rightEye = shapes[shapes.size() - 1];
  
  // Нос
  Point nose = Point(leftEye->getRightTop().getX() +
    (rightEye->getLeftTop().getX() - leftEye->getRightTop().getX()) / 2,
    leftEye->getRightTop().getY() + 2);
  shapes.emplace_back(std::make_shared<Line>(nose, nose));
  
  // Рот
  p1 = head->getLeftBottom();
  p1.setX(p1.getX() + 2);
  p1.setY(p1.getY() - 2);
  p2 = head->getRightBottom();
  p2.setX(p2.getX() - 2);
  p2.setY(p2.getY() - 2);
  shapes.emplace_back(std::make_shared<Line>(p1, p2));
  
  // Линия костюма
  auto costume = std::make_shared<Line>(Point(p1.getX(), p1.getY() + 10),
    Point(p2.getX(), p2.getY() + 10));
  shapes.emplace_back(costume);
  
  // Левая точка
  p1 = Point(costume->getLeftBottom().getX(), costume->getLeftBottom().getY() + 1);
  auto leftDot = std::make_shared<Line>(p1, p1);
  shapes.emplace_back(leftDot);
  
  // Правая точка
  p1 = Point(costume->getRightBottom().getX(), costume->getRightBottom().getY() + 1);
  auto rightDot = std::make_shared<Line>(p1, p1);
  shapes.emplace_back(rightDot);
  
  // Рисуем все фигуры
  for (auto shape : shapes)
    shape->draw(screen.get());
  
  screen->draw();
  
  std::cout << std::endl << "Нажмите Enter для выхода..." << std::endl;
  std::cin.get();
  return 0;
}
