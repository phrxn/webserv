#!/bin/bash

 rm -rf result.txt
 echo -ne "ARQUIVO\n" >> result.txt
 echo -ne "  GET\n" >> result.txt
 echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO |\n" >> result.txt
 echo -ne "          0        |             0            |           0           |             0               |       0       |    "           >> result.txt
 curl -X GET -I localhost:80/dir_000/not_exis.txt  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                             >> result.txt ; echo -ne "    |\n" >> result.txt
#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO |\n" >> result.txt
 echo -ne "          0        |             0            |           0           |             0               |       1       |    "           >> result.txt
 curl -X GET -I localhost:80/dir_000/not_exis.txt  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                             >> result.txt ; echo -ne "    |\n" >> result.txt
#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO |\n" >> result.txt
 echo -ne "          0        |             0            |           0           |             1               |       0       |    "           >> result.txt
 curl -X GET -I localhost:80/dir_000/not_exis.txt/ | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                             >> result.txt ; echo -ne "    |\n" >> result.txt
#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO |\n" >> result.txt
 echo -ne "          0        |             0            |           0           |             1               |       1       |    "           >> result.txt
 curl -X GET -I localhost:80/dir_000/not_exis.txt/ | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                             >> result.txt ; echo -ne "    |\n" >> result.txt
#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO |\n" >> result.txt
 echo -ne "          0        |             0            |           1           |             0               |       0       |    "           >> result.txt
 curl -X GET -I localhost:80/dir_777/not_exis.txt  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                             >> result.txt ; echo -ne "    |\n" >> result.txt
#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO |\n" >> result.txt
 echo -ne "          0        |             0            |           1           |             0               |       1       |    "           >> result.txt
 curl -X GET -I localhost:80/dir_777/not_exis.txt  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                             >> result.txt ; echo -ne "    |\n" >> result.txt
#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO |\n" >> result.txt
 echo -ne "          0        |             0            |           1           |             1               |       0       |    "           >> result.txt
 curl -X GET -I localhost:80/dir_777/not_exis.txt/ | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                             >> result.txt ; echo -ne "    |\n" >> result.txt
#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO |\n" >> result.txt
 echo -ne "          0        |             0            |           1           |             1               |       1       |    "           >> result.txt
 curl -X GET -I localhost:80/dir_777/not_exis.txt/ | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                             >> result.txt ; echo -ne "    |\n" >> result.txt
#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO |\n" >> result.txt
 echo -ne "          0        |             1            |           0           |             0               |       0       |    "           >> result.txt
 curl -X GET -I localhost:81/dir_000/not_exis.txt  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                             >> result.txt ; echo -ne "    |\n" >> result.txt
#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO |\n" >> result.txt
 echo -ne "          0        |             1            |           0           |             0               |       1       |    "           >> result.txt
 curl -X GET -I localhost:81/dir_000/not_exis.txt  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                             >> result.txt ; echo -ne "    |\n" >> result.txt
#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO |\n" >> result.txt
 echo -ne "          0        |             1            |           0           |             1               |       0       |    "           >> result.txt
 curl -X GET -I localhost:81/dir_000/not_exis.txt/ | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                             >> result.txt ; echo -ne "    |\n" >> result.txt
#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO |\n" >> result.txt
 echo -ne "          0        |             1            |           0           |             1               |       1       |    "           >> result.txt
 curl -X GET -I localhost:81/dir_000/not_exis.txt/ | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                             >> result.txt ; echo -ne "    |\n" >> result.txt
#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO |\n" >> result.txt
 echo -ne "          0        |             1            |           1           |             0               |       0       |    "           >> result.txt
 curl -X GET -I localhost:81/dir_777/not_exis.txt  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                             >> result.txt ; echo -ne "    |\n" >> result.txt
#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO |\n" >> result.txt
 echo -ne "          0        |             1            |           1           |             0               |       1       |    "           >> result.txt
 curl -X GET -I localhost:81/dir_777/not_exis.txt  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                             >> result.txt ; echo -ne "    |\n" >> result.txt
#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO |\n" >> result.txt
 echo -ne "          0        |             1            |           1           |             1               |       0       |    "           >> result.txt
 curl -X GET -I localhost:81/dir_777/not_exis.txt/ | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                             >> result.txt ; echo -ne "    |\n" >> result.txt
#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO |\n" >> result.txt
 echo -ne "          0        |             1            |           1           |             1               |       1       |    "           >> result.txt
 curl -X GET -I localhost:81/dir_777/not_exis.txt/ | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                             >> result.txt ; echo -ne "    |\n" >> result.txt
