<?php

	$PageDir = "Pages/";
	$DefaultPage = "homepage";
	$MissingPage = "404";
	
   	/*******************
	* Gereates the hash used to store passwords this also auto-salts the
	* password using the md5 of the string. 
	*/
	function GenerateHash($str) {
		return md5($str.md5($str)); //we salt out password with the md5 of the password
	}
	
	/*******************
	* Checks to see weather or not the user is currently logged in.
	*/
	function LoggedIn() {
		session_start();
		if (!(isset($_SESSION['login']) && $_SESSION['login'] != '')) {
			return false;
		} return true;
	}
	
	function IsAdmin() {
		if(LoggedIn()) {
			require("Inc/dbauth.php");
			$query = "SELECT * FROM accounts WHERE id = " .$_SESSION['UserID']. " and admin = 1";
			mysql_connect ($dbserver, $dbuser, $dbpword);
			mysql_select_db($db) or die(mysql_error()." GetServerList1");
			$result = mysql_query($query) or die(mysql_error()." GetServerList2");

			while($row=mysql_fetch_array($result)) {
				return true;
			}
			return false;
		} else {
			return false;
		}
		echo $_SESSION['UserID'];
	}
	
	function Login($UserName, $RawPassword, $path="Inc/") {
		$password = GenerateHash($RawPassword);
		require($path."dbauth.php");
		
		$query = "SELECT * FROM accounts WHERE username='".$UserName."' AND secret='".$password."'";
		
		mysql_connect ($dbserver, $dbuser, $dbpword);
		
		mysql_select_db($db) or die(mysql_error()." Logging in");
		
		$result=mysql_query($query) or die(mysql_error()." Getting everything");
		
		if(mysql_num_rows($result)>0) {
			$row = mysql_fetch_assoc($result);
			session_start();
			$_SESSION['login'] = '1';
			$_SESSION['UserID'] = $row['id'];
			$_SESSION['fname'] = $row['fname'];
			$_SESSION['lname'] = $row['lname'];
		} else {
			header("location: index.php?Failed=1");
			die();
		}
		
		header("location: .");
	}
	
	function LogOff($UserName, $RawPassword) {
		session_start();
		session_destroy();
		header("location: .");
	}
	
	function NewUser($UserName, $RawPassword, $fname, $lname, $email) {
		require("../Inc/dbauth.php");
		$query = "INSERT into accounts (username, secret, admin, fname, lname, email) values ('$UserName', '".GenerateHash($RawPassword)."', 0, '$fname', '$lname', '$email')";
		mysql_connect ($dbserver, $dbuser, $dbpword);
		mysql_select_db($db) or die(mysql_error()." Creating User1");
		mysql_query($query) or die(mysql_error()." Creating User2");
		return true;
	}
	
	function GetServerList($path="Inc/") {
		include_once($path."dbauth.php");
		$query = "SELECT * FROM servers";
		mysql_connect ($dbserver, $dbuser, $dbpword);
		mysql_select_db($db) or die(mysql_error()." GetServerList1");
		$result = mysql_query($query) or die(mysql_error()." GetServerList2");
		
		$count = 0;
		
		while($row=mysql_fetch_array($result)) {
			$serverList[$count]["Name"] = $row["serverName"];
			$serverList[$count]["MaxPlayers"] = $row["maxPlayers"];
			$serverList[$count]["Players"] = $row["connectedPlayers"];
			$serverList[$count]["IP"] = $row["ipAddr"];
			$serverList[$count]["ID"] = $row["id"];
			$serverList[$count]["Port"] = $row["port"];
			$count ++;
		}
		
		return $serverList;
	}
	
	function DeleteServer($ServerID) {
		require("Inc/dbauth.php");
		$query = "DELETE FROM servers WHERE id = '".$ServerID."'";
		mysql_connect ($dbserver, $dbuser, $dbpword);
		mysql_select_db($db) or die(mysql_error()." DeleteServer1");
		mysql_query($query) or die(mysql_error()." DeleteServer2");
		return true;
	}
	
	/**
	Validate an email address.
	Provide email address (raw input)
	Returns true if the email address has the email 
	address format and the domain exists.
	*/
	function validEmail($email)
	{
		$isValid = true;
		$atIndex = strrpos($email, "@");
		if (is_bool($atIndex) && !$atIndex)
		{
			$isValid = false;
		}
		else
		{
			$domain = substr($email, $atIndex+1);
			$local = substr($email, 0, $atIndex);
			$localLen = strlen($local);
			$domainLen = strlen($domain);
			if ($localLen < 1 || $localLen > 64)
			{
				// local part length exceeded
				$isValid = false;
			}
			else if ($domainLen < 1 || $domainLen > 255)
			{
				// domain part length exceeded
				$isValid = false;
			}
			else if ($local[0] == '.' || $local[$localLen-1] == '.')
			{
				// local part starts or ends with '.'
				$isValid = false;
			}
			else if (preg_match('/\\.\\./', $local))
			{
				// local part has two consecutive dots
				$isValid = false;
			}
			else if (!preg_match('/^[A-Za-z0-9\\-\\.]+$/', $domain))
			{
				// character not valid in domain part
				$isValid = false;
			}
			else if (preg_match('/\\.\\./', $domain))
			{
				// domain part has two consecutive dots
				$isValid = false;
			}
			else if (!preg_match('/^(\\\\.|[A-Za-z0-9!#%&`_=\\/$\'*+?^{}|~.-])+$/', str_replace("\\\\","",$local)))
			{
				// character not valid in local part unless 
				// local part is quoted
				if (!preg_match('/^"(\\\\"|[^"])+"$/',
				str_replace("\\\\","",$local)))
				{
					$isValid = false;
				}
			}
			if ($isValid && !(checkdnsrr($domain,"MX") || checkdnsrr($domain,"A")))
			{
				// domain not found in DNS
				$isValid = false;
			}
		}
		return $isValid;
	}
?>