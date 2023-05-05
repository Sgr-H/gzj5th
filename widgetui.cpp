#include "widgetui.h"
#include "ui_widgetui.h"

Widgetui::Widgetui(QWidget *parent)
    : FramelessWidget(parent)
    , ui(new Ui::Widgetui)
{
    ui->setupUi(this);
}

Widgetui::~Widgetui()
{
    delete ui;
}

