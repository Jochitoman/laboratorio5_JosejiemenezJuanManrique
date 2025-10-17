#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QSerialPort>
#include <QElapsedTimer>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void readSerial();

    void on_botonpuerto_clicked();

    void on_botoninicio_clicked();

    void on_botonpara_clicked();

    void on_botonVelocidad_clicked();

    void processSerial(QString datos);

    void on_botonvoltaje_clicked();

    void setupPlot();

    void makeplot(double mms);

private:
    QByteArray serialData;
    Ui::MainWindow *ui;
    QSerialPort *ttl;
    QString serialBuffer;
    QString parsed_data;
    QElapsedTimer timer;
    QVector<double> tiempo;
    QVector<double> datos;


};
#endif // MAINWINDOW_H
