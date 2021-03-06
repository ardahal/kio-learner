/*
Copyright 2012  Aish Raj Dahal < dahalaishraj at gmail.com >

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of
the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef showHttp_H
#define showHttp_H

#include <QtCore/QObject>
#include <KIO/AccessManager>
#include <KIO/Job>
#include <KIO/MimetypeJob>
#include <KIO/SimpleJob>
#include <KIO/Scheduler>
#include <QtCore/QEventLoop>

class metalinkHttp : public QObject
{
    Q_OBJECT
public:
    metalinkHttp(const KUrl&);
    ~metalinkHttp();
    bool isMetalinkHttp();

public slots:
    void checkVerifiable(KIO::Job *mJob, QString);

private slots:
    void slotHeaderResult(KJob* kjob);
    void checkMetalinkHttp();

private:
    const KUrl m_Url;
    bool m_MetalinkHSatus;
    QEventLoop m_loop;
    QMultiMap<QString, QString> m_headerInfo;
    void parseHeaders(const QString&);
    void setMetalinkHSatus();
    bool m_isVerifyiable;

};



#endif // showHttp_H
