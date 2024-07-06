#include "DrawingArea.h"
#include "Ellipse.h"
#include "triangle.h"
#include "rectangle.h"

using namespace std;

DrawingArea::DrawingArea(QWidget* parent): QWidget{parent}, current_fig(nullptr), current_action(Action::None){

}
DrawingArea::~DrawingArea(){
    figs_conns.clear();
    figures.clear();
}
void DrawingArea::illustrateAction(const Action& act){
    current_action = act;
}

void DrawingArea::placeCurrentFigure(const shared_ptr<Figure>& fig){
    current_fig = fig;
}

void DrawingArea::deserializeFigures(QDataStream& in)
{
    figures.clear();

    int figures_count;
    FigureType fig_type;

    in>>figures_count;

    for(int idx = 0; idx < figures_count; idx++){
        in>>fig_type;
        if(fig_type == FigureType::Ellipse){
            current_fig = std::make_shared<Ellipse>();
        }
        else if(fig_type == FigureType::Rectangle){
            current_fig = std::make_shared<Rectangle>();
        }
        else if(fig_type == FigureType::Triangle){
            current_fig = std::make_shared<Triangle>();
        }
        current_fig->deserialize(in);
        figures.append(current_fig);
    }
}
void DrawingArea::deserializeConnectors(QDataStream& in)
{
    figs_conns.clear();

    int fig1_id, fig2_id, connectors_count;
    FConnector connector;

    in>>connectors_count;

    for(int idx = 0; idx < connectors_count; idx++){
        in>>fig1_id>>fig2_id;
        connector.placeFirstFig(fig1_id, figures[fig1_id]);
        connector.placeScondFig(fig2_id, figures[fig2_id]);
        figs_conns.emplace_back(connector);
    }
}

void DrawingArea::mouseMoveEvent(QMouseEvent* event){
    if(current_action != Action:: None){
        if(current_action == Action::Draw){
            current_fig->updateFinalPiont(event->pos());
        }else if(current_action == Action::Connect){
            current_conn.placeInterimPoint(event->pos());
        }else if(current_action == Action::Move){
            if (current_fig) {
                QPointF newPos = event->pos() - moving_offset;
                if (newPos.x() >= 0 && newPos.x() <= width() &&
                    newPos.y() >= 0 && newPos.y() <= height()) {
                    current_fig->translate(newPos, moving_offset);
                }
                update();
            }
        }
        update();
    }
}

void DrawingArea::mouseReleaseEvent(QMouseEvent* event){
    if(event->button() == Qt::LeftButton){
        if(current_action != Action::None){
            if(current_action == Action::Draw){
                current_fig->updateFinalPiont(event->pos());
                current_fig->updateFigureCoordinates();
                figures.append(current_fig);
            }else{
                if(current_action == Action::Connect){
                    QPointF curr_pos = event->pos();
                    int fig_idx = getFigureIdxByPoint(curr_pos);
                    if(fig_idx>-1){
                        current_conn.placeScondFig(fig_idx, figures[fig_idx]);
                        if(!current_conn.SameFigConn()){
                            figs_conns.emplace_back(current_conn);
                        }
                    }
                }
                setCursor(Qt::ArrowCursor);
                current_conn.reset();
                current_fig = nullptr;
                current_action = Action::None;
                update();
            }
        }
        if (current_action == Action::Move) {
            if (current_fig) {
                current_fig->updateFigureCoordinates();
                current_action = Action::None;
                setCursor(Qt::ArrowCursor);
                update();
            }
        }
    }
}

void DrawingArea::keyBoardAction(QKeyEvent* event){
    if(event->key() == Qt::Key_Escape){
        setCursor(Qt::ArrowCursor);
        current_conn.reset();
        current_fig = nullptr;
        current_action = Action::None;
        update();
    }
}
void DrawingArea::serialize(QDataStream &out) const
{
    out<<((int)figures.size());
    for(const auto& figure : figures){
        figure->serialize(out);
    }

    out<<((int)figs_conns.size());
    for(const auto& connector : figs_conns){
        connector.serialize(out);
    }
}

void DrawingArea::deserialize(QDataStream &in)
{
    current_fig = nullptr;
    deserializeFigures(in);
    deserializeConnectors(in);
}


void DrawingArea::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    if(current_action == Action::Draw){
        current_fig->updateFigureCoordinates();
        current_fig->drawFigure(painter);
    }
    else if(current_action == Action::Connect){
        current_conn.paintInterimConnector(painter);
    }
    for(const auto& figure : figures){
        figure->drawFigure(painter);
    }

    for(const auto& connector : figs_conns){
        connector.paintAllConnector(painter);
    }
}

int DrawingArea::getFigureIdxByPoint(const QPointF& pnt) const{
    for(int i = 0; i < figures.size(); ++i){
        if(figures[i]->isFigContainsPoint(pnt)){
            return i;
        }
    }
    return -1;
}

void DrawingArea:: removeFigure(const int& figure_idx){
    removeFigConns(figure_idx, figures[figure_idx]);
    figures.removeAt(figure_idx);
}

void DrawingArea::removeFigConns(const int& figure_idx, const shared_ptr<Figure>& figure){
    for(auto it = figs_conns.begin(); it!=figs_conns.end();){
        if(it->isFigConn(figure)){
            it = figs_conns.erase(it);
        }else{
            it->UpdateConnectorMove(figure_idx);
            ++it;
        }
    }
}


void DrawingArea::mousePressEvent(QMouseEvent* event){
    if(event->button() == Qt::LeftButton){
        setFocus();
        if(current_action == Action::Draw){
            QPointF current_pos = event->pos();
            current_fig->UpdateStarterPoint(current_pos);
            current_fig->updateFinalPiont(current_pos);
        }else if(current_action!=Action::None){
            current_fig = nullptr;
            QPointF current_pos = event->pos();
            int figure_idx = getFigureIdxByPoint(current_pos);
            if(figure_idx > -1){
                if(current_action == Action::Connect){
                    current_conn.placeFirstFig(figure_idx, figures[figure_idx]);
                }
                else if(current_action == Action::Remove){
                    removeFigure(figure_idx);
                    current_action = Action::None;
                    update();
                }
                else if(current_action == Action::Move){
                    current_fig = figures[figure_idx];
                    moving_offset = current_fig->CalculateOffset(current_pos);
                    setCursor(Qt::PointingHandCursor);
                }
            }else{
                current_action = Action::None;
            }
        }
    }
    else if(event->button() == Qt::RightButton){
        setCursor(Qt::ArrowCursor);
        current_conn.reset();
        current_fig = nullptr;
        current_action = Action::None;
        update();
    }
}



