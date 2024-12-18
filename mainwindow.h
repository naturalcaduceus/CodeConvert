#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void nextFile(int Index);
    void loadFile(QString strDir);
    
private slots:
    void on_BT_choseFile_clicked();
    void on_BT_fromUTF8_clicked();
    void on_BT_fromGBK_clicked();
    void on_BT_skip_clicked();
    void on_CB_files_currentIndexChanged(int index);
    void on_checkBox_copy_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    QLabel m_warning;
    QString m_strTrPath;
};

#endif // MAINWINDOW_H
