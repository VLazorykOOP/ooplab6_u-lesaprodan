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

#include <iostream>
#include <string>

class Transport {
protected:
    std::string name;
public:
    Transport(const std::string& transportName) : name(transportName) {}
    virtual ~Transport() {}

    virtual void displayInfo() const {
        std::cout << "Transport: " << name << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const Transport& transport) {
        os << "Transport: " << transport.name;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Transport& transport) {
        is >> transport.name;
        return is;
    }
};

class Ship : virtual public Transport {
protected:
    int shipId;
public:
    Ship(const std::string& shipName, int id) : Transport(shipName), shipId(id) {}
    virtual ~Ship() {}

    virtual void displayInfo() const override {
        std::cout << "Ship Name: " << name << ", ID: " << shipId << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const Ship& ship) {
        os << static_cast<const Transport&>(ship) << ", ID: " << ship.shipId;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Ship& ship) {
        is >> static_cast<Transport&>(ship) >> ship.shipId;
        return is;
    }
};

class PassengerTransport : virtual public Transport {
protected:
    int passengerCapacity;
public:
    PassengerTransport(const std::string& transportName, int capacity) : Transport(transportName), passengerCapacity(capacity) {}
    virtual ~PassengerTransport() {}

    virtual void displayInfo() const override {
        std::cout << "Passenger Transport: " << name << ", Capacity: " << passengerCapacity << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const PassengerTransport& transport) {
        os << static_cast<const Transport&>(transport) << ", Capacity: " << transport.passengerCapacity;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, PassengerTransport& transport) {
        is >> static_cast<Transport&>(transport) >> transport.passengerCapacity;
        return is;
    }
};

class PassengerShip : public Ship, public PassengerTransport {
public:
    PassengerShip(const std::string& shipName, int id, int capacity)
        : Transport(shipName), Ship(shipName, id), PassengerTransport(shipName, capacity) {}

    virtual void displayInfo() const override {
        std::cout << "Passenger Ship Name: " << name << ", ID: " << shipId << ", Capacity: " << passengerCapacity << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const PassengerShip& ship) {
        os << static_cast<const Ship&>(ship) << ", Capacity: " << ship.passengerCapacity;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, PassengerShip& ship) {
        is >> static_cast<Transport&>(ship) >> static_cast<Ship&>(ship) >> ship.passengerCapacity;
        return is;
    }
};

int main() {
    PassengerShip ship("Titanic", 123, 2000);
    ship.displayInfo();

    std::cout << "Enter details for a passenger ship: ";
    std::cin >> ship;
    std::cout << ship << std::endl;

    return 0;
}
