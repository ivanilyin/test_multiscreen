#include "GraphicsSimpleBrowser.h"

#include <QtGui>
#include <QWebSettings>

const QString GraphicsSimpleBrowser::mDefaultUrl = "tut.by";

GraphicsSimpleBrowser::GraphicsSimpleBrowser(QGraphicsItem *parent) :
    QGraphicsWidget(parent)
  , mGraphicsWebView(0)
  , mAdressBar(0)
  , mBackButton(0)
  , mForwardButton(0)
  , mLoadButton(0)
  , mProgressBar(0)
{
    QWebSettings *gs = QWebSettings::globalSettings();
    gs->setAttribute(QWebSettings::JavaEnabled, true);
    gs->setAttribute(QWebSettings::PluginsEnabled, true);
    gs->setAttribute(QWebSettings::LocalStorageDatabaseEnabled, true);
    gs->setAttribute(QWebSettings::OfflineWebApplicationCacheEnabled, true);
    gs->setAttribute(QWebSettings::OfflineStorageDatabaseEnabled, true);
    gs->setAttribute(QWebSettings::JavascriptCanAccessClipboard, true);
    gs->setAttribute(QWebSettings::DnsPrefetchEnabled, true);

    setAutoFillBackground(true);

    mGraphicsWebView = new QGraphicsWebView();

    mLabel = new QLabel("QGraphicsWebView");

    mCloseButton = new QToolButton();
    mCloseButton->setAutoRaise(true);
    mCloseButton->setText("X");

    mBackButton = new QToolButton();
    mBackButton->setAutoRaise(true);
    mBackButton->setArrowType(Qt::LeftArrow);

    mForwardButton = new QToolButton();
    mForwardButton->setAutoRaise(true);
    mForwardButton->setArrowType(Qt::RightArrow);

    mLoadButton = new QToolButton();
    mLoadButton->setAutoRaise(true);
    mLoadButton->setText("load");

    mAdressBar = new QLineEdit();

    mProgressBar = new QProgressBar();
    mProgressBar->setMinimum(0);
    mProgressBar->setMaximum(100);
    mProgressBar->setValue(0);

    QGraphicsLinearLayout *mainLayer = new QGraphicsLinearLayout(Qt::Vertical);

    QGraphicsLinearLayout *titleLayout = new QGraphicsLinearLayout(Qt::Horizontal);

    QGraphicsProxyWidget *proxyLabel = new QGraphicsProxyWidget();
    proxyLabel->setWidget(mLabel);

    QGraphicsProxyWidget *proxyCloseButton = new QGraphicsProxyWidget();
    proxyCloseButton->setWidget(mCloseButton);

    titleLayout->addItem(proxyLabel);
    titleLayout->addItem(proxyCloseButton);

    QGraphicsWidget *titleLayoutItem = new QGraphicsWidget();
    titleLayoutItem->setLayout(titleLayout);

    QGraphicsLinearLayout *controlPanelLayout = new QGraphicsLinearLayout(Qt::Horizontal);

    QGraphicsProxyWidget *proxyBackButton = new QGraphicsProxyWidget();
    proxyBackButton->setWidget(mBackButton);

    QGraphicsProxyWidget *proxyForwardButton = new QGraphicsProxyWidget();
    proxyForwardButton->setWidget(mForwardButton);

    QGraphicsProxyWidget *proxyAdressBar = new QGraphicsProxyWidget();
    proxyAdressBar->setWidget(mAdressBar);

    QGraphicsProxyWidget *proxyLoadButton = new QGraphicsProxyWidget();
    proxyLoadButton->setWidget(mLoadButton);

    controlPanelLayout->addItem(proxyBackButton);
    controlPanelLayout->addItem(proxyForwardButton);
    controlPanelLayout->addItem(proxyAdressBar);
    controlPanelLayout->addItem(proxyLoadButton);

    QGraphicsWidget *controlPanelLayoutItem = new QGraphicsWidget;
    controlPanelLayoutItem->setLayout(controlPanelLayout);

    QGraphicsProxyWidget *proxyProgressBar = new QGraphicsProxyWidget();
    proxyProgressBar->setWidget(mProgressBar);

    mainLayer->addItem(titleLayoutItem);
    mainLayer->addItem(controlPanelLayoutItem);
    mainLayer->addItem(mGraphicsWebView);
    mainLayer->addItem(proxyProgressBar);

    setLayout(mainLayer);

    connect(mGraphicsWebView, SIGNAL(loadProgress(int)), mProgressBar, SLOT(setValue(int)));
    connect(mGraphicsWebView, SIGNAL(loadStarted()), mProgressBar, SLOT(show()));
    connect(mGraphicsWebView, SIGNAL(loadFinished(bool)), mProgressBar, SLOT(hide()));
    connect(mBackButton, SIGNAL(clicked()), mGraphicsWebView, SLOT(back()));
    connect(mForwardButton, SIGNAL(clicked()), mGraphicsWebView, SLOT(forward()));

    connect(mAdressBar, SIGNAL(returnPressed()), this, SLOT(on_mAdressBar_returnPressed()));
    connect(mLoadButton, SIGNAL(clicked()), this, SLOT(on_mLoadButton_clicked()));
    connect(mGraphicsWebView, SIGNAL(urlChanged(QUrl)), this, SLOT(on_webView_urlChanged(QUrl)));
    connect(mCloseButton, SIGNAL(clicked()), this, SLOT(on_mCloseButton_clicked()));

    mAdressBar->setText(mDefaultUrl);
    load();

    setFlags(ItemIsMovable | ItemIsSelectable | ItemIsFocusable);
}

void GraphicsSimpleBrowser::on_mAdressBar_returnPressed()
{
    load();
}
void GraphicsSimpleBrowser::on_mLoadButton_clicked()
{
    load();
}

void GraphicsSimpleBrowser::on_webView_urlChanged(QUrl purl)
{
    mAdressBar->setText(purl.toString());
}

void GraphicsSimpleBrowser::on_mCloseButton_clicked()
{
    if (scene()) {
        scene()->removeItem(this);
    }
}

void GraphicsSimpleBrowser::load()
{
    QString curUrl = adjustToUrl(mAdressBar->text());
    mAdressBar->setText(curUrl);
    mGraphicsWebView->load(QUrl(curUrl));
}

QString GraphicsSimpleBrowser::adjustToUrl(const QString &str)
{
    QString result = str;

    if (QFileInfo(result.replace("file://", "")).exists()) {
        if (!result.startsWith("file://")) {
            result.prepend("file://");
        }
    } else if (!result.startsWith("http://")) {
        result.prepend("http://");
    }

    return result;
}