#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO |\n" >> result.txt
 echo -ne "          1        |             0            |           0           |             0               |       0       |    "           >> result.txt
 curl -X GET -I localhost:80/dir_000/file_000.txt  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                             >> result.txt ; echo -ne "    |\n" >> result.txt
#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO |\n" >> result.txt
 echo -ne "          1        |             0            |           0           |             0               |       1       |    "           >> result.txt
 curl -X GET -I localhost:80/dir_000/file_777.txt  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                             >> result.txt ; echo -ne "    |\n" >> result.txt
#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO |\n" >> result.txt
 echo -ne "          1        |             0            |           0           |             1               |       0       |    "           >> result.txt
 curl -X GET -I localhost:80/dir_000/file_000.txt/ | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                             >> result.txt ; echo -ne "    |\n" >> result.txt
#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO |\n" >> result.txt
 echo -ne "          1        |             0            |           0           |             1               |       1       |    "           >> result.txt
 curl -X GET -I localhost:80/dir_000/file_777.txt/ | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                             >> result.txt ; echo -ne "    |\n" >> result.txt
#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO |\n" >> result.txt
 echo -ne "          1        |             0            |           1           |             0               |       0       |    "           >> result.txt
 curl -X GET -I localhost:80/dir_777/file_000.txt  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                             >> result.txt ; echo -ne "    |\n" >> result.txt
#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO |\n" >> result.txt
 echo -ne "          1        |             0            |           1           |             0               |       1       |    "           >> result.txt
 curl -X GET -I localhost:80/dir_777/file_777.txt  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                             >> result.txt ; echo -ne "    |\n" >> result.txt
#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO |\n" >> result.txt
 echo -ne "          1        |             0            |           1           |             1               |       0       |    "           >> result.txt
 curl -X GET -I localhost:80/dir_777/file_000.txt/ | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                             >> result.txt ; echo -ne "    |\n" >> result.txt
#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO |\n" >> result.txt
 echo -ne "          1        |             0            |           1           |             1               |       1       |    "           >> result.txt
 curl -X GET -I localhost:80/dir_777/file_777.txt/ | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                             >> result.txt ; echo -ne "    |\n" >> result.txt
#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO |\n" >> result.txt
 echo -ne "          1        |             1            |           0           |             0               |       0       |    "           >> result.txt
 curl -X GET -I localhost:81/dir_000/file_000.txt  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                             >> result.txt ; echo -ne "    |\n" >> result.txt
#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO |\n" >> result.txt
 echo -ne "          1        |             1            |           0           |             0               |       1       |    "           >> result.txt
 curl -X GET -I localhost:81/dir_000/file_777.txt  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                             >> result.txt ; echo -ne "    |\n" >> result.txt
#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO |\n" >> result.txt
 echo -ne "          1        |             1            |           0           |             1               |       0       |    "           >> result.txt
 curl -X GET -I localhost:81/dir_000/file_000.txt/ | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                             >> result.txt ; echo -ne "    |\n" >> result.txt
#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO |\n" >> result.txt
 echo -ne "          1        |             1            |           0           |             1               |       1       |    "           >> result.txt
 curl -X GET -I localhost:81/dir_000/file_777.txt/ | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                             >> result.txt ; echo -ne "    |\n" >> result.txt
#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO |\n" >> result.txt
 echo -ne "          1        |             1            |           1           |             0               |       0       |    "           >> result.txt
 curl -X GET -I localhost:81/dir_777/file_000.txt  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                             >> result.txt ; echo -ne "    |\n" >> result.txt
#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO |\n" >> result.txt
 echo -ne "          1        |             1            |           1           |             0               |       1       |    "           >> result.txt
 curl -X GET -I localhost:81/dir_777/file_777.txt  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                             >> result.txt ; echo -ne "    |\n" >> result.txt
#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO |\n" >> result.txt
 echo -ne "          1        |             1            |           1           |             1               |       0       |    "           >> result.txt
 curl -X GET -I localhost:81/dir_777/file_000.txt/ | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                             >> result.txt ; echo -ne "    |\n" >> result.txt
#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO |\n" >> result.txt
 echo -ne "          1        |             1            |           1           |             1               |       1       |    "           >> result.txt
 curl -X GET -I localhost:81/dir_777/file_777.txt/ | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                             >> result.txt ; echo -ne "    |\n" >> result.txt
 
 












