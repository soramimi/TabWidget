#ifndef MYFRAME_H
#define MYFRAME_H

#include <QFrame>
#include "TabWidget.h"

class MyFrame : public QFrame {
private:
	TabWidget *tabwidget_ = nullptr;
//	TabWidget::Colors colors_;
public:
	MyFrame(QWidget *parent);
	void bindTabWidget(TabWidget *tabwidget);
protected:
	void paintEvent(QPaintEvent *);
};

#endif // MYFRAME_H
