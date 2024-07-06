#include "triangle.h"

using namespace std;

Triangle::Triangle(): Figure(){
    figType = FigureType::Triangle;
}

void Triangle::drawFigure(QPainter& painter) const{
    painter.drawPolygon(FigPolygon);
}

void Triangle::UpdateStarterPoint(const QPointF& pnt){
    StarterPoint = pnt;
}

void Triangle::updateFinalPiont(const QPointF& pnt){
    FinalPoint = pnt;
}

void Triangle::updateFigureCoordinates(){
    FigPolygon.clear();
    QRectF rect(StarterPoint, FinalPoint);
    rect = rect.normalized();
    FigPolygon<<rect.bottomLeft()<<(rect.topLeft() + rect.topRight())/2<<rect.bottomRight();
}

bool Triangle::isFigContainsPoint(const QPointF& pnt) const{
    return FigPolygon.containsPoint(pnt, Qt::OddEvenFill);
}

QPointF Triangle::CalculateOffset(const QPointF& pnt) const{
    return pnt - FigPolygon.boundingRect().topLeft();
}

void Triangle:: translate(const QPointF& current_pnt, const QPointF& offset){
    FigPolygon.translate(current_pnt - offset-FigPolygon.boundingRect().topLeft());
}

void Triangle::serialize(QDataStream& out) const
{
    out<<figType<<StarterPoint<<FinalPoint<<FigPolygon;
}

void Triangle::deserialize(QDataStream& in)
{
    in>>StarterPoint>>FinalPoint>>FigPolygon;
}

QPointF Triangle:: GetCenterOfFigure() const{
    return FigPolygon.boundingRect().center();
}

Triangle::~Triangle(){
    FigPolygon.clear();
}
