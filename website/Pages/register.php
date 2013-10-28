<?php
    $currentFile = $_SERVER["SCRIPT_NAME"];
    $parts = Explode('/', $currentFile);
    $currentFile = $parts[count($parts) - 1];
	if ($currentFile != "index.php") {
		die();
	}
	
	?> 
	
<div class="box">
	<h2>Registration</h2>
	<p>
		<form method="post" action="ActionZone/NewUser.php">
			Want to join the insanity? It's free and quick! Do it NAO!
			<?php if(isset($_GET["failed"])) { echo "<br><br><font color='red'>There was a problem with your input please try again</font><br>"; } ?>
			<div id="register">
				<table>
					<tr><td>First Name:</td><td width="5px"></td><td><input type="text" name="fName"></td></tr>
					<tr><td>Last Name:</td><td width="5px"></td><td><input type="text" name="lName"></td></tr>
					<tr><td>User Name:</td><td width="5px"></td><td><input type="text" name="userName"></td></tr>
					<tr><td>Password:</td><td width="5px"></td><td><input type="password" name="password"></td></tr>
					<tr><td>Confirm:</td><td width="5px"></td><td><input type="password" name="confirm"></td></tr>
					<tr><td>E-mail:</td><td width="5px"></td><td><input type="text" name="email"></td></tr>
					<tr><td colspan="3"><input class="submit" type="submit" value="Submit"></td></tr>
				</table>
			</div>
		</form>
	</p>
</div>

<br class="clearfix" />