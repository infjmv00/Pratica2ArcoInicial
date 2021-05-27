#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Vehicle.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void fillComboBox();
    void resetWindow();

private slots:

    void on_pushButton_Matricula_released();

    void on_pushButton_createVehicle_released();

    void on_engineCheckLine_toggled(bool checked);

    void on_fuelCheckLine_toggled(bool checked);

    void on_pushButton_recoverVehicle_released();

    void on_wagonCheckLine_toggled(bool checked);

private:
    Ui::MainWindow *ui;   
    Vehicle vehicle;
    std::vector<Vehicle> listaVehiculos;
};
#endif // MAINWINDOW_H
