#ifndef WCONTRACTORACCOUNTSELECTBUTTON_H
#define WCONTRACTORACCOUNTSELECTBUTTON_H

#include "wselectorbutton.h"
#include <QLabel>
#include <QHBoxLayout>
#include "ccontractors.h"
#include "wicon.h"
#include "ui_defines.h"

namespace ui
{
namespace selector
{

class WContractorAccountSelectButton : public base::WSelectorButton
{
    Q_OBJECT
public:
    explicit WContractorAccountSelectButton(QWidget *parent = 0);
    virtual ~WContractorAccountSelectButton();
    void setSelfFilter(hacc::model::EContractorFilter filter);

public slots:
    void setCurrencyFilter(const hacc::TDBID &currencyID);

private:
    void idChanged();
    base::WSelectorPopup * constructPopup();
    void setData(const hacc::TDBID &contractorIconID, const QString &contractorName,
                 const hacc::TDBID &accountIconID   , const QString &accountName   ,
                 const hacc::TDBID &currencyIconID  , const QString &currencyName);
    QHBoxLayout *m_layout;
    QLabel      *m_contractorName;
    QLabel      *m_accountName;
    QLabel      *m_currencyName;
    ui::icons::WIcon *m_contractorIcon;
    ui::icons::WIcon *m_accountIcon;
    ui::icons::WIcon *m_currencytIcon;
    hacc::model::EContractorFilter m_filter;
    hacc::TDBID m_currencyID;
    base::WSelectorPopup * m_popup;

private slots:
    void contractorCreated(const hacc::TDBID &contractorID);

signals:
    void currencyIDChanged(const hacc::TDBID & /*currencyID*/);
};

}
}
#endif // WCONTRACTORACCOUNTSELECTBUTTON_H
