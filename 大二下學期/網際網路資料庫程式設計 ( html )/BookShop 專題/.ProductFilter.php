<?php
// 查詢商品資料
$sql = "SELECT id, product_name, price, (SELECT image_path FROM product_images WHERE product_id = products.id LIMIT 1) AS image
            FROM products";

$search = isset($_GET['search']) ? $link->real_escape_string($_GET['search']) : '';
$category = isset($_GET['category']) ? intval($_GET['category']) : 0;

// 添加搜索條件和分類篩選條件
$where_conditions = [];

if ($search) {
    $where_conditions[] = "product_name LIKE '%$search%'";
}

if ($category) {
    $where_conditions[] = "id IN (SELECT product_id FROM product_category WHERE category_id = $category)";
}

if (!empty($where_conditions)) {
    $sql .= " WHERE " . implode(" AND ", $where_conditions);
}

$result = $link->query($sql);

$products = [];
if ($result->num_rows > 0) {
    while ($row = $result->fetch_assoc()) {
        $price = floatval($row['price']);
        // 後兩位數都是 0 就只顯示整數
        $formatted_price = ($price == intval($price)) ? intval($price) : number_format($price, 2);

        $products[] = [
            "id" => $row['id'],
            "name" => $row['product_name'],
            "image" => $row['image'] ? $row['image'] : "https://via.placeholder.com/150",
            "price" => "$" . $formatted_price
        ];
    }
} else {
    $message = "<div class='mt-10vh'>沒有找到商品資料</div>";
}
//------------------------------------------------------------------------------------------------
// 商品分類DropDown動態產生
$sql_categories = "SELECT id, name FROM categories";
$result_categories = $link->query($sql_categories);

$categories = [];
if ($result_categories->num_rows > 0) {
    while ($row = $result_categories->fetch_assoc()) {
        $categories[] = [
            "id" => $row['id'],
            "name" => $row['name']
        ];
    }
} else {
    $categories[] = [
        "id" => 0,
        "name" => "沒有找到分類資料"
    ];
}

// 找到當前選中的分類名稱
$current_category_name = '全部';
$current_category_id = 0;
// 選擇全部, 不會有 category 變數, 因此預設值為 '全部'
if ($category) {
    foreach ($categories as $cat) {
        if ($cat['id'] == $category) {
            $current_category_name = $cat['name'];
            $current_category_id = $cat['id'];
            break;
        }
    }
}

$link->close();