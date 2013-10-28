<?php
    $currentFile = $_SERVER["SCRIPT_NAME"];
    $parts = Explode('/', $currentFile);
    $currentFile = $parts[count($parts) - 1];
	if ($currentFile != "index.php") {
		die();
	}
	
	?> 
<div class="box">
	<p>This Page is under construction.</p>
</div>

<br class="clearfix" />