 #
 # Copyright 2014 Joseph Mills.
 #
 # This program is free software; you can redistribute it and/or modify
 # it under the terms of the GNU Lesser General Public License as published by
 # the Free Software Foundation; version 3.
 #
 # This program is distributed in the hope that it will be useful,
 # but WITHOUT ANY WARRANTY; without even the implied warranty of
 # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 # GNU Lesser General Public License for more details.
 #
 # You should have received a copy of the GNU Lesser General Public License
 # along with this program.  If not, see <http://www.gnu.org/licenses/>.
 #
 # Author: Joseph Mills  <josephjamesmills@gmail.com>
 #
## assign a template
TEMPLATE = subdirs
CONFIG   += ordered
## add the subdirs for all the projects
SUBDIRS += \
        Mango/Ssh/QSsh/qssh.pro \
	Mango \
        Mango/Ssh 

OTHER_FILES += \
README.md





##for docs
include(doc/docs.pri)
