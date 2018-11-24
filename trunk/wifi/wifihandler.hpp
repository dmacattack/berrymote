#ifndef WIFIHANDLER_HPP
#define WIFIHANDLER_HPP

#include <QObject>

class WifiHandler
: public QObject
{
    Q_OBJECT
public:
    WifiHandler();
    ~WifiHandler();

public slots:
    void setWifiCreds(QString ssid, QString pass);

signals:
    void setWifiConnected(bool isConnected);

private:
    QString mSSID;
    QString mPassphrase;
};

#endif // WIFIHANDLER_HPP
