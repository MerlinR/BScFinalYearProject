<?php

$gps = "GPRMC,113037.000,A,5129.5736,N,00234.5809,W,0.26,103.64,090517,,,A*7C";
print("starts<br>");
print($gps);


$buffer = $gps;
if(substr($buffer, 0, 5)=='GPRMC'){

    print(DMStoDEC($buffer));

    echo "\n\n";
}


function DMStoDEC($gps)
{
    $gprmc = explode(',',$gps);

    
} 

  print("end<br>");
  ?>