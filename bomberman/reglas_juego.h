#ifndef REGLAS_JUEGO_H
#define REGLAS_JUEGO_H

#include <QWidget>
#include <QVector>
#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <cstdlib>
#include <ctime>
#include <QObject>
#include <QGraphicsPixmapItem>

#include "personaje.h"
#include "escenario.h"
#include "bomba.h"

#define game_scale_factor 2
#define game_map_rows 13
#define game_map_col 31
#define game_map_size_col 16
#define game_map_size_fil 13

class reglas_juego
{
public:
    reglas_juego(QGraphicsView *graph, QVector<QLabel *> game_labels);
    ~reglas_juego();
    void key_event(QKeyEvent *event);

public slots:
    void placeBomb();

private:
    QGraphicsView *graph;
    QVector<QLabel *> labels;
    QGraphicsScene *scene;
    personaje *bomberman;
    escenario *blocks[game_map_rows][game_map_col];
    unsigned int bomberman_keys[4];
    float difficult = 0.2;

    void set_bomberman_keys();
    void generate_map();
    void setup_scene();
    void setup_bomberman();
    bool bernoulli_event();
    bool left_movement_is_valid(QGraphicsPixmapItem *item);
    bool right_movement_is_valid(QGraphicsPixmapItem *item);
    bool up_movement_is_valid(QGraphicsPixmapItem *item);
    bool down_movement_is_valid(QGraphicsPixmapItem *item);
    void set_focus_element(QGraphicsPixmapItem *item, unsigned int scalex, unsigned int scaley);
    QBrush set_rgb_color(int r, int g, int b, int a = 255);

    Bomba *bombaActual;
    bool canPlaceBomb = true;
};



#endif // REGLAS_JUEGO_H
