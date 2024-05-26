<!-- 有登入 -> 跳轉到 index.php -->
<?php
if (session_status() == PHP_SESSION_NONE) {
    session_start();
}
if (isset($_SESSION['username'])) {
    header("Location: index.php");
    exit();
}