#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <QSharedDataPointer>

class Vector2DData : public QSharedData {
public:
    float X;
    float Y;
};

class Vector2D
{
public:
    Vector2D(float x = 0, float y = 0);
    Vector2D(const Vector2D &);
    Vector2D &operator=(const Vector2D &);

    static Vector2D zero();

    float X() const;
    float Y() const;
    void setX(float x);
    void setY(float y);

    float length() const;
    float lengthSquared() const;
    float normalize();
    float dotProduct(const Vector2D &other) const;
    Vector2D reverse() const;
    void reflect(const Vector2D& norm);
    void rotate(float angle);

    Vector2D operator+(const Vector2D &rhs) const;
    Vector2D operator-(const Vector2D &rhs) const;
    Vector2D operator*(const Vector2D &rhs) const;
    Vector2D operator*(float scalar) const;
    Vector2D operator/(const Vector2D &rhs) const;
    Vector2D operator/(float scalar) const;

    Vector2D operator+=(const Vector2D &rhs);
    Vector2D operator-=(const Vector2D &rhs);
    Vector2D operator*=(const Vector2D &rhs);
    Vector2D operator*=(float scalar);
    Vector2D operator/=(const Vector2D &rhs);
    Vector2D operator/=(float scalar);
    bool operator==(const Vector2D& rhs) const;
    bool operator!=(const Vector2D& rhs) const;
    
private:
    QSharedDataPointer<Vector2DData> d;
};

#endif // VECTOR2D_H
