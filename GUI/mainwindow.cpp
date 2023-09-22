#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      arduino(COM_USED),
      curMaterial(UNKOWN)
{
    nonMetalCntr = 0;
    metalCntr = 0;
    progress = 0;
    ui->setupUi(this);
    setFixedSize(size());
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(trialFunc()));
    timer->start(100);

    ui->progressBar->setStyleSheet(
                "QProgressBar {"
                "background-color: black;"
                "color: white;"
                "border-style: outset;"
                "border-color: #74c8ff;"
                "border-radius: 5px;"
                "text-align: center; }"

                "QProgressBar::chunk {"
                "background-color: #0078d7; "
                "border-radius: 5px;}"
    );

    ui->homingIndicatorLabel->setStyleSheet(INDICATOR_STYLE_SHEET_RED);

    ui->feedingIndicatorLabel->setStyleSheet(INDICATOR_STYLE_SHEET_RED);

    ui->storingIndicatorLabel->setStyleSheet(INDICATOR_STYLE_SHEET_RED);

    ui->metalLabel1->setStyleSheet(INDICATOR_STYLE_SHEET_RED);
    ui->metalLabel2->setStyleSheet(INDICATOR_STYLE_SHEET_RED);
    ui->metalLabel3->setStyleSheet(INDICATOR_STYLE_SHEET_RED);
    ui->metalLabel4->setStyleSheet(INDICATOR_STYLE_SHEET_RED);

    ui->plasticLabel1->setStyleSheet(INDICATOR_STYLE_SHEET_RED);
    ui->plasticLabel2->setStyleSheet(INDICATOR_STYLE_SHEET_RED);
    ui->plasticLabel3->setStyleSheet(INDICATOR_STYLE_SHEET_RED);
    ui->plasticLabel4->setStyleSheet(INDICATOR_STYLE_SHEET_RED);
}

void MainWindow::trialFunc()
{
    char rec[MAX_DATA_LENGTH];
    rec[0] = 'h';
    if(arduino.readSerialPort(rec, MAX_DATA_LENGTH))
    {
        ui->progressBar->setValue(ui->progressBar->value() + 3);
        switch (rec[0]){
            case 'h':
              ui->materialLabel->setText("UNKOWN");
              ui->homingIndicatorLabel->setStyleSheet(INDICATOR_STYLE_SHEET_GREEN);
              ui->feedingIndicatorLabel->setStyleSheet(INDICATOR_STYLE_SHEET_RED);
              ui->storingIndicatorLabel->setStyleSheet(INDICATOR_STYLE_SHEET_RED);
            break;

            case 'f':
                ui->homingIndicatorLabel->setStyleSheet(INDICATOR_STYLE_SHEET_RED);
                ui->feedingIndicatorLabel->setStyleSheet(INDICATOR_STYLE_SHEET_GREEN);
                ui->storingIndicatorLabel->setStyleSheet(INDICATOR_STYLE_SHEET_RED);
            break;

            case 'm':
                ui->materialLabel->setText("METAL");
                ui->homingIndicatorLabel->setStyleSheet(INDICATOR_STYLE_SHEET_RED);
                ui->feedingIndicatorLabel->setStyleSheet(INDICATOR_STYLE_SHEET_RED);
                ui->storingIndicatorLabel->setStyleSheet(INDICATOR_STYLE_SHEET_GREEN);
                curMaterial = METAL;
            break;

            case 'n':
                ui->materialLabel->setText("PLASTIC");
                ui->homingIndicatorLabel->setStyleSheet(INDICATOR_STYLE_SHEET_RED);
                ui->feedingIndicatorLabel->setStyleSheet(INDICATOR_STYLE_SHEET_RED);
                ui->storingIndicatorLabel->setStyleSheet(INDICATOR_STYLE_SHEET_GREEN);
                curMaterial = PLASTIC;
            break;

            case 's':
                if(METAL == curMaterial)
                {
                    metalCntr++;
                    ui->metalLcdNumber->display((int)metalCntr);
                    switch(metalCntr)
                    {
                        case 1:
                            ui->metalLabel1->setStyleSheet(INDICATOR_STYLE_SHEET_GREEN);
                        break;

                        case 2:
                            ui->metalLabel2->setStyleSheet(INDICATOR_STYLE_SHEET_GREEN);
                        break;

                        case 3:
                            ui->metalLabel3->setStyleSheet(INDICATOR_STYLE_SHEET_GREEN);
                        break;

                        case 4:
                            ui->metalLabel4->setStyleSheet(INDICATOR_STYLE_SHEET_GREEN);
                        break;
                    }
                }
                else if(PLASTIC == curMaterial)
                {
                    nonMetalCntr++;
                    ui->plasticLcdNumber->display((int)nonMetalCntr);
                    switch(nonMetalCntr)
                    {
                        case 1:
                            ui->plasticLabel1->setStyleSheet(INDICATOR_STYLE_SHEET_GREEN);
                        break;

                        case 2:
                            ui->plasticLabel2->setStyleSheet(INDICATOR_STYLE_SHEET_GREEN);
                        break;

                        case 3:
                            ui->plasticLabel3->setStyleSheet(INDICATOR_STYLE_SHEET_GREEN);
                        break;

                        case 4:
                            ui->plasticLabel4->setStyleSheet(INDICATOR_STYLE_SHEET_GREEN);
                        break;
                    }
                }
                else
                {

                }
            break;


            case 'z':
                ui->progressBar->setValue(100);
                ui->materialLabel->setText("UNKOWN");
                ui->homingIndicatorLabel->setStyleSheet(INDICATOR_STYLE_SHEET_RED);
                ui->feedingIndicatorLabel->setStyleSheet(INDICATOR_STYLE_SHEET_RED);
                ui->storingIndicatorLabel->setStyleSheet(INDICATOR_STYLE_SHEET_RED);
            break;
        }
    }
}

MainWindow::~MainWindow()
{
    delete timer;
    delete ui;
}
