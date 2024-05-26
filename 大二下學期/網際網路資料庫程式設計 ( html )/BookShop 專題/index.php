<!DOCTYPE html>
<html lang="zh-Hant-TW">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>閱緣書坊</title>
    <!-- 樣式 -->
    <?php include '.Style.php' ?>
    <!-- 連結資料庫 -->
    <?php include '.LinkSql.php'; ?>
    <!-- 搜尋資料 -->
    <?php include '.ProductFilter.php'; ?>
</head>
<!-- 主題切換 -->
<?php include '.Theme.php'; ?>

<body class=<?php echo $theme ?>>
    <!-- 標題橫條 + 切換按鈕 -->
    <?php include '.Header.php'; ?>
    <!-- 主要頁面內容開始 -->
    <main>
        <section>
            <!-- 廣告輪播區域開始 -->
            <section class="container ">
                <div class="slider-wrapper mt-10vh">
                    <!-- 廣告圖片開始 -->
                    <div class="slider">
                        <img id="slide-1" src="images/book.png" alt="slider 1">
                        <img id="slide-2"
                            src="https://plus.unsplash.com/premium_photo-1709311394823-8b0856db0bcc?q=80&w=1171&auto=format&fit=crop&ixlib=rb-4.0.3&ixid=M3wxMjA3fDB8MHxwaG90by1wYWdlfHx8fGVufDB8fHx8fA%3D%3D"
                            alt="slider 2">
                        <img id="slide-3"
                            src="https://images.unsplash.com/photo-1654859869130-fd0a2aa5539b?q=80&w=1228&auto=format&fit=crop&ixlib=rb-4.0.3&ixid=M3wxMjA3fDB8MHxwaG90by1wYWdlfHx8fGVufDB8fHx8fA%3D%3D"
                            alt="slider 3">
                    </div>
                    <!-- 廣告圖片結束 -->
                    <!-- 廣告輪播按鈕開始 (下方的三個點) -->
                    <div class="slider-nav">
                        <a data-index="0"></a>
                        <a data-index="1"></a>
                        <a data-index="2"></a>
                    </div>
                    <!-- 廣告輪播按鈕結束 -->
                    <!-- 上一頁箭頭按鈕 -->
                    <a class="prev-arrow fs-2"><i class='bx bx-chevron-left'></i></a>
                    <!-- 下一頁箭頭按鈕 -->
                    <div class="next-arrow fs-2"><i class='bx bx-chevron-right'></i></div>
                </div>
            </section>
            <!-- 廣告輪播區域結束 -->
            <!-- 商品購買區域開始 -->
            <section class="container mt-5">
                <!--分類按鈕開始 -->
                <div class="row mb-4">
                    <div class="col-md-6">
                        <div class="dropdown">
                            <button class="btn btn-secondary dropdown-toggle" type="button" id="dropdownMenuButton"
                                data-bs-toggle="dropdown" aria-expanded="false">
                                <?php echo htmlspecialchars($current_category_name); ?>
                            </button>
                            <ul class="dropdown-menu" aria-labelledby="dropdownMenuButton">
                                <?php foreach ($categories as $category): ?>
                                    <li><a class="dropdown-item"
                                            href="?category=<?php echo $category['id']; ?>"><?php echo htmlspecialchars($category['name']); ?></a>
                                    </li>
                                <?php endforeach; ?>
                            </ul>
                        </div>
                    </div>
                    <div class="col-md-6 d-flex justify-content-end">
                        <form id='search-box' action="" method="get" class="input-group">
                            <input type="search" name="search" class="form-control" placeholder="搜尋商品..."
                                value="<?php echo htmlspecialchars($search); ?>">
                            <input type="hidden" name="category" value="<?php echo $current_category_id; ?>">
                            <button type="submit" class="btn btn-primary bx bx-search"></button>
                        </form>
                    </div>
                </div>
                <!-- 購物列表 -->
                <div class="row" id="shopping-list">
                    <?php if (!empty($products)): ?>
                        <?php foreach ($products as $product): ?>
                            <div class='col-md-2' title='<?php echo htmlspecialchars($product["name"]); ?>'>
                                <a href='product.php?id=<?php echo $product["id"]; ?>'
                                    class='card-link text-decoration-none text-primary'>
                                    <div class='card mb-3 d-flex flex-column'>
                                        <img src='<?php echo $product["image"]; ?>' class='card-img-top' alt='Product Image'>
                                        <!-- 確保價格放在最低處, 就算文字過長也一樣 -->
                                        <div class='card-body d-flex flex-column'>
                                            <h5 class='card-title text-Nmain clamp-lines mb-auto'>
                                                <?php echo htmlspecialchars($product["name"]); ?>
                                            </h5>
                                            <!-- 購物車按鈕將物品加入購物車, 而不是 product, 使用 javascript 避免回到頁首-->
                                            <a class='cart-link' href="#">
                                                <button class='btn cart' aria-label='購物車圖示'><i class='bi bi-cart'></i></button>
                                            </a>
                                            <p class='card-text fw-bold text-orange mt-auto'><?php echo $product["price"]; ?>
                                            </p>
                                        </div>
                                    </div>
                                </a>
                            </div>
                        <?php endforeach; ?>
                    <?php else: ?>
                        <div>沒有找到商品資料</div>
                    <?php endif; ?>
                </div>
            </section>
            <!-- 商品購買區域結束 -->
        </section>
    </main>
    <?php include '.Footer.php'; ?>
</body>
<?php include '.Script.php' ?>

</html>