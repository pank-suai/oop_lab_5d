// Тест для диагностики проблемы с move
#include "../src/triangle.h"
#include "../src/screen.h"
#include <iostream>

int main() {
  Point p1(10, 10);
  Point p2(20, 10);
  Point p3(15, 5);
  
  Triangle triangle(p1, p2, p3);
  
  std::cout << "До перемещения:" << std::endl;
  std::cout << "  LeftTop: (" << triangle.getLeftTop().getX() << ", " << triangle.getLeftTop().getY() << ")" << std::endl;
  std::cout << "  RightBottom: (" << triangle.getRightBottom().getX() << ", " << triangle.getRightBottom().getY() << ")" << std::endl;
  
  Point moveVector(5, 5);
  triangle.move(moveVector);
  
  std::cout << "После перемещения на (5, 5):" << std::endl;
  std::cout << "  LeftTop: (" << triangle.getLeftTop().getX() << ", " << triangle.getLeftTop().getY() << ")" << std::endl;
  std::cout << "  RightBottom: (" << triangle.getRightBottom().getX() << ", " << triangle.getRightBottom().getY() << ")" << std::endl;
  
  return 0;
}
