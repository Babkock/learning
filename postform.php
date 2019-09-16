<?php
/* Simple $_POST form by Tanner Babcock */

echo <<<END
<html>
<body>
END;

if (!empty($_POST['str']))
    echo "<b>" . $_POST['str'] . "</b><br />";

echo <<<END
<form action="prog.php" method="post" />
    Enter a string: <input type="text" name="str" />
    <input type="submit" value="Submit" />
</form>
</body>
</html>
END;

?>
