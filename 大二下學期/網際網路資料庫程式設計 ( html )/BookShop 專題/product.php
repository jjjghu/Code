<!DOCTYPE html>
<html lang="zh-Hant-TW">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>商品頁面</title>
    <?php include '.Style.php' ?>
    <?php include '.LinkSql.php'; ?>
</head>
<?php include '.Theme.php'; ?>

<body class=<?php echo $theme ?>>
    <!-- 標題橫條 + 切換按鈕 -->
    <?php include '.Header.php'; ?>
    <?php include '.ProductDetail.php'; ?>
    <main class="container text-center">
        <div class="row">
            <div class="col-md-6">
                <!-- 距離標題 10vh -->
                <div class="slider-wrapper product mt-10vh">
                    <div class="slider product">
                        <?php foreach ($images as $index => $image_path): ?>
                            <img id="slider-<?php echo $index + 1; ?>" src="<?php echo $image_path; ?>"
                                alt="slider <?php echo $index + 1; ?>">
                        <?php endforeach; ?>
                    </div>
                    <div class="slider-nav product">
                        <?php foreach ($images as $index => $image_path): ?>
                            <a data-index="<?php echo $index; ?>"></a>
                        <?php endforeach; ?>
                    </div>
                    <!-- 上下頁面 -->
                    <?php
                    if (count($images) > 0) {
                        echo '<div class="prev-arrow fs-2"><i class="bx bx-chevron-left"></i></div>';
                        echo '<div class="next-arrow fs-2"><i class="bx bx-chevron-right"></i></div>';
                    }

                    ?>
                </div>
            </div>
            <!-- 文字靠左, 距離頂部10vh-->
            <div class="col-md-6 mt-10vh text-start">
                <h2 class='fs-1 mt-2'> <?php echo $product_name ?></h2>
                <p class='fs-4 text-orange mt-3'><span class='fs-3'>$</span><?php echo $price ?></p>
                <div class='mt-2' id='author'>作者: <?php echo $author_name ?></div>
                <div class='mt-2' id='write_date'>出版日期: <?php echo $write_date ?></div>
                <div class='mt-2' id='category'>分類: <?php echo $category_names ?></div>
                <!-- 按鈕靠左 -->
                <div class="d-flex justify-content-start mt-3">
                    <button class="btn btn-primary me-2" id='add-to-cart'><i
                            class="bx bx-cart-add me-1"></i>加入購物車</button>
                    <button class="btn btn-success">直接購買</button>
                </div>
            </div>
        </div>
    </main>
    <!-- 簡介區域, 透過按鈕導覽 -->
    <div class="container mt-5">
        <div class="row">
            <!-- 橫向12個物件 -->
            <div class="col-md-12">
                <!-- role: 無障礙訪問 (從bootstrap 文檔上看到的, 用不用沒有太大差別) -->
                <ul class="nav nav-tabs bold-hr" role="tablist">
                    <!-- nav-item, 導覽物件, nav-link 導覽連接, active 為預設選取的東西 -->
                    <li class="nav-item">
                        <a class="nav-link active text_effect" data-bs-toggle="tab" href="#content-intro">內容簡介</a>
                    </li>
                    <li class="nav-item">
                        <a class="nav-link text_effect" data-bs-toggle="tab" href="#content-details">詳細資料</a>
                    </li>
                    <li class="nav-item">
                        <a class="nav-link text_effect" data-bs-toggle="tab" href="#content-author">作者介紹</a>
                    </li>
                    <li class="nav-item">
                        <a class="nav-link text_effect" data-bs-toggle="tab" href="#content-comments">留言區</a>
                        <!-- 外部連接留言區 -->
                    </li>
                </ul>
                <!-- table-content -->
                <div class="tab-content mt-3">
                    <div class="tab-pane fade show active" id="content-intro">
                        <p><?php echo $product_description ?></p>
                    </div>
                    <div class="tab-pane fade" id="content-details">
                        <p><?php echo $product_content ?></p>
                    </div>
                    <div class="tab-pane fade" id="content-author">
                        <p><?php echo $author_bio ?> </p>
                    </div>
                    <div class="tab-pane fade" id="content-comments">
                        <div class="comment-section">
                            <div class="comment">
                                <div class="d-flex justify-content-between">
                                    <div class="d-flex align-items-center">
                                        <img src="images/book.png" class="comment-image me-2">
                                        <span class="comment-username">桂桂的鹹辣豆汁</span>
                                    </div>
                                    <span class="comment-time">17:57, 2024-05-20</span>
                                </div>
                                <div class="comment-content">
                                    啊啊啊啊啊啊啊啊啊啊啊我要去我要去！
                                </div>
                            </div>
                            <div class="comment">
                                <div class="d-flex justify-content-between">
                                    <div class="d-flex align-items-center">
                                        <img src="images/book.png" class="comment-image me-2">
                                        <span class="comment-username">桂桂的鹹辣豆汁</span>
                                    </div>
                                    <span class="comment-time">17:57, 2024-05-20</span>
                                </div>
                                <div class="comment-content ">
                                    啊啊啊啊啊啊啊啊啊啊啊我要去我要去！
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
        <div class="bold-hr"></div>
    </div>
    <div class="container mt-5">
        <pre>
不同比例的圖片都必須要能夠顯示
商品放大鏡 或是詳細查看的頁面
商品推薦(相同作者的書籍, 相似主題的書籍)
現正熱賣 
</pre>
        <!-- 推薦書籍, 最近閱覽,　 -->
    </div>
    <!-- 一個可透過按鈕選取要查看的內容, 內容簡介, 詳細資料, 作者介紹, 留言區  -->
    <!-- footer 開始 -->
    <?php include '.Footer.php'; ?>
    <!-- footer結束 -->
</body>

</html>

<!-- 
作者： 貓膩
出版社：人民文學出版社
出版日期：2017/04/01
語言：簡體中文
定價：234元
優惠價：87折204元
內容簡介
詳細資料
ISBN：9787020127238
規格：493頁 / 21 x 14.8 x 1.5 cm / 普通級 / 1-1
出版地：中國
本書分類：文學小說> 愛情小說> 原創古典小說
推薦商品
最近瀏覽商品
購物說明
Footer
 -->
</body>
<?php include '.Script.php' ?>

</html>