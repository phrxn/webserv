<?php
session_start();

// Check if the user is logged in
if (!isset($_SESSION['user'])) {
    header('Location: login.php');
    exit();
}

// Add product to cart
if (isset($_GET['add'])) {
    $product = $_GET['add'];
    $_SESSION['cart'][] = $product;
}

// Get the cart items
$cart = isset($_SESSION['cart']) ? $_SESSION['cart'] : [];
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Shopping Cart</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <div class="container">
        <h2>Your Shopping Cart</h2>

        <?php if (empty($cart)): ?>
            <p>Your cart is empty.</p>
        <?php else: ?>
            <ul>
                <?php foreach ($cart as $item): ?>
                    <li><?php echo $item; ?></li>
                <?php endforeach; ?>
            </ul>
        <?php endif; ?>

        <h3>Available Products</h3>
        <ul>
            <li><a href="cart.php?add=Product 1">Add Product 1</a></li>
            <li><a href="cart.php?add=Product 2">Add Product 2</a></li>
            <li><a href="cart.php?add=Product 3">Add Product 3</a></li>
        </ul>

        <a href="index.php">Back to Home</a>
    </div>
</body>
</html>
