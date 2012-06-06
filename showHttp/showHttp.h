#ifndef showHttp_H
#define showHttp_H

#include <QtCore/QObject>
#include <KIO/AccessManager>
#include <KIO/Job>
#include <KIO/SimpleJob>
#include <KIO/Scheduler>

class QNetworkReply;


class showHttp : public QObject
{

    Q_OBJECT
public:
    showHttp();
    virtual ~showHttp();

private:
    QNetworkReply * m_headerReply;

public slots:
    void slotResult(KJob* kjob);
    void output();
};

#endif // showHttp_H