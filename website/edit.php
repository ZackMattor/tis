<?php
	require("Inc/functions.php");
	if(!loggedin()) {
		header("location: ./");
	}
	
	if(!isset($_GET['type']) && $_GET['type'] != 1 && $_GET['type'] != 2) {
		header("location: ./?Page=Main");
	}
	
	if($_GET['type'] == 2 && (!isset($_GET['id']) || $_GET['id'] == "")) {
		header("location: ./?Page=Main");
	}
	
	if($_GET['type'] == 2) {
		DeleteIssue($_GET['id']);
		header("location: ./?Page=ViewTitle&title=".$_GET['titleID']);
	} else {
		DeleteTitle($_GET['id']);
		header("location: ./?Page=Main");
	}
?>