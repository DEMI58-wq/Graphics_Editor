#pragma once

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QColor>
#include <QDebug>

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

    PaintScene(QObject* parent = nullptr) : QGraphicsScene(parent) {
        currentType = Selection;
        lineColor = Qt::black;
        fillColor = Qt::white;
        lineWidth = 2;
        setSceneRect(0, 0, 800, 600);
    }

    void setDrawingType(FigureType type) {
        currentType = type;
        qDebug() << "Режим изменен:" << type;
    }

    void setLineColor(QColor color) {
        lineColor = color;
        qDebug() << "Цвет линии изменен";
    }

    void setFillColor(QColor color) {
        fillColor = color;
        qDebug() << "Цвет заливки изменен";
    }

    void setLineWidth(int width) {
        lineWidth = width;
        qDebug() << "Толщина линии изменена на:" << width;
    }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override {
        QGraphicsScene::mousePressEvent(event);
    }

    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override {
        QGraphicsScene::mouseMoveEvent(event);
    }

    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override {
        QGraphicsScene::mouseReleaseEvent(event);
    }

private:
    FigureType currentType;
    QColor lineColor;
    QColor fillColor;
    int lineWidth;
};