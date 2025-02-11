#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStringList>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Load data from file at startup
    loadDataFromFile();

    // Connect button signals to slots
    connect(ui->pushButton, SIGNAL(clicked()),
            this, SLOT(on_pushButton_clicked()));
    connect(ui->pushButton_2, SIGNAL(clicked()),
            this, SLOT(on_pushButton_2_clicked()));
    connect(ui->pushButton_3, SIGNAL(clicked()),
            this, SLOT(close()));
}

MainWindow::~MainWindow()
{
    // Save data to file when exiting
    saveDataToFile();
    delete ui;
}

// Save data to file
void MainWindow::saveDataToFile()
{
    QFile file("inventory.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error!", "Unable to open file for saving.");
        return;
    }

    QTextStream out(&file);
    for (int i = 0; i < medicines.length(); ++i) {
        out << medicines[i] << "," << prices[i] << "," << total_quantity[i] << "\n";
    }

    file.close();
    qDebug() << "Data saved to file.";
}

// Load data from file
void MainWindow::loadDataFromFile()
{
    QFile file("inventory.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error!", "Unable to open file for reading.");
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList data = line.split(",");

        if (data.size() == 3) {
            medicines.append(data[0]);
            prices.append(data[1]);
            total_quantity.append(data[2]);
        }
    }

    file.close();
    qDebug() << "Data loaded from file.";
}

void MainWindow::on_pushButton_clicked()
{
    QString medicine = ui->lineEdit->text();
    QString quantity = ui->lineEdit_3->text();
    QString price = ui->lineEdit_2->text();

    if (medicine.isEmpty() || quantity.isEmpty() || price.isEmpty()) {
        QMessageBox::warning(this, "Error!", "Please fill in all fields.");
        return;
    }

    bool ok;
    int quantity_int = quantity.toInt(&ok);
    if (!ok || quantity_int < 0) {
        QMessageBox::warning(this, "Error!", "Invalid quantity.");
        return;
    }

    medicines.append(medicine);
    prices.append(price);
    total_quantity.append(quantity);

    QMessageBox::information(this, "Success!", "Medicine Added Successfully!");
}

void MainWindow::on_pushButton_2_clicked()
{
    QString user_m = ui->lineEdit->text();
    QString user_q = ui->lineEdit_3->text();

    if (user_m.isEmpty() || user_q.isEmpty()) {
        QMessageBox::warning(this, "Error!", "Please fill in all fields.");
        return;
    }

    bool ok;
    int quantity_int = user_q.toInt(&ok);
    if (!ok || quantity_int < 0) {
        QMessageBox::warning(this, "Error!", "Invalid quantity.");
        return;
    }

    bool found = false;

    for (int i = 0; i < medicines.length(); i++) {
        if (user_m == medicines[i]) {
            found = true;

            int prices_int = prices[i].toInt();
            int total_quantity_int = total_quantity[i].toInt();

            if (quantity_int > total_quantity_int) {
                QMessageBox::warning(this, "Error!", "Insufficient quantity in inventory.");
                return;
            }

            int bill = (quantity_int * prices_int);
            QString bill_str = QString::number(bill);

            total_quantity_int = total_quantity_int - quantity_int;
            total_quantity[i] = QString::number(total_quantity_int);

            QMessageBox::information(this, "Customer Bill",
                                     "Total Bill " + bill_str + " For " + medicines[i] +
                                         "\nRemaining Quantity: " + total_quantity[i]);

            break;
        }
    }

    if (!found) {
        QMessageBox::information(this, "Error!", "Invalid Medicine!");
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    saveDataToFile();  // Save data when the window is closed
    event->accept();
}

void MainWindow::on_pushButton_3_clicked()
{

}

