#include "TabWidget.h"
#include <QDebug>
#include <QMouseEvent>
#include <QPainter>

TabWidget::TabWidget(QWidget *parent)
	: QWidget(parent)
{
}

Qt::Orientation TabWidget::orientation() const
{
	return orientation_;
}

void TabWidget::setOrientation(Qt::Orientation o)
{
	if (o != orientation_) {
		orientation_ = o;
		update();
	}
}

void TabWidget::clear()
{
	items_.clear();
}

void TabWidget::addItem(const QString &text, const QVariant &data)
{
	Item item;
	item.text = text;
	item.data = data;
	items_.push_back(item);
	update();
}

int TabWidget::count() const
{
	return items_.size();
}

void TabWidget::paintEvent(QPaintEvent *)
{
	const int n = count();
	bounds_.clear();
	QPainter pr(this);
	int w = width();
	int h = height();
	const Qt::Orientation o = orientation();
	if (o == Qt::Horizontal) {
		int z = (w - 1) / n;
		int x = 0;
		for (int i = 0; i < n; i++) {
			bounds_.push_back(QRect(x, 0, z, height()));
			int y = (i == selected_) ? 0 : 1;
			pr.save();
			{
				QTransform t;
				t.translate(0, y);
				pr.setTransform(t);
			}
			pr.fillRect(x + 1, 1, z - 2, h, (i == selected_) ? QColor(255, 255, 255) : QColor(240, 240, 240));
			pr.fillRect(x, 2, 1, h, QColor(128, 128, 128));
			pr.fillRect(x + 1, 2, 1, h, QColor(255, 255, 255));
			pr.fillRect(x + 1, 1, 1, 1, QColor(128, 128, 128));
			pr.fillRect(x + 2, 0, z - 3, 1, QColor(128, 128, 128));
			pr.fillRect(x + 2, 1, z - 3, 1, QColor(255, 255, 255));
			pr.fillRect(x + z - 1, 1, 1, 1, QColor(128, 128, 128));
			pr.fillRect(x + z - 0, 2, 1, h, QColor(128, 128, 128));
			pr.fillRect(x + z - 1, 2, 1, h, QColor(192, 192, 192));
			QString s = text(i);
			pr.drawText(x + (z - pr.fontMetrics().size(0, s).width()) / 2, pr.fontMetrics().height() + 2, s);
			pr.restore();
			x += z;
		}
	}
	if (o == Qt::Vertical) {
		int z = (h - 1) / n;
		int y = 0;
		for (int i = 0; i < n; i++) {
			bounds_.push_back(QRect(0, y, width(), z));
			int x = (i == selected_) ? 0 : 1;
			pr.save();
			{
				QTransform t;
				t.translate(x, 0);
				pr.setTransform(t);
			}
			pr.fillRect(1, y + 1, w, z - 2, (i == selected_) ? QColor(255, 255, 255) : QColor(240, 240, 240));
			pr.fillRect(2, y, w, 1, QColor(128, 128, 128));
			pr.fillRect(2, y + 1, w, 1, QColor(255, 255, 255));
			pr.fillRect(1, y + 1, 1, 1, QColor(128, 128, 128));
			pr.fillRect(0, y + 2, 1, z - 3, QColor(128, 128, 128));
			pr.fillRect(1, y + 2, 1, z - 3, QColor(255, 255, 255));
			pr.fillRect(1, y + z - 1, 1, 1, QColor(128, 128, 128));
			pr.fillRect(2, y + z - 0, w, 1, QColor(128, 128, 128));
			pr.fillRect(2, y + z - 1, w, 1, QColor(192, 192, 192));
			{
				QTransform t;
				int tx = pr.fontMetrics().height() + 2;
				int ty = y + z;
				t.translate(x + tx, ty);
				t.rotate(-90);
				pr.setTransform(t);
			}
			QString s = text(i);
			pr.drawText((z - pr.fontMetrics().size(0, s).width()) / 2, 0, s);
			pr.restore();
			y += z;
		}
	}
}

void TabWidget::select(int sel)
{
	selected_ = sel;
	update();
	emit selected(selected_);
}

int TabWidget::selectedIndex() const
{
	return selected_;
}

QString TabWidget::text(int index) const
{
	QString a;
	if (index >= 0 && index < count()) {
		a = items_[index].text;
	}
	return a;
}

QVariant TabWidget::data(int index) const
{
	QVariant a;
	if (index >= 0 && index < count()) {
		a = items_[index].data;
	}
	return a;
}

QRect TabWidget::bounds(int index) const
{
	QRect a;
	if (index >= 0 && index < count()) {
		a = bounds_[index];
	}
	return a;
}

void TabWidget::mousePressEvent(QMouseEvent *event)
{
	QPoint pt = event->pos();
	for (int i = 0; i < bounds_.size(); i++) {
		QRect const &r = bounds_[i];
		if (pt.x() >= r.x() && pt.y() >= r.y() && pt.x() < r.x() + r.width() && pt.y() < r.y() + r.height()) {
			select(i);
			return;
		}
	}
}
