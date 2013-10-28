#include "Vector2D.h"
#include <QSharedData>

#include <math.h>

Vector2D::Vector2D(float x, float y)
    : d(new Vector2DData)
{
    d->X = x;
    d->Y = y;
}

Vector2D::Vector2D(const Vector2D &rhs)
    : d(rhs.d)
{
}

Vector2D Vector2D::zero()
{
    return Vector2D(0, 0);
}

float Vector2D::X() const
{
    return d->X;
}

float Vector2D::Y() const
{
    return d->Y;
}

void Vector2D::setX(float x)
{
    d->X = x;
}

void Vector2D::setY(float y)
{
    d->Y = y;
}


float Vector2D::length() const
{
    return sqrtf(d->X * d->X + d->Y * d->Y);
}

float Vector2D::lengthSquared() const
{
    return d->X * d->X + d->Y * d->Y;
}

float Vector2D::normalize()
{
    float len = length();

    if(len != 0.0)
    {
        d->X /= len;
        d->Y /= len;
    }

    return len;
}

float Vector2D::dotProduct(const Vector2D &other) const
{
    return (d->X * other.X()) + (d->Y * other.Y());
}

Vector2D Vector2D::reverse() const
{
    return Vector2D(-d->X, -d->Y);
}

void Vector2D::reflect(const Vector2D &norm)
{
    *this += norm.reverse() * dotProduct(norm) * 2.0f;
}

void Vector2D::rotate(float angle)
{
    float xt = (d->X * cosf(angle)) - (d->Y * sinf(angle));
    float yt = (d->Y * cosf(angle)) + (d->X * sinf(angle));
    d->X = xt;
    d->Y = yt;
}

Vector2D &Vector2D::operator=(const Vector2D &rhs)
{
    if (this != &rhs)
        d.operator=(rhs.d);
    return *this;
}

Vector2D Vector2D::operator+(const Vector2D &rhs) const
{
    return Vector2D(d->X + rhs.X(), d->Y + rhs.Y());
}

Vector2D Vector2D::operator-(const Vector2D &rhs) const
{
    return Vector2D(d->X - rhs.X(), d->Y - rhs.Y());
}

Vector2D Vector2D::operator*(const Vector2D &rhs) const
{
    return Vector2D(d->X * rhs.X(), d->Y * rhs.Y());
}

Vector2D Vector2D::operator*(float scalar) const
{
    return Vector2D(d->X * scalar, d->Y * scalar);
}

Vector2D Vector2D::operator/(const Vector2D &rhs) const
{
    return Vector2D(d->X / rhs.X(), d->Y / rhs.Y());
}

Vector2D Vector2D::operator/(float scalar) const
{
    return Vector2D(d->X / scalar, d->Y / scalar);
}

Vector2D Vector2D::operator+=(const Vector2D &rhs)
{
    d->X += rhs.X();
    d->Y += rhs.Y();

    return *this;
}

Vector2D Vector2D::operator-=(const Vector2D &rhs)
{
    d->X -= rhs.X();
    d->Y -= rhs.Y();

    return *this;
}

Vector2D Vector2D::operator*=(const Vector2D &rhs)
{
    d->X *= rhs.X();
    d->Y *= rhs.Y();

    return *this;
}

Vector2D Vector2D::operator*=(float scalar)
{
    d->X *= scalar;
    d->Y *= scalar;

    return *this;
}

Vector2D Vector2D::operator/=(const Vector2D &rhs)
{
    d->X /= rhs.X();
    d->Y /= rhs.Y();

    return *this;
}

Vector2D Vector2D::operator/=(float scalar)
{
    d->X /= scalar;
    d->Y /= scalar;

    return *this;
}

bool Vector2D::operator==(const Vector2D& rhs) const
{
    return ((d->X == rhs.X()) && (d->Y == rhs.Y()));
}

bool Vector2D::operator!=(const Vector2D& rhs) const
{
    return !((d->X == rhs.X()) && (d->Y == rhs.Y()));
}
