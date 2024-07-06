#include "drawingwidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QFileDialog>
#include <QKeyEvent>

DrawingWidget::DrawingWidget(QWidget *parent)
    : QWidget(parent), image(800, 600, QImage::Format_ARGB32), drawing(false), erasing(false), drawMode(DrawMode::None)
{
    image.fill(Qt::white);

    saveButton = new QPushButton("Сохранить изображение", this);
    saveButton->setGeometry(10, 10, 150, 30);
    connect(saveButton, &QPushButton::clicked, this, &DrawingWidget::saveImage);

    openButton = new QPushButton("Открыть изображение", this);
    openButton->setGeometry(170, 10, 150, 30);
    connect(openButton, &QPushButton::clicked, this, &DrawingWidget::openImage);

    eraseButton = new QPushButton("Режим Ластика", this);
    eraseButton->setGeometry(330, 10, 100, 30);
    connect(eraseButton, &QPushButton::clicked, this, &DrawingWidget::toggleEraserMode);

    drawRectangleButton = new QPushButton("Прямоугольник", this);
    drawRectangleButton->setGeometry(440, 10, 100, 30);
    connect(drawRectangleButton, &QPushButton::clicked, this, &DrawingWidget::setDrawRectangleMode);

    drawTriangleButton = new QPushButton("Треугольник", this);
    drawTriangleButton->setGeometry(550, 10, 100, 30);
    connect(drawTriangleButton, &QPushButton::clicked, this, &DrawingWidget::setDrawTriangleMode);

    drawEllipseButton = new QPushButton("Эллипс", this);
    drawEllipseButton->setGeometry(660, 10, 100, 30);
    connect(drawEllipseButton, &QPushButton::clicked, this, &DrawingWidget::setDrawEllipseMode);
}

DrawingWidget::~DrawingWidget()
{
}

void DrawingWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0, 0, image);
    if (drawing && (drawMode == DrawMode::Rectangle || drawMode == DrawMode::Triangle || drawMode == DrawMode::Ellipse)) {
        drawCurrentShape(painter);
    }
}

void DrawingWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        drawing = true;
        if (erasing) {
            QPainter painter(&image);
            painter.setPen(QPen(Qt::white, 10, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            painter.drawPoint(lastPoint);
            update();
        }
    }
}

void DrawingWidget::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && drawing) {
        QPainter painter(&image);
        if (erasing) {
            painter.setPen(QPen(Qt::white, 10, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            painter.drawPoint(event->pos());
        } else if (drawMode == DrawMode::None) {
            painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            painter.drawLine(lastPoint, event->pos());
            lastPoint = event->pos();
        } else {
            currentRect.setTopLeft(lastPoint);
            currentRect.setBottomRight(event->pos());
            update();
        }
    }
}

void DrawingWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && drawing) {
        QPainter painter(&image);
        if (erasing) {
            painter.setPen(QPen(Qt::white, 10, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            painter.drawPoint(event->pos());
        } else if (drawMode != DrawMode::None) {
            drawCurrentShape(painter);
        } else {
            painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            painter.drawLine(lastPoint, event->pos());
        }
        drawing = false;
        drawMode = DrawMode::None;
        update();
    }
}

void DrawingWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape && drawing) {
        drawing = false;
        drawMode = DrawMode::None;
        update();
    }
}

void DrawingWidget::saveImage()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Сохранить изображение"), "", tr("PNG Files (*.png);;All Files (*)"));
    if (!fileName.isEmpty()) {
        image.save(fileName);
    }
}

void DrawingWidget::openImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Открыть изображение"), "", tr("PNG Files (*.png);;All Files (*)"));
    if (!fileName.isEmpty()) {
        image.load(fileName);
        update();
    }
}

void DrawingWidget::toggleEraserMode()
{
    erasing = !erasing;
    if (erasing) {
        eraseButton->setText("Режим Рисования");
    } else {
        eraseButton->setText("Режим Ластика");
    }
}

void DrawingWidget::setDrawRectangleMode()
{
    drawMode = DrawMode::Rectangle;
}

void DrawingWidget::setDrawTriangleMode()
{
    drawMode = DrawMode::Triangle;
}

void DrawingWidget::setDrawEllipseMode()
{
    drawMode = DrawMode::Ellipse;
}

void DrawingWidget::drawCurrentShape(QPainter &painter)
{
    switch (drawMode) {
    case DrawMode::Rectangle:
        painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.drawRect(currentRect);
        break;
    case DrawMode::Triangle: {
        QPointF p1 = currentRect.topLeft();
        QPointF p2 = currentRect.topRight();
        QPointF p3 = QPointF((p1.x() + p2.x()) / 2, currentRect.bottom());
        currentPolygon.clear();
        currentPolygon << p1 << p2 << p3;
        painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.drawPolygon(currentPolygon);
        break;
    }
    case DrawMode::Ellipse:
        painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.drawEllipse(currentRect);
        break;
    default:
        break;
    }
}
