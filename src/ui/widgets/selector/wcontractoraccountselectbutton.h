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

private:
    void idChanged();
    base::WSelectorPopup * constructPopup();
    void setData(const hacc::TDBID &contractor_icon, const QString &contractor_name,
                 const hacc::TDBID &account_icon   , const QString &account_name   );
    QHBoxLayout *m_layout;
    QLabel      *m_contractorName;
    QLabel      *m_accountName;
    ui::icons::WIcon *m_contractorIcon;
    ui::icons::WIcon *m_accountIcon;
    hacc::model::EContractorFilter m_filter;

private slots:
    void contractorCreated(const hacc::TDBID &contractorID);
};

}
}
#endif // WCONTRACTORACCOUNTSELECTBUTTON_H