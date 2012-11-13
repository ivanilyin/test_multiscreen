#ifndef GRAPHICSWEBVIEWITEM_H
#define GRAPHICSWEBVIEWITEM_H

#include <QGraphicsWidget>
#include <QGraphicsLinearLayout>
#include <QToolButton>
#include <QProgressBar>
#include <QGraphicsWebView>
#include <QLabel>
#include <QGraphicsScene>
#include <QLineEdit>

class GraphicsSimpleBrowser : public QGraphicsWidget
{
    Q_OBJECT
public:
    static const QString mDefaultUrl;

    explicit GraphicsSimpleBrowser(QGraphicsItem *parent = 0);

private slots:
    void on_mAdressBar_returnPressed();
    void on_mLoadButton_clicked();
    void on_webView_urlChanged(QUrl);
    void on_mCloseButton_clicked();
    void load();

private:
    QString adjustToUrl(const QString &str);

private:
    QGraphicsWebView *mGraphicsWebView;
    QLineEdit *mAdressBar;
    QToolButton *mBackButton;
    QToolButton *mForwardButton;
    QToolButton *mLoadButton;
    QProgressBar *mProgressBar;
    QLabel *mLabel;
    QToolButton *mCloseButton;
};

#endif // GRAPHICSWEBVIEWITEM_H
