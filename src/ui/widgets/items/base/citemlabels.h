#ifndef CITEMLABELS_H
#define CITEMLABELS_H

#include <QWidget>
#include <QMap>
#include "witemlabel.h"
#include <QGridLayout>

namespace ui
{
namespace item
{
namespace base
{

class CItemLabels
{
public:
    CItemLabels();
    virtual ~CItemLabels();
    void initialize(const int &columns, const int &rows, QWidget *parent, QGridLayout *layout);
    void setText   (const int &column , const int &row , const QString     &text);
    void setIcon   (const int &column , const int &row , const QIcon       &icon);
    void setIcon   (const int &column , const int &row , const QString     &file);
    void setIcon   (const int &column , const int &row , const hacc::TDBID &id  );
    ui::widget::WControlLabel *controlLabel(const int &column, const int &row);
    void setPropertyToAll(const char *name, const QVariant &property);
    void setStyleSrcToAll(const QString &style);
    void setLabels(const QStringList& strings);
    int labelsHeight();
    void fixHeight();

private:
    QMap<int, WItemLabel *> m_labels;
    QWidget     *m_parent;
    QGridLayout *m_layout;
    int m_maxDim;
    int m_columns;
    int m_rows;

};

}
}
}
#endif // CITEMLABELS_H
