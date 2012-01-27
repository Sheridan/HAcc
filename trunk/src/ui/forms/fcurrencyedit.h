/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef FCURRENCYEDIT_H
#define FCURRENCYEDIT_H

#include <QDialog>
#include "hacc_types.h"

namespace Ui { class FCurrencyEdit; }
namespace ui
{
namespace form
{

//! Диалог. Редактирование валюты
class FCurrencyEdit : public QDialog
{
    Q_OBJECT

public:
    FCurrencyEdit(QWidget *parent = 0);
    FCurrencyEdit(const hacc::TDBID &currencyID, QWidget *parent = 0);
    ~FCurrencyEdit();
    QString name();
    QString reduction();
    hacc::TDBID iconID();
    bool reductionBeforeNumber();

protected:
    void changeEvent(QEvent *e);

private:
    void init();
    Ui::FCurrencyEdit *m_ui;
};

}
}
#endif // FCURRENCYEDIT_H
