<!DOCTYPE html>
<html lang="zh-Hant-TW">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>書店Demo</title>
    <!-- Bootstrap CSS -->
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css">
    <!-- Bootstrap 圖標 -->
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap-icons@1.8.1/font/bootstrap-icons.css">
    <!-- 自定義 CSS -->
    <link href="css/bookshop.css" rel="stylesheet">
    <!-- boxIcons -->
    <link href='https://unpkg.com/boxicons@2.1.4/css/boxicons.min.css' rel='stylesheet'>
</head>

<!-- 預設黑暗模式 body開始 -->

<body class="dark-theme">
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
            <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarNavDropdown"
                aria-controls="navbarNavDropdown" aria-expanded="false" aria-label="Toggle navigation">
                <span class="navbar-toggler-icon"></span>
            </button>
            <!-- 小視窗切換按鈕結束 -->
            <!-- 導覽連結開始 -->

            <div class="navbar-collapse justify-content-end " id="navbarNavDropdown">
                <ul class="navbar-nav fs-5 text-Nmain">
                    <!-- me-3 = margin-right... why?-->
                    <li class="nav-item title-nav me-3 ">
                        <div class="d-flex align-items-center text-Nmain">
                            <a class="nav-link text-Nmain" href="login.html"><i class='bx bx-user'></i>登入</a>
                            <span>|</span>
                            <a class="nav-link text-Nmain" href="register.html">註冊</a>
                        </div>
                    </li>
                    <li class="nav-item title-nav me-3">
                        <a class="nav-link text-Nmain" href="#"><i class="bx bx-home me-1"></i>會員中心</a>
                    </li>
                    <li class="nav-item title-nav me-3">
                        <a class="nav-link text-Nmain" href="#">
                            <span class='red-dot' id='payMeMoney'>2</span>
                            <i class="bx bx-cart me-1"></i>購物車
                        </a>
                        <div class="cart-items">
                            <!-- Shopping Item -->
                            <div class="shopping-item" id="shopping-item">
                                <div class="dropdown-cart-header">
                                    <span>2 項商品</span>
                                    <a href="cart.html">前往購物車</a>
                                </div>
                                <ul class="shopping-list">
                                    <link>
                                    <div class="cart-img-head">
                                        <a class="cart-img" href="product-details.html"><img src="images/book.png"
                                                alt="#"></a>
                                    </div>

                                    <div class="content">
                                        <h4><a href="product-details.html">獸靈之詩</a></h4>
                                        <p class="quantity">1x - <span class="amount">$199</span></p>
                                    </div>
                                    </link>
                                    <li>
                                        <div class="cart-img-head">
                                            <a class="cart-img" href="product-details.html"><img src="images/book.png"
                                                    alt="#"></a>
                                        </div>
                                        <div class="content">
                                            <h4><a href="product-details.html">玻璃彈珠都是貓的眼睛</a></h4>
                                            <p class="quantity">1x - <span class="amount">$399</span></p>
                                        </div>
                                    </li>
                                </ul>
                                <div class="bottom">
                                    <div class="total">
                                        <span>Total</span>
                                        <span class="total-amount">$598</span>
                                    </div>
                                    <div class="button">
                                        <a href="checkout.html" class="btn animate">結帳</a>
                                    </div>
                                </div>
                            </div>
                            <!--/ End Shopping Item -->
                        </div>
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
    <!-- 主要頁面內容開始 -->
    <main>
        <!-- 購物車內容開始 
        <section class="cartTab">
            <h1 class='fw-light p-1'>Shopping Cart</h1>
            <div class="listCart">
                <div class="item">
                    <div class="image">

                    </div>
                    <div class="name">

                    </div>
                    <div class="totalPrice">

                    </div>
                    <div class="quantity">
                        <span class='minus'></span>
                        <span>1</span>
                        <span class='plus'></span>
                    </div>

                </div>
            </div>
            <div class='btnGroup'>
                <button class='btn btn-success'>關閉</button>
                <button class='btn btn-success'>結帳</button>
            </div>
        </section>
        -->
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
                $products = [
                    ["name" => "Product 1", "image" => "https://via.placeholder.com/150", "price" => "$1.99"],
                    ["name" => "Product 2", "image" => "https://via.placeholder.com/150", "price" => "$2.99"],
                    ["name" => "Product 3", "image" => "https://via.placeholder.com/150", "price" => "$33.99"],
                    ["name" => "Product 4", "image" => "https://via.placeholder.com/150", "price" => "$44.52"],
                    ["name" => "Product 5", "image" => "https://via.placeholder.com/150", "price" => "$52"],
                    ["name" => "Product 6", "image" => "https://via.placeholder.com/150", "price" => "$66"],
                    ["name" => "Product 7", "image" => "https://via.placeholder.com/150", "price" => "$77"],
                ];
                foreach ($products as $product) {
                    echo "<div class='col-md-2'>
                              <a href='product.html' class='card-link text-decoration-none text-primary'>
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
    <footer class="bottom d-flex justify-content-between align-items-center py-3">
        <div class="container d-flex justify-content-between">
            <div class="col-md-4 d-flex align-items-center ">
                <span class="mb-3 mt-3">Copyright © 2024 閱緣書坊 All right reserved</span>
            </div>
            <form>
                <div class="input-group mt-2">
                    <input type="email " class="sub form-control" placeholder="訂閱電子報">
                    <button class="btn btn-primary" type="submit">訂閱</button>
                </div>
            </form>
            <ul class="nav col-md-4 justify-content-end mt-3">
                <li class="ms-3"><a class="text-body-secondary" href="#"><i
                            class='bx bxl-facebook-circle footerIcon'></i></a>
                <li class="ms-3"><a class="text-body-secondary" href="#"><i class='bx bxl-instagram footerIcon'></i></a>
                <li class="ms-3"><a class="text-body-secondary" href="#"><i class='bx bxl-youtube footerIcon'></i></a>
            </ul>
        </div>
    </footer>
    <!-- footer結束 -->
</body>
<!-- Bootstrap js連結 -->
<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js"></script>
<!--自定義js連結 -->
<script src="js/bookshop.js"></script>

</html>