#ifndef DPROGRESS_H
#define DPROGRESS_H

#include <QDialog>
#include "hacc_types.h"

namespace Ui { class DProgress; }
namespace ui
{
namespace form
{

class DProgress : public QDialog
{
    Q_OBJECT

public:
    explicit DProgress();
    ~DProgress();
    void show(const QString & caption, const int & maximumSteps);
    void step();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::DProgress *m_ui;
};

}
}
#endif // DPROGRESS_H
