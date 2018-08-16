#ifndef VRN_VOREENTOOLWINDOW_H
#define VRN_VOREENTOOLWINDOW_H

#include <QWidget>
#include <QDockWidget>
//#include "voreen/qt/voreenqtdefine.h"

namespace voreen {

class VoreenToolWindowTitle : public QWidget {
Q_OBJECT
public:
    VoreenToolWindowTitle(QDockWidget* parent, bool dockable=true);
    virtual QSize sizeHint() const;
    virtual QSize minimumSizeHint() const;
protected:
    virtual void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);
private:
    bool dockable_;
    QPixmap closeButton_;
    QPixmap undockButton_;
    QPixmap maximizeButton_;
};

//----------------------------------------------------------------------------------------------------------------

class VoreenToolWindow : public QDockWidget {
Q_OBJECT
public:
    VoreenToolWindow(QAction* action, QWidget* parent, QWidget* child, const QString& name = "", bool dockable=true);
    /// Returns the action associated with this tool.
    QAction* action() const;
    /// Returns the widget that is wrapped by the tool windows.
    QWidget* child() const;

private:
    QAction* action_;
    QWidget* child_;
};

} // namespace

#endif // VRN_VOREENTOOLWINDOW_H