#include "cbases.h"
#include "st.h"
namespace hacc
{
namespace model
{
namespace base
{

CBases::CBases()
{
    m_maxID = 0;
}

CBases::~CBases()
{}

/**
  * Возвращает новый уникальный идентификатор записи для таблицы БД
  * @see maxDBID()
  * @see m_maxID
  */
hacc::TDBID CBases::nextID()
{
    if(!m_maxID)
    {
        m_maxID = maxDBID();
    }
    return ++m_maxID;
}

/**
  Проверяет кеш готовых QAction и отдает уже созданное, если есть. Иначе создает новое
  при помощи generateAction() и укладывает в кеш
  @see nextID()
  @see m_maxID
  @return Готовую к употреблению QAction
*/
QAction * CBases::constructAction(EActionsTypes atype, const hacc::TDBID &id, QObject *reciever, const char * method)
{
    QAction *& action = m_actions[atype][id];
    if(action == NULL)
    {
        action = generateAction(atype, reciever, method);
        action->setEnabled(HACC_DB->isOpen());
        connect(HACC_DB, SIGNAL(stateChange(bool)), action, SLOT(setEnabled(bool)));
    }
    return action;
}

QAction * CBases::addAction     (const hacc::TDBID &id, QObject *reciever, const char * method) { return constructAction(atAdd     , id, reciever, method); }
QAction * CBases::editAction    (const hacc::TDBID &id, QObject *reciever, const char * method) { return constructAction(atEdit    , id, reciever, method); }
QAction * CBases::removeAction  (const hacc::TDBID &id, QObject *reciever, const char * method) { return constructAction(atRemove  , id, reciever, method); }
QAction * CBases::tagsEditAction(const hacc::TDBID &id, QObject *reciever, const char * method) { return constructAction(atTagsEdit, id, reciever, method); }


}
}
}
