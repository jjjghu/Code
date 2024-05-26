<?php
session_start();
include '.LinkSql.php'; // 包含資料庫連接

// 獲取所有分類
$category_query = "SELECT * FROM categories";
$category_result = $link->query($category_query);

// 獲取所有作者
$author_query = "SELECT * FROM author";
$author_result = $link->query($author_query);

// 處理新增商品
if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST['product_name'])) {
    $product_name = $_POST['product_name'];
    $price = $_POST['price'];
    $author_id = $_POST['author_id'];
    $write_date = $_POST['write_date'];
    $content = $_POST['content'];
    $description = $_POST['description'];
    $category_id = $_POST['category_id'];

    // 插入商品資料
    $stmt = $link->prepare("INSERT INTO products (product_name, price, author_id, write_date) VALUES (?, ?, ?, ?)");
    $stmt->bind_param("sdis", $product_name, $price, $author_id, $write_date);
    $stmt->execute();
    $product_id = $stmt->insert_id;
    $stmt->close();

    // 插入商品內容
    $stmt = $link->prepare("INSERT INTO product_contents (product_id, content, description) VALUES (?, ?, ?)");
    $stmt->bind_param("iss", $product_id, $content, $description);
    $stmt->execute();
    $stmt->close();

    // 插入商品分類
    $stmt = $link->prepare("INSERT INTO product_category (product_id, category_id) VALUES (?, ?)");
    $stmt->bind_param("ii", $product_id, $category_id);
    $stmt->execute();
    $stmt->close();

    header("Location:.AddProduct(超強版本).php");
    exit();
}
?>

<!DOCTYPE html>
<html lang="zh-Hant-TW">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>管理員管理頁面</title>
    <?php include '.Style.php'; ?>
    <style>
        .modal-body {
            max-height: 70vh;
            overflow-y: auto;
        }
    </style>
</head>

<body class="<?php echo $theme; ?>">
    <?php include '.Header.php'; ?>
    <main class="container mt-10vh">
        <!-- 顯示所有商品按鈕 -->
        <div class="d-flex justify-content-end mb-3">
            <button type="button" class="btn btn-primary" data-bs-toggle="modal" data-bs-target="#AddProductModal">
                新增商品
            </button>
        </div>

        <!-- 新增商品 Modal -->
        <div class="modal fade" id="AddProductModal" tabindex="-1" aria-labelledby="AddProductModalLabel"
            aria-hidden="true">
            <div class="modal-dialog modal-dialog-centered modal-xl">
                <div class="modal-content">
                    <div class="modal-header">
                        <h5 class="modal-title" id="AddProductModalLabel">新增商品</h5>
                    </div>
                    <div class="modal-body">
                        <form id="AddProductForm" action=".AddProduct(超強版本).php" method="post">
                            <div class="mb-3">
                                <input type="text" class="form-control" id="product_name" name="product_name"
                                    placeholder="商品名稱" required>
                            </div>
                            <div class="mb-3">
                                <input type="date" class="form-control" id="write_date" name="write_date"
                                    placeholder="撰寫日期" required>
                            </div>
                            <div class="mb-3">
                                <textarea class="form-control" id="content" name="content" rows="5" placeholder="商品內容"
                                    required></textarea>
                            </div>
                            <div class="mb-3">
                                <textarea class="form-control" id="description" name="description" rows="3"
                                    placeholder="商品描述" required></textarea>
                            </div>
                            <div class="row mb-3">
                                <div class="col">
                                    <select class="form-control" id="category_id" name="category_id" required>
                                        <option value="">選擇分類</option>
                                        <?php while ($row = $category_result->fetch_assoc()): ?>
                                            <option value="<?php echo $row['id']; ?>"><?php echo $row['name']; ?></option>
                                        <?php endwhile; ?>
                                    </select>
                                </div>
                                <div class="col">
                                    <select class="form-control" id="author_id" name="author_id" required>
                                        <option value="">選擇作者</option>
                                        <?php while ($row = $author_result->fetch_assoc()): ?>
                                            <option value="<?php echo $row['id']; ?>"><?php echo $row['username']; ?>
                                            </option>
                                        <?php endwhile; ?>
                                    </select>
                                </div>
                                <div class="col">
                                    <input type="number" step="0.01" class="form-control" id="price" name="price"
                                        placeholder="價格" required>
                                </div>
                            </div>
                            <div class="d-flex justify-content-end">
                                <div>
                                    <button type="button" class="btn btn-secondary me-2"
                                        data-bs-dismiss="modal">取消</button>
                                    <button type="submit" class="btn btn-primary">保存變更</button>
                                </div>
                            </div>
                        </form>
                    </div>
                </div>
            </div>
        </div>
    </main>
    <?php include '.Footer.php'; ?>
    <?php include '.Script.php'; ?>
</body>

</html>