/**
  * @file
  * @author Hüseyin Kozan <posta@huseyinkozan.com.tr>
  */

#ifndef HKSTATE_H
#define HKSTATE_H

#include <QObject>

/**
 * @class HKState
 * @brief The HKState class
 * @author Hüseyin Kozan <posta@huseyinkozan.com.tr>
 *
 * You can build a state machine like:
 *   * Derive from HKState
 *     * Manually define signal, slot, and checker (AlarmClock/Alarm.h)
 *     * Use HK_STATE_ADD macro to define signal, slot and checker
 *       (AlarmClock/Mode.h)
 *   * Set and get states as string with set() and toString().
 *     Use changed() signal to inform.
 *
 * See AlarmClock example.
 *
 * TODO : to property, hierarchy, entering(), exiting(), entered(), exited()
 */

class HKState : public QObject
{
    Q_OBJECT

public:
    explicit HKState(QObject *parent = 0);
    virtual ~HKState();

    void set(const QString & state);
    bool is(const QString & state) const;
    QString toString() const;
    QString toDebugString() const;

signals:
    void changing(const QString & current, const QString & next);
    void changed();
};

/**
  * @def HK_STATE_ADD(Name)
  * Adds a state which includes:
  *   * Slot    -> void set...();   // sets state to this ...
  *   * Function-> void is...();    // to check if state is this ...
  *   * Signal  -> void at...();    // to inform after state is this ...
  *
  */
#define HK_STATE_ADD(Name) \
    public Q_SLOTS: \
        void set##Name() { set(#Name); emit at##Name(); } \
    public: \
        bool is##Name() const { return is(#Name); } \
    Q_SIGNALS: \
        void at##Name()

/**
  * @def HK_STATE_SET_DEFAULT(Name)
  * Only calls setter of the given state (set...();).
  */
#define HK_STATE_SET_DEFAULT(Name) \
    set##Name()


#endif // HKSTATE_H
