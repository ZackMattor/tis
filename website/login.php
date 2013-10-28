<?php
	include_once("Inc/functions.php");
	
	if(isset($_GET["logoff"])) {
		LogOff();
	}
	
	if(LoggedIn()){
		header("location: .");
	}
	
	if(isset($_POST["user"]) && isset($_POST["pass"])) {
		login($_POST["user"], $_POST["pass"]);
		die();
	}	
?>