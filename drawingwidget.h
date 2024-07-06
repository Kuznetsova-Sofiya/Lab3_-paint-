#ifndef DRAWINGWIDGET_H
#define DRAWINGWIDGET_H

#include <QWidget>
#include <QImage>
#include <QPoint>
#include <QPushButton>

enum class DrawMode { None, Rectangle, Triangle, Ellipse };

class DrawingWidget : public QWidget
{
    Q_OBJECT

public:
    DrawingWidget(QWidget *parent = nullptr);
    ~DrawingWidget();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void saveImage();
    void openImage();
    void toggleEraserMode();
    void setDrawRectangleMode();
    void setDrawTriangleMode();
    void setDrawEllipseMode();

private:
    QImage image;
    QPoint lastPoint;
    bool drawing;
    bool erasing;
    DrawMode drawMode;
    QRect currentRect;
    QPolygonF currentPolygon;
    QPushButton *saveButton;
    QPushButton *openButton;
    QPushButton *eraseButton;
    QPushButton *drawRectangleButton;
    QPushButton *drawTriangleButton;
    QPushButton *drawEllipseButton;

    void drawCurrentShape(QPainter &painter);
};

#endif // DRAWINGWIDGET_H
