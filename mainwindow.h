#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void set_central();
    void set_MenuBar();
    void set_ToolBar();
    void set_statusBar();
    void set_font();
    void set_fontsize();
    void set_fontblod();
    void set_fontitalic();
    void set_fontcolor();

private:
    Ui::MainWindow *ui;
    QTextEdit* textedit;
    QMenuBar* m_bar;
    QToolBar* t_bar;
};
#endif // MAINWINDOW_H
