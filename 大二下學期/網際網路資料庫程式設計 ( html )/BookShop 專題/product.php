<!DOCTYPE html>
<html lang="zh-Hant-TW" class="">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>商品頁面</title>
    <?php include '.Style.php' ?>
</head>

<?php include '.Theme.php'; ?>
    <!-- 標題橫條 + 切換按鈕 -->
    <?php include '.Header.php'; ?>
    <!-- 廣告輪播區域 -->
    <div class="container text-center">
        <div class="row">
            <div class="col-md-6">
                <!-- 距離標題 10vh -->
                <div class="slider-wrapper product mt-10vh">
                    <div class="slider product">
                        <!-- 三張廣告圖片 -->
                        <!-- https://images.unsplash.com/photo-1682686581498-5e85c7228119?q=80&w=1170&auto=format&fit=crop&ixlib=rb-4.0.3&ixid=M3wxMjA3fDF8MHxwaG90by1wYWdlfHx8fGVufDB8fHx8fA%3D%3D -->
                        <img id="slider-1"
                            src="https://plus.unsplash.com/premium_photo-1709311394823-8b0856db0bcc?q=80&w=1171&auto=format&fit=crop&ixlib=rb-4.0.3&ixid=M3wxMjA3fDB8MHxwaG90by1wYWdlfHx8fGVufDB8fHx8fA%3D%3D"
                            alt="slider 1">
                        <img id="slider-2" src="images\book.png" alt="slider 2">
                        <img id="slider-3"
                            src="https://upload-os-bbs.hoyolab.com/upload/2023/09/24/7698718/29eade6b3489751ed9550e403d121cd8_8032185747461503023.jpg"
                            alt="slider 3">
                    </div>
                    <!-- 廣告輪播按鈕 -->
                    <div class="slider-nav product">
                        <a data-index="0"></a>
                        <a data-index="1"></a>
                        <a data-index="2"></a>
                    </div>
                    <!-- 上一頁箭頭按鈕 -->
                    <div class="prev-arrow fs-2"><i class='bx bx-chevron-left'></i></div>
                    <!-- 下一頁箭頭按鈕 -->
                    <div class="next-arrow fs-2"><i class='bx bx-chevron-right'></i></div>
                </div>
            </div>
            <!-- 文字靠左, 距離頂部7vh-->
            <div class="col-md-6 mt-10vh text-start">
                <h2 class="fs-1">這是商品名稱</h2>
                <p class="fs-4 text-orange"><span class="fs-3">$</span>20.33</p>
                <!--根據資料庫判斷有沒有對應的資訊, 有救顯示在上面, 沒有就隱藏-->
                <div id="author">作者:</div>
                <div id="language">語言:</div>
                <div id="date-of-publish">出版日期:</div>
                <div id="publisher">出版社</div>
                <!-- 按鈕靠左 -->
                <div class="d-flex justify-content-start mt-3">
                    <button class="btn btn-primary me-2" id='add-to-cart'><i class="bx bx-cart-add me-1"></i>加入購物車</button>
                    <button class="btn btn-success">直接購買</button>
                </div>
            </div>
        </div>
    </div>
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
                    </li>
                </ul>
                <!-- table-content -->
                <div class="tab-content mt-3">
                    <div class="tab-pane fade show active" id="content-intro">
                        <p>這是一本很棒的書</p>
                    </div>
                    <div class="tab-pane fade" id="content-details">
                        <ul>
                            <li>ISBN:9787020127238</li>
                            <li>規格:493頁 / 21 x 14.8 x 1.5 cm / 普通級 / 1-1</li>
                            <li>出版地：中國</li>
                            <li>本書分類：文學小說> 愛情小說> 原創古典小說</li>
                        </ul>
                    </div>
                    <div class="tab-pane fade" id="content-author">
                        <p>這是作者的介紹</p>
                    </div>
                    <div class="tab-pane fade" id="content-comments">
                        <p>這是留言區</p>
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