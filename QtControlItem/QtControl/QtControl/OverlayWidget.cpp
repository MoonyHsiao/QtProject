#include "OverlayWidget.h"

void OverlayWidget::newParent()
{
	if (!parent()) return;
	parent()->installEventFilter(this);
	raise();
}

bool OverlayWidget::eventFilter(QObject * obj, QEvent * ev)
{
	if (obj == parent()) {
		if (ev->type() == QEvent::Resize)
			resize(static_cast<QResizeEvent*>(ev)->size());
		else if (ev->type() == QEvent::ChildAdded)
			raise();
	}
	return QWidget::eventFilter(obj, ev);
}

bool OverlayWidget::event(QEvent * ev)
{
	if (ev->type() == QEvent::ParentAboutToChange) {
		if (parent()) parent()->removeEventFilter(this);
	}
	else if (ev->type() == QEvent::ParentChange) {
		newParent();
	}
	return QWidget::event(ev);
}




void LoadingOverlay::setWarningText(QString data)
{
	warningText = data;
}

void LoadingOverlay::paintEvent(QPaintEvent *)
{
	QPainter p{ this };
	p.fillRect(rect(), { 100, 100, 100, 128 });
	p.setPen({ 200, 200, 255 });
	p.setFont({ "arial,helvetica", 48 });
	p.drawText(rect(), warningText, Qt::AlignHCenter | Qt::AlignTop);
}
