#ifndef FTRANSACTIONSELLTHINGEDIT_H
#define FTRANSACTIONSELLTHINGEDIT_H

#include <QDialog>
#include "hacc_types.h"

namespace Ui { class FTransactionSellThingEdit; }

namespace ui
{
namespace form
{

class FTransactionSellThingEdit : public QDialog
{
    Q_OBJECT

public:
    FTransactionSellThingEdit(QWidget *parent = 0);
    FTransactionSellThingEdit(const hacc::TDBID &valuableID, QWidget *parent = 0);
    ~FTransactionSellThingEdit();
    hacc::TDBID valuable();
    hacc::TMoney money();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::FTransactionSellThingEdit *ui;
    void init();
};

}
}
#endif // FTRANSACTIONSELLTHINGEDIT_H
