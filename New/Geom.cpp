//
// Created by Alexander on 09.10.2016.
//

#include "Geom.hpp"

Line :: Line(Point a = {0, 0}, Point b = {0, 0}) {
    start = a;
    end = b;
}

double Line :: length() {
    return pow((start.x - end.x) * (start.x - end.x) + (start.y - end.y) * (start.y - end.y), 0.5);
}

Point Line :: getStart() {
    return start;
}

Point Line :: getEnd() {
    return end;
}

std::vector<Point> Line :: intersection(Line* line) {
    Point start1 = line->getStart(), end1 = line->getEnd();

    double u1 = ((end1.x - start1.x) * (start.y - start1.y) - (end1.y - start1.y) * (start.x - start1.x)) /
                ((end1.y - start1.y) * (end.x - start.x) - (end1.x - start1.x) * (end.y - start.y));
    double u2 = ((end.x - start.x) * (start.y - start1.y) - (end.y - start.y) * (start.x - start1.x)) /
                ((end1.y - start1.y) * (end.x - start.x) - (end1.x - start1.x) * (end.y - start.y));

    double x = start.x + u1 * (end.x - start.x);
    double y = start.y + u1 * (end.y - start.y);

    if ((x != x) || (y != y) || (u1 >1) || (u1 < 0) || (u2 > 1) || (u2 < 0)) {
        return std::vector<Point>();
    }

    Point a = {x, y};

    std::vector<Point> res;
    res.push_back(a);

    return res;
}

std::vector<Point> Line :: intersection(Circle* circle) {
    Point c = circle->getCenter();
    double r = circle->getRadius();
    double k = (start.y - end.y) / (start.x - end.x);
    double b = start.y - k * start.x;
    double A = 1 + k * k;
    double B = -2 * c.x + 2 * k * b - 2 * k * c.y;
    double C = b * b + c.x * c.x - 2 * b * c.y + c.y * c.y - r * r;
    double d = (B * B - 4 * A * C);

    std::vector<Point> res;

    if (d >= 0) {
        double x1 = (-B - sqrt(d)) / (2  * A);
        double x2 = (-B + sqrt(d)) / (2  * A);
        double y1 = k * x1 + b;
        double y2 = k * x2 + b;
        double l = sqrt(x2 * x2 + y2 * y2);

        res.push_back({x1, y1});

        if ((d > 0) && (l <= length())) {
            res.push_back({x2, y2});
        }
    }

    return res;
}

std::vector<Point> Line :: intersection(PolyLine* poly) {
    size_t size = poly->getSize();
    std::vector<Point> temp;
    std::vector<Point> res;

    for (size_t i = 0; i < size; i++) {
        temp = intersection((*poly)[i]);
        if (temp.size()) {
            res.insert(res.begin(), temp.begin(), temp.end());
        }
        temp.clear();
    }

    return res;
}

std::vector<Point> Line :: intersection(Figure* figure) {
    return figure->intersection(this);
}

bool calc (double &x1, double &x2, double p, double q) {
    if (q == 0) {
        x1 = x2 = 0;
        return true;
    } else {
        if (p == 0) {
            double t = -q;
            if (t >= 0) {
                x1 = sqrt(t);
                x2 = -x1;
                return true;
            } else {
                return false;
            }
        } else {
            double d = p * p - 4 * q;
            if (d >= 0) {
                x1 = (-p - sqrt(d)) / 2;
                x2 = (-p + sqrt(d)) / 2;
                return true;
            } else {
                return false;
            }
        }
    }
}

Circle :: Circle(Point c = {0, 0}, double r = 0) {
    center = c;
    radius = r;
}

double Circle :: getRadius() {
    return radius;
}

Point Circle :: getCenter() {
    return center;
}

double Circle :: length() {
    return acos(-1.0) * 2 * radius;
}

std::vector<Point> Circle :: intersection(Line* line) {
    return line->intersection(this);
}

std::vector<Point> Circle :: intersection(Circle* circle) {
    double moveX = center.x, moveY = center.y;
    double a = circle->getCenter().x - moveX, b = circle->getCenter().y - moveY;
    double r = circle->getRadius();

    double p = -a / b;
    double q = (r * r - radius * radius - a * a - b * b) / (2 * b) - (radius * radius);

    double x1, x2, y1, y2;
    if (calc(x1, x2, p, q)) {
        y1 = (r * r - radius *radius - a * a - b * b - 2 * a * x1) / (2 * b);
        y2 = (r * r - radius *radius - a * a - b * b - 2 * a * x2) / (2 * b);
    } else {
        return std::vector<Point>();
    }

    x1 += moveX, x2 += moveX, y1 += moveY, y2 += moveY;

    std::vector<Point> res(1);
    res.push_back({x1, y1});
    if (x1 != x2) {
        res.push_back({x2, y2});
    }

    return res;
}

std::vector<Point> Circle :: intersection(PolyLine* poly) {
    size_t size = poly->getSize();
    std::vector<Point> temp;
    std::vector<Point> res;

    for (size_t i = 0; i < size; i++) {
        temp = intersection((*poly)[i]);
        if (temp.size()) {
            res.insert(res.begin(), temp.begin (), temp.end());
        }
        temp.clear();
    }

    return res;
}

std::vector<Point> Circle :: intersection(Figure* figure) {
    return figure->intersection(this);
}

void PolyLine :: push(Line* line) {
    if ((path.size() == 0) || ((path.back()->getEnd().x == line->getStart().x) &&
                               (path.back()->getEnd().y == line->getStart().y))) {
        path.push_back( line );
    } else {
        path.push_back( new Line(path.back()->getEnd(), line->getStart()) );
        path.push_back( line );
    }
}

PolyLine :: ~PolyLine() {
    int s = path.size();

    for (int i = 0; i < s; i++) {
        delete path[i];
    }

    path.clear();
}

double PolyLine :: length() {
    double l = 0;

    for (int i = 0; i < path.size(); i++) {
        l += path[i]->length();
    }

    return l;
}

size_t PolyLine :: getSize() {
    return path.size();
}

Line* PolyLine :: operator[] (int i) {
    return path[i];
}

std::vector<Point> PolyLine :: intersection(Line* line) {
    return line->intersection(this);
}

std::vector<Point> PolyLine :: intersection(Circle* circle) {
    return circle->intersection(this);
}

std::vector<Point> PolyLine :: intersection(PolyLine* poly) {
    size_t sizeCaller = getSize();
    std::vector<Point> temp;
    std::vector<Point> res;

    for (size_t i = 0; i < sizeCaller; i++) {
        temp = poly->intersection(path[i]);

        if (temp.size()) {
            res.insert(res.begin(), temp.begin(), temp.end());
        }

        temp.clear();
    }

    return res;
}

std::vector<Point> PolyLine :: intersection(Figure* figure) {
    return figure->intersection(this);
}