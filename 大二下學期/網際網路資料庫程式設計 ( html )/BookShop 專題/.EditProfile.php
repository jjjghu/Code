<?php
include '.LinkSql.php';
session_start(); // 確認已啟用會話
$message = '';
// 修改個人資料, 簡介的部分都在這裡, 需要判斷更改的內容
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // 接收表單內容
    $username = $_POST["username"];
    $newpassword = $_POST["newpassword"];
    $penName = $_POST["penName"];
    $email = $_POST["email"];
    $phone = $_POST["phone"];

    // 檢查筆名是否已被使用
    $check_sql = "SELECT id, penName FROM author WHERE id != ? AND penName = ?;";
    $stmt = $link->prepare($check_sql);
    $stmt->bind_param("ss", $_SESSION['user_id'], $penName); // 問號取代變數
    $stmt->execute();
    $stmt->store_result();
    if ($stmt->num_rows > 0) {
        // <div class="text-red text-start">筆名已被使用!</div>
        $_SESSION['message'] = '筆名已被使用!';
        header("Location: userProfile.php");
        exit;
    }

    // 找到使用者 id , 更新資料
    $check_sql = "SELECT * FROM author WHERE id = ?";
    $stmt = $link->prepare($check_sql);
    $stmt->bind_param("s", $_SESSION['user_id']);
    $stmt->execute();
    $stmt->store_result();
    if ($stmt->num_rows > 0) {
        if (empty($newpassword)) {
            // 如果密碼為空，則不更新密碼
            $update_sql = "UPDATE author SET username = ?, penName = ?, email = ?, phone = ? WHERE id = ?";
            $stmt = $link->prepare($update_sql);
            $stmt->bind_param("sssss", $username, $penName, $email, $phone, $_SESSION['user_id']);
        } else {
            // 如果密碼不為空，則更新密碼
            $hashed_password = password_hash($newpassword, PASSWORD_DEFAULT);
            $update_sql = "UPDATE author SET username = ?, password = ?, penName = ?, email = ?, phone = ? WHERE id = ?";
            $stmt = $link->prepare($update_sql);
            $stmt->bind_param("ssssss", $username, $hashed_password, $penName, $email, $phone, $_SESSION['user_id']);
        }
        $stmt->execute();
        // 將 message 存放到SESSION
        // <div class="text-success text-start">更新成功!</div>
        $_SESSION['message'] = '更新成功!';
        $_SESSION['username'] = $username; // 更新 username 值'
        $_SESSION['penName'] = $penName; // 紀錄筆名
        header("Location: userProfile.php");
        exit;
    }
}