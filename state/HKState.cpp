/**
  * @file
  * @author Hüseyin Kozan <posta@huseyinkozan.com.tr>
  */

#include "HKState.h"

/**
 * @brief setter of freely changable state api
 * @param state
 *
 * Tip : Derive this and use macros to be able to use signal-slot connection.
 */
void HKState::set(const QString &state)
{
    if (m_state == state)
        return;
    emit changing(m_state, state);
    m_state = state;
    emit changed();
}

/**
 * @brief checker of freely changable state api
 * @param state
 * @return
 */
bool HKState::is(const QString &state) const
{
    return m_state == state;
}

/**
 * @brief current state (getter of freely changable state api)
 * @return
 */
QString HKState::toString() const
{
    return m_state;
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
            .arg(m_state);
}
