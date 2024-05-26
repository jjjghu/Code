<?php
$servername = "localhost";
$username = "root";
$password = "root123456";
$dbname = "group_07";

$link = new mysqli($servername, $username, $password, $dbname);
$link = mysqli_connect('localhost', 'root', 'root123456', $dbname);
$message = "";

if ($link->connect_error) {
    $message = "連結錯誤代碼: " . mysqli_connect_errno() . "<br>"; // 顯示錯誤代碼
    $message = "連結錯誤訊息: " . mysqli_connect_error() . "<br>"; // 顯示錯誤訊息
} else {
    $message = "資料庫 $dbname 連結成功!<br>";
}
mysqli_query($link, "SET CHARACTER SET utf8");
mysqli_query($link, "SET collation_connection = 'utf8_unicode_ci'");
