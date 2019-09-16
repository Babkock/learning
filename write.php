<?php

$fcont = $_POST['fcont'];
$fname = $_POST['fname'];

	if ($fcont == NULL || $fname == NULL) {
		$s = "<h1>Write a file</h1>";
		$s .= "<form action=\"write.php\" method=\"post\">";
		$s .= "File name: <input type=\"text\" name=\"fname\" /><br />";
		$s .= "Enter a string: <input type=\"text\" name=\"fcont\" /><br />";
		$s .= "<input type=\"submit\" value=\"Write\" /></form>";
		echo $s;
	}
	else {
		$fp = fopen($fname, 'w') or die("<b>Cannot open file " . $fname . " for writing</b>");
		$i = fwrite($fp, $fcont);
		if ($i == FALSE)
			echo "<b>Could not write to " . $fname . "</b>";
		else {
			echo "<b>File " . $fname . " written successfully.</b><br />";
			echo "<a href=\"read.php?file=" . $fname . "\">Read the file.</a>";
		}
	}
	
echo "<br /><br /><a href=\"index.php\">Back to main menu.</a>";

?>
