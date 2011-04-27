/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef WCURRENCYELECTBUTTON_H
#define WCURRENCYELECTBUTTON_H

#include "wselectorbutton.h"
#include <QHBoxLayout>
#include "wicon.h"
#include "ccurrency.h"
#include <QLabel>

namespace ui
{
namespace selector
{

class WCurrencyelectButton : public base::WSelectorButton
{
    Q_OBJECT
public:
    WCurrencyelectButton(QWidget *parent = 0);
    ~WCurrencyelectButton();

private:
    void idChanged();
    base::WSelectorPopup * constructPopup();
    void setCurrencyData(const hacc::TDBID &iconID, const QString &name, const QString &reduction);
    QHBoxLayout      *m_layout;
    QLabel           *m_currencyName;
    ui::icons::WIcon *m_currencyIcon;

private slots:
    void currencyCreated(const hacc::TDBID &currencyID);
};

}
}

#endif // WCURRENCYELECTBUTTON_H
