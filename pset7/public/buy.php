<?php

    // configuration
    require("../includes/config.php"); 
    
    // query DB for availavle cash
    $cash = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
    $balance = $cash[0]["cash"];
    

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // render portfolio
        render("buy_form.php", ["title" => "Buy"]);
    }

    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["symbol"]))
        {
            apologize("You must specify a stock to buy.");
        }
        else if (empty($_POST["shares"]))
        {
            apologize("You must specify a number of shares.");
        }
        
        else 
        {
            $stock = lookup(strtoupper($_POST["symbol"]));
            
            // chack either can the user afford the stock
            if ($balance < $stock["price"]*$_POST["shares"])
            {
                apologize("You can't afford that.");
            }

            //make sure that users can only buy whole shares of stocks, not fractions thereof
            else if (!preg_match("/^\d+$/", $_POST["shares"]))
            {
                apologize("Invalid number of shares.");
            }
            
            // if there is now Quote
            else if ($stock == false)
            {
                apologize("Symbol not found.");
            }
            // buy shares
            CS50::query("INSERT INTO portfolio (user_id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)",$_SESSION["id"], $stock["symbol"], $_POST["shares"]);
            
            //update balance
            CS50::query("UPDATE users SET cash = cash - ? WHERE id = ?", $stock["price"]*$_POST["shares"], $_SESSION["id"]);
            
            // log transaction
            CS50::query("INSERT INTO history (user_id, transaction, symbol, shares, price) VALUES(?, ?, ?, ?, ?)", $_SESSION["id"], 'BUY', $stock["symbol"], $_POST["shares"], $stock["price"]);
            
            // redirect to portfolio
            redirect("/");
        }
    }
    


?>
