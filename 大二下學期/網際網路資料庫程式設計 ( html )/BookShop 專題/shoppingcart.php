<?php 
if (session_status() == PHP_SESSION_NONE) {
    session_start();
}
if (!isset($_SESSION['username'])) {
    header("Location: index.php");
    exit();
}
?>
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>購物車</title>
    <link href="bootstrap-5.3.2-dist/css/bootstrap.min.css" rel="stylesheet">
    <?php include '.Style.php' ?>
</head>
<?php include '.Theme.php'; ?>

<body class=<?php echo $theme ?>>
    <!-- 標題橫條 + 切換按鈕 -->
    <?php include '.Header.php'; ?>
    <!-- 主要頁面內容開始 -->
    <main class="container my-5 mt-10vh">
        <div class="row">
            <!-- 商品列表 -->
            <div class="col-md-8">
                <h2>購物車</h2>
                <?php
                $quantity = 1;
                $pre_products = [
                    ['name' => '關於我為甚麼變成勇者之後拿著一把玩具刀亂砍義大利麵的起因與後續', 'image' => 'images/book.png', 'price' => '123.00', 'quantity' => 1],
                    ['name' => '廢線彼端的人造神明', 'image' => 'images/book.png', 'price' => '123.00', 'quantity' => 1],
                    ['name' => '玻璃彈珠都是貓的眼睛', 'image' => 'images/book.png', 'price' => '55688.00', 'quantity' => 1],
                    ['name' => '大話設計模式', 'image' => 'images/book.png', 'price' => '9527.00', 'quantity' => 20],
                    ['name' => '奧本海默', 'image' => 'images/book.png', 'price' => '9527.00', 'quantity' => 1],
                    ['name' => '擇天記', 'image' => 'images/book.png', 'price' => '500.00', 'quantity' => 1],
                    ['name' => '有關星神的二三事', 'image' => 'images/book.png', 'price' => '9527.00', 'quantity' => 1],
                    ['name' => '物種起源', 'image' => 'images/book.png', 'price' => '42.00', 'quantity' => 1],
                    ['name' => '三體', 'image' => 'images/book.png', 'price' => '3.333', 'quantity' => 1],
                    ['name' => '發呆改變世界', 'image' => 'images/book.png', 'price' => '777.00', 'quantity' => 1],
                    ['name' => '我的小鯊魚', 'image' => 'images/book.png', 'price' => '22.00', 'quantity' => 1],
                    ['name' => '最幸福的人', 'image' => 'images/book.png', 'price' => '99.00', 'quantity' => 1],
                    ['name' => '為甚麼你總是學不會?', 'image' => 'images/book.png', 'price' => '22.00', 'quantity' => 1],
                    ['name' => '銀河鐵道之夜', 'image' => 'images/book.png', 'price' => '22.00', 'quantity' => 1]
                ];
                ?>
                <?php foreach ($pre_products as $product): ?>
                    <div class="preview-product card m-3 shopping-cart">
                        <div class="row g-0">
                            <div class="d-flex align-items-center m-3">
                                <img src="<?php echo $product['image']; ?>" class="preview-image">
                                <div class="flex-grow-1 ms-3">
                                    <div class="card-body shopping-cart w-75">
                                        <h5 class="card-title clamp-lines">
                                            <?php echo $product['name']; ?>
                                        </h5>
                                        <p class="card-text product-price" data-price="<?php echo $product['price']; ?>">
                                            $<?php echo $product['price'] * $product['quantity']; ?></p>
                                        <div class="btn-group" role="group" aria-label="Quantity">
                                            <button type="button" class="btn btn-secondary decrement">-</button>
                                            <input min="0" value='<?php echo $product['quantity']; ?>' type='number'
                                                class="btn btn-outline-secondary quantity text-Nmain">
                                            <button type="button" class="btn btn-secondary increment">+</button>
                                        </div>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </div>
                <?php endforeach; ?>
            </div>
            <!-- 購物車摘要 -->
            <div class="col-md-4">
                <h2>總結</h2>
                <ul class="list-group mt-3" id="summary-list">
                    <?php
                    $total = 0;
                    foreach ($pre_products as $product):
                        $productTotal = $product['price'] * $product['quantity'];
                        $total += $productTotal;
                        ?>
                        <li class="list-group-item d-flex justify-content-between lh-sm ">
                            <div class="w-75">
                                <h6 class="my-0 clamp-lines"><?php echo $product['name']; ?></h6>
                            </div>

                            <span class="text-muted product-total w-25" data-price="<?php echo $product['price']; ?>">$
                                <?php echo $productTotal; ?>
                            </span>
                        </li>
                    <?php endforeach; ?>
                    <li class="list-group-item d-flex justify-content-between">
                        <h5><strong><span class="text-orange">總計</span></strong></h5>
                        <h5><strong class="text-orange  w-25">$<span id="total-price"><?php echo $total; ?></span></strong>
                        </h5>
                    </li>
                </ul>
                <button class="btn btn-success btn-lg btn-block mt-3 w-100">結帳</button>
            </div>

        </div>
    </main>
    <!-- 主要頁面內容結束 -->
    <?php include '.Footer.php'; ?>
    <?php include '.Script.php' ?>
</body>

</html>