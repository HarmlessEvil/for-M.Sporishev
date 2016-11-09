//
// Created by Alexander on 09.10.2016.
//

#ifndef NEW_GEOM_HPP
#define NEW_GEOM_HPP


#include <cmath>
#include <vector>
#include <cstdlib>

struct Point {
    double x, y;
};

class Line;
class Circle;
class PolyLine;

class Figure {
public:
    virtual double length() = 0;
    virtual std::vector<Point> intersection(Figure* figure) = 0;
    virtual std::vector<Point> intersection(Line* line) = 0;
    virtual std::vector<Point> intersection(Circle* circle) = 0;
    virtual std::vector<Point> intersection(PolyLine* poly) = 0;
};

class Line: public Figure {
public:
    Line(Point a, Point b);
    double length() override;
    Point getStart();
    Point getEnd();
    std::vector<Point> intersection(Figure* figure) override;
    std::vector<Point> intersection(Line* line) override;
    std::vector<Point> intersection(Circle* circle) override;
    std::vector<Point> intersection(PolyLine* poly) override;
private:
    Point start, end;
};

class Circle: public Figure{
public:
    Circle(Point c, double r);
    Point getCenter();
    double getRadius();
    double length() override;
    std::vector<Point> intersection(Figure* figure) override;
    std::vector<Point> intersection(Line* line) override;
    std::vector<Point> intersection(Circle* circle) override;
    std::vector<Point> intersection(PolyLine* poly) override;
private:
    Point center;
    double radius;
};

class PolyLine: public Figure {
public:
    ~PolyLine();
    void push(Line* line);
    double length() override;
    size_t getSize();
    Line* operator[] (int i);
    std::vector<Point> intersection(Figure* figure) override;
    std::vector<Point> intersection(Line* line) override;
    std::vector<Point> intersection(Circle* circle) override;
    std::vector<Point> intersection(PolyLine* poly) override;
private:
    std::vector<Line*> path;
};

#endif //NEW_GEOM_HPP
