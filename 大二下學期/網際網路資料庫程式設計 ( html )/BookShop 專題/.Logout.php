<?php
// 清掉 SESSION 
session_start();
session_unset();
session_destroy();
header("Location: index.php");
exit();
