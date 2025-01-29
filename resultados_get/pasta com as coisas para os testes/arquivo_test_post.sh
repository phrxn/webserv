#!/bin/bash

SERVER="localhost"

 rm -rf result.txt
 echo -ne "ARQUIVO\n" >> result.txt
 echo -ne "  POST\n" >> result.txt
 echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          0        |             0            |           0           |             0               |       0       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_000/not_exis.txt"
  curl -v -X POST -F "file=@file_to_upload.txt" "$SERVER":80"$CAMINHO"  2>&1 | grep "HTTP/1.1 " | cut -d ' ' -f 3 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" POST "n" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          0        |             0            |           0           |             0               |       1       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_000/not_exis.txt"
  curl -v -X POST -F "file=@file_to_upload.txt" "$SERVER":80"$CAMINHO"  2>&1 | grep "HTTP/1.1 " | cut -d ' ' -f 3 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" POST "n" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          0        |             0            |           0           |             1               |       0       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_000/not_exis.txt/"
  curl -v -X POST -F "file=@file_to_upload.txt" "$SERVER":80"$CAMINHO"  2>&1 | grep "HTTP/1.1 " | cut -d ' ' -f 3 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" POST "n" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          0        |             0            |           0           |             1               |       1       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_000/not_exis.txt/"
  curl -v -X POST -F "file=@file_to_upload.txt" "$SERVER":80"$CAMINHO"  2>&1 | grep "HTTP/1.1 " | cut -d ' ' -f 3 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" POST "n" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          0        |             0            |           1           |             0               |       0       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_777/not_exis.txt"
  curl -v -X POST -F "file=@file_to_upload.txt" "$SERVER":80"$CAMINHO"  2>&1 | grep "HTTP/1.1 " | cut -d ' ' -f 3 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" POST "n" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          0        |             0            |           1           |             0               |       1       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_777/not_exis.txt"
  curl -v -X POST -F "file=@file_to_upload.txt" "$SERVER":80"$CAMINHO"  2>&1 | grep "HTTP/1.1 " | cut -d ' ' -f 3 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" POST "n" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          0        |             0            |           1           |             1               |       0       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_777/not_exis.txt/"
  curl -v -X POST -F "file=@file_to_upload.txt" "$SERVER":80"$CAMINHO"  2>&1 | grep "HTTP/1.1 " | cut -d ' ' -f 3 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" POST "n" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          0        |             0            |           1           |             1               |       1       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_777/not_exis.txt/"
  curl -v -X POST -F "file=@file_to_upload.txt" "$SERVER":80"$CAMINHO"  2>&1 | grep "HTTP/1.1 " | cut -d ' ' -f 3 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" POST "n" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          0        |             1            |           0           |             0               |       0       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_000/not_exis.txt"
  curl -v -X POST -F "file=@file_to_upload.txt" "$SERVER":81"$CAMINHO"  2>&1 | grep "HTTP/1.1 " | cut -d ' ' -f 3 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" POST "y" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          0        |             1            |           0           |             0               |       1       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_000/not_exis.txt"
  curl -v -X POST -F "file=@file_to_upload.txt" "$SERVER":81"$CAMINHO"  2>&1 | grep "HTTP/1.1 " | cut -d ' ' -f 3 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" POST "y" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          0        |             1            |           0           |             1               |       0       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_000/not_exis.txt/"
  curl -v -X POST -F "file=@file_to_upload.txt" "$SERVER":81"$CAMINHO"  2>&1 | grep "HTTP/1.1 " | cut -d ' ' -f 3 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" POST "y" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          0        |             1            |           0           |             1               |       1       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_000/not_exis.txt/"
  curl -v -X POST -F "file=@file_to_upload.txt" "$SERVER":81"$CAMINHO"  2>&1 | grep "HTTP/1.1 " | cut -d ' ' -f 3 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" POST "y" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          0        |             1            |           1           |             0               |       0       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_777/not_exis.txt"
  curl -v -X POST -F "file=@file_to_upload.txt" "$SERVER":81"$CAMINHO"  2>&1 | grep "HTTP/1.1 " | cut -d ' ' -f 3 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" POST "y" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          0        |             1            |           1           |             0               |       1       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_777/not_exis.txt"
  curl -v -X POST -F "file=@file_to_upload.txt" "$SERVER":81"$CAMINHO"  2>&1 | grep "HTTP/1.1 " | cut -d ' ' -f 3 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" POST "y" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          0        |             1            |           1           |             1               |       0       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_777/not_exis.txt/"
  curl -v -X POST -F "file=@file_to_upload.txt" "$SERVER":81"$CAMINHO"  2>&1 | grep "HTTP/1.1 " | cut -d ' ' -f 3 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" POST "y" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          0        |             1            |           1           |             1               |       1       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_777/not_exis.txt/"
  curl -v -X POST -F "file=@file_to_upload.txt" "$SERVER":81"$CAMINHO"  2>&1 | grep "HTTP/1.1 " | cut -d ' ' -f 3 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" POST "y" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt






#=====================================






