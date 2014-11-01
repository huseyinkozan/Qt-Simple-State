#ifndef MODE_H
#define MODE_H

#include "HKState.h"

/**
 * @brief The TimeKeeping class.
 * @author Hüseyin Kozan <posta@huseyinkozan.com.tr>
 *
 * Example of macro defined states.
 */

class Mode : public HKState
{
    Q_OBJECT

    // add states
    HK_STATE_ADD(Mode12);
    HK_STATE_ADD(Mode24);

public:
    explicit Mode(QObject *parent = 0) : HKState(parent) {
        // set default state, if not state is empty string.
        HK_STATE_SET_DEFAULT(Mode24);
    }
};

#endif // MODE_H
