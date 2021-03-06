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
#ifndef FILEMOVE_H
#define FILEMOVE_H
#include <QDir>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QObject>

class FileMove : public QObject
{
    Q_OBJECT
public:
    explicit FileMove(QObject *parent = 0);
    Q_PROPERTY(QString oldFile READ oldFile WRITE setOldFile NOTIFY oldFileChanged)
    Q_PROPERTY(QString newFile READ newFile WRITE setNewFile NOTIFY newFileChanged)
    Q_INVOKABLE void moveFile();


    QString oldFile()const ;
    void setOldFile(const QString &oldfile);

    QString newFile()const ;
    void setNewFile(const QString &newfile);


    signals:
    void newFileChanged();
    void oldFileChanged();
private:
   QString m_OldFile;
   QString m_NewFile;

};

#endif // FILEMOVE_H
