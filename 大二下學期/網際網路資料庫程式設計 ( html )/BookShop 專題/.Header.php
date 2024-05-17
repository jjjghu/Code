<!DOCTYPE html>
<html lang="zh-tw">

<head>
    <meta charset="UTF-8">
    <title>Header</title>
</head>

<body>
    <header>
        <!-- 固定位置的物件放在最上面 -->
        <!-- 暗黑模式切換按鈕 -->
        <i class='bx bx-moon bx-rotate-270 themeIcon' id="themeIcon"></i>
        <!-- 標題橫條開始 -->
        <nav class="navbar navbar-expand-lg justify-content-between align-items-center fixed-top">
            <div class="container-fluid d-flex justify-content-between">
                <!--標題圖片文字開始 -->
                <a class="text-decoration-none fs-2 text-Nmain col-md-4 d-flex align-items-center" href="index.php">
                    <img src="images/book.png" alt="" class="d-inline-block  align-text-top">
                    閱緣書坊
                </a>
                <!--標題圖片文字結束 -->
                <!-- 小視窗切換按鈕開始 -->
                <button class="navbar-toggler" type="button" data-bs-toggle="collapse"
                    data-bs-target="#navbarNavDropdown" aria-controls="navbarNavDropdown" aria-expanded="false"
                    aria-label="Toggle navigation">
                    <span class="navbar-toggler-icon"></span>
                </button>
                <!-- 小視窗切換按鈕結束 -->
                <!-- 導覽連結開始 -->
                <div class="navbar-collapse justify-content-end " id="navbarNavDropdown">
                    <ul class="navbar-nav fs-5 text-Nmain">
                        <!-- me-3 = margin-right... why?-->
                        <li class="nav-item title-nav me-3 ">
                            <div class="d-flex align-items-center text-Nmain">
                                <a class="nav-link text-Nmain" href="login.php"><i class='bx bx-user'></i>登入</a>
                                <span>|</span>
                                <a class="nav-link text-Nmain" href="register.php">註冊</a>
                            </div>
                        </li>
                        <li class="nav-item title-nav me-3">
                            <a class="nav-link text-Nmain" href="#"><i class="bx bx-home me-1"></i>會員中心</a>
                        </li>
                        <li class="nav-item title-nav me-3">
                            <div class="nav-link text-Nmain" id='toggleCart'>
                                <span class='red-dot' id='cart-count'>0</span>
                                <i class="bx bx-cart me-1"></i>購物車
                            </div>
                            <!-- 購物車預覽頁面開始 -->
                            <div id='cart-preview'>
                                <!-- 商品列表開始 -->
                                <div id='product-list'>
                                    <!-- 商品資訊開始 -->
                                    <?php
                                    $products = [
                                        ['name' => '廢線彼端的人造神明', 'image' => '/images/book.png', 'price' => '123.00', 'quantity' => 1],
                                        ['name' => '玻璃彈珠都是貓的眼睛', 'image' => '/images/book.png', 'price' => '55688.00', 'quantity' => 1],
                                        ['name' => '大話設計模式', 'image' => '/images/book.png', 'price' => '9527.00', 'quantity' => 20],
                                        ['name' => '奧本海默', 'image' => '/images/book.png', 'price' => '9527.00', 'quantity' => 1],
                                        ['name' => '擇天記', 'image' => '/images/book.png', 'price' => '500.00', 'quantity' => 1],
                                        ['name' => '有關星神的二三事', 'image' => '/images/book.png', 'price' => '9527.00', 'quantity' => 1],
                                        ['name' => '物種起源', 'image' => '/images/book.png', 'price' => '42.00', 'quantity' => 1],
                                        ['name' => '三體', 'image' => '/images/book.png', 'price' => '3.333', 'quantity' => 1],
                                        ['name' => '發呆改變世界', 'image' => '/images/book.png', 'price' => '777.00', 'quantity' => 1],
                                        ['name' => '我的小鯊魚', 'image' => '/images/book.png', 'price' => '22.00', 'quantity' => 1],
                                        ['name' => '最幸福的人', 'image' => '/images/book.png', 'price' => '99.00', 'quantity' => 1],
                                        ['name' => '為甚麼你總是學不會?', 'image' => '/images/book.png', 'price' => '22.00', 'quantity' => 1],
                                        ['name' => '我的小鯊魚', 'image' => '/images/book.png', 'price' => '22.00', 'quantity' => 1],
                                        ['name' => '銀河鐵道之夜', 'image' => '/images/book.png', 'price' => '22.00', 'quantity' => 1]
                                    ];
                                    ?>
                                    <?php foreach ($products as $product): ?>
                                        <div class="preview-product py-3">
                                            <!-- 商品圖片 -->
                                            <div class="d-flex align-items-center mb-3">
                                                <img src="<?php echo $product['image']; ?>" class="preview-image ">
                                                <div><?php echo $product['name']; ?></div>
                                            </div>
                                            <!-- 數量和價格 -->
                                            <div class="d-flex justify-content-between align-items-center">
                                                <div class="btn-group" role="group" aria-label="Quantity">
                                                    <button type="button" class="btn btn-secondary decrement">-</button>
                                                    <input min="0" value='<?php echo $product['quantity']; ?>' type='number'
                                                        class="btn btn-outline-secondary quantity text-Nmain"></input>
                                                    <button type="button" class="btn btn-secondary increment">+</button>
                                                </div>
                                                <div class='me-3 productPrice'>$<?php echo $product['price'] * $product['quantity']; ?>
                                                </div>
                                            </div>
                                        </div>
                                    <?php endforeach; ?>
                                    <!-- 商品資訊結束 -->
                                </div>
                                <!-- 商品列表結束 -->
                                <div class='mt-3' id='productSum'>總價格:</div>
                                <div class='btn btn-success mt-3'>結帳</div>
                            </div>
                            <!-- 購物車預覽頁面結束 -->
                        </li>
                        <li class="nav-item title-nav ">
                            <a class="nav-link text-Nmain" href="#"><i class="bx bx-book-open me-1"></i>電子書櫃</a>
                        </li>
                    </ul>
                </div>
            </div>
            <!-- 導覽連結結束 -->
        </nav>
        <!-- 標題橫條結束 -->
    </header>