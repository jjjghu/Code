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
      <h1>註冊</h1>
      <div class='form-step' >
        <div class="input-box">
          <input type="text" placeholder="使用者名稱" required>
          <!-- 左邊圖示 (人頭)-->
          <i class='bx bxs-user icon-left'></i>
        </div>
        <button class="btn nextstep">下一步</button>
      </div>
      <div class='form-step' style="display:none">
        <div class="input-box">
          <input type="text" id="password-box" placeholder="密碼" required>
          <!-- 左邊圖示 (鎖頭) -->
          <i class=' bx bxs-lock-alt icon-left'></i>
          <!-- 右邊圖示 (眼睛) -->
          <i class='bx bx-hide icon-right' id="passwordIcon"></i>
        </div>
        <div class="input-box">
          <input type="password" id="password-check" placeholder="密碼確認" required>
          <!-- 左邊圖示 (鎖頭) -->
          <i class='bx bx-x icon-left' id="check-icon"></i>
        </div>
        <button type="submit" class="btn">下一步</button>
      </div>
      <div class='form-step' style="display:none">
        <div class="input-box">
          <input type="email" placeholder="電子信箱" required>
          <!-- 左邊圖示 (鎖頭) -->
          <i class='bx bxs-envelope icon-left'></i>
        </div>
        <!-- 密碼要求列表, 待編輯 -->
        <button type="submit" class="btn">註冊</button>
      </div>
      <div class="link-out">
        <p>已有帳戶?
          <a href="login.php">登入</a>
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
<!-- 介面依舊需要修改, 避免太長造成不美觀 -->
<!-- 密碼要求需要顯示出來, 完成✓, 未完成✗-->