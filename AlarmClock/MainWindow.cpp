#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QMetaMethod>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // usage of setter slots
    connect(ui->alarmOffButton, SIGNAL(clicked()), &m_alarm, SLOT(setOff()));
    connect(ui->alarmOnButton, SIGNAL(clicked()), &m_alarm, SLOT(setOn()));
    connect(ui->mode12Button, SIGNAL(clicked()), &m_mode, SLOT(setMode12()));
    connect(ui->mode24Button, SIGNAL(clicked()), &m_mode, SLOT(setMode24()));

    // usage of signals
    connect(&m_alarm, SIGNAL(atOff()), SLOT(atState()));
    connect(&m_alarm, SIGNAL(atOn()), SLOT(atState()));
    connect(&m_mode, SIGNAL(atMode12()), SLOT(atState()));
    connect(&m_mode, SIGNAL(atMode24()), SLOT(atState()));

    // usage of substate signals
    connect(m_alarm.getAlert(), SIGNAL(atAll()), SLOT(atState()));
    connect(m_alarm.getAlert(), SIGNAL(atSound()), SLOT(atState()));
    connect(m_alarm.getAlert(), SIGNAL(atVibration()), SLOT(atState()));

    // usage of changing signal
    connect(&m_alarm, SIGNAL(changing(QString,QString)),
            SLOT(stateChanging(QString,QString)));
    connect(&m_mode, SIGNAL(changing(QString,QString)),
            SLOT(stateChanging(QString,QString)));

    // example of state connection
    connect(&m_alarm, SIGNAL(atOff()), &m_mode, SLOT(setMode24()));
    connect(&m_alarm, SIGNAL(atOn()), &m_mode, SLOT(setMode12()));

    // use of debug string
    ui->textEdit->append("<b>Initial states:</b>");
    ui->textEdit->append(m_alarm.toDebugString());
    ui->textEdit->append(m_mode.toDebugString());
    ui->textEdit->append("<b>Changind states...</b>");

    // usage of setters as function call
    m_alarm.setOn();
    m_alarm.setOff();

    // test substates
    m_alarm.setAlert()->setAll();
    m_alarm.setAlert()->setSound();
    m_alarm.setAlert()->setVibration();

    m_mode.setMode12();
    m_mode.setMode24();

    ui->textEdit->append("<b>Use radio buttons to change states.</b>");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::stateChanging(const QString &current, const QString &next)
{
    // find who called and print
    QString s = sender() ? sender()->metaObject()->className() : "?";
    ui->textEdit->append(s + " : " + current + " => " + next + ".");
}

void MainWindow::atState()
{
    // find who and which function called and get proper action
    QObject * s = sender();
    if ( ! s) {
        ui->textEdit->append("atState() : No sender.");
        return;
    }
    int s_i = senderSignalIndex();
    QString m = s->metaObject()->method(s_i).methodSignature().data();

    // debug : find function names
//    ui->textEdit->append(QString("atState() : m=%1, c=%2")
//                         .arg(m).arg(s->metaObject()->className()));

    if ( qobject_cast<Alarm*>(s) == &m_alarm && m == "atOff()")
        ui->alarmOffButton->setChecked(true);
    if ( qobject_cast<Alarm*>(s) == &m_alarm && m == "atOn()")
        ui->alarmOnButton->setChecked(true);
    if ( qobject_cast<Mode*>(s) == &m_mode && m == "atMode12()")
        ui->mode12Button->setChecked(true);
    if ( qobject_cast<Mode*>(s) == &m_mode && m == "atMode24()")
        ui->mode24Button->setChecked(true);
}

