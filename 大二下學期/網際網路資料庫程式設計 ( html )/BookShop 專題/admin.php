<?php
session_start();
include '.LinkSql.php'; // 包含資料庫連接

// 檢查是否為管理員
if (!isset($_SESSION['is_admin']) || $_SESSION['is_admin'] != 1) {
    header("Location: login.php");
    exit();
}

// 獲取所有使用者
$query = "SELECT * FROM author";
$result = $link->query($query);

// 處理新增和修改使用者
if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST['username'])) {
    $username = $_POST['username'];
    $penName = $_POST['penName'];
    $hashed_password = isset($_POST['password']) ? password_hash($_POST['password'], PASSWORD_DEFAULT) : '';
    $email = $_POST['email'];
    $phone = $_POST['phone'];
    $is_admin = isset($_POST['is_admin']) ? 1 : 0; // 檢查是否選擇設定為管理員

    if (isset($_POST['user_id']) && $_POST['user_id'] != '') {
        // 更新使用者 (密碼不會更新, 表單上只是裝飾用)
        $user_id = $_POST['user_id'];
        $stmt = $link->prepare("UPDATE author SET username = ?, penName = ?, email = ?, phone = ?, is_admin = ? WHERE id = ?");
        $stmt->bind_param("ssssii", $username, $penName, $email, $phone, $is_admin, $user_id);
    } else {
        // 新增使用者
        $stmt = $link->prepare("INSERT INTO author (username, penName, password, email, phone, is_admin) VALUES (?, ?, ?, ?, ?, ?)");
        $stmt->bind_param("sssssi", $username, $penName, $hashed_password, $email, $phone, $is_admin);
    }
    $stmt->execute();
    $stmt->close();

    header("Location: admin.php");
    exit();
}

// 處理刪除使用者
if (isset($_GET['delete_user'])) {
    $user_id = $_GET['delete_user'];

    $stmt = $link->prepare("DELETE FROM author WHERE id = ?");
    $stmt->bind_param("i", $user_id);
    $stmt->execute();
    $stmt->close();

    header("Location: admin.php");
    exit();
}
?>
<!DOCTYPE html>
<html lang="zh-Hant-TW">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>管理員頁面</title>
    <?php include '.Style.php'; ?>
</head>

<body class="<?php echo $theme; ?>">
    <?php include '.Header.php'; ?>
    <main class="container mt-10vh">
        <!-- 顯示所有使用者 -->
        <h2 class="mb-3">所有使用者</h2>
        <table class="table table-striped">
            <thead>
                <tr>
                    <th>ID</th>
                    <th>使用者名稱</th>
                    <th>筆名</th>
                    <th>電子郵件</th>
                    <th>電話</th>
                    <th>操作</th>
                </tr>
            </thead>
            <tbody>
                <?php while ($row = $result->fetch_assoc()): ?>
                    <tr>
                        <td><?php echo $row['id']; ?></td>
                        <td <?php if ($row['is_admin'])
                            echo "class='text-danger'"; ?>><?php echo $row['username']; ?></td>
                        <td><?php echo $row['penName']; ?></td>
                        <td><?php echo $row['email']; ?></td>
                        <td><?php echo $row['phone']; ?></td>
                        <td>
                            <button type="button" class="btn btn-primary btn-sm" data-bs-toggle="modal"
                                data-bs-target="#AddUserModal" data-id="<?php echo $row['id']; ?>"
                                data-username="<?php echo $row['username']; ?>"
                                data-penName="<?php echo $row['penName']; ?>" data-email="<?php echo $row['email']; ?>"
                                data-phone="<?php echo $row['phone']; ?>"
                                data-is_admin="<?php echo $row['is_admin']; ?>">編輯</button>
                            <a href="admin.php?delete_user=<?php echo $row['id']; ?>" class="btn btn-danger btn-sm"
                                onclick="return confirm('確定要刪除這個使用者嗎？');">刪除</a>
                        </td>
                    </tr>
                <?php endwhile; ?>
            </tbody>
        </table>
        <!-- 按鈕觸發 Modal -->
        <button type="button" class="btn btn-primary" data-bs-toggle="modal" data-bs-target="#AddUserModal">
            新增使用者
        </button>
        <!-- 顯示所有商品按鈕 -->
        <!-- 新增/編輯使用者 Modal -->
        <div class="modal fade" id="AddUserModal" tabindex="-1" aria-labelledby="AddUserModalLabel" aria-hidden="true">
            <div class="modal-dialog modal-dialog-centered">
                <div class="modal-content">
                    <div class="modal-header">
                        <h5 class="modal-title" id="AddUserModalLabel">新增使用者</h5>
                    </div>
                    <div class="modal-body">
                        <form id="AddUserForm" action="admin.php" method="post">
                            <input type="hidden" id="user_id" name="user_id">
                            <div class="mb-3">
                                <input type="text" class="form-control" id="username" name="username"
                                    placeholder="使用者名稱">
                                <p class="text-danger" id="username-err"></p>
                            </div>
                            <div class="mb-3">
                                <input type="text" class="form-control" id="penName" name="penName" placeholder="筆名">
                                <p class=" text-danger" id="penName-err"></p>
                            </div>
                            <div class="mb-3">
                                <input type="password" class="form-control" id="password" name="password"
                                    placeholder="密碼">
                                <p class=" text-danger" id="password-err"></p>
                            </div>
                            <div class="mb-3">
                                <input type="email" class="form-control" id="email" name="email" placeholder="電子信箱">
                                <p class="text-danger" id="email-err"></p>
                            </div>
                            <div class="mb-3">
                                <input type="tel" class="form-control" id="phone" name="phone" placeholder="手機號碼">
                                <p class="text-danger" id="phone-err"></p>
                            </div>
                            <div class="mb-3 form-check form-switch">
                                <input class="form-check-input" type="checkbox" id="is_admin" name="is_admin">
                                <label class="form-check-label" for="is_admin">設定為管理員</label>
                            </div>
                            <div class="d-flex justify-content-end">
                                <div>
                                    <button type="button" class="btn btn-secondary me-2"
                                        data-bs-dismiss="modal">取消</button>
                                    <button type="submit" id="AddUserConfirm" class="btn btn-primary">保存變更</button>
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