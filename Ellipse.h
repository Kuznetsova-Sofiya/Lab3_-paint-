#ifndef ELLIPSE_H
#define ELLIPSE_H
#include "figure.h"
using namespace std;

class Ellipse:public Figure{
private:
    const int pointsSum = 30;
public:
    Ellipse();
    void drawFigure(QPainter& painter) const override;
    void UpdateStarterPoint(const QPointF& pnt) override;
    void updateFinalPiont(const QPointF& pnt) override;
    void updateFigureCoordinates() override;
    bool isFigContainsPoint(const QPointF& pnt)const override;
    QPointF CalculateOffset(const QPointF& pnt)const override;
    void translate(const QPointF& currentPoint, const QPointF& offset) override;
    void serialize(QDataStream& out) const override;
    void deserialize(QDataStream& in) override;
    QPointF GetCenterOfFigure() const override;
    ~Ellipse();
};

#endif // ELLIPSE_H
