<?php

echo <<<_END
<html><head><title>Image Upload</title>
<link rel=stylesheet type="text/css" href="style.css" />
</head>
<body>
<form method="post" action="upload.php" enctype="multipart/form-data">
Upload an image file. Supported image types are JPEG, GIF, PNG, and TIFF.
<input type="file" name="filename" size="10" />
<input type="submit" value="Upload" /></form>
_END;

if ($_FILES) {
	$name = $_FILES['filename']['name'];
	
	switch ($_FILES['filename']['type']) {
		case "image/jpeg": $ext = "jpg"; break;
		case "image/gif": $ext = "gif"; break;
		case "image/png": $ext = "png"; break;
		case "image/tiff": $ext = "tif"; break;
		default: $ext = ""; break;
	}
	if ($ext) {
		// @mkdir("public");
		$n = "image." . $ext;
		move_uploaded_file($_FILES['filename']['tmp_name'], $n);
		echo "Uploaded image \"" . $name . "\" as \"" . $n . "\":<br />";
		echo "<img src=\"" . $n . "\" />";
	}
	else
		echo $name . " is not a supported image type.";
}
else
	echo "No file selected";

echo "</body></html>";
?>
