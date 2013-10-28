<?php
	require("../Inc/functions.php");
	$ok = true;
	if(isset($_POST["fName"]) && isset($_POST["lName"]) && isset($_POST["userName"]) && isset($_POST["password"]) && isset($_POST["confirm"]) && isset($_POST["email"])) {
		$fName = $_POST["fName"];
		$lName = $_POST["lName"];
		$userName = $_POST["userName"];
		$password = $_POST["password"];
		$confirm = $_POST["confirm"];
		$email = $_POST["email"];
		
		if (preg_match('/^[a-z\d_]{5,20}$/i', $userName)) {
			echo "Your username is ok.<br>";
			if(validEmail($email)) {
				if($password == $confirm) {
					if(NewUser($userName, $password, $fName, $lName, $email)){
						header("location: ../index.php?Page=successfulCreate");
					}
				}
			}
		} else {
            header("location: ../index.php?Page=register&failed");
        }
	} else {
		echo "We are missing something!";
	}
?>