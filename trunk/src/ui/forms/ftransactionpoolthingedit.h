#ifndef FTRANSACTIONPOOLEDIT_H
#define FTRANSACTIONPOOLEDIT_H

#include <QDialog>
#include <QDateTime>
#include "hacc_types.h"
#include "wbase.h"

namespace Ui { class FTransactionPoolThingEdit; }
namespace ui
{
namespace form
{

class FTransactionPoolThingEdit : public QDialog
{
    Q_OBJECT

public:
    explicit FTransactionPoolThingEdit(int poolType, QWidget *parent = 0);
    FTransactionPoolThingEdit(const hacc::TDBID &id, int poolType, QWidget *parent = 0);
    ~FTransactionPoolThingEdit();
    hacc::TDBID seller();// account id
    hacc::TDBID buyer(); // account id
    QDateTime   datetime();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::FTransactionPoolThingEdit *ui;
    void init();
    ui::item::base::WBase * constructContainer(const hacc::TDBID &id = 0);
    int m_type;
    ui::item::base::WBase *m_transactions;
};

}
}
#endif // FTRANSACTIONPOOLEDIT_H
