<?php
    $currentFile = $_SERVER["SCRIPT_NAME"];
    $parts = Explode('/', $currentFile);
    $currentFile = $parts[count($parts) - 1];
	if ($currentFile != "index.php") {
		die();
	}
	if(LoggedIn()) {
		if(isset($_GET["delete"]) && IsAdmin()) {
			DeleteServer($_GET["delete"]);
			header("location: ?Page=serverList");
		}
?> 

<div id="serverList">
	<h2>Server List</h2>
	
	<?php
		$Servers = GetServerList("../Inc/");
		
		if(!isset($Servers)) { echo "There are currently no active servers!"; } else {
			echo '<table>';
				echo '<tr><th>Server Name</th><th>Players</th><th>IP</th></tr>';
				
				foreach( $Servers as $server) {
					echo '<tr><td>'.$server["Name"].'</td><td>'.$server["Players"].'</td><td>'.$server["IP"].'</td> ' . (IsAdmin() ? '<td><a href="?Page=serverList&delete='.$server["ID"].'">DELETE</a></td>':'') . ' </tr>';
				}
				
			echo '</table>';
		}
	?>
</div>

<?php
} else {
	echo "You must login to view the server list!";
}
?>
