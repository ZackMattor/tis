<?php
    $currentFile = $_SERVER["SCRIPT_NAME"];
    $parts = Explode('/', $currentFile);
    $currentFile = $parts[count($parts) - 1];
	if ($currentFile != "index.php") {
		die();
	}
	
	?> 
	
<div class="box">
	<h2>Success!</h2>
	<p>
		You can now go login! When you do login be sure to go to your account page and customize your ship!
	</p>
</div>

<br class="clearfix" />