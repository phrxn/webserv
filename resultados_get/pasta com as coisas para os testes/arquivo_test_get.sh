#!/bin/bash

SERVER="localhost"

 rm -rf result.txt
 echo -ne "ARQUIVO\n" >> result.txt
 echo -ne "  GET\n" >> result.txt
 echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          0        |             0            |           0           |             0               |       0       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_000/not_exis.txt"
 curl -X GET -I "$SERVER":80"$CAMINHO"  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" GET "n" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          0        |             0            |           0           |             0               |       1       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_000/not_exis.txt"
 curl -X GET -I "$SERVER":80"$CAMINHO"  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" GET "n" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          0        |             0            |           0           |             1               |       0       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_000/not_exis.txt/"
 curl -X GET -I "$SERVER":80"$CAMINHO"  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" GET "n" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          0        |             0            |           0           |             1               |       1       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_000/not_exis.txt/"
 curl -X GET -I "$SERVER":80"$CAMINHO"  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" GET "n" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          0        |             0            |           1           |             0               |       0       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_777/not_exis.txt"
 curl -X GET -I "$SERVER":80"$CAMINHO"  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" GET "n" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          0        |             0            |           1           |             0               |       1       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_777/not_exis.txt"
 curl -X GET -I "$SERVER":80"$CAMINHO"  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" GET "n" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          0        |             0            |           1           |             1               |       0       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_777/not_exis.txt/"
 curl -X GET -I "$SERVER":80"$CAMINHO"  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" GET "n" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          0        |             0            |           1           |             1               |       1       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_777/not_exis.txt/"
 curl -X GET -I "$SERVER":80"$CAMINHO"  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" GET "n" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          0        |             1            |           0           |             0               |       0       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_000/not_exis.txt"
 curl -X GET -I "$SERVER":81"$CAMINHO"  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" GET "n" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          0        |             1            |           0           |             0               |       1       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_000/not_exis.txt"
 curl -X GET -I "$SERVER":81"$CAMINHO"  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" GET "n" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          0        |             1            |           0           |             1               |       0       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_000/not_exis.txt/"
 curl -X GET -I "$SERVER":81"$CAMINHO"  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" GET "n" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          0        |             1            |           0           |             1               |       1       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_000/not_exis.txt/"
 curl -X GET -I "$SERVER":81"$CAMINHO"  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" GET "n" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          0        |             1            |           1           |             0               |       0       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_777/not_exis.txt"
 curl -X GET -I "$SERVER":81"$CAMINHO"  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" GET "n" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          0        |             1            |           1           |             0               |       1       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_777/not_exis.txt"
 curl -X GET -I "$SERVER":81"$CAMINHO"  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" GET "n" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          0        |             1            |           1           |             1               |       0       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_777/not_exis.txt/"
 curl -X GET -I "$SERVER":81"$CAMINHO"  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" GET "n" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          0        |             1            |           1           |             1               |       1       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_777/not_exis.txt/"
 curl -X GET -I "$SERVER":81"$CAMINHO"  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" GET "n" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt






#=====================================






#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          1        |             0            |           0           |             0               |       0       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_000/file_000.txt"
 curl -X GET -I "$SERVER":80"$CAMINHO"  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" GET "y" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          1        |             0            |           0           |             0               |       1       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_000/file_777.txt"
 curl -X GET -I "$SERVER":80"$CAMINHO"  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" GET "y" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          1        |             0            |           0           |             1               |       0       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_000/file_000.txt/"
 curl -X GET -I "$SERVER":80"$CAMINHO"  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" GET "y" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          1        |             0            |           0           |             1               |       1       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_000/file_777.txt/"
 curl -X GET -I "$SERVER":80"$CAMINHO"  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" GET "y" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          1        |             0            |           1           |             0               |       0       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_777/file_000.txt"
 curl -X GET -I "$SERVER":80"$CAMINHO"  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" GET "y" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          1        |             0            |           1           |             0               |       1       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_777/file_777.txt"
 curl -X GET -I "$SERVER":80"$CAMINHO"  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" GET "y" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          1        |             0            |           1           |             1               |       0       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_777/file_000.txt/"
 curl -X GET -I "$SERVER":80"$CAMINHO"  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" GET "y" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          1        |             0            |           1           |             1               |       1       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_777/file_777.txt/"
 curl -X GET -I "$SERVER":80"$CAMINHO"  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" GET "y" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          1        |             1            |           0           |             0               |       0       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_000/file_000.txt"
 curl -X GET -I "$SERVER":81"$CAMINHO"  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" GET "y" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          1        |             1            |           0           |             0               |       1       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_000/file_777.txt"
 curl -X GET -I "$SERVER":81"$CAMINHO"  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" GET "y" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          1        |             1            |           0           |             1               |       0       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_000/file_000.txt/"
 curl -X GET -I "$SERVER":81"$CAMINHO"  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" GET "y" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          1        |             1            |           0           |             1               |       1       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_000/file_777.txt/"
 curl -X GET -I "$SERVER":81"$CAMINHO"  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" GET "y" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          1        |             1            |           1           |             0               |       0       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_777/file_000.txt"
 curl -X GET -I "$SERVER":81"$CAMINHO"  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" GET "y" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          1        |             1            |           1           |             0               |       1       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_777/file_777.txt"
 curl -X GET -I "$SERVER":81"$CAMINHO"  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" GET "y" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          1        |             1            |           1           |             1               |       0       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_777/file_000.txt/"
 curl -X GET -I "$SERVER":81"$CAMINHO"  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" GET "y" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          1        |             1            |           1           |             1               |       1       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_777/file_777.txt/"
 curl -X GET -I "$SERVER":81"$CAMINHO"  | grep "HTTP/1.1" | cut -d ' ' -f 2 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" GET "y" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt
