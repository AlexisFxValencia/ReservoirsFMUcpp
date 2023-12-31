#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    QGraphicsScene *scene = new QGraphicsScene(this);
    int width = ui->graphicsView->geometry().width();
    int height = ui->graphicsView->geometry().height();
    scene->setSceneRect(0,0, width, height);
    ui->graphicsView->setScene(scene);
    draw_containers();

    fmu_reader.init_reader((double)time_step/1000);
    fmu_reader.init_model_description();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::update_water_levels);
    timer->start(time_step);
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::draw_containers()
{
    RCP = new QGraphicsRectItem(RCP_x, RCP_y, tank_width, tank_height); // adjust coordinates and size as needed
    QPen pen(Qt::black);
    RCP->setPen(pen);
    ui->graphicsView -> scene()->addItem(RCP);

    TEP = new QGraphicsRectItem(TEP_x, TEP_y, tank_width, tank_height); // adjust coordinates and size as needed
    TEP->setPen(pen);
    ui->graphicsView -> scene()->addItem(TEP);

    RCP_water = new QGraphicsRectItem(RCP_x, tank_height - water_initial_level, tank_width, water_initial_level); // adjust coordinates and size as needed
    QBrush brush(Qt::blue);
    RCP_water->setBrush(brush);
    ui->graphicsView -> scene()->addItem(RCP_water);

    TEP_water = new QGraphicsRectItem(TEP_x, tank_height - water_initial_level, tank_width, water_initial_level); // adjust coordinates and size as needed
    TEP_water->setBrush(brush);
    ui->graphicsView -> scene()->addItem(TEP_water);

}


bool MainWindow::level_in_container(int tank_level){
    if (tank_level < 0 + tolerance || tank_level > tank_height - tolerance){
        return false;
    }else{
        return true;
    }
}

void MainWindow::update_water_levels(){
    double RCP_level = fmu_reader.read("RCP.level");
    double TEP_level = fmu_reader.read("TEP.level");

    if (fmu_reader.level_in_container(RCP_level) and fmu_reader.level_in_container(TEP_level)){
        fmu_reader.take_a_step();
        int RCP_gui_level = RCP_level * water_initial_level;
        int TEP_gui_level = TEP_level * water_initial_level;
        RCP_water->setRect(RCP_x, tank_height - RCP_gui_level, tank_width, RCP_gui_level);
        TEP_water->setRect(TEP_x, tank_height - TEP_gui_level, tank_width, TEP_gui_level);

        ui->label_RCP->setText(QString::number(RCP_level, 'f',3));
        ui->label_TEP->setText(QString::number(TEP_level, 'f',3));
    }
}


void MainWindow::on_actionPause_triggered()
{
    if (on_pause == false){
        timer->stop();
        ui->actionPause->setText("Play");
        on_pause = true;
    } else{
        timer->start(time_step);
        ui->actionPause->setText("Pause");
        on_pause = false;
    }
}

void MainWindow::on_actionx_1_triggered()
{
    fmu_reader.acceleration = 1;
}

void MainWindow::on_actionx_2_triggered()
{
    fmu_reader.acceleration = 2;
}

void MainWindow::on_actionx_10_triggered()
{
    fmu_reader.acceleration = 10;
}



void MainWindow::on_open_buton_clicked()
{
    fmu_reader.open_valve();
    ui->label_vo->setText(QString::number(fmu_reader.valve_opening, 'f',3));
    ui->horizontalSlider->setValue(99);
}

void MainWindow::on_close_buton_clicked()
{
    fmu_reader.close_valve();
    ui->label_vo->setText(QString::number(fmu_reader.valve_opening, 'f',3));
    ui->horizontalSlider->setValue(0);
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    fmu_reader.change_valve_opening((float)value/100);
    ui->label_vo->setText(QString::number(fmu_reader.valve_opening, 'f',3));
}

void MainWindow::on_actionRestart_triggered()
{
    fmu_reader.init_reader((float)time_step/1000);
    fmu_reader.init_model_description();
}



