<!DOCTYPE html>

<?php
ini_set('display_errors', 1);
    ini_set('display_startup_errors', 1);
    error_reporting(E_ALL);

  $servername = "localhost";
  $username = "root";
  $password = "merlin1234";
  $dbname = "Air_Quality";

  $connect = mysqli_connect($servername, $username, $password);

  if (!$connect) {
    die(mysqli_error());
  }

  mysqli_select_db($connect, $dbname);

  
if( isset($_POST['sens_ID']) && !("" == trim($_POST['sens_ID'])))
{
  $temp = $_POST['sens_ID'];
  $query = "SELECT * FROM Results WHERE Sensor_ID = '{$temp}'";
}
elseif( isset($_POST['datestamp'])  && !("" == trim($_POST['datestamp'])))
{
  $date = strtotime($_POST['datestamp']);
  $temp = date('Y-m-d', $date);
  $query = "SELECT * FROM Results WHERE Date = '{$temp}'";
}
else{
  $query = "SELECT * FROM Results";
}

  $result = mysqli_query($connect, $query);
  $result2 = mysqli_query($connect, $query);
//AIzaSyBLK0daqB6GtQz_XCgDTaNzMW0wu7ONQHA //Google API key
?>


<html>
<head>
  <link rel="stylesheet" type="text/css" href="css/index.css">
  <link href='https://fonts.googleapis.com/css?family=Montserrat' rel='stylesheet' type='text/css'>
  <link rel="shortcut icon" href="/images/tab_icon.ico"/>
  <meta name="viewport" content="initial-scale=1.0, user-scalable=no">
  <title>Home</title>

    <link rel="stylesheet" href="//code.jquery.com/ui/1.12.1/themes/base/jquery-ui.css">
    <link rel="stylesheet" href="/resources/demos/style.css">
    <script src="https://code.jquery.com/jquery-1.12.4.js"></script>
    <script src="https://code.jquery.com/ui/1.12.1/jquery-ui.js"></script>
    <script>
    $( function() {
      $( "#datepicker" ).datepicker();
    } );
    </script>
  
</head>

<body>
<div align="center" class="topdiv">
    <h1>Bristol Air Quality & Pollution tracking</h1>
    <small>Merlin Roe - Final year project 2017</small>
</div>

<div class="gmaps">

  <div id="floating-panel">
      <input id="latlng" type="text" value="51.501771,-2.547841">
      <input id="submitGeo" type="button" value="Reverse Geocode">
    </div>

  <div id="map"></div>
  <script>
      function initMap() {
        var map = new google.maps.Map(document.getElementById('map'), {
          zoom: 15,
          center: {lat: 51.501771, lng: -2.547841}
        });
        var geocoder = new google.maps.Geocoder;
        var infowindow = new google.maps.InfoWindow;

        var heatmap = new google.maps.visualization.HeatmapLayer({
          data: getPoints(),
          //map: map
        });
        heatmap.setMap(map);
        heatmap.set('radius', 20)

        document.getElementsByClassName('submitGeo').addEventListener('click', function() {
          geocodeLatLng(geocoder, map, infowindow);
        });
      }

      function geocodeLatLng(geocoder, map, infowindow) {
        var input = document.getElementById('latlng').value;
        var latlngStr = input.split(',', 2);
        var latlng = {lat: parseFloat(latlngStr[0]), lng: parseFloat(latlngStr[1])};
        geocoder.geocode({'location': latlng}, function(results, status) {
          if (status === 'OK') {
            if (results[1]) {
              map.setZoom(15);
              var marker = new google.maps.Marker({
                position: latlng,
                map: map
              });
              infowindow.setContent(results[1].formatted_address);
              infowindow.open(map, marker);
            } else {
              window.alert('No results found');
            }
          } else {
            window.alert('Geocoder failed due to: ' + status);
          }
        });
      }

      function getPoints() {
        return [
          <?php
            while($row = mysqli_fetch_array($result)) {
              ?>
              {location: new google.maps.LatLng(<?php echo $row['Latitude']?>, <?php echo $row['Longitude']?>), weight: <?php echo $row['CO2'] / 400; ?>},
          <?php
            }
          ?>
        ];
      }
    </script>
    <script async defer
    src="https://maps.googleapis.com/maps/api/js?key=AIzaSyBLK0daqB6GtQz_XCgDTaNzMW0wu7ONQHA&libraries=visualization&callback=initMap">
    </script>
</div>

<div class="box">

<table id="linktable">
  <tr>
    <td bgcolor="#bababa"> Device ID </td>
    <td bgcolor="#bababa"> Date </td>
    <td bgcolor="#bababa"> Time </td>
    <td bgcolor="#bababa"> Temperature </td>
    <td bgcolor="#bababa"> Humidity </td>
    <td bgcolor="#bababa"> CO PPM</td>
    <td bgcolor="#bababa"> CO2 PPM</td>
    <td bgcolor="#bababa"> Particles</td>
    <td bgcolor="#bababa"> GPS</td>
  </tr>
  
  <?php
    while($row = mysqli_fetch_array($result2)) {
      ?>
      <tr>
        <td> <?php echo $row['Sensor_ID']?> </td>
        <td> <?php echo $row['Date']?> </td>
        <td> GMT: <?php echo $row['Time']?> </td>
        <td> <?php echo $row['Temperature']?>&deg;C</td>
        <td> <?php echo $row['Humidity']?>%</td>
        <td> <?php echo $row['CO']?> ppm</td>
        <td> <?php echo $row['CO2']?> ppm</td>
        <td> <?php echo $row['Particles']?> </td>
        <td> <input id="submitGeo" type="button" value="Reverse Geocode"> </td>
      </tr>
  <?php
    }
  ?>
</table>
</div>

<div class="querybox">
  <h2>Search:</h2><br>

  <form method="POST" action="index.php">
    Sensor ID: <input type="text" name="sens_ID"><br>
    <input type="Submit" value="Search"><br><br>
  </form>

  <form method="POST" action="index.php">
    Date: <input type="text" name="datestamp" id="datepicker"><br>
    <input type="Submit" value="Search">
  </form>

  <br>

  <form method="POST" action="index.php">
    <input type="Submit" value="Clear Search">
  </form>

</div>

</body>

</html>
