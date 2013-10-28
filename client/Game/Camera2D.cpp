#include "Camera2D.h"

Camera2D::Camera2D()
    :m_x(0), m_y(0), m_rotation(0)
{
    al_identity_transform(&m_identity);

    al_build_transform(&m_camera, 0, 0, 1, 1, m_rotation);
}

void Camera2D::startCamera()
{
    al_build_transform(&m_camera,m_x, m_y, 1, 1, m_rotation);

    al_use_transform(&m_camera);
}

void Camera2D::stopCamera()
{
    al_use_transform(&m_identity);
}

void Camera2D::setX(int X)
{
    m_x = X;
}

void Camera2D::setY(int Y)
{
    m_y = Y;
}

void Camera2D::setRotation(float rotation)
{
    m_rotation = rotation;
}

ALLEGRO_TRANSFORM Camera2D::getCamera() const
{
    return m_camera;
}
