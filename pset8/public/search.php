<?php

    require(__DIR__ . "/../includes/config.php");

    // numerically indexed array of places
    $places = [];

    // TODO: search database for places matching $_GET["geo"], store in $places
    $searchResult = CS50::query("SELECT * FROM places WHERE MATCH(postal_code, place_name, admin_name1) AGAINST (?)", $_GET["geo"]);

    foreach ($searchResult as $row) 
    {
        $places[] = [ 
            'country_code' => $row['country_code'],
            'postal_code' => $row['postal_code'],
            'place_name' => $row['place_name'],
            'admin_name1' => $row['admin_name1'],
            'admin_code1' => $row['admin_code1'],
            'admin_name2' => $row['admin_name2'],
            'admin_code2' => $row['admin_code2'],
            'admin_name3' => $row['admin_name3'],
            'admin_code3' => $row['admin_code3'],
            'latitude' => $row['latitude'],
            'longitude' => $row['longitude'],
            'accuracy' => $row['accuracy']
        ];
    }


    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));

?>