#ifndef FCONTRACTOREDIT_H
#define FCONTRACTOREDIT_H

#include <QDialog>
#include "hacc_types.h"
#include "wexpandedaccountbase.h"

namespace Ui { class FContractorEdit; }
namespace ui
{
namespace form
{

class FContractorEdit : public QDialog
{
    Q_OBJECT
public:
    FContractorEdit(const bool &isSelf, QWidget *parent = 0);
    FContractorEdit(const hacc::TDBID & id, QWidget *parent = 0);
    ~FContractorEdit();
    QString name();
    hacc::TDBID iconId();
    bool ownAccount();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::FContractorEdit *m_ui;
    ui::item::expanded::WExpandedAccountBase *m_accounts;
    void init();
};

}
}
#endif // FCONTRACTOREDIT_H
