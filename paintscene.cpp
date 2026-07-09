#include "paintscene.h"
#include <QPen>
#include <QBrush>
#include <QDebug>
#include <QtGlobal>

PaintScene::PaintScene(QObject* parent) : QGraphicsScene(parent) {
    currentType = Selection;
    lineColor = Qt::black;
    fillColor = Qt::white;
    lineWidth = 2;
    setSceneRect(0, 0, 800, 600);

    tempLine = nullptr;
    tempRect = nullptr;
    tempEllipse = nullptr;
}

void PaintScene::setDrawingType(FigureType type) {
    currentType = type;
    qDebug() << "Mode changed to:" << type;
}

void PaintScene::setLineColor(QColor color) { lineColor = color; }
void PaintScene::setFillColor(QColor color) { fillColor = color; }
void PaintScene::setLineWidth(int width) { lineWidth = width; }

void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    // ЛОГИКА ЛАСТИКА
    if (currentType == Eraser) {
        QGraphicsItem* itemToErase = itemAt(event->scenePos(), QTransform());
        if (itemToErase) {
            removeItem(itemToErase);
            delete itemToErase; // Полностью удаляем из оперативной памяти
        }
        return;
    }

    if (currentType == Selection) {
        QGraphicsScene::mousePressEvent(event);
        return;
    }

    startPoint = event->scenePos();
    QPen pen(lineColor, lineWidth);
    QBrush brush(fillColor);

    switch (currentType) {
    case Line:
        tempLine = new QGraphicsLineItem(QLineF(startPoint, startPoint));
        tempLine->setPen(pen);
        addItem(tempLine);
        break;

    case Rectangle:
        tempRect = new QGraphicsRectItem(QRectF(startPoint, QSizeF(0, 0)));
        tempRect->setPen(pen);
        tempRect->setBrush(brush);
        addItem(tempRect);
        break;

    case Ellipse:
        tempEllipse = new QGraphicsEllipseItem(QRectF(startPoint, QSizeF(0, 0)));
        tempEllipse->setPen(pen);
        tempEllipse->setBrush(brush);
        addItem(tempEllipse);
        break;

    default:
        break;
    }
}

void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    if (currentType == Selection || currentType == Eraser) {
        QGraphicsScene::mouseMoveEvent(event);
        return;
    }

    QPointF currentPoint = event->scenePos();

    if (currentType == Line && tempLine != nullptr) {
        tempLine->setLine(QLineF(startPoint, currentPoint));
    }
    else if (currentType == Rectangle && tempRect != nullptr) {
        qreal x = qMin(startPoint.x(), currentPoint.x());
        qreal y = qMin(startPoint.y(), currentPoint.y());
        qreal w = qAbs(startPoint.x() - currentPoint.x());
        qreal h = qAbs(startPoint.y() - currentPoint.y());
        tempRect->setRect(x, y, w, h);
    }
    else if (currentType == Ellipse && tempEllipse != nullptr) {
        qreal x = qMin(startPoint.x(), currentPoint.x());
        qreal y = qMin(startPoint.y(), currentPoint.y());
        qreal w = qAbs(startPoint.x() - currentPoint.x());
        qreal h = qAbs(startPoint.y() - currentPoint.y());
        tempEllipse->setRect(x, y, w, h);
    }
}

void PaintScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    if (currentType == Selection || currentType == Eraser) {
        QGraphicsScene::mouseReleaseEvent(event);
        return;
    }

    if (tempLine != nullptr) {
        tempLine->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
        tempLine = nullptr;
    }
    else if (tempRect != nullptr) {
        tempRect->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
        tempRect = nullptr;
    }
    else if (tempEllipse != nullptr) {
        tempEllipse->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
        tempEllipse = nullptr;
    }
}