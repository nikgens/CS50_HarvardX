#!/usr/bin/env php

<?php
    // configuration
    require("../includes/config.php");   
    
$file = $argv[1];
if (!file_exists($file)) 
{
    echo "The file $file not exists\n";
}
else
{
    if (($handle = fopen($file, "r")) !== FALSE) 
    {
        while (($data = fgetcsv($handle, 1000, "\t")) !== FALSE) 
        {
            CS50::query("INSERT INTO places (country_code,postal_code,place_name,admin_name1,admin_code1,admin_name2,admin_code2,admin_name3,admin_code3,latitude,longitude,accuracy)
            VALUES (?,?,?,?,?,?,?,?,?,?,?,?)", $data[0],$data[1],$data[2],$data[3],$data[4],$data[5],$data[6],$data[7],$data[8],$data[9],$data[10],$data[11]);
        }
        fclose($handle);
    }
}

?>