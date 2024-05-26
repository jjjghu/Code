<?php include ".LoginRedirect.php"; ?>
<!DOCTYPE html>
<html lang="zh-Hant-TW">

<head>
  <meta charset=" UTF-8">
  <meta http-equiv="Cache-Control" content="no-store" />
  <meta name="viewport" content="width=device-width, initial-scale=1.0" />
  <title>註冊</title>
  <?php include '.Style.php' ?>
  <?php include '.LinkSql.php' ?>
</head>
<?php include '.Theme.php'; ?>
<!-- 新增使用者, 將新用戶的資料家入 -->
<?php
$message = '';
if ($_SERVER["REQUEST_METHOD"] == "POST") {
  $username = $_POST['username'];
  $password = $_POST['password'];
  $passwordCheck = $_POST['passwordCheck'];
  $email = $_POST['email'];
  $phone = $_POST['phone'];

  // 檢查是否所有欄位都有值
  $hashed_password = password_hash($password, PASSWORD_BCRYPT);

  $check_sql = "SELECT id FROM author WHERE username = ? OR email = ?";
  $stmt = $link->prepare($check_sql);
  $stmt->bind_param("ss", $username, $email); // 兩個問號分別取代變數
  $stmt->execute();
  $stmt->store_result();

  if ($stmt->num_rows > 0) {
    $message = "使用者名稱或電子郵件已存在";
  } else {
    // 插入新用戶資料
    $sql = "INSERT INTO author (username, password, email, phone) VALUES (?, ?, ?, ?)";
    $stmt = $link->prepare($sql);
    $stmt->bind_param("ssss", $username, $hashed_password, $email, $phone);

    if ($stmt->execute()) {
      $message = "註冊成功";
      header("Location: login.php"); // 註冊成功後重定向到登入頁面
      exit;
    } else {
      $message = "註冊失敗: " . $stmt->error;
    }
  }
  $stmt->close();
  $link->close();
}
?>

<body class=<?php echo $theme ?>>
  <!-- 標題橫條 + 切換按鈕 -->
  <?php include '.Header.php'; ?>
  <!-- 主要頁面內容開始 -->
  <main class="logincontainer">
    <div class="wrapper">
      <form id="RegisterForm" action="register.php" method='post'>
        <h1>註冊</h1>
        <div>
          <div class="input-box">
            <input type="text" name="username" id="username" placeholder="使用者名稱">
            <!-- 左邊圖示 (人頭)-->
            <i class='bx bxs-user icon-left'></i>
            <p class='ms-1 mt-1 text-red' id="username-err"></p>
          </div>
          <div class="input-box">
            <input type="password" name="password" id="password" placeholder="密碼">
            <!-- 左邊圖示 (鎖頭) -->
            <i class=' bx bxs-lock-alt icon-left'></i>
            <!-- 右邊圖示 (眼睛) -->
            <i class='bx bx-hide icon-right' id="passwordIcon"></i>
            <p class='ms-1 mt-1 text-red' id="password-err"></p>
          </div>
          <div class="input-box">
            <input type="password" name="passwordCheck" id="passwordCheck" placeholder="密碼確認">
            <!-- 左邊圖示 (鎖頭) -->
            <i class='bx bx-x icon-left' id="check-icon"></i>
            <p class='ms-1 mt-1 text-red ' id="passwordCheck-err"></p>
          </div>
          <div class="input-box">
            <input type="email" name="email" id="email" placeholder="電子信箱">
            <!-- 左邊圖示 (信箱) -->
            <i class='bx bxs-envelope icon-left'></i>
            <p class='ms-1 mt-1 text-red' id='email-err'></p>
          </div>
          <div class="input-box">
            <input type="text" name="phone" id="phone" placeholder="手機號碼">
            <!-- 左邊圖示 (手機) -->
            <i class='bx bxs-phone icon-left'></i>
            <p class='ms-1 mt-1 text-red' id='phone-err'></p>
          </div>
        </div>
        <!-- 密碼要求列表, 待編輯 -->
        <button type="submit" class="btn" id="submitButton">註冊</button>
        <div class="link-out">
          <p>已有帳戶?<a href="login.php">登入</a></p>
          <div class='text-red'><?php echo $message; ?></div>
        </div>
      </form>
    </div>
  </main>
  <!-- footer 開始 -->
  <?php include '.Footer.php'; ?>
  <!-- footer結束 -->
</body>
<?php include '.Script.php' ?>

</html>