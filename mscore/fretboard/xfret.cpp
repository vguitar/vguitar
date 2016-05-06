#include "xfret.h"
#include <QVector>
#include <QPainter>
#include <QLinearGradient>
#include <QPalette>
#include "xhighlight.h"

namespace vg
{
    XFret::XFret(QGraphicsItem *parent): QGraphicsRectItem(parent) {}

    void XFret::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {
        Q_UNUSED(option);
        Q_UNUSED(widget);

        painter->setRenderHint(QPainter::Antialiasing);

        QLinearGradient gradient(rect().topLeft(), rect().topRight());

        gradient.setColorAt(0, QColor("#333"));
        gradient.setColorAt(0.5, QColor("#eee"));
        gradient.setColorAt(1, QColor("#333"));

        painter->setPen(Qt::NoPen);
        painter->fillRect(rect(), gradient);
    }

    XDot::XDot(QGraphicsItem *parent, int n): XHighlight(parent, 15), dotNumber(n)
    {
        setRadialColors("#999", "#eee");
        setBorderColor("#eee");
    }


}