#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rectangle.h"
#include "triangle.h"
#include "ellipse.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), drawingAr(new DrawingArea), drawingWidget(new DrawingWidget(this))
{
    ui->setupUi(this);

    QIcon icon_triangle(":/icons/triangle.png");
    ui->pushButton->setIcon(icon_triangle);
    ui->pushButton->setIconSize(QSize(25, 25));

    QIcon icon_rectangle(":/icons/rectangle.png");
    ui->pushButton_3->setIcon(icon_rectangle);
    ui->pushButton_3->setIconSize(QSize(25, 25));

    QIcon icon_ellipse(":/icons/ellipse.png");
    ui->pushButton_4->setIcon(icon_ellipse);
    ui->pushButton_4->setIconSize(QSize(25, 25));

    QIcon icon_connector(":/icons/connect.png");
    ui->pushButton_5->setIcon(icon_connector);
    ui->pushButton_5->setIconSize(QSize(25, 25));

    QIcon icon_remove(":/icons/delete.png");
    ui->pushButton_6->setIcon(icon_remove);
    ui->pushButton_6->setIconSize(QSize(25, 25));

    QIcon icon_move(":/icons/move.png");
    ui->pushButton_8->setIcon(icon_move);
    ui->pushButton_8->setIconSize(QSize(25, 25));

    QIcon icon_save(":/icons/save.png");
    ui->pushButton_7->setIcon(icon_save);
    ui->pushButton_7->setIconSize(QSize(25, 25));

    QIcon icon_load(":/icons/load.png");
    ui->pushButton_2->setIcon(icon_load);
    ui->pushButton_2->setIconSize(QSize(25, 25));

    QIcon icon_start(":/icons/start.png");
    ui->pushButton_9->setIcon(icon_start);
    ui->pushButton_9->setIconSize(QSize(25, 25));

    this->setMinimumSize(800, 800);
    ui->gridLayout_2->addWidget(drawingAr.get());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    drawingAr->illustrateAction(Action::Draw);
    drawingAr->placeCurrentFigure(std::make_shared<Triangle>());
}

void MainWindow::on_pushButton_3_clicked()
{
    drawingAr->illustrateAction(Action::Draw);
    drawingAr->placeCurrentFigure(std::make_shared<Rectangle>());
}

void MainWindow::on_pushButton_4_clicked()
{
    drawingAr->illustrateAction(Action::Draw);
    drawingAr->placeCurrentFigure(std::make_shared<Ellipse>());
}

void MainWindow::on_pushButton_5_clicked()
{
    drawingAr->illustrateAction(Action::Connect);
}

void MainWindow::on_pushButton_8_clicked()
{
    drawingAr->illustrateAction(Action::Move);
}

void MainWindow::on_pushButton_6_clicked()
{
    drawingAr->illustrateAction(Action::Remove);
}

void MainWindow::on_pushButton_7_clicked()
{
    QString file_toSave = QFileDialog::getSaveFileName(this, tr("Save file"), tr("Save files (*.dat)"));
    if (!file_toSave.isEmpty())
    {
        QFile file(file_toSave);
        if (file.open(QIODevice::WriteOnly))
        {
            QDataStream out(&file);
            drawingAr->serialize(out);
            file.close();
        }
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    QString file_toUpload = QFileDialog::getOpenFileName(this, tr("Load file"), "", tr("Saved files (*.dat)"));
    if (!file_toUpload.isEmpty())
    {
        QFile file(file_toUpload);
        if (file.open(QIODevice::ReadOnly))
        {
            QDataStream in(&file);
            drawingAr->deserialize(in);
            file.close();
            update();
        }
    }
}

void MainWindow::on_pushButton_9_clicked()
{
    // drawingWidget как центральный виджет и кнопки сохранения, открытия и удаления и фигур
    setCentralWidget(drawingWidget);
}
