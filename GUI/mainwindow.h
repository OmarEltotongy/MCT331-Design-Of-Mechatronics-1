#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qtimer.h>
#include "SerialPort.hpp"

#define COM_USED                         "\\\\.\\COM13"

#define INDICATOR_STYLE_SHEET_RED       ("QLabel {background-color: #8B0000; border-style: outset; border-color: #74c8ff; border-radius: 7px;}")
#define INDICATOR_STYLE_SHEET_GREEN     ("QLabel {background-color: green; border-style: outset; border-color: #74c8ff; border-radius: 7px;}")
#define INDICATOR_STYLE_SHEET_BLUE      ("QLabel {background-color: #00008B; border-style: outset; border-color: #74c8ff; border-radius: 7px;}")

typedef enum
{
    UNKOWN, METAL, PLASTIC
}MATERIAL;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void trialFunc();

private:
    Ui::MainWindow *ui;
    QTimer* timer;
    SerialPort arduino;
    MATERIAL curMaterial;
    float progress;
    unsigned int metalCntr;
    unsigned int nonMetalCntr;
};
#endif // MAINWINDOW_H
