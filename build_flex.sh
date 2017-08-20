#!/bin/bash


readonly usage="\

Usage: 
	$0 [<targets>]
	$0

Examples:
	$0 modem
	$0 boot
	$0 rpm
	$0 slpi
	$0 adsp
	$0 android
	$0 non-hlos
	$0 meta
	$0 all
"

readonly MODEM_COMPILE_PATH="modem_proc/build/ms"
readonly BOOT_COMPILE_PATH="boot_images/QcomPkg/Msm8998Pkg"
readonly RPM_COMPILE_PATH="rpm_proc/build"
readonly SLPI_COMPILE_PATH="slpi_proc"
readonly ADSP_COMPILE_PATH="adsp_proc"
readonly ANDROID_COMPILE_PATH="LINUX/android"
readonly META_COMPILE_PATH="common/build"


# 显示帮助
function show_help()
{
	echo -e "$usage"
}


# 编译modem
function build_modem()
{
	echo "build modem::++++++++++"
	
	cd ${TOP_DIR}/${MODEM_COMPILE_PATH}
	echo $(pwd)

	python ./build_variant.py 8998.gen.prod bparams=-k

	echo "build modem::----------"
}

# 编译boot
function build_boot()
{
	echo "build boot::++++++++++"
	
	cd ${TOP_DIR}/${BOOT_COMPILE_PATH}
	echo $(pwd)

	python ../buildit.py --variant LA -r RELEASE -t Msm8998Pkg,QcomToolsPkg

	echo "build boot::----------"
}

# 编译rpm
function build_rpm()
{
	echo "build rpm::++++++++++"
	
	cd ${TOP_DIR}/${RPM_COMPILE_PATH}
	echo $(pwd)

	./build_8998.sh

	echo "build rpm::----------"
}

# 编译slpi
function build_slpi()
{
	echo "build slpi::++++++++++"
	
	cd ${TOP_DIR}/${SLPI_COMPILE_PATH}
	python ./build/build.py -c msm8998 -o all

	echo "build slpi::----------"
}

# 编译adsp
function build_adsp()
{
	echo "build adsp::++++++++++"
	
	cd ${TOP_DIR}/${ADSP_COMPILE_PATH}
	python ./build/build.py -c msm8998 -o all

	echo "build adsp::----------"
}

# 编译android
function build_android()
{
	echo "build android::++++++++++"
	
	cd ${TOP_DIR}/${ANDROID_COMPILE_PATH}
	./build.sh msm8998

	echo "build android::----------"
}

# 编译non-hlos


# 编译meta
function build_meta()
{
	echo "build meta::++++++++++"
	
	cd ${TOP_DIR}/${META_COMPILE_PATH}
	./build.py

	echo "build meta::----------"
}

# 编译non-hlos
function build_non-hlos()
{
	echo "build non-hlos::++++++++++"
	
	build_modem
	build_boot
	build_rpm
	build_slpi
	build_adsp

	echo "build non-hlos::----------"
}

# 编译all
function build_all()
{
	echo "build android::++++++++++"
	
	build_non-hlos
	build_android
	build_meta
	
	echo "build android::----------"
}


set -x

# 获取顶层目录
TOP_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
echo "TOP DIR = $TOP_DIR"

# 获取参数列表
echo "arg num = $#"
echo "args = $@"

# 解析编译命令
if [ $# -ne 1 ]; then
	show_help

	exit 1
fi


for i in $*
do
	case $i in
	modem)
		build_modem
		;;
	boot)
		build_boot
		;;
	rpm)
		build_rpm
		;;
	slpi)
		build_slpi
		;;
	adsp)
		build_adsp
		;;
	android)
		build_android
		;;
	non-hlos)
		build_non-hlos
		;;
	meta)
		build_meta
		;;
	all)
		build_all
		;;
	*)
		echo "wrong target: $i"
		show_help
		exit 1
		;;
	esac
done

#show_help
#build_modem
#build_boot
#build_rpm
#build_slpi
#build_android

