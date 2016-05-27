<?php
    
    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // if is empty 
        if (empty($_POST["username"]))
        {
            apologize("You must provide a username.");
        }
        // if is empty 
        if (!ctype_alpha($_POST["username"]))
        {
            apologize("You can use only alphabetic characters in your account.");
        }
        
        // if is empty 
        else if (empty($_POST["password"]))
        {
            apologize("You must provide a password.");
        }
        
        // if not enougth long 
        else if (strlen($_POST["password"]) < 5)
        {
            apologize("Password must be at least 5 characters long.");
        }
        // if password and confirmation not equal
        else if ($_POST["password"] !== $_POST["confirmation"])
        {
            apologize("Those passwords did not match.");
        }
        
        
        
        else 
        {
            $rowIns = CS50::query("INSERT IGNORE INTO users (username, hash, cash) VALUES(?, ?, 10000.0000)", $_POST["username"], password_hash($_POST["password"], PASSWORD_DEFAULT));
            
            if ($rowIns === false)
            {
                apologize("That username appears to be taken.");
            }
            else 
            {
                $rows = CS50::query("SELECT LAST_INSERT_ID() AS id");
                $id = $rows[0]["id"];
                
                // remember that user's now logged in by storing user's ID in session
                $_SESSION["id"] = $id;
                
                if (!empty($_SESSION["id"]))
                {
                    redirect("index.php");
                }
            }
        }
        
        
        
    }

?>