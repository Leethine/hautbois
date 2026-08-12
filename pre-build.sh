#!/bin/sh

# TODO use pkg-config to check dependant packages
# asio dev package and stk dev package should be installed

if [[ "${1}" == "--prefix" ]] && [[ -d "${2}" ]]; then
rm Makefile && cp Makefile.bak Makefile
INSTALL_PATH="$(echo ${2} | tr '/' ' ' | sed 's/ /\\\//g')"
INSTALL_PATH_ESC="$(echo ${2} | tr '/' ' ' | sed 's/ /\\\\\\\//g')"
sed -i 's/###__TEXT_REPLACE_TAG1__###/INSTALLATION_PATH := '"${INSTALL_PATH}"'/g' Makefile
sed -i 's/###__TEXT_REPLACE_TAG2__###/INSTALLATION_PATH_ESCAPE := '"${INSTALL_PATH_ESC}"'/g' Makefile
fi
