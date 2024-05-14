<!DOCTYPE html>
<html lang="zh-Hant-TW"">

<head>
    <meta charset=" UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0" />
<title>登入頁面</title>
<?php include '.Style.php' ?>
</head>

<?php include '.Theme.php'; ?>
<!-- 標題橫條 + 切換按鈕 -->
<?php include '.Header.php'; ?>
<!-- 主要頁面內容開始 -->
<div class="logincontainer">
    <div class="wrapper">
        <form action="">
            <h1>登入</h1>
            <div class="input-box">
                <input type="text" placeholder="使用者名稱" required>
                <!-- 左邊圖示 (人頭)-->
                <i class='bx bxs-user icon-left'></i>
            </div>
            <div class="input-box">
                <input type="password" id="password" placeholder="密碼" required>
                <!-- 左邊圖示 (鎖頭) -->
                <i class='bx bxs-lock-alt icon-left'></i>
                <!-- 右邊圖示 (眼睛) -->
                <i class='bx bx-hide icon-right' id="passwordIcon"></i>
            </div>
            <div class="remember-forgot">
                <label><input type="checkbox">記住我</label>
                <a href="#">忘記密碼?</a>
            </div>
            <button type="submit" class="btn">登入</button>
            <div class="link-out">
                <p>沒有帳戶?
                    <a href="register.php">註冊</a>
                </p>
            </div>
        </form>
    </div>
</div>
<!-- footer 開始 -->
<?php include '.Footer.php'; ?>
<!-- footer結束 -->
</body>
<?php include '.Script.php' ?>

</html>