#ifndef CIDITEM_H
#define CIDITEM_H
#include "hacc_types.h"
namespace hacc
{

//! Интерфейс идентификатора
/*!
 Реализует базовый функционал работы с идентификатором записи БД
 Собственно, хранит этот идентификатор.
 Если ктото наследует этот класс, то подразумевается, что этот "ктото" предоставляет единственную строку БД
*/
class CIDItem
{
public:
    CIDItem(const hacc::TDBID & id = 0);
    hacc::TDBID & id();                         //!< возвращает идентификатор
    virtual void setID(const hacc::TDBID & id); //!< Присваивает значение идентификатору
private:
    hacc::TDBID m_id;                           //!< Идентификатор
};

}
#endif // CIDITEM_H
