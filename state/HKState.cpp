/**
  * @file
  * @author Hüseyin Kozan <posta@huseyinkozan.com.tr>
  */

#include "HKState.h"
#include <QVariant>
#include <QVector>
#include <QMap>
#include <QPointer>

#define HK_PROPERTY_NAME_STATE "hk_state"
#define HK_PROPERTY_NAME_SEPARATOR "hk_separator"

#define HK_PROPERTY_NAME_PARENT_STATE "hk_parent_state"


/**
 * @brief subMapHelper
 * @param s
 * @param state
 * @return
 *
 * On : hk_On_have_Alert -> ptr
 * All : hk__have_Alert -> ptr
 */
QString subMapHelper(HKState * s, const QString & state) {
    return QString("hk_") + state + "_have_" + s->metaObject()->className();
}


/**
 * @brief ctor
 * @param parent
 */
HKState::HKState(QObject *parent)
    : QObject(parent)
{
    // prepare state storage
    if ( ! property(HK_PROPERTY_NAME_STATE).isValid()) {
        setProperty(HK_PROPERTY_NAME_STATE, QVariant(QString("")));
    }
    if ( ! property(HK_PROPERTY_NAME_SEPARATOR).isValid()) {
        setProperty(HK_PROPERTY_NAME_SEPARATOR, QVariant(QChar('/')));
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
 * @param state state string
 *
 * Sets own state and substates. State string
 * must look like a/b/c (if separator is /) to set substate.
 *
 * Assume:
 *   * "a" have substate "1" and "2".
 *   * "b" have no substate.
 *   * Separator is "/"
 * @example set("a") -> sets "a" and sub to empty.
 * @example set("a/1") -> sets "a" and sub to "1".
 * @example set("b") -> sets b.
 */
void HKState::set(const QString &state)
{
    if (toString() == state)
        return;

    QChar sep = property(HK_PROPERTY_NAME_SEPARATOR).toChar();

    // if not have substate -> only change state property
    // else -> set("...") will be the leaf at the object hierarchy.
    // so: if state parent is a HKState,
    //     find the root, collect path while going to root,
    //     call roots func to set states through leaf.

    HKState * hks = NULL;
    QObject * nextParent = this;
    QString path = state;

    while ( (hks = qobject_cast<HKState*>(nextParent)) != NULL) {
        hks->setPath(path);
        QVariant v = hks->property(HK_PROPERTY_NAME_PARENT_STATE);
        if (v.isValid() && ( ! v.toString().isEmpty())) {
            path = v.toString() + sep + path;
        }
        nextParent = hks->parent();
    }
//    qDebug("set(%s) : path = %s", qPrintable(state), qPrintable(path));
}

/**
 * @brief checker of freely changable state api
 * @param state
 * @return true if in this state of substate
 *
 * @example "a/1/x" is("a/1/x") -> true
 * @example "a/1/x" is("a/1")   -> true
 * @example "a/1/y" is("a")     -> true
 */
bool HKState::is(const QString &state) const
{
    if (state.isEmpty())
        return false;
    return property(HK_PROPERTY_NAME_STATE).toString().indexOf(state) == 0;
}

/**
 * @brief current state (getter of freely changable state api)
 * @return
 */
QString HKState::toString() const
{
    return property(HK_PROPERTY_NAME_STATE).toString();
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
            .arg(toString());
}

/**
 * @brief HKState::setSubSeparator
 * @param c
 */
void HKState::setSubSeparator(const QChar &c)
{
    setProperty(HK_PROPERTY_NAME_SEPARATOR, QVariant(c));
}

/**
 * @brief HKState::subSeparator
 * @return
 */
QChar HKState::subSeparator() const
{
    return property(HK_PROPERTY_NAME_SEPARATOR).toChar();
}

/**
 * @brief HKState::addSub
 * @param s substate
 * @param state substate of this state
 */
void HKState::addSub(QObject *s, const QString &state)
{
    // check sub
    HKState * hkState = qobject_cast<HKState*>(s);
    Q_ASSERT(hkState != NULL); // substate must be HKState
    // check state is not added befre
    Q_ASSERT(sub(state) == NULL);
    // set parent state of child
    hkState->setProperty(HK_PROPERTY_NAME_PARENT_STATE, QVariant(state));
}

/**
 * @brief HKState::sub
 * @param state
 * @return
 */
QObject *HKState::sub(const QString &state)
{
    QObjectList ol = children();
    foreach (QObject * o, ol) {
        QVariant v = o->property(HK_PROPERTY_NAME_PARENT_STATE);
        if ( ! v.isValid())
            continue;
        if (v.toString().isEmpty())
            continue;
        if (v.toString() == state)
            return o;
    }
    return NULL;
}

void HKState::setPath(const QString &state)
{
    emit changing(toString(), state);
    setProperty(HK_PROPERTY_NAME_STATE, QVariant(state));
    emit changed();
}
