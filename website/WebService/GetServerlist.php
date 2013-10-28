<?php
	require('../Inc/functions.php');
	$ap = GetServerList("../Inc/");
	echo "<servers>";
	foreach($ap as $server)
	{
		echo "<server>";
		echo "<id>".$server["ID"]."</id>";
		echo "<serverName>".$server["Name"]."</serverName>";
		echo "<maxPlayers>".$server["MaxPlayers"]."</maxPlayers>";
		echo "<connectedPlayers>".$server["Players"]."</connectedPlayers>";
		echo "<ipAddr>".$server["IP"]."</ipAddr>";
		echo "<port>".$server["Port"]."</port>";
		echo "</server>";
	}
	echo "</servers>";
?>