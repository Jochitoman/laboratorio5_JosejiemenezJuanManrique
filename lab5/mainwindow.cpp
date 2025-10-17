#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QVector>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QByteArray>

#define START_BYTE 0xAA

QSerialPort serial;

uint8_t calcChecksum(const QByteArray &data) {
    uint8_t chk = 0;
    for (char b : data) chk ^= static_cast<uint8_t>(b);
    return chk;
}

void sendPacket(uint8_t cmd, QByteArray data) {
    QByteArray packet;
    packet.append(START_BYTE);
    packet.append(cmd);
    packet.append(static_cast<char>(data.size()));
    packet.append(data);

    QByteArray chkData = packet.mid(1); // desde CMD
    uint8_t chk = calcChecksum(chkData);
    packet.append(chk);

    serial.write(packet);
}

QByteArray armarPaquete(uint8_t cmd, QByteArray data) {
    QByteArray paquete;
    paquete.append((char)0xAA);              // start
    paquete.append((char)cmd);               // comando
    paquete.append((char)data.size());       // longitud
    paquete.append(data);                    // datos
    QByteArray paraChecksum = paquete.mid(1); // desde cmd
    paquete.append((char)calcChecksum(paraChecksum)); // checksum
    return paquete;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ttl = new QSerialPort(this);
    setupPlot();
    timer.start();
    serialBuffer = "";
    parsed_data = "";
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        QString puertos = serialPortInfo.portName();
        ui->selepuerto->addItem(puertos);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_botonpuerto_clicked()//cuando presiona el boton del puerto para que abra y cierre
{
    QString ttl_port_name = ui->selepuerto->currentText();
    if(ui->botonpuerto->text() == "Abrir"){
            ttl->setPortName(ttl_port_name);
            ttl->open(QSerialPort::ReadWrite);
            ttl->setBaudRate(QSerialPort::Baud115200);
            ttl->setDataBits(QSerialPort::Data8);
            ttl->setFlowControl(QSerialPort::NoFlowControl);
            ttl->setParity(QSerialPort::NoParity);
            ttl->setStopBits(QSerialPort::OneStop);
            QObject::connect(ttl, SIGNAL(readyRead()), this, SLOT(readSerial()));
            ui->botonpuerto->setText("Cerrar");
    }else{
        ttl->close();
        QObject::disconnect(ttl, SIGNAL(readyRead()), this, SLOT(readSerial()));
        ui->botonpuerto->setText("Abrir");
    }
}

void MainWindow::on_botoninicio_clicked()
{
    QByteArray data; // sin datos extra
    QByteArray paquete = armarPaquete(0x02, data);
    ttl->write(paquete);
    qDebug() << "Enviado arranque:" << paquete.toHex();}

void MainWindow::on_botonpara_clicked()
{
    // --- Enviar comando de paro ---
    QByteArray data; // sin datos extra
    QByteArray paquete = armarPaquete(0x01, data);
    ttl->write(paquete);
    qDebug() << "Enviado paro:" << paquete.toHex();

    // --- Además enviar velocidad = 0 ---
    int16_t vel16 = 0;
    QByteArray velData;
    velData.append((char)(vel16 & 0xFF));        // LSB
    velData.append((char)((vel16 >> 8) & 0xFF)); // MSB

    QByteArray velPaquete = armarPaquete(0x03, velData);
    ttl->write(velPaquete);
    qDebug() << "Velocidad forzada a 0:" << velPaquete.toHex();

    // También actualizar interfaz
    ui->cajaVelocidad->setText("0");
}

void MainWindow::readSerial()
{
    QByteArray data = ttl->readAll();

    if (data.size() >= 2) {
        // STM manda: [LSB][MSB]
        int16_t mms = (static_cast<unsigned char>(data[1]) << 8) |
                      static_cast<unsigned char>(data[0]);

        qDebug() << "mm/s:" << mms;
        ui->recepetor->setText(QString::number(mms));
        makeplot(mms);

    }
}

void MainWindow::processSerial(QString datos){

        //Aquí llegan los datos del puerto serial, se deben tomar las acciones necesarias, como graficar etc.
    qDebug()<< datos;
    if(datos.contains("\r\n")){
        QStringList lista = datos.split("\r\n");
        foreach (QString campos, lista) {
            if(campos.contains("Flow")){
                QStringList lista2 = campos.split(" ");
                if(lista2.length() == 2){
                    QString a = lista2.at(1);
                    //makeplot(a.toDouble(), 2*a.toDouble());
                    }
                }
            }
        }
}

void MainWindow::on_botonVelocidad_clicked(){
    int velocidad = ui->cajaVelocidad->text().toInt();  // convierte texto a int
    if (velocidad > 629) velocidad = 629;
    if (velocidad < -629) velocidad = -629;
    // 2. Convertir a 2 bytes (int16_t → LSB, MSB)
    QByteArray data;
    data.append((char)(velocidad & 0xFF));          // byte bajo
    data.append((char)((velocidad >> 8) & 0xFF));   // byte alto

    // 3. Crear el paquete
    QByteArray paquete = armarPaquete(0x03, data);

    // 4. Enviar por serial
    ttl->write(paquete);

    // 5. Debug
    qDebug() << "Velocidad enviada:" << velocidad << "Paquete:" << paquete.toHex();}

void MainWindow::on_botonvoltaje_clicked()
{
    float volt = ui->cajaVolt->text().toFloat();  // convierte texto a float

    int16_t volt_int = (int16_t)(volt * 1000);   // escala 0.5 → 500

    QByteArray data;
    data.append((char)(volt_int & 0xFF));          // LSB
    data.append((char)((volt_int >> 8) & 0xFF));   // MSB

    QByteArray paquete = armarPaquete(0x04, data);

    ttl->write(paquete);

    qDebug() << "Voltaje enviado:" << volt
             << "Escalado:" << volt_int
             << "Paquete:" << paquete.toHex();
}

void MainWindow::setupPlot()
{
    // inicializar eje tiempo
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setPen(QPen(Qt::blue));
    ui->customPlot->graph(0)->setName("MMS");

    // etiquetas de ejes
    ui->customPlot->xAxis->setLabel("Tiempo (s)");
    ui->customPlot->yAxis->setLabel("MMS");

    // rangos iniciales
    ui->customPlot->xAxis->setRange(0, 1);// 10 segundos visibles
    ui->customPlot->yAxis->setRange(0, 700); // cambia según tu escala de datos

    ui->customPlot->legend->setVisible(true);

    // iniciar timer para el tiempo
    timer.start();
}
void MainWindow::makeplot(double mms)
{
    double t = timer.elapsed() / 1000.0; // tiempo en segundos

    tiempo.append(t);
    datos.append(mms);

    if (tiempo.size() > 10000) { // mantener últimos 200 puntos
        tiempo.remove(0);
        datos.remove(0);
    }

    ui->customPlot->graph(0)->setData(tiempo, datos);
    ui->customPlot->xAxis->setRange(t - 10, t); // muestra últimos 10s
    ui->customPlot->replot();

    QFile logFile("motor_data_75v.log");

    if (logFile.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&logFile);

        out << t << "  " << mms << "\n";
        logFile.close();
    }
}




