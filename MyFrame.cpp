#include "MyFrame.h"

#include <QPainter>

MyFrame::MyFrame(QWidget *parent)
	: QFrame(parent)
{
	setFrameShape(QFrame::NoFrame);

//	colors_.color255 = palette().color(QPalette::Base);
//	colors_.color240 = colors_.color255.lighter(90);
//	colors_.color192 = colors_.color255.lighter(75);
//	colors_.color128 = colors_.color255.lighter(50);
}

void MyFrame::bindTabWidget(TabWidget *tabwidget)
{
	tabwidget_ = tabwidget;
}

void MyFrame::paintEvent(QPaintEvent *)
{
	if (!tabwidget_) return;

	TabWidget::Colors colors = tabwidget_->colors();
	int w = width();
	int h = height();
	QPainter pr(this);

	pr.fillRect(rect(), colors.color255);

	QRect r = tabwidget_->selectedBounds();
	if (!r.isEmpty()) {
		QPoint pt0(r.x(), r.y());
		QPoint pt1 = pt0 + QPoint(r.width(), r.height());
		pt0 = tabwidget_->mapToGlobal(pt0);
		pt1 = tabwidget_->mapToGlobal(pt1);
		pt0 = mapFromGlobal(pt0);
		pt1 = mapFromGlobal(pt1);
		r = QRect(pt0.x(), pt0.y(), pt1.x() - pt0.x(), pt1.y() - pt0.y());
		if (tabwidget_->orientation() == Qt::Horizontal) {
			r = r.adjusted(1, 0, -1, 2);
		} else {
			r = r.adjusted(0, 1, 2, -1);
		}
		QPainterPath path1;
		QPainterPath path2;
		path1.addRect(rect());
		path2.addRect(r);
		path1 = path1.subtracted(path2);
		pr.setClipPath(path1);
	}

	pr.fillRect(0, 0, w, 1, colors.color128);
	pr.fillRect(0, 0, 1, h, colors.color128);
	pr.fillRect(w - 2, 0, 1, h, colors.color192);
	pr.fillRect(0, h - 2, w, 1, colors.color192);
	pr.fillRect(w - 1, 0, 1, h, colors.color128);
	pr.fillRect(0, h - 1, w, 1, colors.color128);

}
