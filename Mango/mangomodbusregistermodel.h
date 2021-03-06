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
#ifndef MANGOMODBUSREGISTERMODEL_H
#define MANGOMODBUSREGISTERMODEL_H

#include <QAbstractListModel>
#include <stdint.h>

struct _modbus;
typedef _modbus modbus_t;

class MangoModbusRegisterModel : public QAbstractListModel
{
    Q_OBJECT

    Q_ENUMS(ModbusRegisterType)
    Q_ENUMS(OutputType)

    Q_PROPERTY(ModbusRegisterType modbusRegisterType READ modbusRegisterType WRITE setModbusRegisterType)
    Q_PROPERTY(OutputType outputType READ outputType WRITE setOutputType)
    Q_PROPERTY(int registerReadAddr READ registerReadAddr WRITE setRegisterReadAddr)
    Q_PROPERTY(int registerReadSize READ registerReadSize WRITE setRegisterReadSize)

public:

    enum ModbusRegisterType {
        Coil = 1,
        Input = 2,
        Register = 3
    };

    enum OutputType {
        Integer16,
        Integer32,
        Float,
        FlippedFloat,
        DoubleFloat
    };

    explicit MangoModbusRegisterModel(QObject *parent = 0);

    Q_INVOKABLE bool connectToServer(const QString& ip, int port = 502);
    Q_INVOKABLE bool isConnected() const;

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    ~MangoModbusRegisterModel();

    ModbusRegisterType modbusRegisterType() const;
    void setModbusRegisterType(ModbusRegisterType modbusRegisterType);

    OutputType outputType() const;
    void setOutputType(OutputType outputType);

    int registerReadAddr() const;
    void setRegisterReadAddr(int registerReadAddr);

    int registerReadSize() const;
    void setRegisterReadSize(int registerReadSize);

public slots:
    void readRegisters();
    void disconnect();

private:
    modbus_t* m_modbusContext;
    QScopedArrayPointer<uint8_t> m_registers;
    int m_numRead;
    ModbusRegisterType m_registerType;
    OutputType m_outputType;
    int m_registerReadAddr;
    int m_registerReadSize;
    bool m_connected;
};

#endif // MANGOMODBUSREGISTERMODEL_H
