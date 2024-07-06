#ifndef CONNECTORS_H
#define CONNECTORS_H
#include "figure.h"
#include <memory>
#include <QWidget>
using namespace std;
class FConnector{
private:
    int figureOne_id, figureTwo_id;
    QPointF Inter_point;
    shared_ptr<Figure> figure1, figure2;
public:
    FConnector();
    void placeFirstFig(const int& fig_id, const shared_ptr<Figure>& figure);
    void placeScondFig(const int& fig_id, const shared_ptr<Figure>& figure);
    void placeInterimPoint(const QPointF& pnt);
    void paintInterimConnector(QPainter& painter) const;
    void paintAllConnector(QPainter& painter) const;
    bool isFigConn(const shared_ptr<Figure>& fig);
    void UpdateConnectorMove(const int& figure_id);
    void serialize(QDataStream& out) const;
    bool SameFigConn() const;
    void reset();
    ~FConnector();
};

#endif // CONNECTORS_H
