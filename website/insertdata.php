<?php
    ini_set('display_errors', 1);
    ini_set('display_startup_errors', 1);
    error_reporting(E_ALL);

    if(isset($_GET['humid'])){

        $servername = "localhost";
        $username = "root";
        $password = "merlin1234";
        $dbname = "Air_Quality";

        $connect = mysqli_connect($servername, $username, $password);

        if (!$connect) {
            die(mysqli_error());
        }

        mysqli_select_db($connect, $dbname);

        $sens_ID = $_GET['sensor_ID'];
        $temp = $_GET['temp'];
        $humid = $_GET['humid'];
        $COt = $_GET['CO2'];
        $particles = $_GET['parti'];
        $gps = $_GET['gps'];

        //GPRMC,113037.000,A,5129.5736,N,00234.5809,W,0.26,103.64,090517,,,A*7C
        //lat: 5129.5736,N
        //long: 00234.5809,W
        $gprmc = explode(',',$gps);

        $date = $gprmc[9];
        $date = substr_replace($date, "/20", 4,0);
        $date = substr_replace($date, "/", 2,0);
        $date = date("Y-m-d", strtotime($date));

        $time = substr($gprmc[1],0,6);
        $time = substr_replace($time, ":", 4,0);
        $time = substr_replace($time, ":", 2,0);

        $lat = degree2decimal($gprmc[3] + $gprmc[4]);
        $long = degree2decimal($gprmc[5] . $gprmc[6]);


        $insert = "INSERT INTO Results (Sensor_ID, Date, Time, Temperature, Humidity, CO2, Particles, Latitude, Longitude) 
        VALUES ('{$sens_ID}', '{$date}', '{$time}', '{$temp}', '{$humid}', '{$COt}', 
        '{$particles}', '{$lat}', '{$long}')";


        if(mysqli_query($connect, $insert)){

            echo "Records inserted successfully.";

        } else{

            echo "ERROR: Could not able to execute $insert. " . mysqli_error($connect);

        }
    }
    else{
        echo "FUCK";
        echo $_GET['sensor_ID'];
    }

    function degree2decimal($deg_coord){
        //reference http://www.directionsmag.com/site/latlong-converter
        //GPS/NMEA fixes are in Degree Minutes.m format
        //for Google maps we need to convert them to decimal degrees
        //sample format of GPS 4533.35 is 45 degrees and 33.35 minutes
        //formula is as follows//Degrees=Degrees 
        //.d = M.m/60//Decimal Degrees=Degrees+.d

        $degree=(int)($deg_coord/100); //simple way
        $minutes= $deg_coord-($degree*100);
        $dotdegree=$minutes/60;
        $decimal=$degree+$dotdegree;
        $direction=substr($deg_coord,-1);

        //South latitudes and West longitudes need to return a negative result
        if (($direction=="S") or ($direction=="W"))       
        { 
            $decimal=$decimal*(-1);
        }
        $decimal=number_format($decimal,4,'.',''); //truncate decimal to 4 places
        return $decimal;
    }


    //Used like so:
    //http://10.0.2.15/insertdata.php?sensor_ID=1&date=2017-03-22&time=12:00:32&temp=17&humid=75&CO=100&CO2=45&parti=3000&lat=423.32&lat_ori=N&long=356.32&long_ori=E

    ///
    //http://10.0.2.15/insertdata.php?sensor_ID=1&temp=21.50&humid=45&CO2=251&parti=567&gps=$GPRMC,113037.000,A,5129.5736,N,00234.5809,W,0.26,103.64,090517,,,A*7C
    ///insertdata.php?sensor_ID=1&temp=22.40&humid=49&CO2=372&parti=2531.06&gps=$GPRMC,113037.000,A,5129.5736,N,00234.5809,W,0.26,103.64,090517,,,A*7C
?>