#ifndef FTRANSACTIONMONEYEDIT_H
#define FTRANSACTIONMONEYEDIT_H

#include <QDialog>
#include <QDateTime>
#include <QSqlQuery>
#include "hacc_types.h"

namespace Ui { class FTransactionMoneyEdit; }
namespace ui
{
namespace form
{

class FTransactionMoneyEdit : public QDialog
{
    Q_OBJECT
public:
    explicit FTransactionMoneyEdit(const int &trType, QWidget *parent = 0);
    explicit FTransactionMoneyEdit(const hacc::TDBID &id, const int &trType, QWidget *parent = 0);
    ~FTransactionMoneyEdit();
    hacc::TDBID source();
    hacc::TDBID destination();
    hacc::TMoney money();
    QDateTime datetime();

    hacc::TMoney commission();
    bool hasCommission();
    bool commissionInPercents();
    bool commissionAlreadyInMoney();
    hacc::TDBID commissionTo();

    // 4 edit
    hacc::TDBID basePoolID();
    hacc::TDBID commissionPoolID();
    hacc::TDBID baseTransactionID();
    hacc::TDBID commissionTransactionID();
    int transactionPoolType();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::FTransactionMoneyEdit *m_ui;
    void init(const int &trType);
    hacc::TDBID m_basePoolID;
    hacc::TDBID m_commissionPoolID;
    hacc::TDBID m_baseTransactionID;
    hacc::TDBID m_commissionTransactionID;
    int m_transactionPoolType;
};

}
}
#endif // FTRANSACTIONMONEYEDIT_H
