#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "States/Alarm.h"
#include "States/Mode.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void stateChanging(const QString & current, const QString & next);
    void atState();

private:
    Ui::MainWindow *ui;

    Alarm m_alarm;
    Mode m_mode;
};

#endif // MAINWINDOW_H
