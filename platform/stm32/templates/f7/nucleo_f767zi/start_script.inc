

	"mkdir -s /conf",
	"mount -t DumbFS /dev/stm32flash0 /conf",
	"conf_setup",

	"netmanager",
	"service telnetd",
	"service httpd",
/*
	"echo 1111 > /conf/1.txt",
	"cat /conf/1.txt",
*/

/*
"flash_erase /dev/flash_fix1",
"tftp -g -o /dev/flash_fix1 embox.bin 192.168.2.1",
*/
