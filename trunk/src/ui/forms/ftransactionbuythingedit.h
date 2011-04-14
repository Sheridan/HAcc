#ifndef FTRANSACTIONTHINGEDIT_H
#define FTRANSACTIONTHINGEDIT_H

#include <QDialog>
#include "hacc_types.h"

namespace Ui { class FTransactionBuyThingEdit; }
namespace ui
{
namespace form
{

class FTransactionBuyThingEdit : public QDialog
{
    Q_OBJECT

public:
    FTransactionBuyThingEdit(QWidget *parent = 0);
    FTransactionBuyThingEdit(const hacc::TDBID &id, QWidget *parent = 0);
    ~FTransactionBuyThingEdit();
    hacc::TDBID thing();
    hacc::TMoney money();
    hacc::TAmount amount();

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_tbClearMoney_clicked();
    void on_tbClearAmount_clicked();
    void validateData();

private:
    Ui::FTransactionBuyThingEdit *ui;
    void init();
    int m_minimumAmount;
};

}
}
#endif // FTRANSACTIONTHINGEDIT_H