/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
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

//! Диалог. Пул транзакций вещей
class FTransactionPoolThingEdit : public QDialog
{
    Q_OBJECT

public:
    explicit FTransactionPoolThingEdit(int poolType, QWidget *parent = 0);
    FTransactionPoolThingEdit(const hacc::TDBID &id, int poolType, QWidget *parent = 0);
    ~FTransactionPoolThingEdit();
    hacc::TDBID sellerAccountID();
    hacc::TDBID buyerAccountID();
    QDateTime   datetime();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::FTransactionPoolThingEdit *m_ui;
    void init();
    ui::item::base::WBase * constructContainer(const hacc::TDBID &id = 0);
    int m_type;
    ui::item::base::WBase *m_transactions;
};

}
}
#endif // FTRANSACTIONPOOLEDIT_H
