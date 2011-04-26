#include "actions.h"

namespace tools
{
namespace actions
{
/**
  Создает непривязанную к действию QAction
  @param icon    Иконка
  @param caption Заголовок
  @param toolTip Всплывающая подсказка
  @return Указатель на QAction, непривязанная к действию
  */
QAction * constructAction(const QIcon & icon, const QString &caption, const QString &toolTip)
{
    QAction *a = new QAction(icon, caption, NULL);
    a->setToolTip(toolTip);
    return a;
}

/**
  Создает привязанную к действию QAction
  @param icon     Иконка
  @param caption  Заголовок
  @param toolTip  Всплывающая подсказка
  @param receiver Объект-получатель сигнала triggered() от созданной QAction
  @param method   Вызываемый метод объекта-получателя сигнала triggered() от созданной QAction
  @return Указатель на QAction, привязанная к действию
  */
QAction * constructAction(const QIcon & icon, const QString &caption, const QString &toolTip,
                          const QObject * receiver, const char * method)
{
    QAction *a = constructAction(icon, caption, toolTip);
    QObject::connect(a, SIGNAL(triggered()), receiver, method);
    return a;
}

}
}
