<?php

    // configuration
    require("../includes/config.php"); 

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // query database for history
        $rows = CS50::query("SELECT * FROM history WHERE user_id = ? ORDER BY timestamp DESC", $_SESSION["id"]);

        $positions = [];
        foreach ($rows as $row)
        {
            $positions[] = [
                "transaction" => $row["transaction"],
                "timestamp" => $row["timestamp"],
                "symbol" => $row["symbol"],
                "shares" => $row["shares"],
                "price" => $row["price"],
                ];
        }
    
        // render portfolio
        render("history.php", ["positions" => $positions, "title" => "History"]);
    }
    
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        CS50::query("DELETE FROM history WHERE user_id = ?", $_SESSION["id"]);
        // redirect to portfolio
        redirect("/");

    }
    
    
?>