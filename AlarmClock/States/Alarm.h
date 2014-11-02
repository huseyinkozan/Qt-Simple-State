#ifndef ALARM_H
#define ALARM_H

#include "HKState.h"
#include "Alarm/Alert.h"
#include "Mode.h"

/**
 * @brief The Alarm class.
 * @author Hüseyin Kozan <posta@huseyinkozan.com.tr>
 *
 * Example of manually defined states.
 */

class Alarm : public HKState
{
    Q_OBJECT

    // add states

signals:
    // signals to emit after state change
    void atOff();
    void atOn();

public slots:
    // slots to be able to change state
    void setOff() { set("Off"); emit atOff(); }
    void setOn() { set("On"); emit atOn(); }

    // substate
    Alert * setAlert() { emit atOn(); return getAlert(); /* to chaning */ }

public:
    // checkers to test if state is ...
    bool isOff() const { return is("Off"); }
    bool isOn() const { return is("On"); }

    // substate
    Alert * getAlert() { return qobject_cast<Alert*>(sub("On")); }

public:
    explicit Alarm(QObject *parent = 0) : HKState(parent) {

        // set default state
        setOff();

        // add substate
        // QObject dtor will delete Alert from memory.
        // "On" states for aler is only for On state.
        addSub(new Alert(this), "On");
    }
};

#endif // ALARM_H
