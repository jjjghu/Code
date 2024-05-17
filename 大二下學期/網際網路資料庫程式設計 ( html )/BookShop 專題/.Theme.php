<?php
$theme = "";
if (isset($_COOKIE['theme'])) {
    $theme = $_COOKIE['theme'];
}
echo '<body class="' . $theme . '">';
// 結尾不需要加入 "? >", 因為只有 php 