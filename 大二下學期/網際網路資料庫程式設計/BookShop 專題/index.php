<!DOCTYPE html>
<html lang="zh-Hant-TW">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>書店Demo</title>
    <?php include '.Style.php' ?>
</head>

<?php include '.Theme.php'; ?>
<!-- 標題橫條 + 切換按鈕 -->
<?php include '.Header.php'; ?>
<!-- 主要頁面內容開始 -->
<main>
    <!-- 廣告輪播區域開始 -->
    <section class="container ">
        <div class="slider-wrapper mt-10vh">
            <!-- 廣告圖片開始 -->
            <div class="slider">
                <img id="slide-1"
                    src="https://images.unsplash.com/photo-1712417827761-7a68ff4a90f3?q=80&w=2670&auto=format&fit=crop&ixlib=rb-4.0.3&ixid=M3wxMjA3fDB8MHxwaG90by1wYWdlfHx8fGVufDB8fHx8fA%3D%3D"
                    alt="slider 1">
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
                        選擇分類
                    </button>
                    <ul class="dropdown-menu" aria-labelledby="dropdownMenuButton">
                        <li><a class="dropdown-item" href="#">分類 1</a></li>
                        <li><a class="dropdown-item" href="#">分類 2</a></li>
                        <li><a class="dropdown-item" href="#">分類 3</a></li>
                    </ul>
                </div>
            </div>
            <div class="col-md-6">
                <input type="search" class="form-control" placeholder="搜尋商品...">
            </div>
        </div>
        <!-- 購物列表 -->
        <div class="row" id="shopping-list">
            <?php
            $picture = "https://via.placeholder.com/150";
            $products = [
                ["name" => "Product 1", "image" => $picture, "price" => "$1.99"],
                ["name" => "Product 2", "image" => $picture, "price" => "$2.99"],
                ["name" => "Product 3", "image" => $picture, "price" => "$33.99"],
                ["name" => "Product 4", "image" => $picture, "price" => "$44.52"],
                ["name" => "Product 5", "image" => $picture, "price" => "$52"],
                ["name" => "Product 6", "image" => $picture, "price" => "$66"],
                ["name" => "Product 7", "image" => $picture, "price" => "$77"],
            ];
            foreach ($products as $product) {
                echo "<div class='col-md-2'>
                              <a href='product.php' class='card-link text-decoration-none text-primary'>
                                  <div class='card mb-3'>
                                      <img src='{$product['image']}' class='card-img-top' alt='Product Image'>
                                      <div class='card-body'>
                                          <h5 class='card-title text-Nmain'>{$product['name']}</h5>
                                          <p class='card-text fw-bold text-orange'>{$product['price']}</p>
                                      </div>
                              </a>
                              <button class='btn cart' aria-label='購物車圖示'><i class='bi bi-cart'></i></button>
                            </div>
                          </div>";
            }
            ?>
        </div>
        </div>
    </section>
    <!-- 商品購買區域結束 -->
</main>
<!-- 主要頁面內容開始 -->
<!-- footer 開始 -->
<?php include '.Footer.php'; ?>
<!-- footer結束 -->
</body>
<?php include '.Script.php' ?>

</html>