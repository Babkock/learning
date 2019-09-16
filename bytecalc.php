<html>
	<head>
		<title>Byte Converter</title>
		<style type="text/css">
			body {
				background-color:#000000;
				color:#ffffff;
				text-align:center;
			}
			#boxa {
				border:1px solid white;
				background-color:#222222;
				color:#ffffff;
				width:600px;
				text-align:center;
			}
			#boxb {
				border:1px solid white;
				background-color:#111111;
				color:#ffffff;
				width:600px;
				text-align:center;
			}
		</style>
<?php

 $unit = 0;
 $num = 0;
 $unit = (int)$_POST['bar'];
 $num = (float)$_POST['foo'];
 
?>
	</head>
	<body>
		<center>
		<h1>Byte Converter</h1>
		<form id="boxa" action="bytecalc.php" method="post">
			<p>Number: <input type="text" name="foo" value=<?php echo "\"" . $num . "\""; ?> />
			<select name="bar">
				<option value="0">Bits</option>
				<option value="1">Bytes</option>
			</select>
			<input type="submit" value="Calculate">
			</p>
		</form>
<p><?php
 $out = "<table id=\"boxb\">";
 $out .= "<tr>";
 if ($unit == 0)
	$out .= "<td>" . $num . "</td><td>Bits</td>";
 else
    $out .= "<td>" . ($num * 8) . "</td><td>Bits</td>";
 $out .= "</tr><tr>";
 if ($unit == 0)
	$out .= "<td>" . ($num / 8) . "</td><td>Bytes</td>";
 else
	$out .= "<td>" . $num . "</td><td>Bytes</td>";
 $out .= "</tr><tr>";
 if ($unit == 0)
	$out .= "<td>" . ($num / 1000) . "</td><td>Kilobits</td>";
 else
	$out .= "<td>" . (($num * 8) / 1000) . "</td><td>Kilobits</td>";
 $out .= "</tr><tr>";
 if ($unit == 0)
    $out .= "<td>" . (($num / 8) / 1000) . "</td><td>Kilobytes</td>";
 else
	$out .= "<td>" . ($num / 1000) . "</td><td>Kilobytes</td>";
 $out .= "</tr><tr>";
 if ($unit == 0)
	$out .= "<td>" . ($num / 1000000) . "</td><td>Megabits</td>";
 else
	$out .= "<td>" . (($num * 8) / 1000000) . "</td><td>Megabits</td>";
 $out .= "</tr><tr>";
 if ($unit == 0)
	$out .= "<td>" . (($num / 8) / 1000000) . "</td><td>Megabytes</td>";
 else
	$out .= "<td>" . ($num / 1000000) . "</td><td>Megabytes</td>";
 $out .= "</tr><tr>";
 if ($unit == 0)
	$out .= "<td>" . ($num / 1000000000) . "</td><td>Gigabits</td>";
 else
	$out .= "<td>" . (($num * 8) / 1000000000) . "</td><td>Gigabits</td>";
 $out .= "</tr><tr>";
 if ($unit == 0)
	$out .= "<td>" . (($num / 8) / 1000000000) . "</td><td>Gigabytes</td>";
 else
	$out .= "<td>" . ($num / 1000000000) . "</td><td>Gigabytes</td>";
 $out .= "</tr></table>";
 echo $out;
?></p>
</center></body>
</html>
