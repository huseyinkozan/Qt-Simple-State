#ifndef ALERT_H
#define ALERT_H

#include "HKState.h"


/**
 * @brief The Alarm class.
 * @author Hüseyin Kozan <posta@huseyinkozan.com.tr>
 *
 * Example of substate.
 */

class Alert : public HKState
{
    Q_OBJECT

    // add states
    HK_ADD_STATE(All);
    HK_ADD_STATE(Sound);
    HK_ADD_STATE(Vibration);

public:
    explicit Alert(QObject *parent = 0) : HKState(parent) {
        // set default state
        HK_SET_DEFAULT_STATE(All);
    }
};

#endif // ALERT_H
