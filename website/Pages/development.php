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
		Developed as a programming project for CP252, this program is the first step towards world domination for Adam "Crazy n00b" Cumings, Zach "Dirty Hacker" Mattor, and Jon "Four-eye'd Oracle" Thomas.
	</p>
    <h2>Source Control</h2>
    <p>
        Triangles in Space is maintained within an <a href="http://subversion.tigris.org/">SVN</a> repository.
    </p>

    <h3>Browse Code</h3>
    <p>
        To browse the latest version Triangle in Space's source code, please visit the <a href="http://foxx.arksaw.com/svn/tis/">websvn portal</a>.
    </p>

    <h3>Get Code</h3>
    <p>
        For read-only access to the svn repository, run <pre>svn co http://foxx.arksaw.com/svn/tis/</pre>.
    </p>

    <h3>Project Specification</h3>
    <p>
        A document containing the specifications for Triangles in Space (including network protocol and database layout) can be found <a href="https://docs.google.com/document/pub?id=1yRdqL-jffXWxMxpPvfzQSCdpDxtSPpZD3lYKuW-NkSU">here</a>.
    </p>
</div>

<br class="clearfix" />