#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          1        |             0            |           0           |             0               |       0       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_000/file_000.txt"
  curl -v -X POST -F "file=@file_to_upload.txt" "$SERVER":80"$CAMINHO"  2>&1 | grep "HTTP/1.1 " | cut -d ' ' -f 3 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" POST "n" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          1        |             0            |           0           |             0               |       1       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_000/file_777.txt"
  curl -v -X POST -F "file=@file_to_upload.txt" "$SERVER":80"$CAMINHO"  2>&1 | grep "HTTP/1.1 " | cut -d ' ' -f 3 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" POST "n" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          1        |             0            |           0           |             1               |       0       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_000/file_000.txt/"
  curl -v -X POST -F "file=@file_to_upload.txt" "$SERVER":80"$CAMINHO"  2>&1 | grep "HTTP/1.1 " | cut -d ' ' -f 3 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" POST "n" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          1        |             0            |           0           |             1               |       1       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_000/file_777.txt/"
  curl -v -X POST -F "file=@file_to_upload.txt" "$SERVER":80"$CAMINHO"  2>&1 | grep "HTTP/1.1 " | cut -d ' ' -f 3 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" POST "n" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          1        |             0            |           1           |             0               |       0       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_777/file_000.txt"
  curl -v -X POST -F "file=@file_to_upload.txt" "$SERVER":80"$CAMINHO"  2>&1 | grep "HTTP/1.1 " | cut -d ' ' -f 3 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" POST "n" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          1        |             0            |           1           |             0               |       1       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_777/file_777.txt"
  curl -v -X POST -F "file=@file_to_upload.txt" "$SERVER":80"$CAMINHO"  2>&1 | grep "HTTP/1.1 " | cut -d ' ' -f 3 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" POST "n" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          1        |             0            |           1           |             1               |       0       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_777/file_000.txt/"
  curl -v -X POST -F "file=@file_to_upload.txt" "$SERVER":80"$CAMINHO"  2>&1 | grep "HTTP/1.1 " | cut -d ' ' -f 3 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" POST "n" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          1        |             0            |           1           |             1               |       1       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_777/file_777.txt/"
  curl -v -X POST -F "file=@file_to_upload.txt" "$SERVER":80"$CAMINHO"  2>&1 | grep "HTTP/1.1 " | cut -d ' ' -f 3 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" POST "n" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          1        |             1            |           0           |             0               |       0       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_000/file_000.txt"
  curl -v -X POST -F "file=@file_to_upload.txt" "$SERVER":81"$CAMINHO"  2>&1 | grep "HTTP/1.1 " | cut -d ' ' -f 3 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" POST "y" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          1        |             1            |           0           |             0               |       1       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_000/file_777.txt"
  curl -v -X POST -F "file=@file_to_upload.txt" "$SERVER":81"$CAMINHO"  2>&1 | grep "HTTP/1.1 " | cut -d ' ' -f 3 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" POST "y" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          1        |             1            |           0           |             1               |       0       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_000/file_000.txt/"
  curl -v -X POST -F "file=@file_to_upload.txt" "$SERVER":81"$CAMINHO"  2>&1 | grep "HTTP/1.1 " | cut -d ' ' -f 3 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" POST "y" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          1        |             1            |           0           |             1               |       1       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_000/file_777.txt/"
  curl -v -X POST -F "file=@file_to_upload.txt" "$SERVER":81"$CAMINHO"  2>&1 | grep "HTTP/1.1 " | cut -d ' ' -f 3 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" POST "y" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          1        |             1            |           1           |             0               |       0       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_777/file_000.txt"
  curl -v -X POST -F "file=@file_to_upload.txt" "$SERVER":81"$CAMINHO"  2>&1 | grep "HTTP/1.1 " | cut -d ' ' -f 3 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" POST "y" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          1        |             1            |           1           |             0               |       1       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_777/file_777.txt"
  curl -v -X POST -F "file=@file_to_upload.txt" "$SERVER":81"$CAMINHO"  2>&1 | grep "HTTP/1.1 " | cut -d ' ' -f 3 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" POST "y" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          1        |             1            |           1           |             1               |       0       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_777/file_000.txt/"
  curl -v -X POST -F "file=@file_to_upload.txt" "$SERVER":81"$CAMINHO"  2>&1 | grep "HTTP/1.1 " | cut -d ' ' -f 3 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" POST "y" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt

#echo -ne "    arquivo existe | dir pai pode ser listado | dir pai pode ser lido | tem barra no fim do caminho | pode ser lido | RESULTADO (nginx) | (myProgram) |\n" >> result.txt
 echo -ne "          1        |             1            |           1           |             1               |       1       |        "           >> result.txt ;
 CAMINHO="/var/www/html/dir_777/file_777.txt/"
  curl -v -X POST -F "file=@file_to_upload.txt" "$SERVER":81"$CAMINHO"  2>&1 | grep "HTTP/1.1 " | cut -d ' ' -f 3 | tr -d '\n'                                    >> result.txt ; echo -ne "        |     " >> result.txt
 ./myProgram "$CAMINHO" POST "y" | tr -d '\n' >> result.txt ;  echo -ne "     |\n" >> result.txt
