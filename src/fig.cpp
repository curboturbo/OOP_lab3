#include "f.h"



Figure::Figure() = default;
Figure::~Figure() noexcept = default;

double Figure::area_calculate() { return 0; }
std::vector<double> Figure::center() { return {}; }



Array::Array() {
    array = new Figure*[0];
    size = 0;
}

Array::Array(const Array& other) : size(other.size) {
    array = new Figure*[other.size];
    for (size_t i = 0; i < other.size; i++) {
        array[i] = other.array[i];
    }
}

Array::Array(Array&& other) noexcept
    : array(other.array), size(other.size) {
    other.array = nullptr;
    other.size = 0;
}

Array::~Array() noexcept {
    delete[] array;
    size = 0;
}

void Array::add_figure(Figure* figure) {
    Figure** resized_array = new Figure*[size + 1];
    for (size_t i = 0; i < size; i++) {
        resized_array[i] = array[i];
    }
    resized_array[size] = figure;
    size += 1;
    delete[] array;
    array = resized_array;
}

void Array::delete_by_index(int index) {
    if (index >= 0 && index < size) {
        int shift = 0;
        Figure** resized_array = new Figure*[size - 1];
        for (size_t i = 0; i < size; i++) {
            if (i == index) {
                shift += 1;
                continue;
            } else {
                resized_array[i - shift] = array[i];
            }
        }
        delete[] array;
        array = resized_array;
        size -= 1;
    } else if (size == 0) {
        throw std::invalid_argument("Clause is empty");
    } else {
        throw std::invalid_argument("Index does not exist");
    }
}

double Array::summary_square() {
    double S = 0;
    for (int i = 0; i < size; i++) {
        S += (*array[i]).area_calculate();
    }
    return S;
}



Triangle::Triangle() {
    coordinates = {};
}

Triangle::Triangle(const std::vector<double>& init) {
    coordinates = init;
}

Triangle::Triangle(const Triangle& other) {
    coordinates = other.coordinates;
}

Triangle::Triangle(Triangle&& other) noexcept {
    coordinates = std::move(other.coordinates);
}

double Triangle::area_calculate() {
    double a = std::sqrt(std::pow(coordinates[0] - coordinates[2], 2) + std::pow(coordinates[1] - coordinates[3], 2));
    double b = std::sqrt(std::pow(coordinates[0] - coordinates[4], 2) + std::pow(coordinates[1] - coordinates[5], 2));
    double c = std::sqrt(std::pow(coordinates[2] - coordinates[4], 2) + std::pow(coordinates[3] - coordinates[5], 2));
    double per = (a + b + c) / 2;
    return std::sqrt(per * (per - a) * (per - b) * (per - c));
}

std::vector<double> Triangle::center() {
    double x = (coordinates[0] + coordinates[2] + coordinates[4]) / 3;
    double y = (coordinates[1] + coordinates[3] + coordinates[5]) / 3;
    return {x, y};
}

bool Triangle::operator==(const Triangle& other) const {
    const double epsilon = 1e-9;
    if (coordinates.size() != other.coordinates.size())
        return false;

    for (size_t i = 0; i < coordinates.size(); ++i) {
        if (std::abs(coordinates[i] - other.coordinates[i]) > epsilon)
            return false;
    }
    return true;
}

