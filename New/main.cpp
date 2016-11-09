#define CATCH_CONFIG_MAIN
#define EPSILON (10e-3)

#include <iostream>
#include "catch.h"
#include "Geom.hpp"

TEST_CASE ("Computes length of a figure") {
    srand((unsigned int) time(0));
    double b = rand() / rand(), c = rand() / rand(), d = rand() / rand(), e = rand() / rand();

    SECTION("Computes length of a line") {
        Line *a = new Line({b, c}, {d, e});
        REQUIRE(a->length() - ((b - d) * (b - d) + (c - e) * (c - e)) < EPSILON);
        delete a;

        a = new Line({0, 0}, {0, 0});
        REQUIRE(a->length() == 0);
        delete a;

        a = new Line({10e9, 0}, {0, 10e9});
        REQUIRE(a->length() - 1.4 * 10e10 < EPSILON);
        delete a;
    }

    SECTION("Computes length of a circle") {
        Circle *a = new Circle({b, c}, d);
        REQUIRE(a->length() - acos(-1) * 2 * d < EPSILON);
        delete a;

        a = new Circle({0, 0}, 0);
        REQUIRE(a->length() == 0);
        delete a;

        a = new Circle({0, 0}, 10e9);
        REQUIRE(a->length() - 10e9 * 2 * acos(-1) < EPSILON);
        delete a;
    }

    SECTION("Computes length of a polyline") {
        PolyLine* a = new PolyLine;
        REQUIRE(a->length() == 0);

        a->push(new Line({b, c}, {d, e}));
        double dist = (b - d) * (b - d) + (c - e) * (c - e);
        REQUIRE(a->length() - dist < EPSILON);

        a->push(new Line({1e9, 1e9}, {1e9, 1e9}));
        REQUIRE((a->length() - (dist + ((1e9 - d) * (1e9 - d) + (1e9 - e) * (1e9 - e)))) < EPSILON);
        delete a;
    }
}

TEST_CASE ("Computes the intersection points of class Line") {

    SECTION("... with another Line"){
        double e = rand();
        Line *a = new Line({-e, 0}, {e, 0}), *b = new Line({0, e}, {0, -e});
        Point c = {0, 0};
        std::vector<Point> vec1, vec2;
        vec1.push_back(c);
        REQUIRE(((vec2 = a->intersection(b))[0].x == vec1[0].x));
        REQUIRE(vec2[0].y == vec1[0].y);
        vec1.clear();
        delete b;


        vec2 = a->intersection(a);
        REQUIRE(vec2.empty());
        delete a;

        a = new Line({-30e9, -10e9}, {10e9, 40e9}), b = new Line({-20e9, -40e9}, {20e9, 10e9});
        vec2 = a->intersection(b);
        REQUIRE(vec2.empty());
        delete a;
        delete b;
        vec2.clear();
    }

    SECTION("... with circle") {
        Line a = Line({5, 2}, {5, -2});
        Circle b = Circle({0, 0}, 4);

        std::vector<Point> vec = a.intersection(&b);
        REQUIRE(vec.empty());
    }
}

TEST_CASE("Intersection of everything with everything") {
    std::vector<Figure*> figures;
    figures.push_back(new Line({-4, 5}, {0, 4}));
    figures.push_back(new Line({-3, 1}, {-1, 6}));
    figures.push_back(new Circle({-5, 3}, 2));
    figures.push_back(new Circle({-1, 1}, 1));

    PolyLine* a = new PolyLine;
    a->push(new Line({-6, 6}, {-5, 0}));
    a->push(new Line({-4, 2}, {-1, 1}));
    figures.push_back(a);

    PolyLine* b = new PolyLine;
    b->push(new Line({-6, -2}, {-5, -1}));
    b->push(new Line({-4, -2}, {-3, -1}));
    b->push(new Line({-2, -2}, {-1, -1}));
    b->push(new Line({-1, -1}, {0, -1}));
    figures.push_back(b);


    SECTION("Line x Line") {
        std::vector<Point> res = figures[0]->intersection(figures[1]);
        REQUIRE(ceil(res[0].y) == 5);
        REQUIRE(ceil(res[0].x) == -1);
        res.clear();
    }

    SECTION("Line x Circle (no)") {
        std::vector<Point> res = figures[1]->intersection(figures[2]);
        REQUIRE(res.empty());
    }

    SECTION("Line x PolyLine") {
        std::vector<Point> res = figures[1]->intersection(figures[4]);
        REQUIRE(res.size() == 1);
        REQUIRE(ceil(res[0].y) == 2);
        REQUIRE(ceil(res[0].x) == -2);
    }

    SECTION("Circle x Circle (no)") {
        std::vector<Point> res = figures[3]->intersection(figures[2]);
        REQUIRE(res.empty());
    }

    SECTION("Circle x PolyLine (amount only)") {
        std::vector<Point> res = figures[4]->intersection(figures[2]);
        REQUIRE(res.size() == 4);
    }

    SECTION("PolyLine x PolyLine (no)") {
        std::vector<Point> res = figures[4]->intersection(figures[5]);
        REQUIRE(res.empty());
    }
}