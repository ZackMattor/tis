<?php
    $currentFile = $_SERVER["SCRIPT_NAME"];
    $parts = Explode('/', $currentFile);
    $currentFile = $parts[count($parts) - 1];
	if ($currentFile != "index.php") {
		die();
	}
	
	?> 
<div class="box">
	<h2>Welcome</h2>
	<p>
		U want play? You make sure register first!
		</p>
		<p>
		You register'd? Descargar esta ahora!
	</p>
</div>

<br class="clearfix" />