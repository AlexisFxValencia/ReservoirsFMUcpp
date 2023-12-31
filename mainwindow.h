#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsRectItem>
#include <QTimer>

#include <fmi4cpp/fmi4cpp.hpp>
#include <iostream>
#include "fmureader.h"

namespace Ui {
class MainWindow;
}

using std::cout, std::endl;
using namespace fmi4cpp;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void init_fmi();
    void draw_containers();
    void update_water_levels();
    bool level_in_container(int tank_level);


private slots:
    void on_open_buton_clicked();
    void on_close_buton_clicked();

    void on_actionRestart_triggered();
    void on_actionPause_triggered();
    void on_actionx_1_triggered();
    void on_actionx_2_triggered();
    void on_actionx_10_triggered();

    void on_horizontalSlider_valueChanged(int value);


private:
    Ui::MainWindow *ui;
    QGraphicsRectItem *RCP;
    QGraphicsRectItem *RCP_water;
    QGraphicsRectItem *TEP;
    QGraphicsRectItem *TEP_water;
    QTimer *timer;
    bool on_pause = false;

    int RCP_x = 0;
    int RCP_y = 0;
    int TEP_x = 200;
    int TEP_y = 0;
    int tank_height = 200;
    int tank_width = 100;
    int water_initial_level = 100;
    int tolerance = 5;
    int time_step = 100; // in milliseconds
    FMUReader fmu_reader = FMUReader();

};

#endif // MAINWINDOW_H
