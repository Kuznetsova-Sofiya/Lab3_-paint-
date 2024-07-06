#include "Ellipse.h"

using namespace std;

Ellipse::Ellipse(): Figure(){
    figType = FigureType::Ellipse;
}

void Ellipse::drawFigure(QPainter& painter) const{
    painter.drawPolygon(FigPolygon);
}

void Ellipse::UpdateStarterPoint(const QPointF& pnt){
    StarterPoint = pnt;
}

void Ellipse::updateFinalPiont(const QPointF& pnt){
    FinalPoint = pnt;
}

void Ellipse::updateFigureCoordinates(){
    FigPolygon.clear();
    QRectF rect(StarterPoint, FinalPoint);
    rect = rect.normalized();

    for(int i = 0; i < pointsSum; ++i){
        qreal angle = 2*M_PI*i/pointsSum;
        qreal x = rect.center().x() + rect.width()/2*qCos(angle);
        qreal y = rect.center().y() + rect.height()/2*qSin(angle);
        FigPolygon << QPointF(x, y);
    }
}

bool Ellipse::isFigContainsPoint(const QPointF& pnt) const{
    return FigPolygon.containsPoint(pnt, Qt::OddEvenFill);
}

QPointF Ellipse::CalculateOffset(const QPointF& pnt) const{
    return pnt - FigPolygon.boundingRect().topLeft();
}

void Ellipse:: translate(const QPointF& current_pnt, const QPointF& offset){
    FigPolygon.translate(current_pnt - offset-FigPolygon.boundingRect().topLeft());
}

void Ellipse::serialize(QDataStream& out) const
{
    out<<figType<<StarterPoint<<FinalPoint<<FigPolygon;
}

void Ellipse::deserialize(QDataStream& in)
{
    in>>StarterPoint>>FinalPoint>>FigPolygon;
}

QPointF Ellipse:: GetCenterOfFigure() const{
    return FigPolygon.boundingRect().center();
}

Ellipse::~Ellipse(){
    FigPolygon.clear();
}
