#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include <QVector>
#include <QStandardItemModel>
#include <QDebug>

#include "note.h"
#include "note_edit_dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void addNoteToList(Note* note, QStandardItemModel *model);

    void readNotesFromFile(QString dataFileName, QString textFolderName, QStandardItemModel *model);
    void readNotesWithCategory(QString category, QStandardItemModel *model);

    void writeNotesDataToFile(QString fileName, QVector<Note*>& list);
    void writeNotesTextToFiles(QString folderName, QVector<Note*>& list);

    int getNotePositionInFile(int left, int right, Note& note, QVector<Note*>& list);

private slots:

    void on_add_note_clicked();

    void on_listView_clicked(const QModelIndex &index);

    void on_open_btn_clicked();
    void on_delete_btn_clicked();

    void on_main_list_btn_clicked();
    void on_archive_list_btn_clicked();

    void on_archive_btn_clicked();

    void on_personal_checkBox_stateChanged(int arg1);
    void on_work_checkBox_stateChanged(int arg1);
    void on_studying_checkBox_stateChanged(int arg1);
    void on_graphicsView_windowIconChanged(const QIcon &icon);

    void on_catPic_linkActivated(const QString &link);

private:
    Ui::MainWindow *ui;

    QVector<Note*> main_notes;
    QVector<Note*> archived_notes;
    QStandardItemModel *main_model;
    QStandardItemModel *archive_model;

    NoteEditDialog noteWindow;

    void removeAllNotesWithUncheckedCategories(QVector<Note*> list);
};
#endif // MAINWINDOW_H
