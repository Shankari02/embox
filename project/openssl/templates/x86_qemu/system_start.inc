"export PWD=/",
"export HOME=/",
"partition",
"service net_service",
"service telnetd",
"service httpd",
"source time_setup.sh",
"mkdir -s /mnt",
"mount -t ramfs /dev/static_ramdisk /mnt",
"openssl_rand_demo",
"tish",
