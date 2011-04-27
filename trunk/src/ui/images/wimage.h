/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef WIMAGE_H
#define WIMAGE_H

#include <QLabel>
namespace ui
{
//! Картинки
namespace images
{
//! Метка - изображение
/**
  В Qt отсутствуют классы виджета изображения, в который можно было бы передать картинку для отрисовке на форме.
  Но стандартный QLabel это умеет делать, хотя у него нет несколько нужных методов и возможностей
  Данный класс - создание нужного контрола.
  */
class WImage : public QLabel
{
    Q_OBJECT
public:
    WImage(QWidget *parent = 0);
    WImage(int side, QWidget *parent = 0);
    ~WImage();
    void setEmptyText(const QString &text); //!< Установка текста по умолчанию
    void resize(int side);                  //!< Изменение размера, квадратный виджет
    void resize(int w, int h);              //!< Изменение размера, прямоугольный виджет
    void clear();                           //!< Очистка изображение, установка текста
    const bool & empty() const;             //!< Нет ли изображение на контроле?

    void setPixmap(const QPixmap &pm, int extent = 128);   //!< Установка изображения-пиксмапа
    void setPixmap(const QString &file, int extent = 128); //!< Загрузка изображения из файла (ресурса)

    QSize sizeHint () const;

private:
    void init();
    bool    m_empty;     //!< Нет ли изображение на контроле?
    QString m_emptyText; //!< Текст, когда нет изображения
    int     m_sideSize;  //!< Размер стороны
    QSize   m_sizeHint;  //!< Размер контрола
};

}
}
#endif // WIMAGE_H
