#!/bin/bash -e

source ../../color.sh

os=`uname`
set -e
MAKE=make
if [[ $os = '' ]]
then
	echo -e $Color_Off$On_Purple$BWhite"Fail to get os info!! [Linux, ibm64, hpux64, ..]"$Color_Off
	exit $?
fi

if [[ $1 = '' ]]
then
	echo -e $Color_Off$On_Purple$BWhite"input build option!! [build, rebuild, clean, ..]"$Color_Off
	exit $?
fi

echo -e $Color_Off$BGreen$os "castella logtest build start!!!================"$Color_Off
if [[ $os = 'Linux' ]]
then
	rm -rf makefile.local;
	ln -s ../../makefile.linux makefile.local;
elif [[ $os = 'ibm64' ]]
then
	rm -rf makefile.local;
	ln -s ../../makefile.ibm64 makefile.local;
elif [[ $os = 'hpux64' ]]
then
	MAKE=gmake
	rm -rf makefile.local;
	ln -s ../../makefile.hpux64 makefile.local;
else
	echo -e $Color_Off$On_Yellow$BBlue"Not supported yet!!" $Color_Off;
fi

if [[ $1 = 'rebuild' ]]
then
	$MAKE clean;
	$MAKE;
	if [[ $? != 0 ]]; then
		echo -e $Color_Off$On_Red$BYellow'Fail to Compile "castella logtest"\n'$Color_Off
		exit 1
	fi
elif [[ $1 = 'build' ]]
then
	$MAKE;
	if [[ $? != 0 ]]; then
		echo -e $Color_Off$On_Red$BYellow'Fail to Compile "castella logtest"\n'$Color_Off
		exit 1
	fi
elif [[ $1 = 'clean' ]]
then
	$MAKE clean;
else
	echo -e $Color_Off$On_Red$BYellow'Option not supported.\n'$Color_Off
fi
echo -e $Color_Off$BGreen$os "castella logtest build finished!!!================"$Color_Off

