<?php
session_start();

// Processar o login
if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    $username = $_POST['username'];
    $password = hash('sha256', $_POST['password']); // Hash da senha

    // Ler o arquivo CSV de usuários
    $file = fopen('../users.csv', 'r');
    $loggedIn = false;

    while (($row = fgetcsv($file)) !== false) {
        if ($row[0] === $username && $row[1] === $password) {
            $_SESSION['loggedin'] = true;
            $_SESSION['username'] = $username;
            $loggedIn = true;
            break;
        }
    }

    fclose($file);

    if ($loggedIn) {
        header('Location: dashboard.php');
        exit;
    } else {
        echo "Invalid username or password! <a href=\"index.php\"> home </a>";
    }
}
?>

