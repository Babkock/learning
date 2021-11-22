<?php

$one = $_POST['one'];
$two = $_POST['two'];
$three = $_POST['three'];
$four = $_POST['four'];

?>
<html>
<head>
<title>Hex Colors</title>
<style type="text/css">
 body {
	background-color:#000000;
	color:#ffffff;
	text-align:center;
 }
 #box {
	border:1px solid white;
	background-color:#222222;
	color:#ffffff;
	width:600px;
	text-align:center;
 }
 #boxa {
	border:1px solid white;
	background-color:<?php echo $one; ?>;
	width:600px;
	text-align:center;
 }
 #boxb {
	border:1px solid white;
	background-color:<?php echo $two; ?>;
	width:600px;
	text-align:center;
 }
 #boxc {
	border:1px solid white;
	background-color:<?php echo $three; ?>;
	width:600px;
	text-align:center;
 }
 #boxd {
	border:1px solid white;
	background-color:<?php echo $four; ?>;
	width:600px;
	text-align:center;
 }
</style>
</head>
<body><center>
<h1>Hex Colors</h1>
<form id="box" action="hexcolors.php" method="post">
	<p>Enter four hex colors:</p>
	<p>Box one: <input type="text" name="one" value=<?php echo "\"" . $one . "\""; ?> /></p>
	<p>Box two: <input type="text" name="two" value=<?php echo "\"" . $two . "\""; ?> /></p>
	<p>Box three: <input type="text" name="three" value=<?php echo "\"" . $three . "\""; ?> /></p>
	<p>Box four: <input type="text" name="four" value=<?php echo "\"" . $four . "\"" ?> /></p>
	<input type="submit" value="Submit">
</form>
<div id="boxa"><br><br><br></div><br>
<div id="boxb"><br><br><br></div><br>
<div id="boxc"><br><br><br></div><br>
<div id="boxd"><br><br><br></div>
</center></body>
</html>
