<!DOCTYPE html>
<html lang="zh-Hant-TW">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>管理員</title>
    <?php include '.Style.php'; ?>
</head>
<?php
if (session_status() == PHP_SESSION_NONE) {
    session_start();
}
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

    $_SESSION['message'] = '<div class="alert alert-success" role="alert">商品新增成功</div>';
    header("Location: userProfile.php");
    exit();
}
?>
<!-- 新增商品 Modal -->
<div class="modal fade" id="editArticleModal" tabindex="-1" aria-labelledby="editArticleModalLabel" aria-hidden="true">
    <div class="modal-dialog modal-dialog-centered modal-xl">
        <div class="modal-content">
            <div class="modal-header">
                <h5 class="modal-title" id="editArticleModalLabel">編輯文章</h5>
            </div>
            <div class="modal-body">
                <form id="editArticle" action=".EditArticle.php" method="post">
                    <!-- 隱藏input, 作者的 id -->
                    <div class="mb-3">
                        <input type="hidden" name="author_id" value="<?php echo $_SESSION['user_id']; ?>">
                    </div>
                    <div class="mb-3">
                        <input type="text" class="form-control" id="product_name" name="product_name" placeholder="標題"
                            required>
                    </div>
                    <div class="mb-3">
                        <textarea class="form-control" id="articleContent" name="content" rows="20"
                            placeholder="內容簡介"></textarea>
                    </div>
                    <div class="mb-3">
                        <textarea class="form-control" id="description" name="description" rows="5" placeholder="詳細資料"
                            required></textarea>
                    </div>
                    <div class="row mb-3">
                        <div class="col">
                            <select class="form-control" id="category_id" name="category_id" required>
                                <!-- 可以改成多選的, 資料庫支持 -->
                                <option value="">選擇分類</option>
                                <?php while ($row = $category_result->fetch_assoc()): ?>
                                    <option value="<?php echo $row['id']; ?>"><?php echo $row['name']; ?></option>
                                <?php endwhile; ?>
                            </select>
                        </div>
                        <div class="col">
                            <input type="number" step="0.01" class="form-control" id="price" name="price"
                                placeholder="價格" required>
                        </div>
                        <div class="col">
                            <input type="date" class="form-control" id="write_date" name="write_date" placeholder="撰寫日期"
                                required>
                        </div>
                    </div>
                    <div class="d-flex justify-content-end">
                        <div>
                            <button type="button" class="btn btn-secondary me-2" data-bs-dismiss="modal">取消</button>
                            <button type="submit" class="btn btn-primary">保存變更</button>
                        </div>
                    </div>
                </form>
            </div>
        </div>
    </div>
</div>


</html>