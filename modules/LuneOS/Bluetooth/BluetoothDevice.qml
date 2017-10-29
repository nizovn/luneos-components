/*
 * Copyright (C) 2013 Christophe Chapuis <chris.chapuis@gmail.com>
 * Copyright (C) 2013 Simon Busch <morphis@gravedo.de>
 * Copyright (C) 2015 Herman van Hazendonk <github.com@herrie.org>
 * Copyright (C) 2015 Nikolay Nizov <nizovn@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

import QtQuick 2.0
import Nemo.DBus 2.0

Item {
    id: _device
    property string name: ""
    property string address: ""
    property int cod: 0
    property bool connected: false
    property bool lastConnectFailed: false
    property bool connecting: false
    property bool trusted: false
    property string path: "/"

    DBusInterface {
        id: btDeviceIntrospection
        service: "org.bluez"
        path: _device.path
        iface: "org.freedesktop.DBus.Properties"
        bus: DBus.SystemBus
        signalsEnabled: true

        function propertiesChanged()
        {
            refreshProperties();
        }
    }
    DBusInterface {
        id: btDevice
        service: "org.bluez"
        path: _device.path
        iface: "org.bluez.Device1"
        bus: DBus.SystemBus
        signalsEnabled: false
    }

    function connectDevice() {
        _device.connecting = true;
        btDevice.call('Connect', undefined,
                      function() {_device.lastConnectFailed = false; _device.connecting = false;},  /* success */
                      function() {_device.lastConnectFailed = true;  _device.connecting = false;}); /* failed  */
    }

    function disconnectDevice() {
        btDevice.call('Disconnect');
    }

    function refreshProperties() {
        btDeviceIntrospection.typedCall('GetAll', [{type: 's', value: "org.bluez.Device1"}], function (result) {
            _device.name = result.Name;
            _device.address = result.Address;
            _device.cod = result.Class;
            _device.trusted = result.Trusted;
            _device.connected = result.Connected;
        });
    }

    Component.onCompleted: {
        refreshProperties();
    }
}