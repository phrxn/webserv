rm -rf /var/www/html/*

mkdir /var/www/html/dir_000
mkdir /var/www/html/dir_000/dir_000
mkdir /var/www/html/dir_000/dir_777

mkdir /var/www/html/dir_777
mkdir /var/www/html/dir_777/dir_000
mkdir /var/www/html/dir_777/dir_777

chmod 777  /var/www/html/dir_000/dir_777
chmod 0    /var/www/html/dir_000/dir_000
chmod 0    /var/www/html/dir_000

chmod 0    /var/www/html/dir_777/dir_000
chmod 777  /var/www/html/dir_777/dir_777
chmod 777  /var/www/html/dir_777