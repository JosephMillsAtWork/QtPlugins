/*
 * Copyright 2014 Joseph Mills.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Author: Joseph Mills  <josephjamesmills@gmail.com>
 */
#include "sftpupload.h"
SftpUpload::SftpUpload(QObject *parent) :
    QObject(parent),
    m_sshPort(22),
    m_timeout(10)
{
}


/*!
 \qmlproperty string SftpUpload::localFile
 This is the local file on your local computer that you would like to upload to a remote server
 */
QString SftpUpload::localFile()
{
    return m_localfile;
}

void SftpUpload::setLocalFile(const QString &localFIle)
{
    m_localfile = localFIle;
}
/*!
 \qmlproperty string SftpUpload::destination
 This is the full path that you want to upload to.

 example: say I have a server with the dir /home/mango/uploads IF I wanted to upload to that folder then I would set it to that,
 \code
 destination: "/home/mango/uploaders"
 \endcode
 */

QString SftpUpload::destination()
{
    return m_destination;
}

void SftpUpload::setDestination(const QString &destination)
{
    m_destination = destination;
}

/*!
  \qmlproperty strinn SftpUpload::username
  This is the Username of the remote machine that you would like to upload to.
 */

QString SftpUpload::username()
{
    return m_username;
}

void SftpUpload::setUsername(const QString &username)
{
    m_username = username;
}

/*!
 \qmlproperty string SftpUpload::hostName
 This is the hostname of the remote machine that you would like to upload your files too.Used with the ssh connection to upload the file.
 */
QString SftpUpload::hostName()
{
    return m_hostName;
}

void SftpUpload::setHostName(const QString &hostName)
{
    m_hostName = hostName;

}
/*!
 \qmlproperty string SftpUpload::passwd
 The Password for the remote machine that you would like to upload the file to.
 */
QString SftpUpload::passwd()
{
    return m_passwd;
}

void SftpUpload::setPasswd(const QString &passwd)
{
    m_passwd = passwd;
}
/*!
  \qmlproperty int SftpUpload::sshPort
 This is used to set the port that ssh is listening on,  By default this is set to port 22
 */
int SftpUpload::sshPort()
{
    return m_sshPort;
}

void SftpUpload::setSshPort(int &sshPort)
{
    m_sshPort = sshPort;
}

int SftpUpload::timeout()
{
    return m_timeout;
}

void SftpUpload::setTimeout(int &timeout)
{
    m_timeout = timeout;
}

void SftpUpload::upload()
{
    QFileInfo info(m_localfile);
    m_localFilename = info.canonicalFilePath();
    m_remoteFilename = m_destination + "/" + info.fileName();

    QSsh::SshConnectionParameters params;
    params.host = m_hostName;
    params.userName = m_username;
    params.password = m_passwd;
    params.authenticationType = QSsh::SshConnectionParameters::AuthenticationTypePassword;
    params.timeout = 30;
    params.port = m_sshPort;

    // TODO free this pointer!
    m_connection = new QSsh::SshConnection(params, this);

    connect(m_connection, SIGNAL(connected()), SLOT(onConnected()));
    connect(m_connection, SIGNAL(error(QSsh::SshError)), SLOT(onConnectionError(QSsh::SshError)));

    qDebug() << "Connecting to host" << m_hostName;

    m_connection->connectToHost();
}







void SftpUpload::onConnected()
{
    qDebug() << "Connected";
    qDebug() << "Trying to create a sftp channel...";

    m_channel = m_connection->createSftpChannel(); //teSftpChannel();

    if (m_channel) {
        connect(m_channel.data(), SIGNAL(initialized()),
                SLOT(onChannelInitialized()));
        connect(m_channel.data(), SIGNAL(initializationFailed(QString)),
                SLOT(onChannelError(QString)));
        connect(m_channel.data(), SIGNAL(finished(QSsh::SftpJobId, QString)),
                SLOT(onOpfinished(QSsh::SftpJobId, QString)));

        m_channel->initialize();

    } else {
        qDebug() << "Error null channel";
    }
}

void SftpUpload::onConnectionError(QSsh::SshError err)
{
    qDebug() << "Connection error" << err;
}

void SftpUpload::onChannelInitialized()
{
    qDebug() << "Channel Initialized";

    // TODO Choose the overwrite mode: SftpOverwriteExisting, SftpAppendToExisting, SftpSkipExisting
    QSsh::SftpJobId job = m_channel->uploadFile(m_localFilename, m_remoteFilename,
                                                QSsh::SftpOverwriteExisting);

    if (job != QSsh::SftpInvalidJob) {
        qDebug() <<  "Starting job #" << job;
    } else {
        qDebug() << "Invalid Job";
    }
}

void SftpUpload::onChannelError(const QString &err)
{
    qDebug() << "Error: " << err;
}

void SftpUpload::onOpfinished(QSsh::SftpJobId job, const QString &err)
{
    qDebug() << "Finished job #" << job << ":" << (err.isEmpty() ? "OK" : err);
    emit done();
}


/*!
 \qmlsignal SftpUpload::upload()
 This is the signal that is sent to C++ to upload the file based on the qmlpropertys that you have set.

 */

