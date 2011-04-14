#ifndef FTRANSACTIONGIFTEDIT_H
#define FTRANSACTIONGIFTEDIT_H

#include <QDialog>
#include <QDateTime>
#include "hacc_types.h"

namespace Ui { class FTransactionGiftEdit; }
namespace ui
{
namespace form
{

class FTransactionGiftEdit : public QDialog
{
    Q_OBJECT

public:
    FTransactionGiftEdit(const int &gType, QWidget *parent = 0);
    FTransactionGiftEdit(const hacc::TDBID & id, const int &gType, QWidget *parent = 0);
    ~FTransactionGiftEdit();
    hacc::TDBID source();
    hacc::TDBID destination();
    hacc::TDBID thing();
    hacc::TDBID valuable();
    QDateTime   datetime();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::FTransactionGiftEdit *m_ui;
    void init(const int &gType);
};

}
}
#endif // FTRANSACTIONGIFTEDIT_H
