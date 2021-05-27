#include "MainWindow.h"
#include "Vehicle.h"


#include <QApplication>

void Vehicles();
void newVehicle();

std::vector<Vehicle> vehicles;

int main(int argc, char *argv[]){

    QApplication a(argc, argv);
    MainWindow vehicleWindow;
    vehicleWindow.show();
    return a.exec();

}

