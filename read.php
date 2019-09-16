<?php

$input = $_POST['fname'];
$get = $_GET['file'];

echo "<h1>Read a file</h1>";

if ($input == NULL && $get == NULL) {
	$s = "<form action=\"read.php\" method=\"post\">";
	$s .= "File name: <input type=\"text\" name=\"fname\" />";
	$s .= "&nbsp; <input type=\"submit\" value=\"Read\" /></form>";
	echo $s;
}
else if ($get == NULL && $input != NULL) {
	$fp = @fopen($input, 'r') or die("<b>Can't open file " . $input . "</b>");
	$s = fgets($fp);
	echo "<b>Contents of " . $input . ":</b><br />" . $s;
	fclose($fp);
}
else if ($get != NULL) {
	$fp = @fopen($get, 'r') or die("<b>Can't open file " . $get . "</b>");
	$s = fgets($fp);
	echo "<b>Contents of " . $get . ":</b><br />" . $s;
	fclose($fp);
}

echo "<br /><br /><a href=\"index.php\">Back to main menu.</a>";

?>
