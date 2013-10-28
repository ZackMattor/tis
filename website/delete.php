<?php
	require("Inc/functions.php");
	if(!loggedin()) {
		header("location: ./");
	}
	
	if(!isset($_GET['type']) && $_GET['type'] != 1 && $_GET['type'] != 2) {
		header("location: ./?Page=WebSales");
	}
	
	if($_GET['type'] == 2 && (!isset($_GET['id']) || $_GET['id'] == "")) {
		header("location: ./?Page=WebSales");
	}
	
	if($_GET['type'] == 2) { //Delete the issue
		DeleteIssue($_GET['id']);
		header("location: ./?Page=ViewTitle&title=".$_GET['titleID']);
	} else {                //Delete the title
		DeleteTitle($_GET['id']);
		header("location: ./?Page=WebSalesTab");
	}
?>