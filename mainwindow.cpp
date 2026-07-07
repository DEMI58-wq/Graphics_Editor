#include "mainwindow.h"
#include "paintscene.h"
#include <QHBoxLayout>
#include <QColorDialog>
#include <QInputDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
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

MainWindow::~MainWindow() {}

void MainWindow::initUI() {
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

void MainWindow::initConnections() {
    connect(btnSelection, &QPushButton::clicked, this, &MainWindow::slotSelectClicked);
    connect(btnLine, &QPushButton::clicked, this, &MainWindow::slotLineClicked);
    connect(btnRect, &QPushButton::clicked, this, &MainWindow::slotRectClicked);
    connect(btnEllipse, &QPushButton::clicked, this, &MainWindow::slotEllipseClicked);
    connect(btnEraser, &QPushButton::clicked, this, &MainWindow::slotEraserClicked);
    connect(btnLineColor, &QPushButton::clicked, this, &MainWindow::slotLineColorClicked);
    connect(btnFillColor, &QPushButton::clicked, this, &MainWindow::slotFillColorClicked);
    connect(btnLineWidth, &QPushButton::clicked, this, &MainWindow::slotLineWidthClicked);
    connect(btnClear, &QPushButton::clicked, scene, &QGraphicsScene::clear);
}

void MainWindow::slotSelectClicked() { scene->setDrawingType(PaintScene::Selection); }
void MainWindow::slotLineClicked() { scene->setDrawingType(PaintScene::Line); }
void MainWindow::slotRectClicked() { scene->setDrawingType(PaintScene::Rectangle); }
void MainWindow::slotEllipseClicked() { scene->setDrawingType(PaintScene::Ellipse); }
void MainWindow::slotEraserClicked() { scene->setDrawingType(PaintScene::Eraser); }

void MainWindow::slotLineColorClicked() {
    QColor color = QColorDialog::getColor(Qt::black, this, "Цвет линии");
    if (color.isValid()) scene->setLineColor(color);
}

void MainWindow::slotFillColorClicked() {
    QColor color = QColorDialog::getColor(Qt::white, this, "Цвет заливки");
    if (color.isValid()) scene->setFillColor(color);
}

void MainWindow::slotLineWidthClicked() {
    bool ok;
    int width = QInputDialog::getInt(this, "Толщина", "Введите толщину:", 2, 1, 20, 1, &ok);
    if (ok) scene->setLineWidth(width);
}