// Тест для проверки утечек памяти
#include "../src/triangle.h"
#include <iostream>
#include <memory>
#include <unistd.h>

int main() {
  std::cout << "Тест утечек памяти - создание/удаление 10000 треугольников..." << std::endl;
  
  for (int i = 0; i < 10000; ++i) {
    // Создание через raw pointer
    Triangle* t1 = new Triangle(Point(10, 10), Point(20, 10), Point(15, 5));
    delete t1;
    
    // Создание через unique_ptr
    auto t2 = std::make_unique<Triangle>(Point(5, 5), Point(15, 5), Point(10, 0));
    
    // Тестирование методов
    t2->move(Point(1, 1));
    t2->rotateLeft();
    t2->flipHorisontally();
    
    if (i % 1000 == 0) {
      std::cout << "  Обработано: " << i << " треугольников" << std::endl;
    }
  }
  
  std::cout << "Тест завершён. Программа продолжает работу для анализа памяти..." << std::endl;
  std::cout << "Запустите 'leaks' с PID этого процесса для проверки утечек." << std::endl;
  
  // Держим программу запущенной для анализа
  std::cout << "PID: " << getpid() << std::endl;
  std::cout << "Нажмите Enter для завершения..." << std::endl;
  std::cin.get();
  
  return 0;
}
