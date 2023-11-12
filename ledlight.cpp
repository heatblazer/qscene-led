#include "ledlight.h"
#include <QPainter>

ledlight::ledlight() : color{0,0,0,0}
{
}

QRectF ledlight::boundingRect() const
{
    return QRectF(0,0,0,0);
}

void ledlight::setRect(const QRect& r)
{
    bounds = r;
}

QPainterPath ledlight::shape() const
{
    QPainterPath path;
    path.addRect(bounds);
    return path;
}

void ledlight::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
           QWidget *widget)
{
//    painter->setBrush(color);

    painter->fillRect(bounds, color);
    painter->drawRect(bounds);
    painter->setBrush(Qt::BrushStyle::Dense1Pattern);
}

void ledlight::hPacket(const QByteArray& arr)
{

}

