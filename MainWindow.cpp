#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "TabWidget.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	ui->frame->bindTabWidget(ui->widget);

	ui->widget->addItem("Tab 1");
	ui->widget->addItem("Tab 2");
	ui->widget->addItem("Tab 3");
	ui->widget->addItem("Tab 4");

	connect(ui->widget, &TabWidget::selected, [&](int s){
		ui->frame->update();
	});
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
//	ui->widget->setOrientation(width() > height() ? Qt::Horizontal : Qt::Vertical);
}
