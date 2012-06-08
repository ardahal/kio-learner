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

#include "metalinkHttp.h"
#include <kdebug.h>
#include <QtCore/QString>

metalinkHttp::metalinkHttp(const KUrl& Url)
  : m_MetalinkHSatus(false),
   m_Url(Url)
{
  
}

metalinkHttp::~metalinkHttp()
{

}

void metalinkHttp::checkMetalinkHttp()
{

  KIO::SimpleJob *job;
  job = KIO::get(m_Url);
  job->addMetaData("PropagateHttpHeader","true");
  job->setRedirectionHandlingEnabled(false);
  connect(job, SIGNAL(result(KJob*)), this, SLOT(slotHeaderResult(KJob*)));
  qDebug() << " Verifying Metalink/HTTP Status" ;
  m_loop.exec();
  
}

void metalinkHttp::slotHeaderResult(KJob* kjob)
{
  KIO::Job* job = qobject_cast<KIO::Job*>(kjob);
  const QString httpHeaders = job ? job->queryMetaData("HTTP-Headers") : QString();
  parseHeaders(httpHeaders);
  setMetalinkHSatus();
  m_loop.exit();
  
}

bool metalinkHttp::isMetalinkHttp()
{
  return m_MetalinkHSatus;
}

void metalinkHttp::parseHeaders(const QString &httpHeader )
{
  QString trimedHeader = httpHeader.mid(httpHeader.indexOf('\n') + 1).trimmed();
  
  foreach (QString line, trimedHeader.split('\n')) {
    int colon = line.indexOf(':');
    QString headerName = line.left(colon).trimmed();
    QString headerValue = line.mid(colon + 1).trimmed();  
    int lessthan_pos = line.indexOf('<');
    if (lessthan_pos >= 0) {
      headerValue = line.mid(lessthan_pos + 1).trimmed();
    }
    m_headerInfo.insertMulti(headerName,headerValue);
  }
}

void metalinkHttp::setMetalinkHSatus()
{
    if ((m_headerInfo.contains("link")) && (m_headerInfo.contains("digest"))) {
        m_MetalinkHSatus = true;
    }
}

#include "metalinkHttp.moc"
