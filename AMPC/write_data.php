<?php 
	$dbusername="epiz_24159024";
	$dbpassword="q@6sQr@RXHAm@s2";
	$server="sql211.byetcluster.com";
	$My_db="epiz_24159024_accident_data";

	$dbconnect=mysql_pconnect($server,$dbusername,$dbpassword);
	$dbselect=mysql_select_db($My_db,$dbconnect);

	$sql="INSERT INTO SAVE_DATA (Latitude,Longitude) VALUES ('".$_GET["data1"]."','".$_GET["data2"]."')";

	mysql_query($sql);

 ?>