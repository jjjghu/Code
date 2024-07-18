<?php
$servername = "localhost";
$username = "root";
$password = "root123456";
$dbname = "group_29";

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
// 送出查詢的SQL指令
if (
	$result = mysqli_query($link, "SELECT p.product_name, p.price, c.quantity, (SELECT image_path FROM product_images WHERE product_id = p.id LIMIT 1) AS image 
            FROM cart c 
            JOIN products p ON c.product_id = p.id 
            WHERE c.user_id = 2")
) {
	$data = '';
	while ($row = $result->fetch_assoc()) {
		$product_name = htmlspecialchars($row['product_name']);
		$price = htmlspecialchars($row['price']);
		$quantity = htmlspecialchars($row['quantity']);
		$image = !empty($row['image']) ? htmlspecialchars($row['image']) : 'images/book_big.png';

		$data .= "<div class='preview-product card m-3 shopping-cart'>
                    <div class='row g-0'>
                        <div class='d-flex align-items-center m-3'>
                            <img src='$image' class='preview-image'>
                            <div class='flex-grow-1 ms-3'>
                                <div class='card-body shopping-cart w-75'>
                                    <h5 class='card-title clamp-lines'>$product_name</h5>
                                    <p class='card-text product-price' data-price='$price'>
                                        $" . $price * $quantity . "
                                    </p>
                                    <div class='btn-group' role='group' aria-label='Quantity'>
                                        <button type='button' class='btn btn-secondary decrement'>-</button>
                                        <input min='0' value='$quantity' type='number' class='btn btn-outline-secondary quantity text-Nmain'>
                                        <button type='button' class='btn btn-secondary increment'>+</button>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </div>
                  </div>";
	}
	mysqli_free_result($result); // 釋放佔用的記憶體
}
mysqli_close($link); // 關閉資料庫連結
?>
<!DOCTYPE html>
<html lang="en">

<head>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1.0" />
	<title>購物車</title>
	<link href="bootstrap-5.3.2-dist/css/bootstrap.min.css" rel="stylesheet">
	<?php include '.Style.php'; ?>
</head>
<?php include '.Theme.php'; ?>

<body class="<?php echo htmlspecialchars($theme); ?>">
	<!-- 標題橫條 + 切換按鈕 -->
	<?php include '.Header.php'; ?>
	<!-- 主要頁面內容開始 -->
	<main class="container my-5 mt-10vh">
		<div class="row">
			<!-- 商品列表 -->
			<div class="col-md-8">
				<h2>購物車</h2>
				<?php echo $data; ?>
			</div>
		</div>
	</main>
	<!-- 主要頁面內容結束 -->
	<?php include '.Footer.php'; ?>
	<?php include '.Script.php'; ?>
</body>

</html>