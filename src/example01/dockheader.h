#pragma once

#include <QWidget>

class QDockWidget;

class DockHeader : public QWidget
{
    Q_OBJECT

public:
    DockHeader(QDockWidget* dockWidget);
    ~DockHeader();

    void UpdateIcons();

protected slots:
    void OnDockButton();
    void OnCloseButton();
    void OnMaximizeButton();
    void OnPinButton();
    void OnTopLevelChanged(bool isFloating);
    void focusInEvent(QFocusEvent* event) override;
    void focusOutEvent(QFocusEvent* event) override;

private:
    QDockWidget*    mDockWidget;
    QPushButton*    mMaximizeButton;
    QPushButton*    mPinButton;
    QPushButton*    mCloseButton;
    QPushButton*    mDockButton;

    void MakeHeaderButton(QPushButton* button, const char* iconFileName, const char* toolTipText);
    void mouseDoubleClickEvent(QMouseEvent* event) override;
};
