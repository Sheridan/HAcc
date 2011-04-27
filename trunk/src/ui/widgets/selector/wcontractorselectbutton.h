/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef WCONTRACTORSELECTBUTTON_H
#define WCONTRACTORSELECTBUTTON_H

#include "wselectorbutton.h"
#include <QHBoxLayout>
#include "wicon.h"
#include "ccontractors.h"
#include <QLabel>

namespace ui
{
namespace selector
{

class WContractorSelectButton : public base::WSelectorButton
{
    Q_OBJECT
public:
    WContractorSelectButton(QWidget *parent = 0);
    ~WContractorSelectButton();
    void setSelfFilter(hacc::model::EContractorFilter filter);

private:
    void idChanged();
    base::WSelectorPopup * constructPopup();
    void setContractorData(const hacc::TDBID &iconID, const QString &name);
    QHBoxLayout      *m_layout;
    QLabel           *m_contractorName;
    ui::icons::WIcon *m_contractorIcon;
    hacc::model::EContractorFilter m_filter;

private slots:
    void contractorCreated(const hacc::TDBID &contractorID);
};

}
}
#endif // WCONTRACTORSELECTBUTTON_H
