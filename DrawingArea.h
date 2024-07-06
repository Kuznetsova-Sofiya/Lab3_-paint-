#ifndef DRAWINGAREA_H
#define DRAWINGAREA_H
#include <QWidget>
#include <QMouseEvent>
#include <memory>
#include "Connectors.h"
using namespace std;

enum class Action{None, Move, Draw, Remove, Connect};

class DrawingArea:public QWidget{
    Q_OBJECT
private:
    void deserializeFigures(QDataStream& in);
    void deserializeConnectors(QDataStream& in);
    int getFigureIdxByPoint(const QPointF& pnt) const;
    void removeFigure(const int& fig_idx);
    void removeFigConns(const int& fig_idx, const shared_ptr<Figure>& figure);

signals:
private:
    Action current_action;
    QPointF moving_offset;
    QList<shared_ptr<Figure>> figures;
    shared_ptr<Figure> current_fig;
    FConnector current_conn;
    QVector<FConnector> figs_conns;

public:
    explicit DrawingArea(QWidget* parent = nullptr);// Конструктор для создания зоны, в которой пользователь сможет рисовать
    void illustrateAction(const Action& act); //Функция отображения того, что делает пользователь
    void placeCurrentFigure(const shared_ptr<Figure>& fig); //Функция, которая отвечает за расположение фигуры
    void serialize(QDataStream& out) const;
    void deserialize(QDataStream& in);
    void mousePressEvent(QMouseEvent* event) override; //Отслеживание нажатия ЛКМ
    void mouseMoveEvent(QMouseEvent* event) override; //Отслеживание движения мыши при зажатой ЛКМ
    void mouseReleaseEvent(QMouseEvent* event) override;
    void keyBoardAction(QKeyEvent* event);//Обработка нажатий клавиатуры
    void paintEvent(QPaintEvent* event) override;
    ~DrawingArea();

};

#endif // DRAWINGAREA_H
