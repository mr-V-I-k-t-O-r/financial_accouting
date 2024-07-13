#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

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
    void on_account_clicked();

    void on_employee_clicked();

    void on_post_clicked();

    void on_operation_clicked();

    void on_subject_clicked();

    void on_create_report_clicked();

    void on_type_clicked();

    void on_organization_clicked();

    void on_person_clicked();

private:
    Ui::MainWindow *ui;

protected:
    QSqlDatabase db;
};
#endif // MAINWINDOW_H
