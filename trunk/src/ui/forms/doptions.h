#ifndef DOPTIONS_H
#define DOPTIONS_H

#include <QDialog>
#include "hacc_types.h"

namespace Ui { class DOptions; }

namespace ui
{
namespace form
{

class DOptions : public QDialog
{
    Q_OBJECT

public:
    explicit DOptions(QWidget *parent = 0);
    ~DOptions();

protected:
    void changeEvent(QEvent *e);

private slots:
    void defaultCurrencySet(const hacc::TDBID &currencyID);

private:
    Ui::DOptions *m_ui;
};

}
}
#endif // DOPTIONS_H
