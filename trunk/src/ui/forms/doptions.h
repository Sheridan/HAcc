#ifndef DOPTIONS_H
#define DOPTIONS_H

#include <QDialog>

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
    void on_buttonBox_accepted();

private:
    Ui::DOptions *m_ui;
};

}
}
#endif // DOPTIONS_H
