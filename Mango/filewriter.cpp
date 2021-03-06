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
#include "filewriter.h"
#include <QDir>

/*!
 * \qmltype FileWriter
 * \inqmlmodule Mango 0.1
 * \ingroup Mango
 * \inherits Item
 * \since 5.3
 * \title A Qml Plugin that is used to write to files and also change persmmisons of files.
 */
FileWriter::FileWriter(QObject *parent) :
    QObject(parent)
{
}
/*!
 * \qmlproperty string FileWriter::fileName
 * 
 * sets the filename that one wishes to read write or change permissions on from QML
 */
QString FileWriter::fileName() const
{
    return m_FileName;
}
void FileWriter::setFileName(const QString &fileName)
{
    if (m_FileName == fileName)
        return;
    m_FileName = fileName;
    emit fileNameChanged();
}

/*!
 * \qmlproperty string FileWriter::makeDir
 * 
 * Used as a signal in QML to make a directory. Not a path please see mkpath for more info about making paths on a local machine.
 */
QString FileWriter::makeDir()
{
    return m_MakeDir;
}

void FileWriter::setMakeDir(const QString &dirPath){
    m_MakeDir = dirPath;
}
/*!
 * \qmlproperty string FileWriter::removeDir
 * 
 * sets the file that on wishes to remove from the local file system.
 */
QString FileWriter::removeDir()
{
    return m_RemoveDir;
}
void FileWriter::setRemoveDir(const QString &removeDir){
    m_RemoveDir = removeDir;
}

/*!
 * \qmlsignal FileWriter::removePath()
 * Used in QML to remove a Path from a file system
 */
void FileWriter::removePath(){
    QDir qdir;
    if (qdir.exists(m_RemoveDir)){
        qdir.rmpath(m_RemoveDir);
    }else{
        qDebug() << "the path " << m_RemoveDir << "Does not exsit  so there no need to remove it" ;
    }
}
/*!
 * \qmlsignal FileWriter::changePermissions()
 * used in QML to change the permissions of a file.  This is a signal that needs to be called.
 */
void FileWriter::changePermissions(const QString &filename, const QString &permissions)
{
    QFile file;
    file.setFileName(filename);
    if (permissions == "+x" )
    {
        file.setPermissions(QFileDevice::ExeUser);
        file.setPermissions(QFileDevice::ExeGroup);
        file.setPermissions(QFileDevice::ExeOwner);
        file.setPermissions(QFileDevice::ExeOther);
    }
    else if (permissions == "+w")
    {
        file.setPermissions(QFileDevice::WriteUser);
        file.setPermissions(QFileDevice::WriteGroup);
        file.setPermissions(QFileDevice::WriteOwner);
        file.setPermissions(QFileDevice::WriteOther);
    }
    else if (permissions == "+r")
    {
        file.setPermissions(QFileDevice::ReadUser);
        file.setPermissions(QFileDevice::ReadGroup );
        file.setPermissions(QFileDevice::ReadOwner);
        file.setPermissions(QFileDevice::ReadOther);
    }
    else if(permissions ==  "o+r")
    {
        file.setPermissions(QFileDevice::ReadOwner);
    }
    else if(permissions == "o+r")
    {
        file.setPermissions(QFileDevice::WriteOwner);
    }
    else if(permissions == "o+x")
    {
        file.setPermissions(QFileDevice::ExeOwner);
    }
    else if (permissions == "u+r")
    {
        file.setPermissions(QFileDevice::ReadUser);
    }
    else if (permissions == "u+w")
    {
        file.setPermissions(QFileDevice::WriteUser);
    }
    else if(permissions == "u+e")
    {
        file.setPermissions(QFileDevice::ExeUser);
    }
    else if (permissions == "g+r")
    {
        file.setPermissions(QFileDevice::ReadGroup);
    }
    else if (permissions == "g+w")
    {
        file.setPermissions(QFileDevice::WriteGroup);
    }
    else if(permissions == "g+x")
    {
        file.setPermissions(QFileDevice::ExeGroup);
    }
    else if(permissions == "o+r")
    {
        file.setPermissions(QFileDevice::ReadOther);
    }
    else if(permissions == "o+w")
    {
        file.setPermissions(QFileDevice::WriteOther);
    }
    else if (permissions == "o+x")
    {
        file.setPermissions(QFileDevice::ExeOther);
    }
    else
    {
        qDebug() << "Permission not allowed with the type of " <<  permissions;
    }
}
/*!
 * \qmlsignal FileWriter::createPath()
 * used in QML to create a path on a local filesystem
 */
void FileWriter::createPath(){
    QDir qdir;
    if (!qdir.exists(m_MakeDir)){
        qdir.mkpath(m_MakeDir);
    }else{
        qDebug() << "the path " << m_MakeDir << "is allready there no need to create one" ;
    }
}
/*!
 * \qmlproperty string FileWriter::output
 * This is used to write to a file.  the output is what is wrote to a file when the signal writeFile() is called.
 */
QString FileWriter::output() const
{
    return m_Output;
}
void FileWriter::setOutput( const QString &output)
{
    if (m_Output == output)
        return;
    m_Output = output;
    emit outputChanged();
}

/*!
 * \qmlsignal FileWriter::writeFile()
 * used in QML as a signal to write a contents to a file
 */
void FileWriter::writeFile() {
    QFile mFile(m_FileName);
    if(!mFile.open(QFile::ReadWrite  | QFile::Text )){
        qDebug() << "Could not open the File for writing  " << m_FileName ;
        return ;
    }
    QTextStream out(&mFile);
    out << m_Output;
    mFile.flush();
    mFile.close();
}
