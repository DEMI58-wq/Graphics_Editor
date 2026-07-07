#pragma once

#include <QMainWindow>
#include <QGraphicsView>
#include <QPushButton>
#include <QVBoxLayout>

class PaintScene;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void slotSelectClicked();
    void slotLineClicked();
    void slotRectClicked();
    void slotEllipseClicked();
    void slotEraserClicked();
    void slotLineColorClicked();
    void slotFillColorClicked();
    void slotLineWidthClicked();

private:
    void initUI();
    void initConnections();

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