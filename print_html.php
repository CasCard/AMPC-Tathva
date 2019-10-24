<html>
<head>
    <title>Accident Log</title>
    <meta charset="UTF-8">
    <link href="https://fonts.googleapis.com/css?family=Roboto&display=swap" rel="stylesheet">
    <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.0/css/bootstrap.min.css">
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
  <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.0/js/bootstrap.min.js"></script>
    <style>
    body{
        font-family: 'Roboto', sans-serif;
        text-align:center;
        margin:0px;
        padding:0px;
        
        }
    table{
        padding: 30px;
        border-radius: 25px;
        width:60%;
        border-collapse:collapse;
        box-shadow: 5px 5px 3px 3px #f0f0f0;
    }
    th,td{
        text-align: left;
    }
    tr:hover{
        background-color:#f5f5f5;
    }
    th{
        height:50px;
        text-align:left;
        padding:15px;
        
    }
    td{
        padding:15px;
        vertical-align:bottom;
    }
    tr:nth-child(even){
        background-color:#f2f2f2;
    }
    table.center{
        margin-left:auto;
        margin-right:auto;
    }
    .footer {
   position: fixed;
   left: 0;
   bottom: 0;
   width: 100%;
   background-color: red;
   color: black;
   text-align: center;
}

.footer {
  position: absolute;
  right: 0;
  bottom: 0;
  left: 0;
  padding: 1rem;
  background-color: #efefef;
  text-align: center;
}
    
    </style>
</head>
<body>
<nav class="navbar navbar-inverse">
  <div class="container-fluid">
    <div class="navbar-header">
      <a class="navbar-brand" href="#">Acci Portal</a>
    </div>
    <ul class="nav navbar-nav">
      <li class="active"><a href="#">Home</a></li>
      <li><a href="#">News</a></li>
      <li><a href="#">Contact</a></li>
      <li><a href="#">About</a></li>
    </ul>
    
    <!--<button class="btn btn-danger navbar-btn">Button</button>-->
 
    
    
  </div>
</nav>

<?php
$user="abelcd";
$password="abelcd@2001";
$server="localhost";
$dbname ="accident_data";

$con=mysqli_connect($server,$user,$password,$dbname);
// Check connection
if (mysqli_connect_errno())
{
echo "Failed to connect to MySQL: " . mysqli_connect_error();
}

$result = mysqli_query($con,"SELECT * FROM accident_log");

echo "<table class='table table-striped'>
<tr>
<th scope='col'>ID</th>
<th scope='col'>Time</th>
<th scope='col'>Latitude</th>
<th scope='col'>Longitude</th>
<th scope='col'>Link</th>
</tr>";

while($row = mysqli_fetch_array($result))
{
echo "<tr>";
echo "<td>" . $row['ID'] . "</td>";
echo "<td>" . $row['Time'] . "</td>";
echo "<td>" . $row['Latitude'] . "</td>";
echo "<td>" . $row['Longitude'] . "</td>";
echo '<td><a href="' . $row['Link'] . '">' . $row['Link'] . '</a></td>';
// echo "<td>" . $row['Link'] . "</td>";
echo "</tr>";
}
echo "</table>";

mysqli_close($con);
?>
</body>
</html>