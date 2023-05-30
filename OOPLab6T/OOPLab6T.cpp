#include <iostream>
#include <cmath>

class Equation {
public:
    virtual void solve() = 0;
};

class LinearEquation : public Equation {
private:
    double a, b;

public:
    LinearEquation(double a, double b) : a(a), b(b) {}

    void solve() override {
        if (a != 0) {
            double x = -b / a;
            std::cout << "Linear equation solution: x = " << x << std::endl;
        } else {
            std::cout << "Invalid linear equation (a = 0)" << std::endl;
        }
    }
};

class QuadraticEquation : public Equation {
private:
    double a, b, c;

public:
    QuadraticEquation(double a, double b, double c) : a(a), b(b), c(c) {}

    void solve() override {
        double discriminant = b * b - 4 * a * c;
        if (discriminant > 0) {
            double x1 = (-b + std::sqrt(discriminant)) / (2 * a);
            double x2 = (-b - std::sqrt(discriminant)) / (2 * a);
            std::cout << "Quadratic equation solutions: x1 = " << x1 << ", x2 = " << x2 << std::endl;
        } else if (discriminant == 0) {
            double x = -b / (2 * a);
            std::cout << "Quadratic equation solution (double root): x = " << x << std::endl;
        } else {
            std::cout << "Quadratic equation has no real solutions" << std::endl;
        }
    }
};

class BiquadraticEquation : public Equation {
private:
    double a, b;

public:
    BiquadraticEquation(double a, double b) : a(a), b(b) {}

    void solve() override {
        double squareRoot = std::sqrt(b);
        if (squareRoot * squareRoot == b) {
            double x1 = std::sqrt(a) + squareRoot;
            double x2 = std::sqrt(a) - squareRoot;
            std::cout << "Biquadratic equation solutions: x1 = " << x1 << ", x2 = " << x2 << std::endl;
        } else {
            std::cout << "Biquadratic equation has no real solutions" << std::endl;
        }
    }
};

int main() {
    LinearEquation linear(2, -3);
    QuadraticEquation quadratic(1, -5, 6);
    BiquadraticEquation biquadratic(9, 16);

    Equation* equations[] = {&linear, &quadratic, &biquadratic};

    for (int i = 0; i < 3; i++) {
        equations[i]->solve();
    }

    return 0;
}