Triangle& Triangle::operator=(const Triangle& other) {
    if (this != &other) {
        coordinates = other.coordinates;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& stream, const Triangle& triangle) {
    stream << "figure: triangle\n";
    for (size_t i = 0; i < triangle.coordinates.size(); i += 2) {
        stream << '(' << triangle.coordinates[i] << ',' << triangle.coordinates[i + 1] << ')';
        stream << '\n';
    }
    return stream;
}

std::istream& operator>>(std::istream& istream, Triangle& triangle) {
    std::cout << "Define triangle like a list of 6 element, if will be equal (x1,y1,x2,y2,x3,y3)" << std::endl;
    triangle.coordinates.resize(6);
    for (int i = 0; i < 6; i++) {
        istream >> triangle.coordinates[i];
    }
    return istream;
}

Triangle::operator double() {
    return area_calculate();
}


Square::Square() {
    coordinates = {};
}

Square::Square(const std::vector<double>& init) {
    coordinates = init;
}

Square::Square(const Square& other) {
    coordinates = other.coordinates;
}

Square::Square(Square&& other) noexcept {
    coordinates = std::move(other.coordinates);
}

std::vector<double> Square::center() {
    const double epsilon = 1e-9;
    double x = coordinates[0];
    double y = coordinates[1];
    double x1 = 0;
    double y1 = 0;
    for (int i = 2; i < coordinates.size() - 1; i += 2) {
        if (std::abs(x - coordinates[i]) > epsilon && std::abs(y - coordinates[i + 1]) > epsilon) {
            x1 = coordinates[i];
            y1 = coordinates[i + 1];
        }
    }
    return {(x1 + x) / 2, (y1 + y) / 2};
}

double Square::area_calculate() {
    double x = coordinates[0];
    double y = coordinates[1];
    double x1;
    double y1;
    const double epsilon = 1e-9;
    for (int i = 2; i < coordinates.size() - 1; i += 2) {
        if (std::abs(x - coordinates[i]) < epsilon || std::abs(y - coordinates[i + 1]) < epsilon) {
            x1 = coordinates[i];
            y1 = coordinates[i + 1];
            break;
        }
    }
    double length = std::sqrt(std::pow(x - x1, 2) + std::pow(y - y1, 2));
    return length * length;
}

bool Square::operator==(const Square& other) const {
    const double epsilon = 1e-9;
    if (coordinates.size() != other.coordinates.size())
        return false;

    for (size_t i = 0; i < coordinates.size(); ++i) {
        if (std::abs(coordinates[i] - other.coordinates[i]) > epsilon)
            return false;
    }
    return true;
}

Square& Square::operator=(const Square& other) {
    if (this != &other) {
        coordinates = other.coordinates;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& stream, const Square& square) {
    stream << "figure: square\n";
    for (size_t i = 0; i < square.coordinates.size(); i += 2) {
        stream << '(' << square.coordinates[i] << ',' << square.coordinates[i + 1] << ')';
        stream << '\n';
    }
    return stream;
}

std::istream& operator>>(std::istream& istream, Square& square) {
    std::cout << "Define square like a list of 8 element, if will be equal (x1,y1,x2,y2,x3,y3,x4,y4)" << std::endl;
    square.coordinates.resize(8);
    for (int i = 0; i < 8; i++) {
        istream >> square.coordinates[i];
    }
    return istream;
}

Square::operator double() {
    return area_calculate();
}



Octagon::Octagon() {
    coordinates = {};
}

Octagon::Octagon(const std::vector<double>& init) {
    coordinates = init;
}

Octagon::Octagon(const Octagon& other) {
    coordinates = other.coordinates;
}

Octagon::Octagon(Octagon&& other) noexcept {
    coordinates = std::move(other.coordinates);
}

std::vector<double> Octagon::center() {
    double x_sum = 0;
    double y_sum = 0;
    for (int i = 0; i < 16; i++) {
        if (i % 2 == 0) {
            x_sum += coordinates[i];
        } else {
            y_sum += coordinates[i];
        }
    }
    return {x_sum / 8, y_sum / 8};
}

double Octagon::area_calculate() {
    int n = coordinates.size();
    int points = n / 2;
    double S = 0;
    for (int i = 0; i < n - 3; i += 2) {
        S += coordinates[i] * coordinates[i + 3];
    }
    S += coordinates[0] * coordinates[n - 1];
    for (int i = 1; i < n - 2; i += 2) {
        S -= coordinates[i] * coordinates[i + 1];
    }
    S -= coordinates[n - 2] * coordinates[1];
    return std::abs(S) / 2.0;
}

bool Octagon::operator==(const Octagon& other) const {
    const double epsilon = 1e-9;
    if (coordinates.size() != other.coordinates.size())
        return false;

    for (size_t i = 0; i < coordinates.size(); ++i) {
        if (std::abs(coordinates[i] - other.coordinates[i]) > epsilon)
            return false;
    }
    return true;
}

Octagon& Octagon::operator=(const Octagon& other) {
    if (this != &other) {
        coordinates = other.coordinates;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& stream, const Octagon& octagon) {
    stream << "figure: octagon\n";
    for (size_t i = 0; i < octagon.coordinates.size(); i += 2) {
        stream << '(' << octagon.coordinates[i] << ',' << octagon.coordinates[i + 1] << ')';
        stream << '\n';
    }
    return stream;
}

std::istream& operator>>(std::istream& istream, Octagon& octagon) {
    std::cout << "Define octagon like a list of 8 element, it will be equal (x1,y1,x2,y2,x3,y3,...,x8,y8)" << std::endl;
    octagon.coordinates.resize(16);
    for (int i = 0; i < 16; i++) {
        istream >> octagon.coordinates[i];
    }
    return istream;
}

Octagon::operator double() {
    return area_calculate();
}

