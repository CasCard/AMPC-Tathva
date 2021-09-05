<!DOCTYPE html>
<html>
<head>
	<title>Accident Log</title>
</head>
<body>
	<table>
		<thead>
			<tr>
				<td>ID</td>
				<td>Date and Time</td>
				<td>Latitude</td>
				<td>Longitude</td>
				<td>Link</td>
			</tr>
		</thead>
<tbody>

<?php 
	$user="epiz_24159024";
	$password="abelcd2001";
	$server="sql211.byetcluster.com";

	$db=mysql_connect($server,$user,$password);
	if(!$db){
		die('Not Connected : '.mysql_error());
	}
	$dbname ="epiz_24159024_accident_data";
	
	$db_select=mysal_select_db($dbname,$db);
		if (!$db_select) {
				# code...
				die("Database selection also failed miserably :".mysql_error());
			}

	$results = mysql_query("SELECT ID, Time, Latitude, Longitude, Link FROM accident_log");
		while ($row = mysql_fetch_array($results)) {
		?>
			<tr>
				<td><?php $row['ID']?></td>
				<td><?php $row['Time']?></td>
				<td><?php $row['Latitude']?></td>
				<td><?php $row['Longitude']?></td>
				<td><?php $row['Link']?></td>
			</tr>	
		<?php
		}
		?>
	</tbody>
</table>
</body>
</html>