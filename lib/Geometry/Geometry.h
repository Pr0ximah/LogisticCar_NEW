#ifndef _GEOMETRY_H
#define _GEOMETRY_H

/// @brief 几何向量类，用于数学运算
/// @date 2024.03.06
/// @example 示意图
/// y /
/// |/ angle
/// --x
class Vector2D {
private:
    double x_ = 0, y_ = 0;

public:
    Vector2D() = default;
    Vector2D(int x, int y);
    Vector2D(const Vector2D &vec);

    // 获取向量角度，逆时针为正 (radians)
    double GetAngleRad();

    // 获取向量角度，逆时针为正 (degrees)
    double GetAngleDeg();

    // 获取向量模长
    double GetModule();

    // 获取X坐标
    double GetX() const;

    // 获取Y坐标
    double GetY() const;
};

// 角度转换弧度
double Deg2Rad(double deg);

// 弧度转换角度
double Rad2Deg(double rad);

// 符号函数
int Sign(double val);

#endif  //_GEOMETRY_H