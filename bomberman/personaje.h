#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "sprites.h"

#define bomberman_pixel_x_size 16
#define bomberman_pixel_y_size 16
#define bomberman_speed 8

class personaje : public QObject, public QGraphicsPixmapItem
{
public:
    personaje(unsigned int scale);
    void set_keys(unsigned int *keys);
    void move(unsigned int key, bool is_valid);
    ~personaje();

private:
    QRect set_complete_sprites();
    void set_animations();
    void set_left_animation();
    void set_right_animation();
    void set_up_animation();
    void set_down_animation();
    void set_death_animation();

    sprites *pixmap_management;
    unsigned int keys[4];
};

#endif // PERSONAJE_H
