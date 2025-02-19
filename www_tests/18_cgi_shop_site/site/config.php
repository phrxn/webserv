<?php
// Start session
session_start();

// Check if user is logged in
if (!isset($_SESSION['user'])) {
    header('Location: login.php');  // Redirect to login if not logged in
    exit();
}
?>
