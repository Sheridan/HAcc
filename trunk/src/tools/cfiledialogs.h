#ifndef CFILEDIALOGS_H
#define CFILEDIALOGS_H
#include <QFileDialog>

namespace tools
{
//! Базовые диалоги
namespace dialog
{

//! Результат диалога
struct SFileDialogResult
{
    QStringList fileNames; //!< Имена выбранных файлов
    bool        dialogOk;  //!< Диалог был завершен по Accept  а не иначе
    SFileDialogResult()
    {
        fileNames = QStringList();
        dialogOk  = false;
    }
};

//! Базовые диалоги
class CFileDialogs
{
public:
    static SFileDialogResult getOpenFileName  (const QString &title, const QString &extentions);                            //!< Открыть один файл
    static SFileDialogResult getOpenFilesNames(const QString &title, const QString &extentions);                            //!< Открыть несколько файлов
    static SFileDialogResult getNewFileName   (const QString &title, const QString &extentions, const QString &defaultExt); //!< Создать файл

    static SFileDialogResult getOpenImage(const QString &title);                                                            //!< Открыть файлы картинок

private:
    static QFileDialog     * fileDialog       (const QString &title                      , const QString &extentions);      //!< База для диалога
    static SFileDialogResult execFileDialog   (QFileDialog *dlg    , const QString &title, const QString &extentions);      //!< Запуск диалога
};

}
}
#endif // CFILEDIALOGS_H
