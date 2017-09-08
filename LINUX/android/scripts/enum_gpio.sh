# 枚举所有的gpio信息
function gpio_info()
{
	echo "gpo test::++++++++++"

	cd /sys/class/gpio
	for i in gpiochip* ; do echo `cat $i/label`: `cat $i/base` ; done

	echo "gpo test::----------"
}

# 测试pio
function gpo_test()
{
	echo "gpo test::++++++++++"
	
	echo $1 > /sys/class/gpio/export
	cd /sys/class/gpio/gpio$1
	echo '1' > value
	echo 'out' > direction
	echo '1' > value
	sleep 5
	echo '0' > value
	sleep 5

	echo "gpo test::----------"
}


set -x
gpio_info
gpo_test 121
