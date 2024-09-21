<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>

<?php
$servername = "localhost";
$username = "root";
$password = "root123456";
$dbname = "board";

$link = new mysqli($servername, $username, $password, $dbname);
$link = mysqli_connect('localhost', 'root', 'root123456', $dbname);
$message = "";

if ($link->connect_error) {
    $message = "連結錯誤代碼: " . mysqli_connect_errno() . "<br>"; // 顯示錯誤代碼
    $message = "連結錯誤訊息: " . mysqli_connect_error() . "<br>"; // 顯示錯誤訊息
} else {
    $message = "資料庫 $dbname 連結成功!<br>";
}
mysqli_query($link, "SET CHARACTER SET utf8");
mysqli_query($link, "SET collation_connection = 'utf8_unicode_ci'");
// echo $message;

// 獲取表單的輸入
$name = $_POST['name'];
$sex = $_POST['sex'];
$mail = $_POST['mail'];
$subject = $_POST['subject'];
$content = $_POST['content'];

$sql = "INSERT INTO message (subject, name, sex, mail, content, time) VALUES ('$subject', '$name', '$sex', '$mail', '$content', NOW())";

if (mysqli_query($link, $sql)) {
    echo "插入成功";
} else {
    echo "Error: " . $sql . "<br>";
}
?>

<body>

    <div align="center">
        <span style="font-size:15pt;color:blue;font-weight:bold">訪客留言版</span>
        <!-- <form name="form1" method="POST" action="/web/php/examples/board/board.php" data-sharkid="__form__0"> -->
        <form name="form1" method="POST" action="S1154041.php" data-sharkid="__form__0">
            <table border="1" width="50%" id="table1">
                <tbody>
                    <tr>
                        <td width="100" align="center">姓 名</td>
                        <td align="left"><input type="text" name="name" size="20" data-sharkid="__0">　</td>
                    </tr>
                    <tr>
                        <td width="100" align="center">性 別</td>
                        <td align="left"><input type="radio" name="sex" value="M" data-sharkid="__1">男 　<input
                                type="radio" name="sex" value="F" data-sharkid="__2">女　</td>
                    </tr>
                    <tr>
                        <td width="100" align="center">E-mail</td>
                        <td align="left"><input type="text" name="mail" size="30" data-sharkid="__3">　</td>
                    </tr>
                    <tr>
                        <td width="100" align="center">標 題</td>
                        <td align="left"><input type="text" name="subject" size="50" data-sharkid="__4">　</td>
                    </tr>
                    <tr>
                        <td width="100" align="center">留言內容</td>
                        <td align="left"><textarea name="content" rows="10" cols="50" data-sharkid="__5"></textarea>
                        </td>
                    </tr>
                    <tr>
                        <td colspan="2" align="center"><input name="B1" type="submit" value=" 送 出 ">　<input name="B2"
                                type="reset" value=" 回留言版 " onclick="javascript:location.href='list.php'"></td>
                    </tr>
                </tbody>
            </table>
        </form>
        <span></span>
    </div>




</body>

</html>