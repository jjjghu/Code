<?php
$servername = "localhost";
$username = "root";
$password = "root123456";
$dbname = "db_product";

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


$pid = $_GET['pid'];
$sql = "SELECT * FROM product where pid='$pid'";
$result = $link->query($sql);
$data = "";
$i = 0;
// 送出查詢的SQL指令
if ($result->num_rows > 0) {
	while ($row = $result->fetch_assoc()) {
		$data .= "<tr><td><div><img src='images/$row[pic]' /><br><b>$row[name]</b><br>價格：<span style='color:red'>$row[price]</span><br>庫存量：$row[stock]</div><hr>$row[description]<div><a href='product.php'>回上一頁</a></div></td></tr>";
		++$i;
	}
	mysqli_free_result($result); // 釋放佔用的記憶體
}
$link->close(); // 關閉資料庫連結
?>
<!DOCTYPE html>
<html>

<head>
	<meta charset="UTF-8">
	<title>商品詳細內容</title>
	<style>
		td {
			padding: 30px;
		}

		div {
			text-align: center;
		}
	</style>
</head>

<body>
	<table border="1" align="center" width="500">
		<?php echo $data; ?>
	</table>
</body>

</html>