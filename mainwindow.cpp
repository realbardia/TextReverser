#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::on_textEdit_textChanged()
{
    QString result;
    QString text = ui->textEdit->toPlainText();
    QStringList lines = text.split("\n");
    for(const QString &l: lines)
    {
        for(qint32 i=l.count()-1; i >= 0; i--)
        {
            QChar ch = l.at(i);
            if(ch.direction() != QChar::DirAL && result.count() > 0)
            {
                qint32 lastIdx = result.count()-1;
                while(lastIdx >= 0 && result.at(lastIdx).direction() != QChar::DirAL && result.at(lastIdx) != '\n')
                    lastIdx--;

                if(lastIdx == -1)
                    result += ch;
                else
                    result.insert(lastIdx+1, ch);
            }
            else
                result += ch;

        }
        result += "\n";
    }
    ui->textBrowser->setText(result);
}

MainWindow::~MainWindow()
{
    delete ui;
}
