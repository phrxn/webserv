<?php
session_start();
session_destroy();  // Destroy all session variables
header('Location: login.php');  // Redirect to login page
exit();
?>
