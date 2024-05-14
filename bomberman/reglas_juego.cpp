#include "reglas_juego.h"


reglas_juego::reglas_juego(QGraphicsView *graph, QVector<QLabel *> game_labels)
{
    srand(time(NULL));

    this->graph = graph;
    labels = game_labels;
    setup_scene();
    setup_bomberman();
    generate_map();

    bombaActual = nullptr;
}

reglas_juego::~reglas_juego()
{
    delete scene;
}

void reglas_juego::key_event(QKeyEvent *event)
{
    bool is_valid = true;

    if(unsigned(event->key()) == bomberman_keys[0]) is_valid = left_movement_is_valid(bomberman);
    else if(unsigned(event->key()) == bomberman_keys[1]) is_valid = right_movement_is_valid(bomberman);
    else if(unsigned(event->key()) == bomberman_keys[2]) is_valid = up_movement_is_valid(bomberman);
    else if(unsigned(event->key()) == bomberman_keys[3]) is_valid = down_movement_is_valid(bomberman);

    if(bomberman->x()<700 && bomberman->x()>230) set_focus_element(bomberman,bomberman_pixel_x_size*game_scale_factor,0);

    bomberman->move(event->key(),is_valid);

    if (event->key() == Qt::Key_Space) {
        // Presionar la tecla de espacio crea una bomba y la coloca en la escena
        placeBomb();
    }
}

void reglas_juego::set_bomberman_keys()
{
    bomberman_keys[0] = Qt::Key_A;
    bomberman_keys[1] = Qt::Key_D;
    bomberman_keys[2] = Qt::Key_W;
    bomberman_keys[3] = Qt::Key_S;
}

void reglas_juego::generate_map()
{
    for(unsigned int fil = 0; fil < game_map_rows; fil++){
        for(unsigned int col = 0; col< game_map_col; col++){
            if(fil == 0 || fil == game_map_rows-1 || col == 0 || col == game_map_col -1 || (col%2==0 && fil%2==0)) blocks[fil][col] = new escenario(game_scale_factor,1);
            else if(bernoulli_event() && !(fil==1 && col==1) && !(fil==1 && col==2) && !(fil==2 && col==1)) blocks[fil][col] = new escenario(game_scale_factor,2);
            else blocks[fil][col] = new escenario(game_scale_factor,0);
            blocks[fil][col]->setX(game_scale_factor*blocks_pixel_x_size*col);
            blocks[fil][col]->setY(game_scale_factor*blocks_pixel_y_size*fil);
            scene->addItem(blocks[fil][col]);
        }
    }
}

void reglas_juego::setup_scene()
{

    graph->setGeometry(0,0,
                       game_scale_factor*blocks_pixel_x_size*game_map_size_col,
                       game_scale_factor*blocks_pixel_y_size*game_map_size_fil);
    scene = new QGraphicsScene;
    scene->setSceneRect(0,0,graph->width()-2, graph->height()-2);
    graph->setScene(scene);
    scene->setBackgroundBrush(set_rgb_color(56,135,0));
}

void reglas_juego::setup_bomberman()
{
    set_bomberman_keys();

    bomberman = new personaje(game_scale_factor);
    bomberman->set_keys(bomberman_keys);
    scene->addItem(bomberman);
}

bool reglas_juego::bernoulli_event()
{
    return (rand()/float(RAND_MAX)) < difficult;
}

bool reglas_juego::left_movement_is_valid(QGraphicsPixmapItem *item)
{
    int xf1,yf1,xf2,yf2;
    bool is_valid1, is_valid2;

    xf1 = item->x()-bomberman_speed;
    yf1 = item->y();
    xf2 = item->x()-bomberman_speed;
    yf2 = item->y()+(bomberman_pixel_y_size*game_scale_factor)-1;

    is_valid1 = blocks[yf1/(bomberman_pixel_y_size*game_scale_factor)][xf1/(bomberman_pixel_x_size*game_scale_factor)]->get_type()==0;
    is_valid2 = blocks[yf2/(bomberman_pixel_y_size*game_scale_factor)][xf2/(bomberman_pixel_x_size*game_scale_factor)]->get_type()==0;

    return is_valid2 && is_valid1;
}

bool reglas_juego::right_movement_is_valid(QGraphicsPixmapItem *item)
{
    int xf1,yf1,xf2,yf2;
    bool is_valid1, is_valid2;

    xf1 = item->x()+(bomberman_pixel_x_size*game_scale_factor)-1+bomberman_speed;
    yf1 = item->y();
    xf2 = item->x()+(bomberman_pixel_x_size*game_scale_factor)-1+bomberman_speed;
    yf2 = item->y()+(bomberman_pixel_y_size*game_scale_factor)-1;

    is_valid1 = blocks[yf1/(bomberman_pixel_y_size*game_scale_factor)][xf1/(bomberman_pixel_x_size*game_scale_factor)]->get_type()==0;
    is_valid2 = blocks[yf2/(bomberman_pixel_y_size*game_scale_factor)][xf2/(bomberman_pixel_x_size*game_scale_factor)]->get_type()==0;

    return is_valid2 && is_valid1;
}

bool reglas_juego::up_movement_is_valid(QGraphicsPixmapItem *item)
{
    int xf1,yf1,xf2,yf2;
    bool is_valid1, is_valid2;

    xf1 = item->x();
    yf1 = item->y() - bomberman_speed;
    xf2 = item->x() +(bomberman_pixel_x_size*game_scale_factor)-1;
    yf2 = item->y() - bomberman_speed;

    is_valid1 = blocks[yf1/(bomberman_pixel_y_size*game_scale_factor)][xf1/(bomberman_pixel_x_size*game_scale_factor)]->get_type()==0;
    is_valid2 = blocks[yf2/(bomberman_pixel_y_size*game_scale_factor)][xf2/(bomberman_pixel_x_size*game_scale_factor)]->get_type()==0;

    return is_valid2 && is_valid1;
}

bool reglas_juego::down_movement_is_valid(QGraphicsPixmapItem *item)
{
    int xf1,yf1,xf2,yf2;
    bool is_valid1, is_valid2;

    xf1 = item->x();
    yf1 = item->y() + bomberman_speed+(bomberman_pixel_y_size*game_scale_factor)-1;
    xf2 = item->x()+(bomberman_pixel_x_size*game_scale_factor)-1;
    yf2 = item->y()+(bomberman_pixel_y_size*game_scale_factor)-1 +bomberman_speed;

    is_valid1 = blocks[yf1/(bomberman_pixel_y_size*game_scale_factor)][xf1/(bomberman_pixel_x_size*game_scale_factor)]->get_type()==0;
    is_valid2 = blocks[yf2/(bomberman_pixel_y_size*game_scale_factor)][xf2/(bomberman_pixel_x_size*game_scale_factor)]->get_type()==0;

    return is_valid2 && is_valid1;
}

void reglas_juego::set_focus_element(QGraphicsPixmapItem *item,unsigned int scalex, unsigned int scaley)
{
    scene->setSceneRect(item->x()+scalex-scene->width()/2,0,scene->width(),scene->height());
}

QBrush reglas_juego::set_rgb_color(int r, int g, int b, int a)
{
    QBrush color;

    color.setColor(QColor::fromRgb(r,g,b,a));
    color.setStyle(Qt::SolidPattern);

    return color;
}

void reglas_juego::placeBomb()
{
    // Crear una bomba y agregarla a la escena
    Bomba *bomba = new Bomba();
    scene->addItem(bomba);

    // Puedes configurar aquí cualquier lógica adicional de la bomba, por ejemplo, su posición
    bomba->setPos(bomberman->x(), bomberman->y());
}
