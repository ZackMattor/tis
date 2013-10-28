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
		Triangles in space is a free, open-source, multiplayer game that is currently in development. In this real-time action game you will fly around space, as your own customized triangle, and try to defeat your enemies!
		
	</p>
</div>
<h3>News</h3>
<ul class="section-list">
	<li class="first"><h4>Website falling together</h4><span>The website seems to be coming together... I have the basic skeleton done, but much content needs to be filled in, along with some functional pages, such as the register screen. This is probably my highest priority at this time.</span></li>
	<li><h4>We are here!</h4><span>Development has started! This is the website for our final project! Hopefully we will be able to see some progress over the next few weeks! You can view our most up-to-date project spec <a href="https://docs.google.com/document/pub?id=1yRdqL-jffXWxMxpPvfzQSCdpDxtSPpZD3lYKuW-NkSU">here</a>.</span></li>
</ul>
<br class="clearfix" />