#pragma once

#include <QMainWindow>
#include <QGraphicsView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include "paintscene.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr) : QMainWindow(parent) {
        QWidget* centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);

        scene = new PaintScene(this);
        view = new QGraphicsView(scene, this);
        view->setRenderHint(QPainter::Antialiasing);

        initUI();
        initConnections();

        QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);
        mainLayout->addLayout(toolsLayout);
        mainLayout->addWidget(view);

        resize(1000, 700);
    }

private slots:
    void slotSelectClicked() { scene->setDrawingType(PaintScene::Selection); }
    void slotLineClicked() { scene->setDrawingType(PaintScene::Line); }
    void slotRectClicked() { scene->setDrawingType(PaintScene::Rectangle); }
    void slotEllipseClicked() { scene->setDrawingType(PaintScene::Ellipse); }
    void slotEraserClicked() { scene->setDrawingType(PaintScene::Eraser); }

    void slotLineColorClicked() { scene->setLineColor(Qt::red); }
    void slotFillColorClicked() { scene->setFillColor(Qt::blue); }
    void slotLineWidthClicked() { scene->setLineWidth(5); }

    void slotSaveClicked() { qDebug() << "Нажата кнопка Сохранить"; }
    void slotLoadClicked() { qDebug() << "Нажата кнопка Загрузить"; }

private:
    void initUI() {
        btnSelection = new QPushButton("Выделение", this);
        btnLine = new QPushButton("Линия", this);
        btnRect = new QPushButton("Прямоугольник", this);
        btnEllipse = new QPushButton("Круг", this);
        btnEraser = new QPushButton("Ластик", this);
        btnLineColor = new QPushButton("Цвет линии", this);
        btnFillColor = new QPushButton("Цвет заливки", this);
        btnLineWidth = new QPushButton("Толщина линии", this);
        btnSave = new QPushButton("Сохранить", this);
        btnLoad = new QPushButton("Загрузить", this);
        btnClear = new QPushButton("Очистить", this);

        toolsLayout = new QVBoxLayout();
        toolsLayout->addWidget(btnSelection);
        toolsLayout->addWidget(btnLine);
        toolsLayout->addWidget(btnRect);
        toolsLayout->addWidget(btnEllipse);
        toolsLayout->addWidget(btnEraser);
        toolsLayout->addWidget(btnLineColor);
        toolsLayout->addWidget(btnFillColor);
        toolsLayout->addWidget(btnLineWidth);
        toolsLayout->addStretch();
        toolsLayout->addWidget(btnSave);
        toolsLayout->addWidget(btnLoad);
        toolsLayout->addWidget(btnClear);
    }

    void initConnections() {
        connect(btnSelection, SIGNAL(clicked()), this, SLOT(slotSelectClicked()));
        connect(btnLine, SIGNAL(clicked()), this, SLOT(slotLineClicked()));
        connect(btnRect, SIGNAL(clicked()), this, SLOT(slotRectClicked()));
        connect(btnEllipse, SIGNAL(clicked()), this, SLOT(slotEllipseClicked()));
        connect(btnEraser, SIGNAL(clicked()), this, SLOT(slotEraserClicked()));
        connect(btnLineColor, SIGNAL(clicked()), this, SLOT(slotLineColorClicked()));
        connect(btnFillColor, SIGNAL(clicked()), this, SLOT(slotFillColorClicked()));
        connect(btnLineWidth, SIGNAL(clicked()), this, SLOT(slotLineWidthClicked()));
        connect(btnSave, SIGNAL(clicked()), this, SLOT(slotSaveClicked()));
        connect(btnLoad, SIGNAL(clicked()), this, SLOT(slotLoadClicked()));
        connect(btnClear, SIGNAL(clicked()), scene, SLOT(clear()));
    }

    PaintScene* scene;
    QGraphicsView* view;
    QVBoxLayout* toolsLayout;

    QPushButton* btnLine;
    QPushButton* btnRect;
    QPushButton* btnEllipse;
    QPushButton* btnSelection;
    QPushButton* btnEraser;
    QPushButton* btnLineColor;
    QPushButton* btnFillColor;
    QPushButton* btnLineWidth;
    QPushButton* btnSave;
    QPushButton* btnLoad;
    QPushButton* btnClear;
};