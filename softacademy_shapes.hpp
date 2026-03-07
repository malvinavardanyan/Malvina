#ifndef SOFTACADEMY_SHAPES_HPP
#define SOFTACADEMY_SHAPES_HPP

#include <cstddef>
#include <stdexcept>
#include <cmath>
#include <math.h>
#include <iostream>
namespace softacademy {

    class Shape {
    public:
        virtual ~Shape() = default;

        virtual double area() const = 0;
        virtual double perimeter() const = 0;
    };

    class Circle final : public Shape {
    public:
        explicit Circle(double radius)
            :m_radius(radius) {
            if (radius <= 0) {
                throw std::invalid_argument("invalid argument");
            }
        }

        double radius() const noexcept {
            return m_radius;
        }

        double area() const override {
            return M_PI * m_radius * m_radius;
        }
        double perimeter() const override {
            return 2 * M_PI * m_radius;
        }

    private:
        double m_radius;
    };

    class Rectangle final : public Shape {
    public:
        Rectangle(double width, double height)
            :m_width(width)
            , m_height(height) {
            if (m_width <= 0 || m_height <= 0) {
                throw std::invalid_argument("invalid argument");
            }
        }

        double width() const noexcept {
            return m_width;
        }
        double height() const noexcept {
            return m_height;
        }

        double area() const override {
            return m_height * m_width;
        }
        double perimeter() const override {
            return 2 * (m_height + m_width);
        }

    private:
        double m_width;
        double m_height;
    };

    class Triangle final : public Shape {
    public:
        Triangle(double a, double b, double c)
            :m_a(a)
            , m_b(b)
            , m_c(c) {
            valid_triangle(a, b, c);
        }

        double a() const noexcept {
            return m_a;
        }
        double b() const noexcept {
            return m_b;
        }
        double c() const noexcept {
            return m_c;
        }

        double area() const override {
            double p = (m_a + m_b + m_c) / 2;
            return std::sqrt(p * (p - m_a) * (p - m_b) * (p - m_c));
        }
        double perimeter() const override {
            return m_a + m_b + m_c;
        }

    private:
        double m_a;
        double m_b;
        double m_c;

    private:
        void valid_triangle(double a, double b, double c) const {
            if (a <= 0 || b <= 0 || c <= 0) {
                throw std::invalid_argument("invalid argument");
            }
            if (a >= b + c || b >= c + a || c >= b + a) {
                throw std::invalid_argument("invalid argument");
            }
        }
    };

} // namespace softacademy

#endif // SOFTACADEMY_SHAPES_HPP
