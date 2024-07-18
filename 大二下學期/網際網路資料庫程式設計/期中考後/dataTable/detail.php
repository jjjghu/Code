<?php
$link = mysqli_connect("localhost", "root", "root123456", "db_product") // 建立MySQL的資料庫連結
 or die("無法開啟MySQL資料庫連結!<br>");

// 送出編碼的MySQL指令
mysqli_query($link, 'SET CHARACTER SET utf8');
mysqli_query($link, "SET collation_connection = 'utf8_unicode_ci'");

$pid = $_GET['pid'];
// 送出查詢的SQL指令
if ($result = mysqli_query($link, "SELECT * FROM product where pid='$pid'")) {
	while ($row = mysqli_fetch_assoc($result)) {
		$data .= "<tr>\r\n<td><div><img src='images/$row[pic]' /><br><b>$row[name]</b><br>價格：<span style='color:red'>$row[price]</span><br>庫存量：$row[stock]</div><hr>$row[description]<div><a href='product.php'>回上一頁</a></div></td>\r\n</tr>\r\n";
		$i++;
	}
	mysqli_free_result($result); // 釋放佔用的記憶體
}
mysqli_close($link); // 關閉資料庫連結
?>
<!DOCTYPE html>
<html>

<head>
<meta charset="UTF-8">
<title>商品詳細內容</title>
<style>
	td{
		padding: 30px;
	}
	div{
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