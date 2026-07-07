#pragma once

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QColor>
#include <QPointF>

class PaintScene : public QGraphicsScene {
    Q_OBJECT

public:
    enum FigureType {
        Selection,
        Line,
        Rectangle,
        Ellipse,
        Eraser
    };

    PaintScene(QObject* parent = nullptr);

    void setDrawingType(FigureType type);
    void setLineColor(QColor color);
    void setFillColor(QColor color);
    void setLineWidth(int width);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private:
    FigureType currentType;
    QColor lineColor;
    QColor fillColor;
    int lineWidth;
    QPointF startPoint;

    QGraphicsLineItem* tempLine;
    QGraphicsRectItem* tempRect;
    QGraphicsEllipseItem* tempEllipse;
};