#!/usr/bin/bash

NORMAL='\033[0m'
BOLD='\033[1m'
GREEN='\033[32m'
RED='\033[31m'
HOME_DIR=$(pwd)
IFS=$'\n'

for path in $(find . -name "CMakeLists.txt" | sed -e "s/CMakeLists.txt//")
do
	echo -e "${GREEN}${BOLD}Building ${path}...${NORMAL}"
	cd ${path}
	rm -rf build
	cmake -H. -Bbuild > /dev/null
	touch build/CMakeLog.txt
	cmake --build build 2> build/CMakeLog.txt
	if [ -s build/CMakeLog.txt ]
	then
		cat build/CMakeLog.txt
		echo -e "${RED}${BOLD}Build failed${NORMAL}\n"
	else
		echo -e "${GREEN}${BOLD}Build completed${NORMAL}\n"
	fi
	cd ${HOME_DIR}
done