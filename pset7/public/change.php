<?php
    
    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("change_form.php", ["title" => "Change password"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // query database for user
        $rows = CS50::query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);
        // check password
        if (count($rows) == 1)
        {
            // first (and only) row
            $row = $rows[0];
            // compare hash of user's input against hash that's in database
            if (!password_verify($_POST["old_password"], $row["hash"]))
            {
                apologize("You entered wrong old password.");
            }
            else if (empty($_POST["new_password"]))
            {
                apologize("New password can not be empty.");
            }
        
            // if password and confirmation not equal
            else if ($_POST["new_password"] !== $_POST["confirmation"])
            {
                apologize("New password and confirmation does not match.");
            }
        }
        

            CS50::query("UPDATE users SET hash = ? WHERE id = ?",  password_hash($_POST["new_password"], PASSWORD_DEFAULT), $_SESSION["id"]);
            // log out current user, if any
            logout();

            // redirect user
            redirect("/");


        
        
        
    }

?>