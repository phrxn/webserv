<?php
// Get the HTTP method used
$method = $_SERVER['REQUEST_METHOD'];

// Set the background color and message based on the HTTP method
switch ($method) {
    case 'GET':
        $background_color = 'lightgreen';  // Light green for GET
        $message = 'GET';
        break;
    case 'POST':
        $background_color = 'cyan';  // Cyan for POST
        $message = 'POST';
        break;
    case 'DELETE':
        $background_color = 'lightcoral';  // Light red for DELETE
        $message = 'DELETE';
        break;
    default:
        $background_color = 'white';  // Default background
        $message = 'Unsupported Method';
        break;
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>HTTP Verb Display</title>
    <style>
        body {
            background-color: <?php echo $background_color; ?>;
            height: 100vh;
            margin: 0;
            display: flex;
            justify-content: center;
            align-items: center;
            text-align: center;
            flex-direction: column;
        }
        h2 {
            font-size: 2em;
            color: black;
        }
        button {
            padding: 10px 20px;
            margin: 10px;
            font-size: 1.2em;
            cursor: pointer;
            background-color: #4CAF50; /* Green background */
            border: none;
            color: white;
            border-radius: 5px;
        }
        button:hover {
            background-color: #45a049; /* Darker green on hover */
        }
    </style>
</head>
<body>
    <h2 id="methodMessage"><?php echo $message; ?></h2>

    <!-- Button to send POST request -->
    <button id="postButton">Send POST Request</button>

    <!-- Button to send DELETE request -->
    <button id="deleteButton">Send DELETE Request</button>

    <script>
        // Function to update page based on the response from the server
        function updatePage(responseText, backgroundColor, methodMessage) {
            // Update the body background color and the h2 message
            document.body.style.backgroundColor = backgroundColor;
            document.getElementById('methodMessage').innerHTML = methodMessage;
        }

        // Send POST request
        document.getElementById('postButton').addEventListener('click', function() {
            fetch('/form.php', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/x-www-form-urlencoded',
                },
                body: 'username=JohnDoe&email=john.doe@example.com'
            })
            .then(response => response.text())
            .then(data => {
                // Update the page without reloading
                updatePage(data, 'cyan', 'POST');
            })
            .catch(error => console.error('Error:', error));
        });

        // Send DELETE request
        document.getElementById('deleteButton').addEventListener('click', function() {
            fetch('/form.php', {
                method: 'DELETE',
            })
            .then(response => response.text())
            .then(data => {
                // Update the page without reloading
                updatePage(data, 'lightcoral', 'DELETE');
            })
            .catch(error => console.error('Error:', error));
        });
    </script>
</body>
</html>
