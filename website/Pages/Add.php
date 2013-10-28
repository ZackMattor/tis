<?php
	if(!loggedin()) {
		header("location: ./");
	}
	
	if(!isset($_GET['type']) && $_GET['type'] != 1 && $_GET['type'] != 2) {
		header("location: ./?Page=WebSales");
	}
	if($_GET['type'] == 2 && (!isset($_GET['titleID']) || $_GET['titleID'] == "")) {
		header("location: ./?Page=WebSales");
	}
?>
	<style type="text/css">
		/* Form styles */
		p.legend { margin-bottom: 1em; }
		p.legend em { color: #C00; font-style: normal; }

		div.errors { margin: 0 0 10px 0; padding: 5px 10px; border: #FC6 1px solid; background-color: #FFC; }
		div.errors p { margin: 0; }
		div.errors p em { color: #C00; font-style: normal; font-weight: bold; }
		
		div.form-container { margin: 0px; padding:0px; background-color: #FFF;}
		div.form-container form p { margin: 0; }
		div.form-container form p.note { margin-left: 170px; font-size: 90%; color: #333; }
		div.form-container form fieldset { margin: 10px 0; padding: 10px; border: #DDD 1px solid; }
		div.form-container form legend { font-weight: bold; color: #666; }
		div.form-container form fieldset div { padding: 0.25em 0; }
		div.form-container label { margin-right: 10px; padding-right: 10px; width: 150px; display: block; float: left; text-align: right; position: relative; }
		div.form-container label.error, 
		div.form-container span.error { color: #C00; }
		div.form-container label em { position: absolute; right: 0; font-size: 120%; font-style: normal; color: #C00; }
		div.form-container input.error { border-color: #C00; background-color: #FEF; }
		div.form-container input:focus,
		div.form-container input.error:focus, 
		div.form-container textarea:focus {	background-color: #FFC; border-color: #FC6; }
		div.form-container div.controlset label, 
		div.form-container div.controlset input { display: inline; float: none; }
		div.form-container div.controlset label.controlset { display: block; float: left; }
		div.form-container div.controlset div { margin-left: 170px; }
		div.form-container div.buttonrow { margin-left: 180px; }
	</style>
<div class="form-container">
	<form action="AddAction.php" method="post">
		<fieldset>
			<legend>Adding a <?php echo $_GET['type']==1?"Title":"Issue"; ?>!</legend>
			
			<label for="name">Name of <?php echo $_GET['type']==1?"Title":"Issue"; ?></label>
			<input id="name" name="name" type="text">
			<br>
			
			<input name="type" value="<?php echo $_GET['type']; ?>" type="hidden">
			<input name="titleID" value="<?php echo $_GET['titleID']; ?>" type="hidden">
			<?php 
			if($_GET['type'] == 2) {
				?>
				<label for="name">Bucket Location of <?php echo $_GET['type']==1?"Title":"Issue"; ?></label>
				<input id="name" name="bucket" type="text"><br>
				 <?php
			}
			?>
			<label>&nbsp;</label>
			
			<input type="submit">
		</fieldset>
	</form>
	</div>
	
