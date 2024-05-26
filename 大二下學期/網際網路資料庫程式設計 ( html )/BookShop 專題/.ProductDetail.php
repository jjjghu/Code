<?php
$servername = "localhost";
$username = "root";
$password = "root123456";
$dbname = "group_07";

$link = new mysqli($servername, $username, $password, $dbname);

if ($link->connect_error) {
    die("連結失敗: " . $link->connect_error);
}

mysqli_query($link, "SET CHARACTER SET utf8");
mysqli_query($link, "SET collation_connection = 'utf8_unicode_ci'");

$product_id = isset($_GET['id']) ? intval($_GET['id']) : 0;

if ($product_id > 0) {
    // 查詢商品基本資訊和內容
    $sql = "SELECT 
                p.product_name, 
                p.price, 
                a.penName AS author_name, 
                a.bio AS author_bio, 
                p.write_date, 
                pc.description AS product_description, 
                pc.content AS product_content 
            FROM products p
            JOIN author a ON p.author_id = a.id
            JOIN product_contents pc ON p.id = pc.product_id
            WHERE p.id = $product_id";
    $result = $link->query($sql);

    if ($result->num_rows == 1) {
        $row = $result->fetch_assoc();

        // 後兩位數都是 0 就只顯示整數
        $price = floatval($row['price']);
        // 後兩位數都是 0 就只顯示整數
        $formatted_price = ($price == intval($price)) ? intval($price) : number_format($price, 2);

        $product_name = $row['product_name']; // 商品名稱
        $author_name = $row['author_name']; // 作者
        $author_bio = $row['author_bio']; // 作者自我介紹
        $write_date = $row['write_date']; // 寫作時間
        $product_description = nl2br($row['product_description']); // 商品介紹
        $product_content = nl2br($row['product_content']); // 商品內容

        // 查詢商品分類
        $sql_categories = "SELECT c.name AS category_name 
                           FROM categories c
                           JOIN product_category pc ON c.id = pc.category_id
                           WHERE pc.product_id = $product_id";
        $result_categories = $link->query($sql_categories);
        $categories = [];
        while ($row_category = $result_categories->fetch_assoc()) {
            $categories[] = $row_category['category_name'];
        }
        $category_names = implode(', ', $categories);

        // 查詢商品圖片
        $sql_images = "SELECT image_path FROM product_images WHERE product_id = $product_id";
        $result_images = $link->query($sql_images);
        $images = [];
        while ($row_image = $result_images->fetch_assoc()) {
            $images[] = $row_image['image_path'];
        }

        // 假設沒有圖片，使用預設圖片
        if (empty($images)) {
            $images[] = 'images/book.png';
        }
    } else {
        echo $result->num_rows == 0 ? "<div class='mt-10vh'>找不到商品資料</div>" : "<div class='mt-10vh'>找到多筆商品資料, 請確認ID是否正確</div>";
        exit;
    }
} else {
    echo "<div class='mt-10vh'> 無效的商品 ID</div>";
    exit;
}

$link->close();