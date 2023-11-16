#ifndef LEDLIGHT_H
#define LEDLIGHT_H
#include <QGraphicsRectItem>
#include <QGraphicsItem>


QColor& getNextColor(int idx);


class ledlight : public QGraphicsItem
{
    QColor color;
    QRect bounds;
public:
    ledlight();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void setRect(const QRect& r);
    void setColor(const QColor c) { color = c; };

signals:
    void onPacket(const QByteArray& data);

public slots:

    void hPacket(const QByteArray& data);

};

#endif // LEDLIGHT_H
