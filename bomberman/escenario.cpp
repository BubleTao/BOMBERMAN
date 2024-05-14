#include "escenario.h"

escenario::escenario(unsigned int scale, unsigned int type)
{
    this->scale = scale;
    pixmap = new sprites(":/sprites.png",scale);
    pixmap->cut_character_pixmap(set_complete_sprites());
    pixmap->set_design_size(blocks_pixel_x_size,
                            blocks_pixel_y_size);

    this->type = type;
    set_type_block();
}

escenario::~escenario()
{
    delete pixmap;
}

unsigned int escenario::get_type()
{
    return type;
}

QRect escenario::set_complete_sprites()
{
    QRect dim;

    dim.setX(3*blocks_pixel_x_size);
    dim.setY(3*blocks_pixel_y_size);
    dim.setHeight(1*blocks_pixel_y_size);
    dim.setWidth(9*blocks_pixel_x_size);

    return dim;
}

QRect escenario::set_non_destructible_block()
{
    QRect dim;

    dim.setX(0);
    dim.setY(0);
    dim.setHeight(1*blocks_pixel_y_size);
    dim.setWidth(1*blocks_pixel_x_size);

    return dim;
}

QRect escenario::set_destructible_block()
{
    QRect dim;

    dim.setX(1*blocks_pixel_x_size);
    dim.setY(0);
    dim.setHeight(1*blocks_pixel_y_size);
    dim.setWidth(1*blocks_pixel_x_size);

    return dim;
}

void escenario::set_type_block()
{
    if(type == 1) setPixmap(pixmap->get_fixed_image(set_non_destructible_block()));
    else if(type == 2) setPixmap(pixmap->get_fixed_image(set_destructible_block()));
}
