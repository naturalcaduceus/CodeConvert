#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include "transcode.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList TypeItems;
    TypeItems<<"UTF-8"<<"GBK";
    ui->comboBox->addItems(TypeItems);

    ui->progressBar->reset();
    //同步滚动条
    ui->PTE_readByGBK->setVerticalScrollBar(ui->verticalScrollBar);
    ui->PTE_readByUTF8->setVerticalScrollBar(ui->verticalScrollBar);

    ui->statusBar->addWidget(&m_warning);
    m_warning.setText("欢迎使用，如果遇到大文件请用命令行转换，author：CSDN@超自然祈祷");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_BT_choseFile_clicked()
{
    QStringList StrDirs = QFileDialog::getOpenFileNames(this,"选择多个文件",
                                                            QApplication::applicationFilePath(),
                                                        "All text files (*.cpp *.c *.h *.pro *.txt)");
    if(StrDirs.isEmpty()) return ;

    ui->CB_files->clear();
    ui->CB_files->addItems(StrDirs);
    ui->CB_files->setCurrentIndex(0);

    ui->progressBar->setMaximum(StrDirs.size());
    ui->progressBar->reset();

    //会自动触发on_CB_files_currentIndexChanged（）函数，不用主动调用
}

void MainWindow::nextFile(int Index)
{
    if(Index >= ui->CB_files->count())
    {
        ui->progressBar->setValue(Index);
        QMessageBox::warning(this,"列表到底了","列表已经完成");
        ui->PTE_readByGBK->clear();
        ui->PTE_readByUTF8->clear();
        return;
    }
    ui->CB_files->setCurrentIndex(Index);
    ui->LE_pathShow->setText(ui->CB_files->currentText());
    ui->progressBar->setValue(Index);

    loadFile(ui->CB_files->currentText());
}

void MainWindow::loadFile(QString strDir)
{
    if(strDir.isEmpty())
    {
        QMessageBox::warning(this,"警告","文件读取发生问题");
    }
    else
    {
        m_strTrPath = strDir;

        //
        g_transfrom.readFile(strDir);
        ui->PTE_readByGBK->clear();
        ui->PTE_readByGBK->appendPlainText(g_transfrom.ReadFromGBK());

        ui->PTE_readByUTF8->clear();
        ui->PTE_readByUTF8->appendPlainText(g_transfrom.ReadFromUTF8());
    }
}

void MainWindow::on_BT_fromUTF8_clicked()
{
    QString type = ui->comboBox->currentText();
    if(type == "GBK"){
        g_transfrom.coverUTF8toGBK(m_strTrPath);
        m_warning.setText("转换成功");
    }
    else{
        m_warning.setText("与原格式相同，无需转换");
    }
    nextFile(ui->CB_files->currentIndex()+1);
}

void MainWindow::on_BT_fromGBK_clicked()
{
    QString type = ui->comboBox->currentText();
    if(type == "UTF-8"){
        g_transfrom.coverGBKtoUTF8(m_strTrPath);
        m_warning.setText("转换成功");
    }
    else{
        m_warning.setText("与原格式相同，无需转换");
    }
    nextFile(ui->CB_files->currentIndex()+1);
}

void MainWindow::on_BT_skip_clicked()
{
    nextFile(ui->CB_files->currentIndex()+1);
    m_warning.setText("跳过文件");
}

void MainWindow::on_CB_files_currentIndexChanged(int index)
{
    if(ui->CB_files->count()>index && 0<=index){
        nextFile(index);
    }
}
