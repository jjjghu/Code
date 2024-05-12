<?php
//Cookie 課堂練習--網頁個人化設定
session_start();

if (isset($_COOKIE['counter']))
    $cnt = $_COOKIE['counter'] + 1;
else
    $cnt = 1;
setcookie('counter', $cnt, time() + 88888);

if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    $font_color = $_POST['c1'] ?? 'black';
    $font_size = $_POST['s1'] ?? '16';
    setcookie('font_color', $font_color, time() + 88888);
    setcookie('font_size', $font_size, time() + 88888);
} else {
    $font_color = $_COOKIE['font_color'] ?? 'black';
    $font_size = $_COOKIE['font_size'] ?? '16';
}
?>
<html>

<head>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
    <title> Cookie 練習</title>
    <style type="text/css">
        table
        {
            font-size: <?php echo $font_size ?>px;
            color:  <?php echo $font_color ?>;
        }
    </style>
</head>

<body>
    <div>
        <form name="form1" action="" method="POST">
            字體顏色：<input name="c1" type="text" size="7" value="<?php echo $font_color; ?>">
            字體大小：<input type="text" name="s1" size="3" value="<?php echo $font_size; ?>"> px
            <input type="submit" name="submit" value="送出">
        </form>
        您是第 <span style="color:blue;font-weight:bold"><?php echo $cnt; ?></span> 次瀏覽本網頁
        <p></p>
        <table border="0" cellspacing="0" cellpadding="2">
            <tr>
                <td colspan="2">王翰《涼州詞》</td>
            </tr>
            <tr>
                <td>葡萄美酒夜光杯，</td>
                <td>欲飲琵琶馬上催。</td>
            </tr>
            <tr>
                <td>醉臥沙場君莫笑，</td>
                <td>古來征戰幾人回。</td>
            </tr>
        </table>
    </div>
</body>

</html>