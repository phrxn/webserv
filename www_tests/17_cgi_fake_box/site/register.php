<?php

$user_created = false;
// Verifica se o formulário foi enviado
if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    $username = $_POST['username'];
    $password = hash('sha256', $_POST['password']); // Hash da senha

    // Verifica se o arquivo CSV de usuários existe. Se não, cria um novo.
    $filename = '../users.csv';
    if (!file_exists($filename)) {
        // Cria o arquivo se não existir
        fopen($filename, 'w');
    }

    // Lê os usuários já cadastrados
    $file = fopen($filename, 'r');
    $userExists = false;

    while (($row = fgetcsv($file)) !== false) {
        if ($row[0] === $username) {
            $userExists = true; // Usuário já existe
            break;
        }
    }

    fclose($file);

    // Se o usuário já existir, retorna mensagem
    if ($userExists) {
    	echo "<script>alert('Username already taken!');</script>";
    } else {
        // Se o usuário não existe, salva no arquivo CSV
        $file = fopen($filename, 'a');  // Abre o arquivo para anexar
        if ($file) {
            fputcsv($file, [$username, $password]); // Salva o novo usuário no arquivo
            fclose($file);

            // Cria a pasta do usuário para uploads
            mkdir("../uploads/$username");

	    echo "<script>alert('User has been registered! Welcome " . $username . "');</script>";
	    $user_created = true;
        } else {
            echo "Error saving user data!";
        }
    }
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Register</title>
    <link rel="stylesheet" href="styles.css">
</head>
<body class="body_back">
   <div class="overlay"></div>
    <div class="register-container">
        <h2>Register</h2>
<?php
if ($user_created){
       echo '<p>User created return to home: <a href="index.php">Login</a></p>';
}else{
       echo '<form method="POST" action="register.php">';
       echo '    <input type="text" name="username" placeholder="Username" required>';
       echo '     <input type="password" name="password" placeholder="Password" required>';
       echo '    <button type="submit">Register</button>';
       echo '</form>';
       echo '<p>Already have an account? <a href="index.php">Login here</a></p>';
     }
?>
    </div>
</body>
</html>

