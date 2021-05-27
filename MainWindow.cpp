#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <iostream>
#include "Vehicle.h"
#include <QInputDialog>
#include <QMessageBox>
#include <sstream>
#define NULL 0
#define STRING(num) #num

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->cvvLine->setDisabled(true);
    ui->fueltypeLine->setDisabled(true);
    ui->wagonNumberLine->setDisabled(true);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fillComboBox(){
    ui->comboBox_listVehicles->clear();
    int quantity = listaVehiculos.size();
    for (int i = 0; i < quantity;i++){
        ui->comboBox_listVehicles->addItem(QString::fromStdString((listaVehiculos[i].getName())));
    }


}
//Este metodo reinicia los valores a elegir de la ventana
void MainWindow::resetWindow(){
    ui->colorLine->setCurrentIndex(0);
    ui->wingsCheckLine->setChecked(false);
    ui->reactorCheckLine->setChecked(false);
    ui->cvvLine->setText("");
    ui->engineCheckLine->setChecked(false);
    ui->fueltypeLine->setEnabled(false);
    ui->fuelCheckLine->setChecked(false);
    ui->undercarriageCheckLine->setChecked(false);


}
void MainWindow::on_pushButton_Matricula_released()
{
    srand(time(NULL));
    std::string registerNumber;
    char letter;
    for(int i = 0; i<=3;i++){
       registerNumber.push_back((rand()%10+48));
    }
    registerNumber.push_back('-');

    for(int i = 0; i<=2;i++){
        letter = (rand()%26+65);
        while(letter=='A'||letter=='E'||letter=='I'||letter=='O'||letter=='U'||letter=='a'||letter=='e'||letter=='i'||letter=='o'||letter=='u'){
            letter = (rand()%26+65);
        }
        registerNumber.push_back(letter);
    }
    QString str = QString::fromUtf8(registerNumber.data(),registerNumber.size());
    ui->registrationLine->setText(str);
}

//Boton de creacion de vehiculo, se toma valor a todos los campos
void MainWindow::on_pushButton_createVehicle_released()
{
    std::string name = ui->nameLine->text().toStdString();
    int wheelNumber = ui->wheelNumber->currentText().toInt();

    std::string wheelKitS = ui->wheelKitLine->currentText().toStdString();
    bool wheelKit;
    if(wheelKitS.compare("Spare Wheel") == 0){
        wheelKit = true;
    }else{
        wheelKit = false;
    }

    std::string color = ui->colorLine->currentText().toStdString();
    bool wings = ui->wingsCheckLine->checkState();
    bool undercarriage = ui->undercarriageCheckLine->checkState();
    bool reactors = ui->reactorCheckLine->checkState();
    bool locomotive = ui->locomotiveCheckLine->checkState();
    bool engine = ui->engineCheckLine->checkState();
    int cvv = ui->cvvLine->text().toInt();

    bool fuel = ui->fuelCheckLine->checkState();
    std::string fuelTypeS = ui->fueltypeLine->currentText().toStdString();
    char fuelType;
    if(fuelTypeS.compare("Gasoline") == 0){
        fuelType = 'g';
    }else if(fuelTypeS.compare("Electric") == 0){
        fuelType = 'e';
    }else if(fuelTypeS.compare("Querosene") == 0){
        fuelType = 'q';
    }else if(fuelTypeS.compare("Diesel") == 0){
        fuelType = 'd';
    }else if(fuelTypeS.compare("Hibrid") == 0){
        fuelType = 'h';
    }else{
        fuelType = 'x';
    }
    bool wagons = ui->wagonCheckLine->checkState();
    int wagonNumber = ui->wagonNumberLine->value();
    std::string registration = ui->registrationLine->text().toStdString();
     Vehicle vehicle = Vehicle(name, wheelNumber, engine, cvv, fuel, fuelType, color, wings, reactors, undercarriage, locomotive, wagons, wagonNumber, wheelKit, registration);
     if(vehicle.isASportsCar(wheelNumber, engine, cvv, fuel, fuelType, wings, reactors, undercarriage, locomotive, wagons, wheelKit) == false
             && vehicle.isAPlane(wheelNumber, engine, cvv, fuel, fuelType, color, wings, reactors, undercarriage, locomotive, wagons, wheelKit) == false
             && vehicle.isABike(wheelNumber,engine,fuel,wings,reactors,locomotive,wagons,wheelKit) == false
             && vehicle.isTricycle(wheelNumber,engine,fuel,reactors,wings,undercarriage,locomotive,wagons,wheelKit) ==false
             && vehicle.isTrain() == false
             && vehicle.isAMotorBike() == false
             && vehicle.isACar() == false || name == "")

             {
    // Cuando tengamos todos los datos, descomentar y completar la linea siguiente.

        QMessageBox mensaje;
                 mensaje.setText("Data Information incomplete");
                 mensaje.exec();
            }

     else {

    listaVehiculos.push_back(Vehicle(name, wheelNumber, engine, cvv, fuel, fuelType, color, wings, reactors, undercarriage, locomotive, wagons, wagonNumber, wheelKit, registration));

    int sizeList = listaVehiculos.size();    

    //int numberVehicles = ++sizeList;
    QString QNVehicles = QString::fromStdString(static_cast<std::ostringstream*>(&(std::ostringstream() << sizeList++))->str());
    ui->vehiculosCreados_lineEdit->setText(QNVehicles);
    fillComboBox();

}
    resetWindow();
}
void MainWindow::on_engineCheckLine_toggled(bool checked)
{
    if(checked){
        ui->cvvLine->setDisabled(false);
        ui->cvvLine->setText("80");
    }else{
        ui->cvvLine->setDisabled(true);
        ui->cvvLine->setText("");
    }
}
void MainWindow::on_fuelCheckLine_toggled(bool checked)
{
    if(checked){
        ui->fueltypeLine->setDisabled(false);
    }else{
        ui->fueltypeLine->setDisabled(true);
    }
}

void MainWindow::on_pushButton_recoverVehicle_released()
{   if(ui->comboBox_listVehicles->currentText() !=NULL){
         listaVehiculos[ui->comboBox_listVehicles->currentIndex()].toString();
       } else {
            QMessageBox mensaje;
            mensaje.setText("Don`t exist vehicles");
            mensaje.exec();
        }


}
void MainWindow::on_wagonCheckLine_toggled(bool checked){
    if(checked){
        ui->wagonNumberLine->setDisabled(false);
    }else{
        ui->wagonNumberLine->setDisabled(true);

    }
}
