#ifndef UI_DEFINES_H
#define UI_DEFINES_H

#define HACC_STD_TRANSLATE_UI(_class,_base) \
void _class::changeEvent(QEvent *e) \
{ \
    _base::changeEvent(e); \
    switch (e->type())  \
    { case QEvent::LanguageChange: m_ui->retranslateUi(this); break; \
    default: break; } \
}

#endif // UI_DEFINES_H
