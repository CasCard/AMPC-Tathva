<?php
$servername = "localhost";
$username = "abelcd";
$password = "abelcd@2001";
$dbname = "accident_data";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$sql = "INSERT INTO accident_log (Latitude, Longitude, Link)
VALUES ('".$_GET["lat"]."','".$_GET["lon"]."','".$_GET["lin"]."')";

if ($conn->query($sql) === TRUE) {
    echo "New record created successfully";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}

$conn->close();
?>
