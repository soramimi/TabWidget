#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QVariant>
#include <QWidget>

class TabWidget : public QWidget {
	Q_OBJECT
private:
	struct Item {
		QString text;
		QVariant data;
	};
	QList<Item> items_;
	QList<QRect> bounds_;
	int selected_ = 0;
	Qt::Orientation orientation_ = Qt::Horizontal;
protected:
	void paintEvent(QPaintEvent *) override;
	void mousePressEvent(QMouseEvent *event);
public:
	explicit TabWidget(QWidget *parent = nullptr);
	Qt::Orientation orientation() const;
	void setOrientation(Qt::Orientation o);

	void clear();
	void addItem(const QString &text, const QVariant &data = QVariant());
	int count() const;

	void select(int sel);
	int selectedIndex() const;
	QString text(int index) const;
	QVariant data(int index) const;
	QRect bounds(int index) const;
signals:
	void selected(int index);
};

#endif // TABWIDGET_H
