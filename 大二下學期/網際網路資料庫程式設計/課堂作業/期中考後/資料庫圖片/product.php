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

$i = 0;
$data = "";
$sql = "SELECT * FROM product";
$result = $link->query($sql);
// 送出查詢的SQL指令
if ($result->num_rows > 0) {
	while ($row = $result->fetch_assoc()) {
		if ($i % 4 == 0) {
			if ($i > 0) {
				$data .= "</tr>";
			}
			$data .= "<tr align='center'>";
		}
		$data .= "<td><img width='200' height='200' src='images/$row[pic]' /><br><b><a href='detail.php?pid=$row[pid]'>$row[name]</a></b><br>價格：<span style='color:red'>$row[price]</span><br>庫存量：$row[stock]</td>";
		++$i;
	}
	$data .= "</tr>";
	mysqli_free_result($result);
}
$link->close();
?>
<!DOCTYPE html>
<html>

<head>
	<meta charset="UTF-8">
	<title>顯示所有商品(圖片)內容</title>
	<style>
		td {
			padding: 30px;
		}
	</style>
</head>

<body>
	<table border="1" align="center">
		<?php echo $data; ?>
	</table>
</body>

</html>