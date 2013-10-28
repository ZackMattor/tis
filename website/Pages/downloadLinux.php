<?php
    $currentFile = $_SERVER["SCRIPT_NAME"];
    $parts = Explode('/', $currentFile);
    $currentFile = $parts[count($parts) - 1];
	if ($currentFile != "index.php") {
		die();
	}
	
	?> 
<div class="box">
	<h2>Download for Linux</h2>
    <h3>Ubuntu Packages</h3>
    <p>
        Binary packages for Ubuntu 12.04 are available from the <a href="">Triangles in Space PPA</a>.<br />
        To install them, run the following commands from the console.
        <pre>
        sudo add-apt-repository ppa:echidnaman/tis
        sudo apt-get update
        sudo apt-get install tisclient tisserver
        </pre>
    </p>
    <h3>Source</h3>
    <p>
        To obtain a copy of Triangle in Space's source code, see the <a href="?Page=development">Development</a> page.
</div>

<br class="clearfix" />