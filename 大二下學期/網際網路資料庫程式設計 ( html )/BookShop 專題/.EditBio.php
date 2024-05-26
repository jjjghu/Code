<?php
include '.LinkSql.php';
if (session_status() == PHP_SESSION_NONE) {
    session_start();
}
$message = '';
// 修改個人資料, 簡介的部分都在這裡, 需要判斷更改的內容
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // 接收表單內容
    $bio = $_POST['bio'];

    $update_sql = "UPDATE author SET bio = ? WHERE id = ?";
    $stmt = $link->prepare($update_sql);
    $stmt->bind_param("ss", $bio, $_SESSION['user_id']); // 問號取代變數
    $stmt->execute();
    // 判斷執行是否成功, 沒有變化也算失敗, 不要被誤導
    if ($stmt->affected_rows > 0) {
        // <div class="text-red text-start">更新成功!</div>
        $_SESSION['message'] = '更新成功!';
        header("Location: userProfile.php");
        exit;

    } else {
        $_SESSION['message'] = '更新失敗!';
        header("Location: userProfile.php");
        exit;
    }

}