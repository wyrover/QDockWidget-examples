#include "precompiled_all.h"
#include "dockheader.h"
#include <QDockWidget>


DockHeader::DockHeader(QDockWidget* dockWidget) : QWidget()
    
{
    setObjectName("DockHeader");

    mDockWidget = dockWidget;

    QHBoxLayout* mainLayout = new QHBoxLayout();
    QWidget* innerWidget = new QWidget();
    innerWidget->setObjectName("DockHeader");
    mainLayout->addWidget(innerWidget);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->setSizeConstraint(QLayout::SetNoConstraint);
    setLayout(mainLayout);

    QHBoxLayout* layout = new QHBoxLayout();
    layout->setMargin(2);
    layout->setSpacing(0);
    layout->setSizeConstraint(QLayout::SetNoConstraint);
    innerWidget->setLayout(layout);

    QPixmap handleImage("Images/DockHandle.png");
    QLabel* handle = new QLabel();
    handle->setPixmap(handleImage);
    handle->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    handle->setObjectName("DockHeaderTitle");
    layout->addWidget(handle);

    QLabel* label = new QLabel();
    label->setObjectName("DockHeaderTitle");
    label->setText(mDockWidget->windowTitle());
    label->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    layout->addWidget(label);

    QSpacerItem* spacer = new QSpacerItem(1, 1, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    layout->addSpacerItem(spacer);

    mDockButton = new QPushButton();
    MakeHeaderButton(mDockButton, "/Images/Icons/DockUndock.png", "Dock or undock this window");
    connect(mDockButton, SIGNAL(clicked()), this, SLOT(OnDockButton()));
    layout->addWidget(mDockButton);

    mMaximizeButton = new QPushButton();
    MakeHeaderButton(mMaximizeButton, "/Images/Icons/DockMaximize.png", "Maximize the window");
    connect(mMaximizeButton, SIGNAL(clicked()), this, SLOT(OnMaximizeButton()));
    layout->addWidget(mMaximizeButton);
    if (mDockWidget->isFloating() == false) {
        mMaximizeButton->setHidden(true);
    }

    mPinButton = new QPushButton();
    MakeHeaderButton(mPinButton, "/Images/Icons/DockPin.png", "Enables or disables docking of the window");
    connect(mPinButton, SIGNAL(clicked()), this, SLOT(OnPinButton()));
    layout->addWidget(mPinButton);
    if (mDockWidget->isFloating() == false) {
        mPinButton->setHidden(true);
    }

    mCloseButton = new QPushButton();
    MakeHeaderButton(mCloseButton, "/Images/Icons/DockClose.png", "Close this dock window");
    connect(mCloseButton, SIGNAL(clicked()), this, SLOT(OnCloseButton()));
    layout->addWidget(mCloseButton);

    connect(mDockWidget, SIGNAL(topLevelChanged(bool)), this, SLOT(OnTopLevelChanged(bool)));

    UpdateIcons();

    // setup to get focus when we click or use the mouse wheel
    setFocusPolicy((Qt::FocusPolicy)(Qt::ClickFocus));
}

DockHeader::~DockHeader()
{
}

void DockHeader::UpdateIcons()
{
    mMaximizeButton->setHidden(!mDockWidget->isFloating());
    mPinButton->setHidden(!mDockWidget->isFloating());
    mCloseButton->setHidden((mDockWidget->features() & QDockWidget::DockWidgetClosable) == false);

    if (mDockWidget->allowedAreas() == Qt::NoDockWidgetArea) {
        mPinButton->setIcon(QIcon("Images/Icons/DockPinned.png"));
        mPinButton->setToolTip("The window is currently pinned, so you can move it freely over the interface, without it being inserted into it");
    }
    else {
        mPinButton->setToolTip("The window is currently unpinned, so moving it over the interface will allow you to dock it at a given location");
        mPinButton->setIcon(QIcon("Images/Icons/DockPin.png"));
    }

    if (mDockWidget->windowState() & Qt::WindowMaximized) {
        mMaximizeButton->setIcon(QIcon("Images/Icons/DockRestore.png"));
        mMaximizeButton->setToolTip("Restore the window to a non-maximized state");
    }
    else {
        mMaximizeButton->setIcon(QIcon("Images/Icons/DockMaximize.png"));
        mMaximizeButton->setToolTip("Maximize");
    }

    if (mDockWidget->isFloating()) {
        mDockButton->setIcon(QIcon("Images/Icons/DockDock.png"));
        mDockButton->setToolTip("Dock the window, putting it back into the interface");
    }
    else {
        mDockButton->setIcon(QIcon("Images/Icons/DockUndock.png"));
        mDockButton->setToolTip("Undock the window, making it a floating window");
    }
}

void DockHeader::OnDockButton()
{
    mDockWidget->setFloating(!mDockWidget->isFloating());
    UpdateIcons();
}

void DockHeader::OnCloseButton()
{
    mDockWidget->close();
}

void DockHeader::OnMaximizeButton()
{
    if (mDockWidget->windowState() & Qt::WindowMaximized) {
        mDockWidget->setWindowState(Qt::WindowNoState);
    }
    else {
        mDockWidget->setWindowState(Qt::WindowMaximized);
    }

    UpdateIcons();
}

void DockHeader::OnPinButton()
{
    if (mDockWidget->allowedAreas() != Qt::NoDockWidgetArea) {
        mDockWidget->setAllowedAreas(Qt::NoDockWidgetArea);
    }
    else {
        mDockWidget->setAllowedAreas(Qt::AllDockWidgetAreas);
    }

    UpdateIcons();
}

void DockHeader::OnTopLevelChanged(bool isFloating)
{
    if (isFloating) {
        mDockWidget->setAllowedAreas(Qt::NoDockWidgetArea);
        mDockWidget->raise();
        mDockWidget->setFocus();
        //mDockWidget->grabKeyboard();

        // setWindowFlags calls setParent() when changing the flags for a window, causing the widget to be hidden.
        // you must call show() to make the widget visible again
        //mDockWidget->setWindowFlags(Qt::Window);
        //mDockWidget->show();
    }
    else {
        mDockWidget->setAllowedAreas(Qt::AllDockWidgetAreas);
        mDockWidget->raise();
        mDockWidget->setFocus();
        //mDockWidget->grabKeyboard();
    }

    UpdateIcons();
}

void DockHeader::focusInEvent(QFocusEvent* event)
{
    Q_UNUSED(event);
    grabKeyboard();
    update();
}

void DockHeader::focusOutEvent(QFocusEvent* event)
{
    Q_UNUSED(event);
    releaseKeyboard();
    update();
}

void DockHeader::MakeHeaderButton(QPushButton* button, const char* iconFileName, const char* toolTipText)
{
    button->setObjectName("DockHeaderIcon");
    button->setToolTip(toolTipText);
    button->setIcon(QIcon(iconFileName));
}

void DockHeader::mouseDoubleClickEvent(QMouseEvent* event)
{
    Q_UNUSED(event);
    if (mDockWidget->isFloating()) {
        OnMaximizeButton();
    }
    else {
        OnDockButton();
    }
}
