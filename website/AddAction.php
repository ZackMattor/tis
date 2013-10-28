<?php
	require("Inc/functions.php");
	if((!isset($_POST['name']) || $_POST['name'] == "") || ($_POST['type'] != 1 && $_POST['type'] != 2)) {
		header("location: ./?Page=WebSalesTab");
	}
	
	if($_POST['type'] == 1) {
		AddTitle($_POST['name']);
		header("location: ./?Page=WebSalesTab");
	} else {
		AddIssue($_POST['name'], $_POST['titleID'], $_POST['bucket']);
		header("location: ./?Page=ViewTitle&title=".$_POST['titleID']);
	}
?>