<?php

    // configuration
    require("../includes/config.php"); 
    
    // query database for user
    $rows = CS50::query("SELECT * FROM portfolio WHERE user_id = ?", $_SESSION["id"]);
    
    $positions = [];
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
                "name" => $stock["name"],
                "price" => $stock["price"],
                "shares" => $row["shares"],
                "symbol" => $row["symbol"]
            ];
        }
    }
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        if (empty($rows))
        {
            apologize("Nothing to sell.");
        }
        
        // render portfolio
        render("sell_form.php", ["positions" => $positions, "title" => "Sell"]);
    }
    
    
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["symbol"]))
        {
            apologize("You must select a stock to sell.");
        }
        
        else 
        {
            //delete row with selected shares
            CS50::query("DELETE FROM portfolio WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
            
            //update balance
            CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $stock["price"]*$row["shares"], $_SESSION["id"]);
            
            // log transaction
            CS50::query("INSERT INTO history (user_id, transaction, symbol, shares, price) VALUES(?, ?, ?, ?, ?)", $_SESSION["id"], 'SELL', $row["symbol"], $row["shares"], $stock["price"]);
            
            // redirect to portfolio
            redirect("/");
        }
    }
    


?>
