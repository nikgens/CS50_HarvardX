<?php

    // configuration
    require("../includes/config.php"); 
    

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // render portfolio
        render("account_form.php", ["title" => "Account"]);
    }
    
    
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["amount"]))
        {
            apologize("You must choose the amount.");
        }
        
        else 
        {
            
            //update balance
            CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $_POST["amount"], $_SESSION["id"]);
            
            
            // redirect to portfolio
            redirect("/");
        }
    }
    


?>
