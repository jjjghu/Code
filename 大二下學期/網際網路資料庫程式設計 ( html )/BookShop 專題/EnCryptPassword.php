<?php
$servername = "localhost";
$username = "root";
$password = "root123456";
$dbname = "group_07";

// 建立資料庫連接
$link = new mysqli($servername, $username, $password, $dbname);

// 檢查連接
if ($link->connect_error) {
    die("連接失敗: " . $link->connect_error);
}

mysqli_query($link, "SET CHARACTER SET utf8");
mysqli_query($link, "SET collation_connection = 'utf8_unicode_ci'");

// 獲取所有使用者資料
$sql = "SELECT id, password FROM author";
$result = $link->query($sql);

if ($result->num_rows > 0) {
    while ($row = $result->fetch_assoc()) {
        $user_id = $row['id'];
        // 密碼
        $plain_password = $row['password'];

        // 加密密碼
        $hashed_password = password_hash($plain_password, PASSWORD_BCRYPT);

        // 更新資料庫中的密碼
        $update_sql = "UPDATE author SET password = ? WHERE id = ?";
        $update_stmt = $link->prepare($update_sql);
        $update_stmt->bind_param("si", $hashed_password, $user_id);

        if ($update_stmt->execute()) {
            echo "使用者 ID $user_id 的密碼已更新為加密密碼<br>";
        } else {
            echo "更新使用者 ID $user_id 的密碼時發生錯誤: " . $update_stmt->error . "<br>";
        }

        $update_stmt->close();
    }
} else {
    echo "沒有找到使用者資料";
}

$link->close();
?>
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>更新密碼</title>
</head>

<body>
    密碼更新!
</body>

</html>