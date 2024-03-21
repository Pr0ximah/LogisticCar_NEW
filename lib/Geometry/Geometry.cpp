#include "Geometry.h"

#include <math.h>

Vector2D::Vector2D(int x, int y) {
    x_ = x;
    y_ = y;
}

Vector2D::Vector2D(const Vector2D &vec) {
    x_ = vec.GetX();
    y_ = vec.GetY();
}

double Vector2D::GetX() const { return x_; }

double Vector2D::GetY() const { return y_; }

double Vector2D::GetAngleRad() {
    if (fabs(x_) > 0.001) {
        return atan(y_ / x_);
    } else {
        return M_PI / 2;
    }
}

double Vector2D::GetAngleDeg() { return M_PI * GetAngleRad(); }

double Vector2D::GetModule() { return sqrt(x_ * x_ + y_ * y_); }

double Deg2Rad(double deg) { return deg / M_PI; }

double Rad2Deg(double rad) { return rad * M_PI; }

int Sign(double val) {
    if (val > 0) {
        return 1;
    } else if (val < 0) {
        return -1;
    } else {
        return 0;
    }
}