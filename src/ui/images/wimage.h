#ifndef WIMAGE_H
#define WIMAGE_H

#include <QLabel>
namespace ui
{
//! Картинки
namespace images
{

class WImage : public QLabel
{
    Q_OBJECT
public:
    explicit WImage(QWidget *parent = 0);
    explicit WImage(int side, QWidget *parent = 0);
    ~WImage();
    void setEmptyText(const QString &text);
    void resize(int side);
    void resize(int w, int h);
    void clear();
    const bool & empty() const;

    void setPixmap(const QPixmap &pm, int extent = 128);
    void setPixmap(const QString &file, int extent = 128);

    QSize sizeHint () const;

private:
    void init();
    bool m_empty;
    QString m_emptyText;
    int m_sideSize;
    QSize m_sizeHint;
};

}
}
#endif // WIMAGE_H
