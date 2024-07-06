#include "rectangle.h"

using namespace std;

Rectangle::Rectangle(): Figure(){
    figType = FigureType::Rectangle;
}

void Rectangle::drawFigure(QPainter& painter) const{
    painter.drawPolygon(FigPolygon);
}

void Rectangle::UpdateStarterPoint(const QPointF& pnt){
    StarterPoint = pnt;
}

void Rectangle::updateFinalPiont(const QPointF& pnt){
    FinalPoint = pnt;
}

void Rectangle::updateFigureCoordinates(){
    FigPolygon.clear();
    QRectF rect(StarterPoint, FinalPoint);
    rect = rect.normalized();
    FigPolygon<<rect.bottomLeft()<<rect.bottomRight()<<rect.topRight()<<rect.topLeft();
}

bool Rectangle::isFigContainsPoint(const QPointF& pnt) const{
    return FigPolygon.containsPoint(pnt, Qt::OddEvenFill);
}

QPointF Rectangle::CalculateOffset(const QPointF& pnt) const{
    return pnt - FigPolygon.boundingRect().topLeft();
}

void Rectangle:: translate(const QPointF& current_pnt, const QPointF& offset){
    FigPolygon.translate(current_pnt - offset-FigPolygon.boundingRect().topLeft());
}

void Rectangle::serialize(QDataStream& out) const
{
    out<<figType<<StarterPoint<<FinalPoint<<FigPolygon;
}

void Rectangle::deserialize(QDataStream& in)
{
    in>>StarterPoint>>FinalPoint>>FigPolygon;
}

QPointF Rectangle:: GetCenterOfFigure() const{
    return FigPolygon.boundingRect().center();
}

Rectangle::~Rectangle(){
    FigPolygon.clear();
}
