/**
  * @file
  * @author Hüseyin Kozan <posta@huseyinkozan.com.tr>
  */

#include "HKState.h"
#include <QVariant>

#define PROPERTY_NAME "hk_state"

/**
 * @brief ctor
 * @param parent
 */
HKState::HKState(QObject *parent) : QObject(parent)
{
    // prepare state storage
    if ( ! property(PROPERTY_NAME).isValid()) {
        setProperty(PROPERTY_NAME, QVariant(QString("")));
    }
}

/**
 * @brief dtor
 */
HKState::~HKState()
{
}

/**
 * @brief setter of freely changable state api
 * @param state
 *
 * Tip : Derive this and use macros to be able to use signal-slot connection.
 */
void HKState::set(const QString &state)
{
    if (property(PROPERTY_NAME).toString() == state)
        return;
    emit changing(property(PROPERTY_NAME).toString(), state);
    setProperty(PROPERTY_NAME, QVariant(state));
    emit changed();
}

/**
 * @brief checker of freely changable state api
 * @param state
 * @return
 */
bool HKState::is(const QString &state) const
{
    return property(PROPERTY_NAME).toString() == state;
}

/**
 * @brief current state (getter of freely changable state api)
 * @return
 */
QString HKState::toString() const
{
    return property(PROPERTY_NAME).toString();
}

/**
 * @brief the current state with class name
 * @return
 */
QString HKState::toDebugString() const
{
    return QString("%1 %2 = %3;")
            .arg(metaObject()->className())
            .arg(objectName())
            .arg(property(PROPERTY_NAME).toString());
}
