#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTextEdit>
#include <QIcon>
#include <QLabel>
#include <QComboBox>
#include <QFontComboBox>
#include <QStatusBar>
#include <QTimer>
#include <QDateTime>
#include <QPushButton>
#include <QColor>
#include <QTextCharFormat>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(1200, 800);
    set_MenuBar();
    set_ToolBar();
    set_central();
    set_statusBar();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::set_MenuBar(){
    // 创建菜单栏
    m_bar = ui->menuBar;
    // 往菜单栏中添加菜单
    QMenu* m_file = m_bar->addMenu("文件");
    // 往菜单中添加活动项
    m_file->addAction(QIcon(":/res/open.png"), "打开");
    m_file->addAction(QIcon(":/res/new.png"), "新建");
    m_file->addAction(QIcon(":/res/save.png"), "保存");
    m_file->addAction(QIcon(":/res/quit.png"), "退出");

    QMenu* m_edit = m_bar->addMenu("编辑");
    m_edit->addAction(QIcon(":/res/quash.png"), "撤销");
    m_edit->addAction(QIcon(":/res/r_quash.png"), "反撤销");
    m_edit->addAction(QIcon(":/res/copy.png"), "复制");
    m_edit->addAction(QIcon(":/res/shear.png"), "剪切");
    m_edit->addAction(QIcon(":/res/stickup.png"), "粘贴");
}

void MainWindow::set_ToolBar(){

    t_bar = ui->mainToolBar;
    set_font();
    set_fontsize();
    set_fontblod();
    set_fontitalic();
    set_fontcolor();

}

void MainWindow::set_central(){
    // 创建文本框
    textedit = new QTextEdit(this);
    // 将文本框置于MainWindow中间
    this->setCentralWidget(textedit);
}

void MainWindow::set_statusBar(){
    QStatusBar* s_bar = ui->statusBar;
    QLabel* bel = new QLabel("时间", this);
    s_bar->addWidget(bel);
    QTimer* timer = new QTimer(this);
    QObject::connect(timer, &QTimer::timeout, [=](){
        QString str = QDateTime::currentDateTime().toString();
        bel->setText("时间："+str);
    });
    timer->start(1000);
}

void MainWindow::set_font(){
    // 设置bel的父亲是t_bar,防止内存泄漏
    QLabel* bel = new QLabel("字体", t_bar);
    // 让bel在工具栏中显示
    t_bar->addWidget(bel);

    QFontComboBox* fontbox = new QFontComboBox(t_bar);
    t_bar->addWidget(fontbox);

    QObject::connect(fontbox, &QFontComboBox::currentFontChanged, this, [this](const QFont& font){
        this->textedit->setFont(font);
    });
}
// 字体大小
void MainWindow::set_fontsize(){
    QLabel* bel = new QLabel("字号",t_bar);
    t_bar->addWidget(bel);
    QComboBox* comBox = new QComboBox(t_bar);
    t_bar->addWidget(comBox);
    for (int i = 9; i < 19; i++) {
        // 将i转换成字符串
        comBox->addItem(QString::number(i));
    }
    QObject::connect(comBox, &QComboBox::currentTextChanged, this, [this](QString index){
        this->textedit->setFontPointSize(index.toDouble());
    });

}

// 字体加粗
void MainWindow::set_fontblod(){
    QPushButton* btn = new QPushButton(QIcon(), "加粗", t_bar);
    t_bar->addWidget(btn);
    QObject::connect(btn, &QPushButton::clicked, this, [this](){
        this->textedit->setFontWeight(textedit->fontWeight() == QFont::Normal ? QFont::Bold : QFont::Normal);
    });
}
// 斜体
void MainWindow::set_fontitalic(){
    QPushButton* btn = new QPushButton(QIcon(), "斜体", t_bar);
    t_bar->addWidget(btn);
    QObject::connect(btn, &QPushButton::clicked, this, [this](){
        this->textedit->setFontItalic(textedit->fontItalic() == true ? false : true);
    });
}

void MainWindow::set_fontcolor(){
    QPushButton* bnt = new QPushButton(QIcon(), "颜色", this);
    t_bar->addWidget(bnt);
    QObject::connect(bnt, &QPushButton::clicked, this, [this](){
        QColor color = QColorDialog::getColor();
        QTextCharFormat format;
        format.setForeground(QBrush(color));
        textedit->mergeCurrentCharFormat(format);
    });
}
