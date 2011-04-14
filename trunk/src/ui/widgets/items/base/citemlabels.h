#ifndef CITEMLABELS_H
#define CITEMLABELS_H

#include <QWidget>
#include <QMap>
#include "witemlabel.h"
#include <QGridLayout>

namespace ui
{
namespace item
{
namespace base
{

//! Ячейки для грида
/**
  Используются как в самом гриде, так и в заголовках
  */
class CItemLabels
{
public:
    CItemLabels();
    virtual ~CItemLabels();
    void initialize(const int &columns, const int &rows, QWidget *parent, QGridLayout *layout);
    void setText   (const int &column , const int &row , const QString     &text); //!< Присваивание текста ячейке
    void setIcon   (const int &column , const int &row , const QIcon       &icon); //!< Присваивание иконки ячейке
    void setIcon   (const int &column , const int &row , const QString     &file); //!< Присваивание иконки ячейке
    void setIcon   (const int &column , const int &row , const hacc::TDBID &iid ); //!< Присваивание иконки ячейке
    ui::widget::WControlLabel *controlLabel(const int &column, const int &row);    //!< Вернет ячейку
    void setPropertyToAll(const char *name, const QVariant &property);             //!< Установка QObject property каждой ячейке
    void setStyleSrcToAll(const QString &style);                                   //!< Установка стиля каждой ячейке
    void setLabels(const QStringList& strings);                                    //!< Присваивание текста ячейкам
    int labelsHeight();                                                            //!< Высота строки
    void fixHeight();                                                              //!< фиксация высоты

private:
    int id(const int &column, const int &row); //!< вычисление идентификатора для ячеек
    QMap<int, WItemLabel *> m_labels; //!< Ячейки
    QWidget     *m_parent;            //!< Родитель для ячейки
    QGridLayout *m_layout;            //!< Разметка
    int m_maxDim;                     //!< Максимальный делитель. Для вычисления id
    int m_columns;                    //!< Количество столбцов
    int m_rows;                       //!< Количество строк

};

}
}
}
#endif // CITEMLABELS_H
