<?php
session_start();

// Verifica se o usuário está logado
if (!isset($_SESSION['username'])) {
    header("Location: index.php");
    exit();
}

$username = $_SESSION['username'];
$uploadDirectory = '../' . 'uploads/' . $username . '/';

// Função para logout
if (isset($_GET['logout'])) {
    session_destroy();
    header("Location: index.php");
    exit();
}

// Função para excluir arquivo
if (isset($_GET['delete'])) {
    $fileToDelete = $_GET['delete'];
    $filePath = $uploadDirectory . $fileToDelete;

    if (file_exists($filePath)) {
        unlink($filePath); // Exclui o arquivo
        header("Location: dashboard.php?deleted=true");
        exit();
    } else {
        header("Location: dashboard.php?error=true");
        exit();
    }
}

// Função para download de arquivo
if (isset($_GET['download'])) {
    $fileToDownload = $_GET['download'];
    $filePath = $uploadDirectory . $fileToDownload;

    if (file_exists($filePath)) {
        // Configura cabeçalhos para forçar o download do arquivo
        header('Content-Description: File Transfer');
        header('Content-Type: application/octet-stream');
        header('Content-Disposition: attachment; filename="' . basename($filePath) . '"');
        header('Content-Length: ' . filesize($filePath));
        readfile($filePath);
        exit();
    } else {
        header("Location: dashboard.php?error=true");
        exit();
    }
}

// Listar arquivos do usuário
$files = [];
if (is_dir($uploadDirectory)) {
    $files = array_diff(scandir($uploadDirectory), array('.', '..'));
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Dashboard</title>
    <link rel="stylesheet" href="styles.css">
</head>
<body>
    <!-- Barra de Navegação com Logout -->
    <div class="navbar">
 	<img src="images/fakebox_logo.png" alt="Logo">
        <a href="dashboard.php" class="link">Dashboard</a>
        <a href="upload.php" class="link">Upload File</a>
        <a href="?logout=true" class="logout-btn">Logout</a>
    </div>

    <!-- Container do Dashboard -->
    <div class="container-dashboard">
        <h2>Welcome, <?php echo htmlspecialchars($username); ?>!</h2>

        <!-- Mensagem de Sucesso ou Erro -->
        <div class="message">
            <?php
                if (isset($_GET['deleted'])) {
                    echo "<p class='success'>File deleted successfully!</p>";
                } elseif (isset($_GET['error'])) {
                    echo "<p class='error'>Error deleting file!</p>";
                }
            ?>
        </div>

        <h3>Your Uploaded Files</h3>
        <table class="file-table">
            <tr>
                <th>File Name</th>
                <th>Action</th>
            </tr>
            <?php if (empty($files)): ?>
                <tr>
                    <td colspan="2">No files uploaded yet.</td>
                </tr>
            <?php else: ?>
                <?php foreach ($files as $file): ?>
                    <tr>
                        <td><?php echo htmlspecialchars($file); ?></td>
                        <td>
                            <a href="?download=<?php echo urlencode($file); ?>" class="download-btn">Download</a>
                            <a href="?delete=<?php echo urlencode($file); ?>" class="delete-btn">Delete</a>
                        </td>
                    </tr>
                <?php endforeach; ?>
            <?php endif; ?>
        </table>
    </div>
</body>
</html>

