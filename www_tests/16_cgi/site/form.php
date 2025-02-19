<?php
// Check if the form was submitted and store the values in cookies
if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    // Check if 'username' and 'email' fields were received
    if (isset($_POST['username']) && isset($_POST['email'])) {
        // Store the values of the fields in cookies (for 30 days)
        setcookie('username', $_POST['username'], time() + (30 * 24 * 60 * 60), "/"); // 30 days
        setcookie('email', $_POST['email'], time() + (30 * 24 * 60 * 60), "/"); // 30 days

        echo "Username: " . htmlspecialchars($_POST['username']) . "<br>\n";
        echo "Email: " . htmlspecialchars($_POST['email']) . "<br>\n";
    } else {
        echo "Error: Data not received correctly.<br>\n";
    }
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Simple File Upload</title>
</head>
<body>
    <h2>Form</h2>
    <form action="/form.php" method="POST" enctype="multipart/form-data">
        <!-- Fill in the fields with the cookie values if they exist -->
        <input type="text" name="username" value="<?php echo isset($_COOKIE['username']) ? htmlspecialchars($_COOKIE['username']) : ''; ?>" />
        <input type="text" name="email" value="<?php echo isset($_COOKIE['email']) ? htmlspecialchars($_COOKIE['email']) : ''; ?>" />
        <input type="submit" />
    </form>
</body>
</html>
