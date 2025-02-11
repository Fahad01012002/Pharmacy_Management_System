#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QCloseEvent>

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
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void closeEvent(QCloseEvent *event);

    void on_pushButton_3_clicked();

private:
    void saveDataToFile();
    void loadDataFromFile();

    Ui::MainWindow *ui;
    QStringList medicines;
    QStringList prices;
    QStringList total_quantity;
};
#endif // MAINWINDOW_H
