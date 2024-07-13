#include "create_report.h"
#include "ui_create_report.h"

Create_Report::Create_Report(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Create_Report)
{}

Create_Report::Create_Report(QSqlDatabase *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Create_Report),
    db(*db)
{
    ui->setupUi(this);
    this->db.open();

}

Create_Report::~Create_Report()
{
    db.close();
    delete ui;
}

void Create_Report::on_exit_button_clicked()
{
    this->close();
}


void Create_Report::on_report_button_clicked()
{
    if(ui->date_finish->date() < ui->date_start->date()){
        return;
    }
    query = new QSqlQuery;
    query->prepare("SELECT operations.summ, operation_types.income FROM operations JOIN operation_types ON (operation_types.id = operations.operation_type) WHERE operations.date >= :date_start AND operations.date <= :date_finish;");
    query->bindValue(":date_start", ui->date_start->date());
    query->bindValue(":date_finish", ui->date_finish->date());
    query->exec();
    while(query->next()){
        summ = query->value(0).toInt();
        income = query->value(1).toBool();
        if(income){
            ++count_income;
            summ_income += summ;
            summ_total += summ;
        }
        else{
            ++count_expense;
            summ_expense += summ;
            summ_total -= summ;
        }
        ++count_total;
    }
    QString report;
    report += "За выбранный промежуток времени:\n";
    report += QString("Доходов: %1\n").arg(summ_income);
    report += QString("Операций, принесших доход: %1\n").arg(count_income);
    report += QString("Расходов: %1\n").arg(summ_expense);
    report += QString("Операций, принесших расход: %1\n").arg(count_expense);
    report += QString("Общее изменение: %1\n").arg(summ_total);
    report += QString("Всего операций: %1\n").arg(count_total);
    ui->report->setText(report);
    delete query;
    summ_income = 0;
    summ_expense = 0;
    summ_total = 0;
    count_income = 0;
    count_expense = 0;
    count_total = 0;
}

