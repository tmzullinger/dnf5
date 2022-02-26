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


#ifndef MICRODNF_COMMANDS_DOWNGRADE_DOWNGRADE_HPP
#define MICRODNF_COMMANDS_DOWNGRADE_DOWNGRADE_HPP


#include <libdnf-cli/session.hpp>

#include <memory>
#include <vector>


namespace microdnf {


class DowngradeCommand : public libdnf::cli::session::Command {
public:
    explicit DowngradeCommand(Command & parent);
    void run() override;

private:
    std::vector<std::string> pkg_specs;
    std::vector<std::string> pkg_file_paths;
};


}  // namespace microdnf


#endif  // MICRODNF_COMMANDS_DOWNGRADE_DOWNGRADE_HPP
