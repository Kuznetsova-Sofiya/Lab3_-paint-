#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "figure.h"

using namespace std;

class Triangle:public Figure{
public:
    Triangle();
    void drawFigure(QPainter& painter) const override;
    void UpdateStarterPoint(const QPointF& pnt) override;
    void updateFinalPiont(const QPointF& pnt) override;
    void updateFigureCoordinates() override;
    bool isFigContainsPoint(const QPointF& pnt) const override;
    QPointF CalculateOffset(const QPointF& pnt)const override;
    void translate(const QPointF& currentPoint, const QPointF& offset) override;
    void serialize(QDataStream& out) const override;
    void deserialize(QDataStream& in) override;
    QPointF GetCenterOfFigure() const override;
    ~Triangle();
};

#endif // TRIANGLE_H
