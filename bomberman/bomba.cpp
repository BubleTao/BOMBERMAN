#include "bomba.h"
#include <QPixmap>
#include <QTimer>
#include <QGraphicsScene>

Bomba::Bomba()
{
    // Cargar la imagen de la bomba desde el archivo de imagen
    QPixmap bombaImage("D:/Descargas/bomberman/bomba.png"); // Ajusta la ruta de la imagen según sea necesario
    setPixmap(bombaImage.scaled(20, 10)); // Escalar la imagen de la bomba
}
