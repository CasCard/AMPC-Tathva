<!DOCTYPE html>
<html>
<head>
	<title>Accident Log</title>
</head>
<body>
	<?php
$user="epiz_24159024";
$password="abelcd2001";
$server="sql211.byetcluster.com";
$dbname ="epiz_24159024_accident_data";
$con=mysqli_connect($server,$user,$password,$dbname);
// Check connection
if (mysqli_connect_errno())
{
echo "Failed to connect to MySQL: " . mysqli_connect_error();
}

$result = mysqli_query($con,"SELECT * FROM accident_log");

echo "<table border='1'>
<tr>
<th>ID</th>
<th>Time</th>
<th>Latitude</th>
<th>Longitude</th>
<th>Link</th>
</tr>";

while($row = mysqli_fetch_array($result))
{
echo "<tr>";
echo "<td>" . $row['ID'] . "</td>";
echo "<td>" . $row['Time'] . "</td>";
echo "<td>" . $row['Latitude'] . "</td>";
echo "<td>" . $row['Longitude'] . "</td>";
echo "<td>" . $row['Link'] . "</td>";
echo "</tr>";
}
echo "</table>";

mysqli_close($con);
?>
</body>
</html>
