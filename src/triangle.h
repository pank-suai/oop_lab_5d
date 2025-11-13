#pragma once
// Файл triangle.h
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "shape.h"
#include "rotatable.h"
#include "reflectable.h"
#include "line.h"
#include <algorithm>

// Треугольник - фигура с возможностью поворота и отражения
class Triangle : public Shape, public Rotatable, public reflectable
{
protected:
  Line* _side1;  // Первая сторона треугольника
  Line* _side2;  // Вторая сторона треугольника
  Line* _side3;  // Третья сторона треугольника
  
public:
  // Конструктор: принимает три вершины треугольника
  Triangle(const Point& p1, const Point& p2, const Point& p3);
  
  // Методы из базового класса Shape
  virtual void draw(Screen* screen) const override;
  virtual void move(Point p) override;
  virtual Point getLeftTop() const override;
  virtual Point getRightTop() const override;
  virtual Point getLeftBottom() const override;
  virtual Point getRightBottom() const override;
  
  // Методы из класса Rotatable
  virtual void rotateLeft() override;
  virtual void rotateRight() override;
  
  // Методы из класса reflectable
  virtual void flipHorisontally() override;
  virtual void flipVertically() override;
  
  // Деструктор - освобождаем память от линий
  virtual ~Triangle();
};

// Реализация конструктора
Triangle::Triangle(const Point& p1, const Point& p2, const Point& p3)
{
  // Создаем три стороны треугольника, соединяя вершины
  _side1 = new Line(p1, p2);  // Сторона между первой и второй вершиной
  _side2 = new Line(p2, p3);  // Сторона между второй и третьей вершиной
  _side3 = new Line(p3, p1);  // Сторона между третьей и первой вершиной
}

// Отрисовка треугольника на экране
void Triangle::draw(Screen* screen) const
{
  // Рисуем все три стороны
  _side1->draw(screen);
  _side2->draw(screen);
  _side3->draw(screen);
}

// Перемещение треугольника на вектор p
void Triangle::move(Point p)
{
  // Перемещаем все три стороны
  _side1->move(p);
  _side2->move(p);
  _side3->move(p);
}

// Получение левой верхней габаритной точки
Point Triangle::getLeftTop() const
{
  // Находим минимальные координаты X и Y среди всех сторон
  std::uint32_t minX = std::min({
    _side1->getLeftTop().getX(),
    _side2->getLeftTop().getX(),
    _side3->getLeftTop().getX()
  });
  
  std::uint32_t minY = std::min({
    _side1->getLeftTop().getY(),
    _side2->getLeftTop().getY(),
    _side3->getLeftTop().getY()
  });
  
  return Point(minX, minY);
}

// Получение правой верхней габаритной точки
Point Triangle::getRightTop() const
{
  // Находим максимальный X и минимальный Y
  std::uint32_t maxX = std::max({
    _side1->getRightTop().getX(),
    _side2->getRightTop().getX(),
    _side3->getRightTop().getX()
  });
  
  std::uint32_t minY = std::min({
    _side1->getRightTop().getY(),
    _side2->getRightTop().getY(),
    _side3->getRightTop().getY()
  });
  
  return Point(maxX, minY);
}

// Получение левой нижней габаритной точки
Point Triangle::getLeftBottom() const
{
  // Находим минимальный X и максимальный Y
  std::uint32_t minX = std::min({
    _side1->getLeftBottom().getX(),
    _side2->getLeftBottom().getX(),
    _side3->getLeftBottom().getX()
  });
  
  std::uint32_t maxY = std::max({
    _side1->getLeftBottom().getY(),
    _side2->getLeftBottom().getY(),
    _side3->getLeftBottom().getY()
  });
  
  return Point(minX, maxY);
}

// Получение правой нижней габаритной точки
Point Triangle::getRightBottom() const
{
  // Находим максимальные координаты X и Y среди всех сторон
  std::uint32_t maxX = std::max({
    _side1->getRightBottom().getX(),
    _side2->getRightBottom().getX(),
    _side3->getRightBottom().getX()
  });
  
  std::uint32_t maxY = std::max({
    _side1->getRightBottom().getY(),
    _side2->getRightBottom().getY(),
    _side3->getRightBottom().getY()
  });
  
  return Point(maxX, maxY);
}

// Поворот влево - не реализовано для данной задачи
void Triangle::rotateLeft()
{
  /* не реализовано */
}

// Поворот вправо - не реализовано для данной задачи
void Triangle::rotateRight()
{
  /* не реализовано */
}

// Горизонтальное отражение - не реализовано для данной задачи
void Triangle::flipHorisontally()
{
  /* не реализовано */
}

// Вертикальное отражение - не реализовано для данной задачи
void Triangle::flipVertically()
{
  /* не реализовано */
}

// Деструктор - удаляем все три стороны, чтобы избежать утечек памяти
Triangle::~Triangle()
{
  delete _side1;
  delete _side2;
  delete _side3;
}

#endif // TRIANGLE_H
