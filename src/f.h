#pragma once
#include <string>
#include <initializer_list>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <iostream>
#include <istream>

class Figure {
protected:
    std::vector<double> coordinates;

public:
    Figure();
    virtual ~Figure() noexcept;

    virtual double area_calculate();
    virtual std::vector<double> center();
};

class Array {
public:
    Array();
    Array(const Array& other);
    Array(Array&& other) noexcept;
    virtual ~Array() noexcept;

    void add_figure(Figure* figure);
    void delete_by_index(int index);
    double summary_square();

private:
    Figure** array;
    size_t size;
};

class Triangle : public Figure {
public:
    Triangle();
    Triangle(const std::vector<double>& init);
    Triangle(const Triangle& other);
    Triangle(Triangle&& other) noexcept;

    double area_calculate() override;
    std::vector<double> center() override;

    bool operator==(const Triangle& other) const;
    Triangle& operator=(const Triangle& other);

    friend std::ostream& operator<<(std::ostream& stream, const Triangle& triangle);
    friend std::istream& operator>>(std::istream& istream, Triangle& triangle);

    operator double();
};

class Square : public Figure {
public:
    Square();
    Square(const std::vector<double>& init);
    Square(const Square& other);
    Square(Square&& other) noexcept;

    std::vector<double> center() override;
    double area_calculate() override;

    bool operator==(const Square& other) const;
    Square& operator=(const Square& other);

    friend std::ostream& operator<<(std::ostream& stream, const Square& square);
    friend std::istream& operator>>(std::istream& istream, Square& square);

    operator double();
};

class Octagon : public Figure {
public:
    Octagon();
    Octagon(const std::vector<double>& init);
    Octagon(const Octagon& other);
    Octagon(Octagon&& other) noexcept;

    std::vector<double> center() override;
    double area_calculate() override;

    bool operator==(const Octagon& other) const;
    Octagon& operator=(const Octagon& other);

    friend std::ostream& operator<<(std::ostream& stream, const Octagon& octagon);
    friend std::istream& operator>>(std::istream& istream, Octagon& octagon);

    operator double();
};