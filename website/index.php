<?php
	date_default_timezone_set('EST');
	require("Inc/functions.php");
	session_start();
	
	/***************
	 *Page Operation*
	 ***************/
	 if(isset($_GET["Page"])) {
		$page = $_GET["Page"].".php";
	 } else {
	 $page = "homepage".".php";
	 }
	 
	 if(!file_exists($PageDir.$page)){
		$page = $MissingPage.".php";
	 }
?>


<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<!--
Design by Free CSS Templates
http://www.freecsstemplates.org
Released for free under a Creative Commons Attribution 3.0 License

Name       : Reinstated
Description: A two-column, fixed-width design with dark color scheme.
Version    : 1.0
Released   : 20120326
-->
<html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<meta http-equiv="content-type" content="text/html; charset=utf-8" />
		<meta name="description" content="" />
		<meta name="keywords" content="" />
		<title>Reinstated by nodethirtythree + Free CSS Templates</title>
		<link href="http://fonts.googleapis.com/css?family=Oswald" rel="stylesheet" type="text/css" />
		<link rel="stylesheet" type="text/css" href="css/style.css" />
		<script type="text/javascript" src="js/jquery-1.7.1.min.js"></script>
		<script type="text/javascript" src="js/jquery.dropotron-1.0.js"></script>
		<script type="text/javascript" src="js/init.js"></script>
	</head>
	<body>
		<div id="wrapper">
			<div id="header">
				<div id="logo">
					<h1><a href="index.php?Page=homepage">Triangles In Space</a></h1>
				</div>
				<div id="search">
					<form action="login.php" method="post">
						<div>
						<?php if(!LoggedIn()) { ?>
							<?php echo isset($_GET['Failed'])?"Login Failed<br>":""?>
							<input class="form-text" name="user" size="32" maxlength="64" /><br>
							<input class="form-text" name="pass" type="password" size="32" maxlength="64" /><br>
							<input class="form-submit" value="Login" type="submit"/>
						<?php } else { ?>
							<?php echo "Welcome " . (IsAdmin() ? "Admin " : " ") . $_SESSION['fname']; ?>
							<br>Do you want to <a href="login.php?logoff">logout</a>?
						<?php } ?>
						</div>
					</form>
				</div>
			</div>
			<div id="menu">
				<ul>
					<li><a href="?Page=homepage">Homepage</a></li>
					<li><a href="?Page=development">Development</a></li>
					<li>
						Download<span class="arrow"></span>
						<ul>
							<li>
                                Client <span class="arrow"></span>
                                <ul>
                                    <li class="first"><a href="?Page=construction">Windows</a></li>
                                    <li><a href="?Page=downloadLinux">Linux</a></li>
                                </ul>
                            </li>
							<li>
								Server <span class="arrow"></span>
								<ul>
									<li class="first"><a href="?Page=construction">Windows</a></li>
									<li><a href="?Page=downloadLinux">Linux</a></li>
								</ul>
							</li>
						</ul>
					</li>
					<?php if(LoggedIn()) { ?>
					<li><a href="?Page=construction">Account</a></li>
					<li><a href="?Page=serverList">Server List</a></li>
					<?php } else { ?>
					<li class="last"><a href="?Page=register">Register</a></li>
					<?php } ?>
					<li><a href="?Page=construction">Contact</a></li>
				</ul>
				<br class="clearfix" />
			</div>

			<div id="page">
				<div id="content">
<?php
	include($PageDir.$page);
?>
				</div>
				<div id="sidebar">
					<div class="box">
						<h3>Powered By</h3>
						<ul class="list">
							<li class="first"><a href="http://alleg.sourceforge.net/">Allegro</a></li>
							<li><a href="http://qt.nokia.com/products/">Qt SDK</a></li>
							<li><a href="http://www.php.net/">PHP</a></li>
							<li><a href="http://www.mysql.com/">MySQL</a></li>
							<li><a href="http://www.ubuntu.com/">Ubuntu</a></li>
							<li><a href="http://subversion.tigris.org/">SVN</a></li>
							<li class="last"><a href="http://nhti.edu/">NHTI</a></li>
						</ul>
					</div>
					<div class="box">
						<h3></h3>
						<p>
							Standards are paper. I use paper to wipe my butt every day. That's how much that paper is worth.<br><i><a href="https://bugzilla.redhat.com/show_bug.cgi?id=638477#c129">-Linus Torvalds 2010-</a></i>
						</p>
					</div>
				</div>
				<br class="clearfix" />
			</div>
		</div>
		<div id="footer">
			&copy; 2012 arksaw.com. | Powered by <a href="http://nodethirtythree.com/jquery/dropotron">Dropotron</a> | Design by <a href="http://nodethirtythree.com">nodethirtythree</a> and <a href="http://www.freecsstemplates.org/">CSS Templates</a>.
		</div>
	</body>
</html>