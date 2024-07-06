#include "Connectors.h"

FConnector::FConnector():figureOne_id(-1), figureTwo_id(-1), figure1(nullptr), figure2(nullptr){

}

void FConnector::placeFirstFig(const int &fig_id, const shared_ptr<Figure>& figure){
    figureOne_id = fig_id;
    figure1 = figure;
    Inter_point = figure->GetCenterOfFigure();
}

void FConnector::placeScondFig(const int &fig_id, const shared_ptr<Figure>& figure){
    figureTwo_id = fig_id;
    figure2 = figure;
}

void FConnector::placeInterimPoint(const QPointF& pnt){
    Inter_point = pnt;
}

void FConnector::paintInterimConnector(QPainter& painter) const{
    painter.drawLine(QLineF(figure1->GetCenterOfFigure(), Inter_point));
}

void FConnector::paintAllConnector(QPainter& painter) const{
    painter.drawLine(QLineF(figure1->GetCenterOfFigure(), figure2->GetCenterOfFigure()));
}

void FConnector::UpdateConnectorMove(const int& fig_id){
    if(figureOne_id > fig_id){
        figureOne_id--;
    }
    if(figureTwo_id > fig_id){
        figureTwo_id--;
    }
}

void FConnector::serialize(QDataStream &out) const
{
    out<<figureOne_id<<figureTwo_id;
}

bool FConnector::SameFigConn() const{
    return figureOne_id == figureTwo_id;
}

void FConnector::reset(){
    figure1 = nullptr;
    figure2 = nullptr;
    figureOne_id = -1;
    figureTwo_id =-1;
}

FConnector::~FConnector(){}

bool FConnector::isFigConn(const shared_ptr<Figure>& fig){
    return figure1 == fig || figure2 == fig;
}
