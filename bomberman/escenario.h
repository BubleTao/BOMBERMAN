#ifndef ESCENARIO_H
#define ESCENARIO_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "sprites.h"

#define blocks_pixel_x_size 16
#define blocks_pixel_y_size 16

class escenario : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    escenario(unsigned int scale, unsigned int type);
    ~escenario();
    unsigned int get_type();

private:
    sprites *pixmap;
    unsigned int scale, type;
    QRect set_complete_sprites();
    QRect set_non_destructible_block();
    QRect set_destructible_block();
    void set_type_block();
};

#endif // ESCENARIO_H
