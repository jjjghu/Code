<?php

$link = mysqli_connect("localhost", "root", "root123456", "school") // 建立MySQL的資料庫連結
    or die("無法開啟MySQL資料庫連結!<br>");

mysqli_query($link, 'SET CHARACTER SET utf8');
mysqli_query($link, "SET collation_connection = 'utf8_unicode_ci'");
$arr_sex = array('F' => '女', 'M' => '男');
if ($result = mysqli_query($link, "SELECT * FROM students")) {
    while ($row = mysqli_fetch_assoc($result)) {
        $a['data'][] = array($row["stud_no"], $row["stud_name"], $arr_sex[$row["stud_sex"]], $row["stud_addr"]);
    }
    mysqli_free_result($result); // 釋放佔用的記憶體
}
mysqli_close($link); // 關閉資料庫連結

echo json_encode($a);

?>