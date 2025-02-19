<?php
session_start();

// Verifica se o usuário está logado
if (!isset($_SESSION['username'])) {
    header("Location: index.php");
    exit();
}

$username = $_SESSION['username'];

// Função para logout
if (isset($_GET['logout'])) {
    session_destroy();
    header("Location: index.php");
    exit();
}

// Lógica de Upload de Arquivo
if ($_SERVER['REQUEST_METHOD'] == 'POST' && isset($_FILES['file'])) {
    $uploadDirectory = '../uploads/' . $username . '/';

    // Cria o diretório do usuário se não existir
    if (!is_dir($uploadDirectory)) {
        mkdir($uploadDirectory, 0777, true);
    }

    // Caminho do arquivo
    $uploadPath = $uploadDirectory . basename($_FILES['file']['name']);

    if (move_uploaded_file($_FILES['file']['tmp_name'], $uploadPath)) {
        // Redireciona após sucesso
        header("Location: upload.php?success=true");
        exit();
    } else {
        // Redireciona após erro
        header("Location: upload.php?error=true");
        exit();
    }
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Upload File</title>
    <link rel="stylesheet" href="styles.css">
</head>
<body>
    <!-- Barra de Navegação com Logout -->
    <div class="navbar">
 	<img src="images/fakebox_logo.png" alt="Logo">
        <a href="dashboard.php" class="link">Dashboard</a>
        <a href="#" class="link">Upload File</a>
        <a href="?logout=true" class="logout-btn">Logout</a>
    </div>

    <!-- Container principal -->
    <div class="container-dashboard">
        <h2>Upload a File</h2>

        <div class="upload-container">
            <form action="upload.php" method="POST" enctype="multipart/form-data">
                <label for="file">Choose a file to upload:</label>
                <input type="file" name="file" id="file" required>
                <button type="submit">Upload</button>
            </form>

            <!-- Mensagem de sucesso ou erro -->
            <div class="message">
                <?php
                    if (isset($_GET['success'])) {
                        echo "<p class='success'>File uploaded successfully!</p>";
                    } elseif (isset($_GET['error'])) {
                        echo "<p class='error'>Error uploading file!</p>";
                    }
                ?>
            </div>
        </div>
    </div>
</body>
</html>

