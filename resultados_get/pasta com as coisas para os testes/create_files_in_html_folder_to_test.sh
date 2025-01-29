rm -rf /var/www/html/*

mkdir /var/www/html/dir_000
echo -ne a > /var/www/html/dir_000/file_000.txt
echo -ne a > /var/www/html/dir_000/file_777.txt

mkdir /var/www/html/dir_777
echo -ne a > /var/www/html/dir_777/file_000.txt
echo -ne a > /var/www/html/dir_777/file_777.txt

chmod 0    /var/www/html/dir_000
chmod 777  /var/www/html/dir_000/file_777.txt
chmod 0    /var/www/html/dir_000/file_000.txt

chmod 0    /var/www/html/dir_777/file_000.txt
chmod 777  /var/www/html/dir_777/file_777.txt
chmod 777  /var/www/html/dir_777