/*
Copyright Contributors to the libdnf project.

This file is part of libdnf: https://github.com/rpm-software-management/libdnf/

Libdnf is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

Libdnf is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with libdnf.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "base.hpp"

#include "dbus.hpp"
#include "utils.hpp"

#include <fmt/format.h>
#include <libdnf/repo/repo.hpp>
#include <sdbus-c++/sdbus-c++.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <thread>

void Base::dbus_register() {
    auto dbus_object = session.get_dbus_object();
    dbus_object->registerMethod(
        dnfdaemon::INTERFACE_BASE, "read_all_repos", "", "b", [this](sdbus::MethodCall call) -> void {
            session.get_threads_manager().handle_method(*this, &Base::read_all_repos, call, session.session_locale);
        });
    dbus_object->registerSignal(dnfdaemon::INTERFACE_REPO, dnfdaemon::SIGNAL_REPO_KEY_IMPORT_REQUEST, "ossssx");
    dbus_object->registerSignal(dnfdaemon::INTERFACE_BASE, dnfdaemon::SIGNAL_DOWNLOAD_ADD_NEW, "os");
    dbus_object->registerSignal(dnfdaemon::INTERFACE_BASE, dnfdaemon::SIGNAL_DOWNLOAD_PROGRESS, "ott");
    dbus_object->registerSignal(dnfdaemon::INTERFACE_BASE, dnfdaemon::SIGNAL_DOWNLOAD_END, "o");
    dbus_object->registerSignal(dnfdaemon::INTERFACE_BASE, dnfdaemon::SIGNAL_DOWNLOAD_MIRROR_FAILURE, "o");
}

sdbus::MethodReply Base::read_all_repos(sdbus::MethodCall & call) {
    bool retval = session.read_all_repos();
    auto reply = call.createReply();
    reply << retval;
    return reply;
}
