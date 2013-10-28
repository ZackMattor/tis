#ifndef CAMERA2D_H
#define CAMERA2D_H

#include <allegro5/allegro.h>

class Camera2D
{
public:
    Camera2D();

    void startCamera();
    void stopCamera();

    void setX(int X);
    void setY(int Y);
    void setRotation(float rotation);

    ALLEGRO_TRANSFORM getCamera() const;
private:
    ALLEGRO_TRANSFORM m_camera;
    ALLEGRO_TRANSFORM m_identity;
    int m_x, m_y;
    float m_rotation;
};

#endif // CAMERA2D_H
