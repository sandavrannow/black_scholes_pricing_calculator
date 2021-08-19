#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "main_back.cpp"
#include <QString>
using namespace std ;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_pushButton_2_clicked() {

    ui->doubleSpinBox->setValue( 0.0 ) ;
    ui->doubleSpinBox_2->setValue( 0.0 ) ;
    ui->doubleSpinBox_3->setValue( 0.0 ) ;
    ui->doubleSpinBox_4->setValue( 0.0 ) ;
    ui->doubleSpinBox_5->setValue( 0.0 ) ;
    ui->lcdNumber->display( 0 ) ;
    ui->lcdNumber_2->display( 0 ) ;
    ui->lcdNumber_4->display( 0 ) ;
    ui->lcdNumber_5->display( 0 ) ;
    ui->lcdNumber_3->display( 0 ) ;
    ui->lcdNumber_6->display( 0 ) ;
    ui->lcdNumber_7->display( 0 ) ;
    ui->lcdNumber_9->display( 0 ) ;
    ui->lcdNumber_10->display( 0 ) ;
    ui->lcdNumber_11->display( 0 ) ;
    ui->lcdNumber_12->display( 0 ) ;
    ui->lcdNumber_13->display( 0 ) ;

}

void MainWindow::on_pushButton_clicked() {

    double underlying_price = ui->doubleSpinBox->value() ;
    double strike_price = ui->doubleSpinBox_3->value() ;
    double risk_free_rate = ui->doubleSpinBox_2->value() ;
    double volatility = ui->doubleSpinBox_4->value() ;
    double time = ui->doubleSpinBox_5->value() ;

    if ( underlying_price != 0 && strike_price != 0 && risk_free_rate != 0 && volatility != 0 && time != 0 ) {

        double call_delta = calculate_call_delta(underlying_price, strike_price, risk_free_rate, volatility , time ) ;
        double put_delta = calculate_put_delta(underlying_price, strike_price, risk_free_rate, volatility , time ) ;


        double call_gamma = calculate_call_gamma(underlying_price, strike_price, risk_free_rate, volatility , time ) ;
        double put_gamma = calculate_put_gamma(underlying_price, strike_price, risk_free_rate, volatility , time ) ;
        double call_vega = calculate_call_vega(underlying_price, strike_price, risk_free_rate, volatility , time ) ;
        double put_vega = calculate_put_vega(underlying_price, strike_price, risk_free_rate, volatility , time ) ;
        double call_theta = calculate_call_theta(underlying_price, strike_price, risk_free_rate, volatility , time ) ;
        double put_theta = calculate_put_theta(underlying_price, strike_price, risk_free_rate, volatility , time ) ;
        double call_rho = calculate_call_rho(underlying_price, strike_price, risk_free_rate, volatility , time ) ;
        double put_rho = calculate_put_rho(underlying_price, strike_price, risk_free_rate, volatility , time ) ;
        double call_price = calculate_call_price(underlying_price, strike_price, risk_free_rate, volatility , time ) ;
        double put_price = calculate_put_price( call_price , underlying_price , strike_price , risk_free_rate , time ) ;
        ui->lcdNumber->display( call_delta ) ;
        ui->lcdNumber_2->display( put_delta ) ;
        ui->lcdNumber_4->display( call_gamma ) ;
        ui->lcdNumber_5->display( put_gamma ) ;
        ui->lcdNumber_3->display( call_vega ) ;
        ui->lcdNumber_6->display( put_vega ) ;
        ui->lcdNumber_7->display( call_theta ) ;
        ui->lcdNumber_9->display( put_theta ) ;
        ui->lcdNumber_10->display( call_rho ) ;
        ui->lcdNumber_11->display( put_rho ) ;
        ui->lcdNumber_12->display( call_price ) ;
        ui->lcdNumber_13->display( put_price ) ;

    }
}

